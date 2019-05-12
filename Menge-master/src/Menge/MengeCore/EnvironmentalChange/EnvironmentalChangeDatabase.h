
#ifndef __Environmental_Change_DATABASE_H__
#define __Environmental_Change_DATABASE_H__

#include "MengeCore/EnvironmentalChange/EnvironmentalChange.h"
#include "MengeCore/EnvironmentalChange/EnvironmentalChangeFactory.h"
#include "MengeCore/PluginEngine/ElementDatabase.h"

namespace Menge {

	namespace Agents {
		/*!
		 *	@brief		The database of registered EnvironmentalChange implementations.
		 */
		typedef ElementDB< EnvironmentalChangeFactory, EnvironmentalChange > EnvironmentalChangeDB;

	}	// namespace Agents

#ifndef DOXYGEN_SHOULD_SKIP_THIS

	template<> 
	void ElementDB< Agents::EnvironmentalChangeFactory, Agents::EnvironmentalChange >::addBuiltins();
	template<> std::string 
		ElementDB< Agents::EnvironmentalChangeFactory, Agents::EnvironmentalChange >::getElementName();

#endif	 // DOXYGEN_SHOULD_SKIP_THIS

}	// namespace Menge
#endif	// __STATE_SELECTOR_DATABASE_H__
