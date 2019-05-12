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
 *	@file		StateSelector.h
 *	@brief		The definition of the agent initial state selector element.  
 *				This is the mechanism which determines which state in the FSM the agent starts in.
 */
#ifndef __GLOBAL_PLAN_H__
#define	__GLOBAL_PLAN_H__

#include "MengeCore/mengeCommon.h"
#include "MengeCore/PluginEngine/Element.h"
#include "MengeCore/Agents/Map.h"
#include <map> 
#include "MengeCore/Agents/MapSets/MapVertexList.h"
#include "MengeCore/GlobalPlan/GlobalPlanAgent.h"
#include "MengeCore/Agents/BaseAgent.h"
namespace Menge {

	namespace Agents {
		// forward declaration
		class BaseAgent;

		/*!
		 *	@brief		Exception class for state selector computation.
		 */
		class MENGE_API GlobalPlanException : public virtual MengeException {
		public:
			/*!
			 *	@brief		Default constructor.
			 */
			GlobalPlanException() : MengeException() {}

			/*!
			 *	@brief		Constructor with message.
			 *
			 *	@param		s		The exception-specific message.
			 */
			GlobalPlanException( const std::string & s ): MengeException(s) {}
		};

		/*!
		 *	@brief		The fatal state selector exception.
		 */
		class MENGE_API GlobalPlanFatalException : public GlobalPlanException,
													  public MengeFatalException {
		public:
			/*!
			 *	@brief		Default constructor.
			 */
			GlobalPlanFatalException() : MengeException(), GlobalPlanException(),
											MengeFatalException() {}

			/*!
			 *	@brief		Constructor with message.
			 *
			 *	@param		s		The exception-specific message.
			 */
			GlobalPlanFatalException( const std::string & s ): MengeException(s),
																  GlobalPlanException(),
																  MengeFatalException() {}
		};




		class MENGE_API GlobalPlan : public Element {
		public:
			/*!
			 *	@brief		Constructor
			 */
			GlobalPlan();
			virtual std::string getPlan() = 0;
			virtual std::vector<Menge::Math::Vector2> getGlobalPlan(std::map<int, Menge::Agents::Connection > connectionMapTemp,
				std::map<int, Menge::Agents::Path > pathMapTemp,
				std::vector<Agents::Map *> _maps,
				Math::Vector2 agentPos,
				int id
			) const = 0;
			virtual void initAgentInfo(std::vector<Agents::Map *> _maps,
				std::vector<BaseAgent *> agents
			) const = 0;
		protected:
			/*!
			 *	@brief		Virtual destructor.
			 */
			virtual ~GlobalPlan();

		public:


			mutable	std::map<int, GlobalPlanAgent*> _globalPlanAgents;
		};

	} // namespace Agents
}	// namespace Menge
#endif // __STATE_SELECTOR_H__
