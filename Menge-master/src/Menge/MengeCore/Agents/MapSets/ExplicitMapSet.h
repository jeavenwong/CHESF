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
 *	@file		ExplicitMapSet.h
 *	@brief		An Mapset which creates Maps based on explicit definitions in XML
 */

#ifndef __EXPLICIT_MAP_SET_H__
#define __EXPLICIT_MAP_SET_H__

#include "MengeCore/mengeCommon.h"
#include "MengeCore/Agents/Map.h"
#include "MengeCore/Agents/MapSets/ListMapSet.h"
#include "MengeCore/Agents/MapSets/MapSetFactory.h"
#include "MengeCore/Agents/MapSets/MapVertexList.h"

#include <vector>

namespace Menge {

	namespace Agents {

		class ExplicitMapSetFactory;
		/*!
		 *	@brief		Definition of Map set class which produces Maps based on
		 *				explicit definition in an XML file.
		 */
		class MENGE_API ExplicitMapSet : public ListMapSet {
		public:
			/*!
			 *	@brief		Constructor
			 */
			ExplicitMapSet();

		};

		//////////////////////////////////////////////////////////////////////////////

		/*!
		 *	@brief		Factory for ExplicitGenerator
		 */
		class MENGE_API ExplicitMapSetFactory : public MapSetFactory {
		public:
			/*!
			 *	@brief		The name of the Mapset type.
			 *
			 *	The set's name must be unique among all registered Mapset components.  
			 *	Each Mapset factory must override this function.
			 *
			 *	@returns	A string containing the unique Mapset name.
			 */
			virtual const char * name() const { return "explicit"; }

			/*!
			 *	@brief		A description of the Map set
			 *
			 *	Each Mapset factory must override this function.
			 *
			 *	@returns	A string containing the Mapset description.
			 */
			virtual const char * description() const {
				return "Map definitions given by explicit vertex lists in the XML "
					"specification.";
			};

		protected:
			/*!
			 *	@brief		Create an instance of this class's Mapset implementation.
			 *
			 *	All MapSetFactory sub-classes must override this by creating (on the heap)
			 *	a new instance of its corresponding MapSet type.  The various field values
			 *	of the instance will be set in a subsequent call to MapSetFactory::setFromXML.
			 *	The caller of this function takes ownership of the memory.
			 *
			 *	@returns		A pointer to a newly instantiated ExplicitMapSet class.
			 */
			MapSet * instance() const { return new ExplicitMapSet(); }

			/*!
			 *	@brief		Given a pointer to an MapSet instance, sets the appropriate fields
			 *				from the provided XML node.
			 *
			 *	It is assumed that the value of the `type` attribute is this MapSet's type.
			 *	(i.e. MapSetFactory::thisFactory has already been called and returned true.)
			 *	If sub-classes of MapSetFactory introduce *new* MapSet parameters, then
			 *	the sub-class should override this method but explicitly call the parent class's
			 *	version.
			 *
			 *	@param		gen			A pointer to the MapSet whose attributes are to be set.
			 *	@param		node		The XML node containing the MapSet attributes.
			 *	@param		specFldr	The path to the specification file.  If the MapSet
			 *							references resources in the file system, it should be
			 *							defined relative to the specification file location.  This
			 *							is the folder containing that path. 
			 *	@returns	A boolean reporting success (true) or failure (false).
			 */
			virtual bool setFromXML( MapSet * gen, TiXmlElement * node,
									 const std::string & specFldr ) const;

			/*!
			 *	@brief		Parses an Map position from an \<Map\> tag.
			 *
			 *	@param		node		The XML node containing the agent definition.
			 *	@returns	Vector of Vector2s representing the Map parsed
			 *	@throws		MapSetException if the Map tag is mangled or incomplete
			 */
			MapVertexList parseMap( TiXmlElement * node) const;
		};
	}	// namespace Agents
}	// namespace Menge
#endif	// __EXPLICIT_Map_SET_H__
