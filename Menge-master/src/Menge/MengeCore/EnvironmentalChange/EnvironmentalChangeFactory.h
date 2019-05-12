
#ifndef __Environmental_Change_FACTORY_H__
#define __Environmental_Change_FACTORY_H__

#include "MengeCore/CoreConfig.h"
#include "MengeCore/PluginEngine/ElementFactory.h"
#include "MengeCore/EnvironmentalChange/EnvironmentalChange.h"

namespace Menge {

	namespace Agents {
		/*!
		 *	@brief		A class for parsing the xml description of an initial state selector element
		 *				and instantiating particular instances.
		 */
		class MENGE_API EnvironmentalChangeFactory : public ElementFactory< EnvironmentalChange > {
		};
	}	// namespace Agents
}	// namespace Menge
#endif // __STATE_SELECTOR_FACTORY_H__
