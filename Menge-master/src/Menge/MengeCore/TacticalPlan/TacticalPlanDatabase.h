
#ifndef __TacticalPlan_DATABASE_H__
#define __TacticalPlan_DATABASE_H__

#include "MengeCore/TacticalPlan/TacticalPlan.h"
#include "MengeCore/TacticalPlan/TacticalPlanFactory.h"
#include "MengeCore/PluginEngine/ElementDatabase.h"

namespace Menge {

	namespace Agents {
		/*!
		 *	@brief		The database of registered state selector implementations.
		 */
		typedef ElementDB< TacticalPlanFactory, TacticalPlan > TacticalPlanDB;

	}	// namespace Agents

#ifndef DOXYGEN_SHOULD_SKIP_THIS

	template<> 
	void ElementDB< Agents::TacticalPlanFactory, Agents::TacticalPlan >::addBuiltins();
	template<> std::string 
		ElementDB< Agents::TacticalPlanFactory, Agents::TacticalPlan >::getElementName();

#endif	 // DOXYGEN_SHOULD_SKIP_THIS

}	// namespace Menge
#endif	// __STATE_SELECTOR_DATABASE_H__
