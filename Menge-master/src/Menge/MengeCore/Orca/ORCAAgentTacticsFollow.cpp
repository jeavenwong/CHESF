///*
//
//License
//
//Menge
//Copyright ?and trademark ?2012-14 University of North Carolina at Chapel Hill.
//All rights reserved.
//
//Permission to use, copy, modify, and distribute this software and its documentation
//for educational, research, and non-profit purposes, without fee, and without a
//written agreement is hereby granted, provided that the above copyright notice,
//this paragraph, and the following four paragraphs appear in all copies.
//
//This software program and documentation are copyrighted by the University of North
//Carolina at Chapel Hill. The software program and documentation are supplied "as is,"
//without any accompanying services from the University of North Carolina at Chapel
//Hill or the authors. The University of North Carolina at Chapel Hill and the
//authors do not warrant that the operation of the program will be uninterrupted
//or error-free. The end-user understands that the program was developed for research
//purposes and is advised not to rely exclusively on the program for any reason.
//
//IN NO EVENT SHALL THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL OR THE AUTHORS
//BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
//DAMAGES, INCLUDING LOST PROFITS, ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS
//DOCUMENTATION, EVEN IF THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL OR THE
//AUTHORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL AND THE AUTHORS SPECIFICALLY
//DISCLAIM ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE AND ANY STATUTORY WARRANTY
//OF NON-INFRINGEMENT. THE SOFTWARE PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND
//THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL AND THE AUTHORS HAVE NO OBLIGATIONS
//TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
//
//Any questions or comments should be sent to the authors {menge,geom}@cs.unc.edu
//
//*/
//
//
//#include "MengeCore/Orca/ORCAAgentTacticsFollow.h"
//#include "MengeCore/Agents/BaseAgent.h"
//#include "MengeCore/Math/consts.h"
//#include "MengeCore/Orca/ORCASimulator.h"
//#include "MengeCore/Core.h"
//#include <algorithm>
//#include <cassert>
//#include <limits>
//
//namespace ORCA {
//
//	using Menge::Math::Vector2;
//	using Menge::Math::sqr;
//
//	/////////////////////////////////////////////////////////////////////////////
//	//                     Implementation of ORCA::Agent
//	/////////////////////////////////////////////////////////////////////////////
//
//	/////////////////////////////////////////////////////////////////////////////
//	float ORCAAgentTacticsFollow::computeDistanceSq_PosToGoal() {
//
//		float disSq = 0;
//		float chaX = _agent->_pos._x - _agent->_nextGoal._x;
//		float chaY = _agent->_pos._y - _agent->_nextGoal._y;
//		disSq = pow(chaX, 2) + pow(chaY, 2);
//		return disSq;
//	}
//
//#ifndef DOXYGEN_SHOULD_SKIP_THIS
//
//
//	//������ �ڸ�����agent�� ����ͬ��һ���Ŷӵģ�Ӱ�����ߵ�agent��ID
//	size_t ORCAAgentTacticsFollow::getGoalInterface() const {
//		if (_agent->_nearAgents.size() == 0) return -1;//����������� ����û���Ŷӳ�Աʱִ��̽����Ϊ
////TODO ��ʱû�����Ŷ�
//		Agent * currAgent = (Agent *)(_agent->_nearAgents[0].agent);
//		float maxInfluence = currAgent->_influence;
//		int maxId = 0;
//		for (size_t i = 1; i < _agent->_nearAgents.size(); i++) {
//			Agent * tempAgent = (Agent *)(_agent->_nearAgents[i].agent);
//			float tempInfluence = tempAgent->_influence;
//			if (maxInfluence < tempInfluence) {
//				maxInfluence = tempInfluence;
//				maxId = i;
//			}
//		}
//
//		if (_agent->_influence >= maxInfluence) {
//			return -2;//��ǰagent��Ӱ�����ߣ���leader
//		}
//		//�ҵ�������leader
//		return maxId;
//
//	}
//
//	//���Ӧ�ý� getleaderID ������
//	size_t ORCAAgentTacticsFollow::getGoal() {
//
//		//if (_groupAgents.size() == 0) {
//		//	_leaderID = -1;
//		//	return -1;
//		//}//����������� ����û���Ŷӳ�Աʱִ��̽����Ϊ
//		// //TODO ��ʱû�����Ŷ�
//		//Agent * currAgent = (Agent *)(_groupAgents[0]);
//		//int maxInfluence = currAgent->_influence;
//		//int maxId = 0;
//		//for (size_t i = 1; i < _groupAgents.size(); i++) {
//		//	Agent * tempAgent = (Agent *)(_groupAgents[i]);
//		//	int tempInfluence = tempAgent->_influence;
//		//	if (maxInfluence < tempInfluence) {
//		//		maxInfluence = tempInfluence;
//		//		_leaderID = tempAgent->_id;
//		//		maxId = i;
//		//	}
//		//}
//
//		//if (_influence >= maxInfluence) {
//		//	_leaderID = -2;
//		//	return -2;//��ǰagent��Ӱ�����ߣ���leader
//		//}
//		//Agent * leaderAgent = (Agent *)(_groupAgents[maxId]);
//		//leaderAgent->_influence += _influence;
//		////�ҵ�������leader
//		//return maxId;
//
//
//
//
//		if (_agent->_nearAgents.size() == 0) {
//			_agent->_leaderID = -1;
//			return -1;
//		}//����������� ����û���Ŷӳ�Աʱִ��̽����Ϊ
//		 //TODO ��ʱû�����Ŷ�
//		Agent * currAgent = (Agent *)(_agent->_nearAgents[0].agent);
//		int maxInfluence = currAgent->_influence;
//		int maxId = 0;
//		for (size_t i = 1; i < _agent->_nearAgents.size(); i++) {
//			Agent * tempAgent = (Agent *)(_agent->_nearAgents[i].agent);
//			int tempInfluence = tempAgent->_influence;
//			if (maxInfluence < tempInfluence) {
//				maxInfluence = tempInfluence;
//				_agent->_leaderID = tempAgent->_id;
//				maxId = i;
//			}
//		}
//
//		if (_agent->_influence >= maxInfluence) {
//			_agent->_leaderID = -2;
//			return -2;//��ǰagent��Ӱ�����ߣ���leader
//		}
//		Agent * leaderAgent = (Agent *)(_agent->_nearAgents[maxId].agent);
//		leaderAgent->_influence += _agent->_influence;
//		//�ҵ�������leader
//		return maxId;
//
//	}
//
//	//������һ����Ŀ���  ���㷨�Ǽ����Ŷ���Ӱ��������agent��ΪĿ���
//	Menge::Math::Vector2 ORCAAgentTacticsFollow::computeNextGoal() {
//		/*
//		Ĭ�Ϸ��� ��һ�� ȫ��Ŀ���
//		�����һ�����ر��ʱ���Ƴ���һ���㣬�ٷ��ء��ڶ����㡱
//		*/
//		if (_agent->_globalGoals.size() > 0) {
//
//			float dis = _agent->_pos.distance(_agent->_globalGoals[0]);
//
//			if (dis < 5 && _agent->currentMapID >= 0 && _agent->currentMapID < _agent->_maps.size())
//			{
//				bool inOldMap = _agent->_maps[_agent->currentMapID]->pointInMap(_agent->_pos);
//				if (!inOldMap) {
//					for (int i = 1; i < _agent->_globalGoals.size(); i++) {
//						_agent->_globalGoals[i - 1] = _agent->_globalGoals[i];
//					}
//				}
//			}
//			return _agent->_globalGoals[0];
//		}
//		else {
//			//ִ�и�����Ϊ
//			followLeaderBehavior();
//		}
//
//	}
//
//	Menge::Math::Vector2 ORCAAgentTacticsFollow::computeNextPrefSpeed() {
//
//		if (_agent->_pos._y<=-25) {
//			_agent->_prefSpeed = 0;
//		}
//
//		//Vector2 goalPoint = this->_nextGoal;
//		////ʧȥleaderλ��
//		//if (_missFollowing) {
//		//	float tempDis = _leaderPath[0].distance(_pos);
//		//	if (tempDis< 0.1) {
//		//		for (int i = 1; i < _leaderPath.size(); i++) {
//		//			_leaderPath[i - 1] = _leaderPath[i];
//		//		}
//		//	}
//		//	else {
//		//		this->_nextGoal = _leaderPath[0];
//		//	}
//
//		//}
//		//else {
//		//	//����Ǹ����ߣ���leader���ڸ��� ��leader������ͬ�ٶ�
//		//	float dis = _pos.distance(_leaderPos);
//		//	if (_isFollowing) {
//		//		if(dis <= 3.5 && !_missFollowing)
//		//		return _leaderPrefSpeed;
//		//	}
//		//	else {
//		//		//�����Agent��Ϊleader 
//		//		Vector2 groupPos(0, 0);
//		//		for (int i = 0; i < _groupAgents.size(); i++) {
//		//			Agent * currAgent = (Agent *)(_groupAgents[i]);
//		//			groupPos += currAgent->_pos;
//		//		}
//		//		groupPos = groupPos / _groupAgents.size();
//		//		Vector2 disp2 = groupPos - this->_pos;
//		//		const float distSp2 = absSq(disp2);
//
//
//		//		if (distSp2 > 15) {
//		//			goalPoint = groupPos;
//		//		}
//		//	
//		//	}
//		//	
//		//}
//
//
//		//���ݵ�ǰλ�ú�Ŀ��λ�ã����������ٶ�
//		// speed �����ٶ�ȷ��  ..���������ΪĬ�Ϸ���
//		//�����Ŷӳ�Ա������λ��
//		
//		Vector2 goalPoint = _agent->_nextGoal;
//		Vector2 disp = goalPoint - _agent->_pos;
//		const float distSq = absSq(disp);
//		float speed = _agent->_prefSpeed;
//		if (distSq > 1e-8) {
//			// Distant enough that I can normalize the direction.
//			disp.set(disp / sqrtf(distSq));//��λ��
//		}
//		else {
//			disp.set(0.f, 0.f);
//		}
//
//		Menge::Agents::PrefVelocity newVel;
//		if (distSq <= 0.0001f) {
//			// I've basically arrived -- speed should be zero.
//			speed = 0.f;
//		}
//		else {
//			const float speedSq = speed * speed;
//			const float TS_SQD = Menge::SIM_TIME_STEP * Menge::SIM_TIME_STEP;
//			if (distSq / speedSq < TS_SQD) {
//				// The distance is less than I would travel in a single time step.
//				speed = sqrtf(distSq) / Menge::SIM_TIME_STEP;
//			}
//		}
//
//
//		newVel.setSingle(disp);
//		newVel.setTarget(goalPoint);
//		newVel.setSpeed(speed);
//		_agent->setPreferredVelocity(newVel);
//
//		return disp*speed;
//	}
//
//	//Menge::Math::Vector2 Agent::computeNextGoal() {
//	//	//��Ҫ�ж��Ƿ���ɢ�ɹ�
//	//	//���㵱ǰ����Map
//	//	_currentMapIndex = -1;
//	//	for (int i = 0; i < _maps.size(); i++) {
//	//		bool agentInTheMap = _maps[i]->pointInMap(_pos);
//	//		if (agentInTheMap) {
//	//			_currentMapIndex = i;
//	//			//if (_currentMapIndex!=_nextMapIndex) {
//	//			//	return _nextGoal;
//	//			//}
//	//			break;
//	//		}
//	//	}
//	//	if (_currentMapIndex == -1) return _pos;//�뿪��ʵ������
//	//	//�жϵ�ǰλ����֮ǰ����Ŀ���ľ��룬С��һ��ֵ�ż�����Ŀ��	
//	//	float disSq = computeDistanceSq_PosToGoal();
//	//	if (disSq > 0.1) {
//	//		return _nextGoal;
//	//		//nextGoalIsTemp = false;
//	//	}
//	//	else {
//	//		//����һ�νӽ�Ŀ���ʱ������ԭ�������ǰ��һС�ξ���
//	//		//if (!_nextGoalIsTemp) {
//	//		//	_nextGoalIsTemp = true;
//	//		//	return Menge::Math::Vector2(_nextGoal._x * 2 - _pos._x, _nextGoal._y * 2 - _pos._y);
//	//		//}
//	//		//_nextGoalIsTemp = false;
//	//		return followLeaderBehavior();
//	//	}
//	//	return Menge::Math::Vector2(0, -20);
//	//}
//
//	ORCAAgentTacticsFollow::ORCAAgentTacticsFollow(Agent *agent)
//	{
//		_agent = agent;
//	}
//
//	ORCAAgentTacticsFollow::~ORCAAgentTacticsFollow()
//	{
//	}
//
//	int ORCAAgentTacticsFollow::findLeaderInNearAgent(size_t leaderID) {
//
//		for (size_t i = 0; i < _agent->_nearAgents.size(); i++) {
//			size_t currID = _agent->_nearAgents[i].agent->_id;
//			if (leaderID == currID) {
//				//�ڵ�ǰ�ھ��� �ҵ���֮ǰ��leader����������ǰleader
//				return i;//���� leader��nearAgent�е��±�
//			}
//		}
//		return -1;//��ʱ ��Ҫ����ѡ��leader
//
//	}
//
//	Menge::Math::Vector2 ORCAAgentTacticsFollow::followLeaderBehavior() {
//		//���ж��Ƿ�����leader��ǰleader �����ھ�
//		//�ڸ����ھ��� �ҵ���leader
//		int leaderIndex = findLeaderInNearAgent(_agent->_leaderID);
//		if (leaderIndex == -1) {
//			leaderIndex = getGoal();//����ѡ��leader
//		}
//		//ǰ���쵼��λ�ã�����ִ��̽����Ϊ
//		if (leaderIndex >= 0 && leaderIndex < _agent->_nearAgents.size()) {
//			const Menge::Agents::BaseAgent *temp = _agent->_nearAgents[leaderIndex].agent;
//			Menge::Math::Vector2 leaderPos = temp->_pos;//ѡ��leader��Ŀ���Ϊ�Լ���Ŀ���
//			_agent->_isFollowing = true;
//			//�����ǰλ�ø�leader�ܽ�����ͣ�ƶ�
//			if (_agent->_pos.distance(leaderPos)<2) {
//							leaderPos = temp->_nextGoal;
//			}
//			//_leaderPath.push_back(leaderPos);
//			_agent->_leaderPrefSpeed = temp->_nextPrefSpeed;
//			_agent->_leaderPos = temp->_pos;
//			//�ж�leader�Ƿ���ͬһ��Map
//			for (int m = 0; m < _agent->_maps.size(); m++) {
//				bool inMap = _agent->_maps[m]->pointInMap(_agent->_pos);
//				if (inMap) {
//					if (_agent->_maps[m]->pointInMap(leaderPos)) {
//						_agent->_missFollowing = false;
//					}
//					else {
//						float minDis =INT_MAX;
//						int minConIndex;
//						for (int k = 0; k < _agent->_maps[m]->_connections.size(); k++) {
//						//�ҵ���leader�������
//							float temp = leaderPos.distance(_agent->_maps[m]->_connections[k].pos);
//							if (temp < minDis) {
//								minDis = temp;
//								minConIndex = k;
//							}
//						}
//						_agent->_leaderPath.clear();
//						_agent->_leaderPath.push_back(_agent->_maps[m]->_connections[minConIndex].pos);
//						_agent->_leaderPath.push_back(leaderPos);
//						_agent->_missFollowing = true;
//						break;
//						
//					}
//
//				}
//				
//			}
//			// std::cout <<"��"<<_id<<"����ѡ����leader"<<temp->_id<<"Ŀ��㣺("<<leaderPos._x<<","<<leaderPos._y<<")"<<std::endl;
//			return leaderPos;
//		}
//		else {
//			Vector2 groupPos(0, 0);
//			for (int i = 0; i < _agent->_groupAgents.size(); i++) {
//				Agent * currAgent = (Agent *)(_agent->_groupAgents[i]);
//				groupPos += currAgent->_pos;
//			}
//			groupPos = groupPos / _agent->_groupAgents.size();
//			return groupPos;
//			//return exploreBehavior();
//		}
//	}
//	Menge::Math::Vector2 ORCAAgentTacticsFollow::exploreBehavior() {
//		//ִ��̽����Ϊ
//				//�ڵ�ǰ������ ȷ��ǰ������ ��Ҫ��¼�Ѿ�ȥ�����ţ�
//				//��ǰ�����г��ڣ�ǰ������
//
//		for (int m = 0; m < _agent->_maps.size(); m++) {
//			bool isOut=true;
//			bool inMap = _agent->_maps[m]->pointInMap(_agent->_pos);
//			if (inMap) {
//				isOut = false;
//				_agent->_currentMapIndex = _agent->_maps[m]->_id;
//				break;
//			}
//			if (isOut) {
//				return _agent->_pos;
//			}
//		}
//		if (_agent->_maps[_agent->_currentMapIndex]->_hasExist) {
//			for (int j = 0; j < _agent->_maps[_agent->_currentMapIndex]->_nextMapsIndex.size(); j++) {
//				if (_agent->_maps[_agent->_currentMapIndex]->_nextMapsIndex[j] == -1) {//����Map���±�
//					Menge::Math::Vector2 goal = _agent->_maps[_agent->_currentMapIndex]->_connections[j].pos;//Ŀ�����Ϊ ����
//					_agent->_nextMapIndex = -1;//��ʾ����
//					_agent->_catchNextMap = false;
//					return goal;
//				}
//			}
//		}
//		else {
//			//��ǰMapû�г��ڣ����ѡ��һ���ţ���
//			int index = (rand() % (_agent->_maps[_agent->_currentMapIndex]->_connections.size()));
//			Menge::Math::Vector2 goal = _agent->_maps[_agent->_currentMapIndex]->_connections[index].pos;//Ŀ�����Ϊ �����һ����
//			_agent->_nextMapIndex = _agent->_maps[_agent->_currentMapIndex]->_nextMapsIndex[index];
//			_agent->_catchNextMap = false;
//			return goal;
//
//
//		}
//
//
//
//	}
//	//����Ϥ��Ϊ
//	Menge::Math::Vector2 ORCAAgentTacticsFollow::highEnvironmentFamiliarityBehavior() {
//		/*
//		�ܻ�ȡ���е�ͼ��Ϣ ��Agent��ǰλ��Ϊ����㣬�Ե�ͼ�����е� connectionΪ�ӽڵ�
//		��������ͼ �����õϽ�˹�����㷨 �������·��
//
//		*/
//		return Menge::Math::Vector2(0, 0);
//
//	}
//	Menge::Math::Vector2 ORCAAgentTacticsFollow::middleEnvironmentFamiliarityBehavior() {
//		return Menge::Math::Vector2(0, 0);
//	}
//	Menge::Math::Vector2 ORCAAgentTacticsFollow::lowEnvironmentFamiliarityBehavior() {
//		return Menge::Math::Vector2(0, 0);
//	}
//
//#endif  // DOXYGEN_SHOULD_SKIP_THIS
//
//}	// namespace ORCA
