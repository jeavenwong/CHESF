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
 *	@file		MapSetDatabase.h
 *	@brief		Central database for querying available Map set implementations.
 *
 *	For Map sets to be used in simulation, they must register 
 *	themselves into the MapSetDB.  This is done via the PluginEngine.
 */

#ifndef __MAP_SET_DATABASE_H__
#define __MAP_SET_DATABASE_H__

#include "MengeCore/Agents/MapSets/MapSet.h"
#include "MengeCore/Agents/MapSets/MapSetFactory.h"
#include "MengeCore/PluginEngine/ElementDatabase.h"

namespace Menge {

	namespace Agents {
		/*!
		 *	@brief		The database of registered aMap set implementations.
		 */
		typedef ElementDB< MapSetFactory, MapSet > MapSetDB;

	}	// namespace Agents

#ifndef DOXYGEN_SHOULD_SKIP_THIS

	// Declarations of explicit specialization
	template<> 
	void ElementDB< Agents::MapSetFactory, Agents::MapSet >::addBuiltins();

	template<> 
	std::string ElementDB< Agents::MapSetFactory, Agents::MapSet >::getElementName();

#endif	 // DOXYGEN_SHOULD_SKIP_THIS

}	// namespace Menge

#endif	// __Map_SET_DATABASE_H__
