
#ifndef __OperationPlan_DATABASE_H__
#define __OperationPlan_DATABASE_H__

#include "MengeCore/OperationPlan/OperationPlan.h"
#include "MengeCore/OperationPlan/OperationPlanFactory.h"
#include "MengeCore/PluginEngine/ElementDatabase.h"

namespace Menge {

	namespace Agents {
		/*!
		 *	@brief		The database of registered state selector implementations.
		 */
		typedef ElementDB< OperationPlanFactory, OperationPlan > OperationPlanDB;

	}	// namespace Agents

#ifndef DOXYGEN_SHOULD_SKIP_THIS

	template<> 
	void ElementDB< Agents::OperationPlanFactory, Agents::OperationPlan >::addBuiltins();
	template<> std::string 
		ElementDB< Agents::OperationPlanFactory, Agents::OperationPlan >::getElementName();

#endif	 // DOXYGEN_SHOULD_SKIP_THIS

}	// namespace Menge
#endif	// __STATE_SELECTOR_DATABASE_H__
