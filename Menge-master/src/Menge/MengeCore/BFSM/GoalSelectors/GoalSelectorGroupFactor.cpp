
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
			//�ڸ�����agent�� ����Ӱ�����ߵ�agent��ID
			int leaderId = agent->getGoalInterface();
			
			//��ǰagent��leader,����ʱ��Ϊleader����Ϥ���Σ�ֱ��ǰ��xml�е�ָ��λ�ã�
			
			if (leaderId == -2) {
				//ѡ��goalSet�������һ��goal��ΪĿ���
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

			//��ǰagent����leader����Ҫ����leader�����
			if (leaderId != -1&& leaderId != -2) {
			   const Agents::BaseAgent *other = (agent->_nearAgents[leaderId].agent);
			   const Vector2 op = other->_pos;
			   return new PointGoal(op);
			}

			//��ʾ��ǰagent����û���ھӣ�ִ��̽����Ϊ
			if (leaderId == -1 ) {
				
			}


			return goal;
			

		}
	}	// namespace BFSM
}	// namespace Menge
