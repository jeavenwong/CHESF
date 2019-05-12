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
 *	@file		MapSet.h
 *	@brief		The definition of the MapSet element
 *				Defines the numbers and positions of Maps in a set
 */
#ifndef __MAP_SET_H__
#define	__MAP_SET_H__

#include "MengeCore/MengeException.h"
#include "MengeCore/PluginEngine/Element.h"

namespace Menge {

	namespace Agents {
		// forward declaration
		class Map;
		class MapSetFactory;
		
		/*!
		 *	@brief		Exception class for Map set instantiation
		 */
		class MENGE_API MapSetException : public virtual MengeException {
		public:
			/*!
			 *	@brief		Default constructor.
			 */
			MapSetException() : MengeException() {}		

			/*!
			 *	@brief		Constructor with message.
			 *
			 *	@param		s		The exception-specific message.
			 */
			MapSetException( const std::string & s ): MengeException(s) {}
		};

		/*!
		 *	@brief		The fatal Map set exception.
		 */
		class MENGE_API MapSetFatalException : public MapSetException,
													public MengeFatalException {
		public:
			/*!
			 *	@brief		Default constructor.
			 */
			MapSetFatalException() : MengeException(), MapSetException(),
										  MengeFatalException() {}

			/*!
			 *	@brief		Constructor with message.
			 *
			 *	@param		s		The exception-specific message.
			 */
			MapSetFatalException( const std::string & s ) : MengeException(s),
																 MapSetException(),
																 MengeFatalException() {}
		};


		/*!
		 *	@brief		The base class for Map set definitions
		 *
		 *    This is an abstract class defining the functions of an Map set in Menge
		 *    Map sets must be able to provide a count of Maps in their definition
		 *    and pass those Maps on to the SpatialQuery
		 */
		class MENGE_API MapSet : public Element {
		public:
			/*!
			 *	@brief		Default constructor
			 */
			MapSet();

			friend class MapSetFactory;

		protected:
			/*!
			 *	@brief		Protected destructor.  The destroy method should be used
			 *				to delete an instance of an Map set.
			 */
			virtual ~MapSet();

		public:
			
			/*!
			 *	@brief		Reports the number of Maps in the set.
			 *
			 *	@returns	The number of Maps in this set.
			 */
			virtual size_t MapCount() = 0;

			/*!
			 *	@brief		Returns the ith Map.
			 *
			 *	@param		i		The index of the requested Map.
			 *	@returns	A pointer to the corresponding Map instance.
			 *	@throws		MapSetException if the index, i, is invalid.
			 */
			virtual Map * getMap( size_t i ) = 0;
			
			/*!
			 *	@brief		Sets the class of this Map set.
			 *
			 *	@param		cl		the class id to which the Map set belongs.
			 */
			virtual void setClass( size_t cl) { _class = cl; };

			/*!
			 *	@brief		Gets the class of this Map set.
			 *
			 *	@returns	The class id to which the Map set belongs.
			 */
			virtual size_t getClass() { return _class; };

		protected:
			
			/*!
			 *	@brief		The class for the Maps in this set.
			 *
			 *				This works with the BaseAgent::_MapSet member
			 *				to determine which Maps affect an agent.
			 */
			size_t _class;
		};

	} // namespace Agents
}	// namespace Menge
#endif // __Map_SET_H__
