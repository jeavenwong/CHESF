/*
 Menge Crowd Simulation Framework

 Copyright and trademark 2012-17 University of North Carolina at Chapel Hill

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0
 or
    LICENSE.txt in the root of the Menge repository.

 Any questions or comments should be sent to the authors menge@cs.unc.edu

 <http://gamma.cs.unc.edu/Menge/>
*/

/*!
 *  @file       ORCAAgent.h
 *  @brief      Contains the PedVOAgent class.
 */

#ifndef __ORCA_AGENT_H__
#define __ORCA_AGENT_H__

#include "MengeCore/Agents/BaseAgent.h"

#include "MengeCore/Math/Line.h"
#include "MengeCore/Orca/ORCAAgentTacticsFollow.h"
#include <vector>

namespace ORCA {
	/*!
	 *  @brief      Defines an agent in the simulation.
	 */
	class MENGE_API Agent : public Menge::Agents::BaseAgent 	{
	public:
		/*!
		 *	@brief		Constructor
		 */
		Agent();

		/*!
		 *  @brief      Destroys this agent instance.
		 */
		~Agent();

		/*!
		 *  @brief      Computes the new velocity of this agent.
		 */
		void computeNewVelocity();
		int Agent::findLeaderInNearAgent(size_t leaderID);

		/*!
		 *	@brief		Used by the plugin system to know what artifacts to associate with
		 *				agents of this type.  Every sub-class of must return a globally
		 *				unique value if it should be associated with unique artifacts.
		 */
		virtual std::string getStringId() const;

		/*!
		 *	@brief			Based on the neighbors, computes the ORCA lines
		 *
		 *	@returns		The total number of obstacle lines
		 */
		size_t computeORCALines();
		float computeDistanceSq_PosToGoal();

		//重写父类的三个方法
		//ORCA模型中 此方法 是 在附近的agent中 查找影响度最高的agent的ID
		virtual size_t  getGoalInterface() const;
		virtual size_t  getGoal();
		virtual Menge::Math::Vector2 computeNextGoal();
		virtual Menge::Math::Vector2 computeNextPrefSpeed();
		/*!
		 *	@brief		The set of ORCA constraints.
		 */
		std::vector<Menge::Math::Line> _orcaLines;
		//std::vector<Menge::Agents::Map *> _maps;
		std::vector<bool> environmentFamiliaritySet;//对map是否熟悉
		/*!
		 *	@brief		The time horizon for inter-agent interactions.
		 */
		float _timeHorizon;
		int _environmentFamiliarity;//0表示低熟悉度 1表示中，2表示高
		/*!
		 *	@brief		The time horizon for agent-obstacle interactions.
		 */
		float _timeHorizonObst;

		// DEFAULT VALUES FOR THE AGENT PARAMTERS
		/*!
		 *	@brief		The default time horizon for inter-agent interactions.
		 */
		static const float TAU;

		/*!
		 *	@brief		The default time horizon for agent-obstacle interactions.
		 */
		static const float TAU_OBST;

		/*! @brief	The name identifier for this agent type. */
		static const std::string NAME;

		//agent的团队影响力
		float _influence;
		size_t _leaderID;//-1表示附近没有邻居，-2表示自己是leader
		bool _isFollowing=false;
		bool _missFollowing=false;
		Menge::Math::Vector2 _leaderPrefSpeed;
		Menge::Math::Vector2 _leaderPos;
		std::vector<Menge::Math::Vector2> _leaderPath;
		bool _nextGoalIsTemp;
		int _nextMapIndex;
		int _currentMapIndex;
		bool _catchNextMap;
		friend class Simulator;

  protected:
		/*!
		 *	@brief		Constructs an ORCA line for the given obstacle
		 *				under the assumption that the agent is on its right side.
		 *				If appropriate, it adds the obstacle to the set of orca lines.
		 *
		 *	@param		obstNbrID		The index of the near-by obstacle to test.
		 *	@param		invTau			1 / _timeHorizonObst - the inverse of the 
		 *								time horizon for obstacles.
		 *	@param		flip			The agent is on the left side of this obstacle.
		 */
		void obstacleLine( size_t obstNbrID, const float invTau, bool flip );
		Menge::Math::Vector2 followLeaderBehavior();
		Menge::Math::Vector2 exploreBehavior();

		Menge::Math::Vector2 highEnvironmentFamiliarityBehavior();
		Menge::Math::Vector2 middleEnvironmentFamiliarityBehavior();
		Menge::Math::Vector2 lowEnvironmentFamiliarityBehavior();
  };

  /*!
   *  @brief      Solves a one-dimensional linear program on a specified line
   *              subject to linear constraints defined by lines and a circular
   *              constraint.
   *
   *  @param      lines         Lines defining the linear constraints.
   *  @param      lineNo        The specified line constraint.
   *  @param      radius        The radius of the circular constraint.
   *  @param      optVelocity   The optimization velocity.
   *  @param      directionOpt  True if the direction should be optimized.
   *  @param      result        A reference to the result of the linear program.
   *  @returns    True if successful.
   */
  bool linearProgram1( const std::vector<Menge::Math::Line>& lines, size_t lineNo,
					   float radius, const Menge::Math::Vector2 & optVelocity,
					   bool directionOpt, Menge::Math::Vector2& result );

  /*!
   *  @brief      Solves a two-dimensional linear program subject to linear
   *              constraints defined by lines and a circular constraint.
   *
   *  @param      lines         Lines defining the linear constraints.
   *  @param      radius        The radius of the circular constraint.
   *  @param      optVelocity   The optimization velocity.
   *  @param      directionOpt  True if the direction should be optimized.
   *  @param      result        A reference to the result of the linear program.
   *  @returns    The number of the line it fails on, and the number of lines if successful.
   */  
  size_t linearProgram2( const std::vector<Menge::Math::Line>& lines, float radius,
						 const Menge::Math::Vector2& optVelocity, bool directionOpt,
						 Menge::Math::Vector2& result );

  /*!
   *  @brief      Solves a two-dimensional linear program subject to linear
   *              constraints defined by lines and a circular constraint.
   *
   *  @param      lines         Lines defining the linear constraints.
   *  @param      numObstLines  Count of obstacle lines.
   *  @param      beginLine     The line on which the 2-d linear program failed.
   *  @param      radius        The radius of the circular constraint.
   *  @param      result        A reference to the result of the linear program.
   */
  void linearProgram3( const std::vector<Menge::Math::Line>& lines, size_t numObstLines,
					   size_t beginLine, float radius, Menge::Math::Vector2& result );


}		// namespace ORCA

#endif
