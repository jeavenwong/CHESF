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
#ifndef __TacticalPlan_H__
#define	__TacticalPlan_H__

#include "MengeCore/Agents/BaseAgent.h"
#include "MengeCore/mengeCommon.h"
#include "MengeCore/PluginEngine/Element.h"
#include "MengeCore/Agents/BaseAgent.h"

namespace Menge {

	namespace Agents {
		// forward declaration
		class BaseAgent;

		/*!
		 *	@brief		Exception class for state selector computation.
		 */
		class MENGE_API TacticalPlanException : public virtual MengeException {
		public:
			/*!
			 *	@brief		Default constructor.
			 */
			TacticalPlanException() : MengeException() {}

			/*!
			 *	@brief		Constructor with message.
			 *
			 *	@param		s		The exception-specific message.
			 */
			TacticalPlanException( const std::string & s ): MengeException(s) {}
		};

		/*!
		 *	@brief		The fatal state selector exception.
		 */
		class MENGE_API TacticalPlanFatalException : public TacticalPlanException,
													  public MengeFatalException {
		public:
			/*!
			 *	@brief		Default constructor.
			 */
			TacticalPlanFatalException() : MengeException(), TacticalPlanException(),
											MengeFatalException() {}

			/*!
			 *	@brief		Constructor with message.
			 *
			 *	@param		s		The exception-specific message.
			 */
			TacticalPlanFatalException( const std::string & s ): MengeException(s),
				                                                 TacticalPlanException(),
																  MengeFatalException() {}
		};




		class MENGE_API TacticalPlan : public Element {
		public:
			/*!
			 *	@brief		Constructor
			 */
			TacticalPlan();
			BaseAgent * _baseAgent;
		protected:
			/*!
			 *	@brief		Virtual destructor.
			 */
			virtual ~TacticalPlan();

		public:
			/*!
			 *	@brief		Provides the name of a plan.
			 *
			 *	Ths must be overriden by child classes.
			 *
			 *	@returns:		The name of the plan.
			 */
			virtual std::string getPlan() = 0;

			virtual Menge::Math::Vector2 computeNextGoal()= 0;
			virtual void initAgentInfo(std::vector<Agents::Map *> _maps,
				std::vector<BaseAgent *> agents
			) const = 0;
		};

	} // namespace Agents
}	// namespace Menge
#endif // __STATE_SELECTOR_H__
