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
#ifndef __Environmental_Change_H__
#define	__Environmental_Change_H__

#include "MengeCore/mengeCommon.h"
#include "MengeCore/PluginEngine/Element.h"
#include "MengeCore/Agents/Map.h"
#include <map> 
#include "MengeCore/Agents/MapSets/MapVertexList.h"
#include "MengeCore/Agents/ObstacleSets/ExplicitObstacleSet.h"
#include "MengeCore/Agents/ObstacleSets/ListObstacleSet.h"
#include "MengeCore/Agents/ObstacleSets/ObstacleSetDatabase.h"

namespace Menge {

	namespace Agents {
		// forward declaration
		class BaseAgent;
		/*!
		 *	@brief		Exception class for state selector computation.
		 */
		class MENGE_API EnvironmentalChangeException : public virtual MengeException {
		public:
			/*!
			 *	@brief		Default constructor.
			 */
			EnvironmentalChangeException() : MengeException() {}

			/*!
			 *	@brief		Constructor with message.
			 *
			 *	@param		s		The exception-specific message.
			 */
			EnvironmentalChangeException( const std::string & s ): MengeException(s) {}
		};

		/*!
		 *	@brief		The fatal state selector exception.
		 */
		class MENGE_API EnvironmentalChangeFatalException : public EnvironmentalChangeException,
													  public MengeFatalException {
		public:
			/*!
			 *	@brief		Default constructor.
			 */
			EnvironmentalChangeFatalException() : MengeException(), EnvironmentalChangeException(),
											MengeFatalException() {}

			/*!
			 *	@brief		Constructor with message.
			 *
			 *	@param		s		The exception-specific message.
			 */
			EnvironmentalChangeFatalException( const std::string & s ): MengeException(s),
															EnvironmentalChangeException(),
																  MengeFatalException() {}
		};

		/*!
		 *	@brief		The base class for selecting an agent's intial state.
		 *
		 *	This is an abstract class, primarily defining the mechanism for selecting
		 *	an agent's initial state.
		 */

		class MENGE_API EnvironmentalChange : public Element {
		public:
			/*!
			 *	@brief		Constructor
			 */
			EnvironmentalChange();
			mutable bool enable = true;
			mutable bool _show = false;
			ObstacleSet * _obSet;
		protected:
			/*!
			 *	@brief		Virtual destructor.
			 */
			virtual ~EnvironmentalChange();
			
		public:
			/*!
			 *	@brief		Provides the name of a EnvironmentalChange.
			 *
			 *	Ths must be overriden by child classes.
			 *
			 *	@returns:		The name of the EnvironmentalChange.
			 */
			virtual std::string getName() = 0;
			virtual std::vector<Menge::Math::Vector2> getVisVertex() = 0;
			virtual bool getEnvironmentalChange(std::map<int, Menge::Agents::Connection > &connectionMapTemp,
												std::map<int, Menge::Agents::Path > &pathMapTemp,
												std::vector<BaseAgent*> &agents,
				                                Menge::Agents::ObstacleSet **ob,
												float _globalTime
			) const = 0;
		};

	} // namespace Agents
}	// namespace Menge
#endif // __STATE_SELECTOR_H__
