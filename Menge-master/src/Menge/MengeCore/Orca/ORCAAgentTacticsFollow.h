///*
// Menge Crowd Simulation Framework
//
// Copyright and trademark 2012-17 University of North Carolina at Chapel Hill
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
// or
//    LICENSE.txt in the root of the Menge repository.
//
// Any questions or comments should be sent to the authors menge@cs.unc.edu
//
// <http://gamma.cs.unc.edu/Menge/>
//*/
//
///*!
// *  @file       ORCAAgent.h
// *  @brief      Contains the PedVOAgent class.
// */
//
//#ifndef __ORCAAgentTacticsFollow_H__
//#define __ORCAAgentTacticsFollow_H__
//
//#include "MengeCore/orca/ORCAAgent.h"
//#include "MengeCore/Math/Line.h"
//
//#include <vector>
//
//namespace ORCA {
//	/*!
//	 *  @brief      Defines an agent in the simulation.
//	 */
//	class MENGE_API ORCAAgentTacticsFollow {
//	public:
//		/*!
//		 *	@brief		Constructor
//		 */
//		ORCAAgentTacticsFollow(Agent *agent);
//
//		/*!
//		 *  @brief      Destroys this agent instance.
//		 */
//		~ORCAAgentTacticsFollow();
//
//
//
//		int ORCAAgentTacticsFollow::findLeaderInNearAgent(size_t leaderID);
//
//
//		float ORCAAgentTacticsFollow::computeDistanceSq_PosToGoal();
//
//		//重写父类的三个方法
//		//ORCA模型中 此方法 是 在附近的agent中 查找影响度最高的agent的ID
//	    size_t  getGoalInterface() const;
//	    size_t  getGoal();
//	    Menge::Math::Vector2 computeNextGoal();
//	    Menge::Math::Vector2 computeNextPrefSpeed();
//
//		Agent *_agent;
//
//		friend class Simulator;
//
//  protected:
//		Menge::Math::Vector2 followLeaderBehavior();
//		Menge::Math::Vector2 exploreBehavior();
//
//		Menge::Math::Vector2 highEnvironmentFamiliarityBehavior();
//		Menge::Math::Vector2 middleEnvironmentFamiliarityBehavior();
//		Menge::Math::Vector2 lowEnvironmentFamiliarityBehavior();
//  };
//
//
//
//
//}		// namespace ORCA
//
//#endif
