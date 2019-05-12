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
//	//不用了 在附近的agent中 查找同属一个团队的，影响度最高的agent的ID
//	size_t ORCAAgentTacticsFollow::getGoalInterface() const {
//		if (_agent->_nearAgents.size() == 0) return -1;//这里存在问题 附近没有团队成员时执行探索行为
////TODO 暂时没考虑团队
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
//			return -2;//当前agent的影响度最高，是leader
//		}
//		//找到的区域leader
//		return maxId;
//
//	}
//
//	//这个应该叫 getleaderID 更合适
//	size_t ORCAAgentTacticsFollow::getGoal() {
//
//		//if (_groupAgents.size() == 0) {
//		//	_leaderID = -1;
//		//	return -1;
//		//}//这里存在问题 附近没有团队成员时执行探索行为
//		// //TODO 暂时没考虑团队
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
//		//	return -2;//当前agent的影响度最高，是leader
//		//}
//		//Agent * leaderAgent = (Agent *)(_groupAgents[maxId]);
//		//leaderAgent->_influence += _influence;
//		////找到的区域leader
//		//return maxId;
//
//
//
//
//		if (_agent->_nearAgents.size() == 0) {
//			_agent->_leaderID = -1;
//			return -1;
//		}//这里存在问题 附近没有团队成员时执行探索行为
//		 //TODO 暂时没考虑团队
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
//			return -2;//当前agent的影响度最高，是leader
//		}
//		Agent * leaderAgent = (Agent *)(_agent->_nearAgents[maxId].agent);
//		leaderAgent->_influence += _agent->_influence;
//		//找到的区域leader
//		return maxId;
//
//	}
//
//	//计算下一步的目标点  此算法是计算团队中影响力最大的agent作为目标点
//	Menge::Math::Vector2 ORCAAgentTacticsFollow::computeNextGoal() {
//		/*
//		默认返回 第一个 全局目标点
//		当离第一个点特别近时，移除第一个点，再返回“第二个点”
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
//			//执行跟随行为
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
//		////失去leader位置
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
//		//	//如果是跟随者，且leader就在附近 与leader保持相同速度
//		//	float dis = _pos.distance(_leaderPos);
//		//	if (_isFollowing) {
//		//		if(dis <= 3.5 && !_missFollowing)
//		//		return _leaderPrefSpeed;
//		//	}
//		//	else {
//		//		//这里的Agent作为leader 
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
//		//根据当前位置和目标位置，计算最优速度
//		// speed 最优速度确定  ..这个可以作为默认方法
//		//计算团队成员的中心位置
//		
//		Vector2 goalPoint = _agent->_nextGoal;
//		Vector2 disp = goalPoint - _agent->_pos;
//		const float distSq = absSq(disp);
//		float speed = _agent->_prefSpeed;
//		if (distSq > 1e-8) {
//			// Distant enough that I can normalize the direction.
//			disp.set(disp / sqrtf(distSq));//单位化
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
//	//	//需要判断是否疏散成功
//	//	//计算当前所在Map
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
//	//	if (_currentMapIndex == -1) return _pos;//离开了实验区域
//	//	//判断当前位置与之前计算目标点的距离，小于一定值才计算新目标	
//	//	float disSq = computeDistanceSq_PosToGoal();
//	//	if (disSq > 0.1) {
//	//		return _nextGoal;
//	//		//nextGoalIsTemp = false;
//	//	}
//	//	else {
//	//		//当第一次接近目标点时，保持原方向继续前进一小段距离
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
//				//在当前邻居中 找到了之前的leader，继续跟随前leader
//				return i;//返回 leader在nearAgent中的下标
//			}
//		}
//		return -1;//此时 需要重新选择leader
//
//	}
//
//	Menge::Math::Vector2 ORCAAgentTacticsFollow::followLeaderBehavior() {
//		//先判断是否已有leader，前leader 还是邻居
//		//在附近邻居中 找到旧leader
//		int leaderIndex = findLeaderInNearAgent(_agent->_leaderID);
//		if (leaderIndex == -1) {
//			leaderIndex = getGoal();//重新选择leader
//		}
//		//前往领导者位置，或者执行探索行为
//		if (leaderIndex >= 0 && leaderIndex < _agent->_nearAgents.size()) {
//			const Menge::Agents::BaseAgent *temp = _agent->_nearAgents[leaderIndex].agent;
//			Menge::Math::Vector2 leaderPos = temp->_pos;//选择leader的目标点为自己的目标点
//			_agent->_isFollowing = true;
//			//如果当前位置跟leader很近，暂停移动
//			if (_agent->_pos.distance(leaderPos)<2) {
//							leaderPos = temp->_nextGoal;
//			}
//			//_leaderPath.push_back(leaderPos);
//			_agent->_leaderPrefSpeed = temp->_nextPrefSpeed;
//			_agent->_leaderPos = temp->_pos;
//			//判断leader是否在同一个Map
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
//						//找到离leader最近的门
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
//			// std::cout <<"第"<<_id<<"个人选择了leader"<<temp->_id<<"目标点：("<<leaderPos._x<<","<<leaderPos._y<<")"<<std::endl;
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
//		//执行探索行为
//				//在当前区域内 确定前往的门 需要记录已经去过的门，
//				//当前区域有出口，前往出口
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
//				if (_agent->_maps[_agent->_currentMapIndex]->_nextMapsIndex[j] == -1) {//出口Map的下标
//					Menge::Math::Vector2 goal = _agent->_maps[_agent->_currentMapIndex]->_connections[j].pos;//目标点设为 出口
//					_agent->_nextMapIndex = -1;//表示出口
//					_agent->_catchNextMap = false;
//					return goal;
//				}
//			}
//		}
//		else {
//			//当前Map没有出口，随机选择一个门（）
//			int index = (rand() % (_agent->_maps[_agent->_currentMapIndex]->_connections.size()));
//			Menge::Math::Vector2 goal = _agent->_maps[_agent->_currentMapIndex]->_connections[index].pos;//目标点设为 随机的一个门
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
//	//高熟悉行为
//	Menge::Math::Vector2 ORCAAgentTacticsFollow::highEnvironmentFamiliarityBehavior() {
//		/*
//		能获取所有地图信息 以Agent当前位置为根结点，以地图中所有的 connection为子节点
//		构建无向图 ，再用迪杰斯特拉算法 计算最佳路径
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
