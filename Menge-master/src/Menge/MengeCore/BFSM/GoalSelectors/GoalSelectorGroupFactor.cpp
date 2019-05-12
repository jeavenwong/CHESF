
#include "MengeCore/BFSM/GoalSelectors/GoalSelectorGroupFactor.h"

#include "MengeCore/Agents/BaseAgent.h"
#include "MengeCore/BFSM/GoalSet.h"
#include "MengeCore/BFSM/Goals/Goal.h"
#include "MengeCore/BFSM/Goals/GoalPoint.h"
#include <cassert>

namespace Menge {

	namespace BFSM {

		/////////////////////////////////////////////////////////////////////
		//                   Implementation of NearestGoalSelector
		/////////////////////////////////////////////////////////////////////
		
		Goal * GroupFactorGoalSelector::getGoal(const Agents::BaseAgent * agent) const {
			assert(agent != 0x0 && "GoalSelectorGroupFactor requires a valid base agent!");
	
	
			PointGoal * goal = new PointGoal();
			//在附近的agent中 查找影响度最高的agent的ID
			int leaderId = agent->getGoalInterface();
			
			//当前agent是leader,（暂时认为leader是熟悉地形，直接前往xml中的指定位置）
			
			if (leaderId == -2) {
				//选择goalSet中最近的一个goal作为目标点
				const size_t GOAL_COUNT = _goalSet->size();
				if (GOAL_COUNT == 0) {
					logger << Logger::ERR_MSG;
					logger << "NearestGoalSelector was unable to provide a goal for agent ";
					logger << agent->_id << ".  There were no available goals in the goal set.";
					return 0x0;
				}
				const Vector2 p = agent->_pos;

				Goal * bestGoal;

				bestGoal = _goalSet->getIthGoal(0);
				Vector2 disp = bestGoal->getCentroid() - p;
				float bestDist = absSq(disp);
				for (size_t i = 1; i < GOAL_COUNT; ++i) {
					Goal * testGoal = _goalSet->getIthGoal(i);
					disp = testGoal->getCentroid() - p;
					float testDist = absSq(disp);
					if (testDist < bestDist) {
						bestDist = testDist;
						bestGoal = testGoal;
					}
				}
				return bestGoal;
			}

			//当前agent不是leader，需要跟随leader的情况
			if (leaderId != -1&& leaderId != -2) {
			   const Agents::BaseAgent *other = (agent->_nearAgents[leaderId].agent);
			   const Vector2 op = other->_pos;
			   return new PointGoal(op);
			}

			//表示当前agent附近没有邻居，执行探索行为
			if (leaderId == -1 ) {
				
			}


			return goal;
			

		}
	}	// namespace BFSM
}	// namespace Menge
