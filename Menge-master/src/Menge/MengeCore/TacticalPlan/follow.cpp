

#include "MengeCore/TacticalPlan/follow.h"



namespace Menge {

	namespace Agents {

		////////////////////////////////////////////////////////////////////////////
		//			Implementation of ConstProfileSelectorFactory
		////////////////////////////////////////////////////////////////////////////

		void  TacticalFollowPlan::initAgentInfo(std::vector<Agents::Map *> _maps,
			std::vector<BaseAgent *> agents
		) const {

			//����_agents ��������agent��id��Ϣ����ÿ��Agent�����Ŷ�Ӱ����
			for (size_t i = 0; i < agents.size(); i++) {
				TacticalPlanAgent* tpa = new TacticalPlanAgent();
				tpa->_id = agents[i]->_id;
				
				//������Ϥ��map�������Ի�����Ϥ��Ϊ �Ŷ�Ӱ����
				int familiarityCount = 0;
				for each (bool var in agents[i]->environmentFamiliaritySet)
				{
					if (var)familiarityCount++;
				}
				tpa->_influence = familiarityCount;
				_tacticalAgents.insert(std::pair<int, TacticalPlanAgent*>(agents[i]->_id, tpa));
				
			}
				
		}


	    Menge::Math::Vector2 TacticalFollowPlan::computeNextGoal(){
			/*
			Ĭ�Ϸ��� ��һ�� ȫ��Ŀ���
			�����һ�����ر��ʱ���Ƴ���һ���㣬�ٷ��ء��ڶ����㡱
			*/
			//_agent = (ORCA::Agent *)_baseAgent;//��ʼ����ǰAgent

			map<int, TacticalPlanAgent*>::iterator iter;
			iter = _tacticalAgents.find(_baseAgent->_id);
			if (iter != _tacticalAgents.end())
			{
				_agent = iter->second;
			}
			//else {
			//	TacticalPlanAgent* tpa = new TacticalPlanAgent();
			//	tpa->_id = _baseAgent->_id;
			//	_tacticalAgents.insert(std::pair<int, TacticalPlanAgent*>(_baseAgent->_id, tpa));
			//	_agent = tpa;
			//}

			if (_baseAgent->_globalGoals.size() > 0) {

				float dis = _baseAgent->_pos.distance(_baseAgent->_globalGoals[0]);

				if (dis < 5 && _baseAgent->currentMapID >= 0 && _baseAgent->currentMapID < _baseAgent->_maps.size())
				{
					bool inOldMap = _baseAgent->_maps[_baseAgent->currentMapID]->pointInMap(_baseAgent->_pos);
					if (!inOldMap) {
						for (int i = 1; i < _baseAgent->_globalGoals.size(); i++) {
							_baseAgent->_globalGoals[i - 1] = _baseAgent->_globalGoals[i];
						}
					}
				}
				return _baseAgent->_globalGoals[0];
			}
			else {
				//ִ�и�����Ϊ
				return followLeaderBehavior();
			}
		}


		TacticalFollowPlanFactory::TacticalFollowPlanFactory() : TacticalPlanFactory() {
			_nameID = _attrSet.addStringAttribute( "type", true, "" );
		}

		////////////////////////////////////////////////////////////////////////////

		bool TacticalFollowPlanFactory::setFromXML(TacticalPlan * sel, TiXmlElement * node,
													const std::string & specFldr ) const {
			TacticalFollowPlan * dGP = dynamic_cast< TacticalFollowPlan * >( sel );
			assert(dGP != 0x0 && "Trying to set attributes of a const state selector element on "
					"an incompatible object" );
			//����������һЩ��Ҫ�Ĳ���
			if ( !TacticalPlanFactory::setFromXML(dGP, node, specFldr ) ) return false;
			dGP->setPlanName( _attrSet.getString( _nameID ) );

			return true;
		}

		float TacticalFollowPlan::computeDistanceSq_PosToGoal() {

			float disSq = 0;
			float chaX = _baseAgent->_pos._x - _baseAgent->_nextGoal._x;
			float chaY = _baseAgent->_pos._y - _baseAgent->_nextGoal._y;
			disSq = pow(chaX, 2) + pow(chaY, 2);
			return disSq;
		}

		//������ �ڸ�����agent�� ����ͬ��һ���Ŷӵģ�Ӱ�����ߵ�agent��ID
		size_t TacticalFollowPlan::getGoalInterface() const {
			if (_baseAgent->_nearAgents.size() == 0) return -1;//����������� ����û���Ŷӳ�Աʱִ��̽����Ϊ
														   //TODO ��ʱû�����Ŷ�
			ORCA::Agent * currAgent = (ORCA::Agent *)(_baseAgent->_nearAgents[0].agent);
			float maxInfluence = currAgent->_influence;
			int maxId = 0;
			for (size_t i = 1; i < _baseAgent->_nearAgents.size(); i++) {
				ORCA::Agent * tempAgent = (ORCA::Agent *)(_baseAgent->_nearAgents[i].agent);
				float tempInfluence = tempAgent->_influence;
				if (maxInfluence < tempInfluence) {
					maxInfluence = tempInfluence;
					maxId = i;
				}
			}

			if (_agent->_influence >= maxInfluence) {
				return -2;//��ǰagent��Ӱ�����ߣ���leader
			}
			//�ҵ�������leader
			return maxId;

		}

		//���Ӧ�ý� getleaderID ������
		size_t TacticalFollowPlan::getGoal() {

			if (_baseAgent->_nearAgents.size() == 0) {
				_agent->_leaderID = -1;
				return -1;
			}//����������� ����û���Ŷӳ�Աʱִ��̽����Ϊ
			 //TODO ��ʱû�����Ŷ�
		
		    BaseAgent *	currAgent= (BaseAgent *)_baseAgent->_nearAgents[0].agent;
			map<int, TacticalPlanAgent*>::iterator iter;
			int maxInfluence, maxId;
			iter = _tacticalAgents.find(_baseAgent->_nearAgents[0].agent->_id);
			if (iter != _tacticalAgents.end())
			{
				 maxInfluence = iter->second->_influence;
				 maxId = 0;
			}
			for (size_t i = 1; i < _baseAgent->_nearAgents.size(); i++) {
	
				iter = _tacticalAgents.find(_baseAgent->_nearAgents[i].agent->_id);
				if (iter != _tacticalAgents.end())
				{
					int tempInfluence = iter->second->_influence;
					if (maxInfluence < tempInfluence) {
						maxInfluence = tempInfluence;
						_agent->_leaderID = iter->second->_id;
						maxId = i;
					}
				}
			}

			if (_agent->_influence >= maxInfluence) {
				_agent->_leaderID = -2;
				return -2;//��ǰagent��Ӱ�����ߣ���leader
			}
		//	ORCA::Agent * leaderAgent = (ORCA::Agent *)(_baseAgent->_nearAgents[maxId].agent);
		//	leaderAgent->_influence += _agent->_influence;
			iter = _tacticalAgents.find(_baseAgent->_nearAgents[maxId].agent->_id);
			if (iter != _tacticalAgents.end())
			{
				iter->second->_influence += _agent->_influence;
			}
			//�ҵ�������leader
			return maxId;

		}


		Menge::Math::Vector2 TacticalFollowPlan::computeNextPrefSpeed() {

			if (_baseAgent->_pos._y <= -25) {
				_baseAgent->_prefSpeed = 0;
			}
		//���ݵ�ǰλ�ú�Ŀ��λ�ã����������ٶ�
		// speed �����ٶ�ȷ��  ..���������ΪĬ�Ϸ���
		//�����Ŷӳ�Ա������λ��

		Vector2 goalPoint = _baseAgent->_nextGoal;
		Vector2 disp = goalPoint - _baseAgent->_pos;
		const float distSq = absSq(disp);
		float speed = _baseAgent->_prefSpeed;
		if (distSq > 1e-8) {
			// Distant enough that I can normalize the direction.
			disp.set(disp / sqrtf(distSq));//��λ��
		}
		else {
			disp.set(0.f, 0.f);
		}

		Menge::Agents::PrefVelocity newVel;
		if (distSq <= 0.0001f) {
			// I've basically arrived -- speed should be zero.
			speed = 0.f;
		}
		else {
			const float speedSq = speed * speed;
			const float TS_SQD = Menge::SIM_TIME_STEP * Menge::SIM_TIME_STEP;
			if (distSq / speedSq < TS_SQD) {
				// The distance is less than I would travel in a single time step.
				speed = sqrtf(distSq) / Menge::SIM_TIME_STEP;
			}
		}


		newVel.setSingle(disp);
		newVel.setTarget(goalPoint);
		newVel.setSpeed(speed);
		_baseAgent->setPreferredVelocity(newVel);

		return disp*speed;
	}

		int TacticalFollowPlan::findLeaderInNearAgent(size_t leaderID) {

			for (size_t i = 0; i < _baseAgent->_nearAgents.size(); i++) {
				size_t currID = _baseAgent->_nearAgents[i].agent->_id;
				if (leaderID == currID) {
					//�ڵ�ǰ�ھ��� �ҵ���֮ǰ��leader����������ǰleader
					return i;//���� leader��nearAgent�е��±�
				}
			}
			return -1;//��ʱ ��Ҫ����ѡ��leader

		}

		Menge::Math::Vector2 TacticalFollowPlan::followLeaderBehavior() {
			//���ж��Ƿ�����leader��ǰleader �����ھ�
			//�ڸ����ھ��� �ҵ���leader
			int leaderIndex = findLeaderInNearAgent(_agent->_leaderID);
			if (leaderIndex == -1) {
				leaderIndex = getGoal();//����ѡ��leader
			}
			//ǰ���쵼��λ�ã�����ִ��̽����Ϊ
			if (leaderIndex >= 0 && leaderIndex < _baseAgent->_nearAgents.size()) {
				const Menge::Agents::BaseAgent *temp = _baseAgent->_nearAgents[leaderIndex].agent;
				Menge::Math::Vector2 leaderPos = temp->_pos;//ѡ��leader��Ŀ���Ϊ�Լ���Ŀ���
				_agent->_isFollowing = true;
				//�����ǰλ�ø�leader�ܽ�����ͣ�ƶ�
				if (_baseAgent->_pos.distance(leaderPos)<2) {
					leaderPos = temp->_nextGoal;
				}
				//_leaderPath.push_back(leaderPos);
				_agent->_leaderPrefSpeed = temp->_nextPrefSpeed;
				_agent->_leaderPos = temp->_pos;
				//�ж�leader�Ƿ���ͬһ��Map
				for (int m = 0; m < _baseAgent->_maps.size(); m++) {
					bool inMap = _baseAgent->_maps[m]->pointInMap(_baseAgent->_pos);
					if (inMap) {
						if (_baseAgent->_maps[m]->pointInMap(leaderPos)) {
							_agent->_missFollowing = false;
						}
						else {
							float minDis = INT_MAX;
							int minConIndex;
							for (int k = 0; k < _baseAgent->_maps[m]->_connections.size(); k++) {
								//�ҵ���leader�������
								float temp = leaderPos.distance(_baseAgent->_maps[m]->_connections[k].pos);
								if (temp < minDis) {
									minDis = temp;
									minConIndex = k;
								}
							}
							_agent->_leaderPath.clear();
							_agent->_leaderPath.push_back(_baseAgent->_maps[m]->_connections[minConIndex].pos);
							_agent->_leaderPath.push_back(leaderPos);
							_agent->_missFollowing = true;
							break;

						}

					}

				}
				// std::cout <<"��"<<_id<<"����ѡ����leader"<<temp->_id<<"Ŀ��㣺("<<leaderPos._x<<","<<leaderPos._y<<")"<<std::endl;
				return leaderPos;
			}
			else {
				Vector2 groupPos(0, 0);
				for (int i = 0; i < _baseAgent->_groupAgents.size(); i++) {
					ORCA::Agent * currAgent = (ORCA::Agent *)(_baseAgent->_groupAgents[i]);
					groupPos += currAgent->_pos;
				}
				groupPos = groupPos / _baseAgent->_groupAgents.size();
				return groupPos;
				//return exploreBehavior();
			}
		}
		Menge::Math::Vector2 TacticalFollowPlan::exploreBehavior() {
			//ִ��̽����Ϊ
			//�ڵ�ǰ������ ȷ��ǰ������ ��Ҫ��¼�Ѿ�ȥ�����ţ�
			//��ǰ�����г��ڣ�ǰ������

			for (int m = 0; m < _baseAgent->_maps.size(); m++) {
				bool isOut = true;
				bool inMap = _baseAgent->_maps[m]->pointInMap(_baseAgent->_pos);
				if (inMap) {
					isOut = false;
					_agent->_currentMapIndex = _baseAgent->_maps[m]->_id;
					break;
				}
				if (isOut) {
					return _baseAgent->_pos;
				}
			}
			if (_baseAgent->_maps[_agent->_currentMapIndex]->_hasExist) {
				for (int j = 0; j < _baseAgent->_maps[_agent->_currentMapIndex]->_nextMapsIndex.size(); j++) {
					if (_baseAgent->_maps[_agent->_currentMapIndex]->_nextMapsIndex[j] == -1) {//����Map���±�
						Menge::Math::Vector2 goal = _baseAgent->_maps[_agent->_currentMapIndex]->_connections[j].pos;//Ŀ�����Ϊ ����
						_agent->_nextMapIndex = -1;//��ʾ����
						_agent->_catchNextMap = false;
						return goal;
					}
				}
			}
			else {
				//��ǰMapû�г��ڣ����ѡ��һ���ţ���
				int index = (rand() % (_baseAgent->_maps[_agent->_currentMapIndex]->_connections.size()));
				Menge::Math::Vector2 goal = _baseAgent->_maps[_agent->_currentMapIndex]->_connections[index].pos;//Ŀ�����Ϊ �����һ����
				_agent->_nextMapIndex = _baseAgent->_maps[_agent->_currentMapIndex]->_nextMapsIndex[index];
				_agent->_catchNextMap = false;
				return goal;


			}



		}
		//����Ϥ��Ϊ
		Menge::Math::Vector2 TacticalFollowPlan::highEnvironmentFamiliarityBehavior() {
			/*
			�ܻ�ȡ���е�ͼ��Ϣ ��Agent��ǰλ��Ϊ����㣬�Ե�ͼ�����е� connectionΪ�ӽڵ�
			��������ͼ �����õϽ�˹�����㷨 �������·��

			*/
			return Menge::Math::Vector2(0, 0);

		}
		Menge::Math::Vector2 TacticalFollowPlan::middleEnvironmentFamiliarityBehavior() {
			return Menge::Math::Vector2(0, 0);
		}
		Menge::Math::Vector2 TacticalFollowPlan::lowEnvironmentFamiliarityBehavior() {
			return Menge::Math::Vector2(0, 0);
		}



	}	// namespace Agents
}	// namespace Menge
