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
 *	@file		ListMapSet.h
 *	@brief		An abstract class for any Map set which will need an _Maps list.
 *				Provides transformations from vertex vectors
 */

#ifndef __LIST_MAP_SET_H__
#define __LIST_MAP_SET_H__

#include "MengeCore/mengeCommon.h"
#include "MengeCore/Agents/Map.h"
#include "MengeCore/Agents/MapSets/MapSetFactory.h"
#include "MengeCore/Agents/MapSets/MapSet.h"
#include "MengeCore/Agents/MapSets/MapVertexList.h"

#include <vector>

namespace Menge {

	namespace Agents {

		/*!
		 *	@brief		Definition of Map set class which produces Maps based on
		 *				explicit definition in an XML file.
		 */
		class MENGE_API ListMapSet : public MapSet {
		public:
			/*!
			 *	@brief		Constructor
			 */
			ListMapSet();

		protected:
			/*!
			 *	@brief		Destructor
			 */
			~ListMapSet();

		public:
			/*!
			 *	@brief		Reports the number of Maps in the set
			 *
			 *	@returns	The number of Maps in this set
			 */
			virtual size_t MapCount() { return _Maps.size(); }

			/*!
			 *	@brief		Get the ith Map.
			 *
			 *	@param		i		The index of the requested Map.
			 *	@returns	The Map object
			 *	@throws		MapSetException if the index, i, is invalid.
			 */
			virtual Map * getMap( size_t i );
			
			/*!
			 *	@brief		Adds an Map  to the generator
			 *
			 *	@param		o		The Map Object to be added
			 *	@returns	true if the Map was added successfully
			 *	@throws		MapSetException if the Map is malformed
			 */
			bool addMap(Map * o);

			/*!
			 *	@brief		Adds an Map  to the generator from a list of vertices
			 *
			 *	@param		o 		MapVertexList struct representing the incoming Map
			 *	@returns	true if the Map was added successfully
			 *	@throws		MapSetException if the Map is malformed
			 */
			bool addMap(MapVertexList o);
			
			friend class ExplicitMapSetFactory;

		protected:
			/*!
			 *	@brief		The Maps in an internal list
			 */
			std::vector< Map *>	_Maps;
		};

		
	}	// namespace Agents
}	// namespace Menge
#endif	// __EXPLICIT_Map_SET_H__
