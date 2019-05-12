
#ifndef __GL0BAL_PLAN_DATABASE_H__
#define __GL0BAL_PLAN_DATABASE_H__

#include "MengeCore/GlobalPlan/GlobalPlan.h"
#include "MengeCore/GlobalPlan/GlobalPlanFactory.h"
#include "MengeCore/PluginEngine/ElementDatabase.h"

namespace Menge {

	namespace Agents {
		/*!
		 *	@brief		The database of registered state selector implementations.
		 */
		typedef ElementDB< GlobalPlanFactory, GlobalPlan > GlobalPlanDB;

	}	// namespace Agents

#ifndef DOXYGEN_SHOULD_SKIP_THIS

	template<> 
	void ElementDB< Agents::GlobalPlanFactory, Agents::GlobalPlan >::addBuiltins();
	template<> std::string 
		ElementDB< Agents::GlobalPlanFactory, Agents::GlobalPlan >::getElementName();

#endif	 // DOXYGEN_SHOULD_SKIP_THIS

}	// namespace Menge
#endif	// __STATE_SELECTOR_DATABASE_H__
