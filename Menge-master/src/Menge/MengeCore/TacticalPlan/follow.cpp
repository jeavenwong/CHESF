

#include "MengeCore/TacticalPlan/follow.h"



namespace Menge {

	namespace Agents {

		////////////////////////////////////////////////////////////////////////////
		//			Implementation of ConstProfileSelectorFactory
		////////////////////////////////////////////////////////////////////////////

		void  TacticalFollowPlan::initAgentInfo(std::vector<Agents::Map *> _maps,
			std::vector<BaseAgent *> agents
		) const {

			//遍历_agents 保存所有agent的id信息，给每个Agent设置团队影响力
			for (size_t i = 0; i < agents.size(); i++) {
				TacticalPlanAgent* tpa = new TacticalPlanAgent();
				tpa->_id = agents[i]->_id;
				
				//计算熟悉的map个数，以环境熟悉度为 团队影响力
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
			默认返回 第一个 全局目标点
			当离第一个点特别近时，移除第一个点，再返回“第二个点”
			*/
			//_agent = (ORCA::Agent *)_baseAgent;//初始化当前Agent

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
				//执行跟随行为
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
			//这里可以添加一些必要的参数
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

		//不用了 在附近的agent中 查找同属一个团队的，影响度最高的agent的ID
		size_t TacticalFollowPlan::getGoalInterface() const {
			if (_baseAgent->_nearAgents.size() == 0) return -1;//这里存在问题 附近没有团队成员时执行探索行为
														   //TODO 暂时没考虑团队
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
				return -2;//当前agent的影响度最高，是leader
			}
			//找到的区域leader
			return maxId;

		}

		//这个应该叫 getleaderID 更合适
		size_t TacticalFollowPlan::getGoal() {

			if (_baseAgent->_nearAgents.size() == 0) {
				_agent->_leaderID = -1;
				return -1;
			}//这里存在问题 附近没有团队成员时执行探索行为
			 //TODO 暂时没考虑团队
		
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
				return -2;//当前agent的影响度最高，是leader
			}
		//	ORCA::Agent * leaderAgent = (ORCA::Agent *)(_baseAgent->_nearAgents[maxId].agent);
		//	leaderAgent->_influence += _agent->_influence;
			iter = _tacticalAgents.find(_baseAgent->_nearAgents[maxId].agent->_id);
			if (iter != _tacticalAgents.end())
			{
				iter->second->_influence += _agent->_influence;
			}
			//找到的区域leader
			return maxId;

		}


		Menge::Math::Vector2 TacticalFollowPlan::computeNextPrefSpeed() {

			if (_baseAgent->_pos._y <= -25) {
				_baseAgent->_prefSpeed = 0;
			}
		//根据当前位置和目标位置，计算最优速度
		// speed 最优速度确定  ..这个可以作为默认方法
		//计算团队成员的中心位置

		Vector2 goalPoint = _baseAgent->_nextGoal;
		Vector2 disp = goalPoint - _baseAgent->_pos;
		const float distSq = absSq(disp);
		float speed = _baseAgent->_prefSpeed;
		if (distSq > 1e-8) {
			// Distant enough that I can normalize the direction.
			disp.set(disp / sqrtf(distSq));//单位化
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
					//在当前邻居中 找到了之前的leader，继续跟随前leader
					return i;//返回 leader在nearAgent中的下标
				}
			}
			return -1;//此时 需要重新选择leader

		}

		Menge::Math::Vector2 TacticalFollowPlan::followLeaderBehavior() {
			//先判断是否已有leader，前leader 还是邻居
			//在附近邻居中 找到旧leader
			int leaderIndex = findLeaderInNearAgent(_agent->_leaderID);
			if (leaderIndex == -1) {
				leaderIndex = getGoal();//重新选择leader
			}
			//前往领导者位置，或者执行探索行为
			if (leaderIndex >= 0 && leaderIndex < _baseAgent->_nearAgents.size()) {
				const Menge::Agents::BaseAgent *temp = _baseAgent->_nearAgents[leaderIndex].agent;
				Menge::Math::Vector2 leaderPos = temp->_pos;//选择leader的目标点为自己的目标点
				_agent->_isFollowing = true;
				//如果当前位置跟leader很近，暂停移动
				if (_baseAgent->_pos.distance(leaderPos)<2) {
					leaderPos = temp->_nextGoal;
				}
				//_leaderPath.push_back(leaderPos);
				_agent->_leaderPrefSpeed = temp->_nextPrefSpeed;
				_agent->_leaderPos = temp->_pos;
				//判断leader是否在同一个Map
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
								//找到离leader最近的门
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
				// std::cout <<"第"<<_id<<"个人选择了leader"<<temp->_id<<"目标点：("<<leaderPos._x<<","<<leaderPos._y<<")"<<std::endl;
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
			//执行探索行为
			//在当前区域内 确定前往的门 需要记录已经去过的门，
			//当前区域有出口，前往出口

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
					if (_baseAgent->_maps[_agent->_currentMapIndex]->_nextMapsIndex[j] == -1) {//出口Map的下标
						Menge::Math::Vector2 goal = _baseAgent->_maps[_agent->_currentMapIndex]->_connections[j].pos;//目标点设为 出口
						_agent->_nextMapIndex = -1;//表示出口
						_agent->_catchNextMap = false;
						return goal;
					}
				}
			}
			else {
				//当前Map没有出口，随机选择一个门（）
				int index = (rand() % (_baseAgent->_maps[_agent->_currentMapIndex]->_connections.size()));
				Menge::Math::Vector2 goal = _baseAgent->_maps[_agent->_currentMapIndex]->_connections[index].pos;//目标点设为 随机的一个门
				_agent->_nextMapIndex = _baseAgent->_maps[_agent->_currentMapIndex]->_nextMapsIndex[index];
				_agent->_catchNextMap = false;
				return goal;


			}



		}
		//高熟悉行为
		Menge::Math::Vector2 TacticalFollowPlan::highEnvironmentFamiliarityBehavior() {
			/*
			能获取所有地图信息 以Agent当前位置为根结点，以地图中所有的 connection为子节点
			构建无向图 ，再用迪杰斯特拉算法 计算最佳路径

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
