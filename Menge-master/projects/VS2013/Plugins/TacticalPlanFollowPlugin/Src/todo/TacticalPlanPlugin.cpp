

#include "TacticalPlanPlugin.h"



namespace Menge {

	namespace Agents {

		////////////////////////////////////////////////////////////////////////////
		//			Implementation of ConstProfileSelectorFactory
		////////////////////////////////////////////////////////////////////////////

		void  PLUGCLASS::initAgentInfo(std::vector<Agents::Map *> _maps,
			std::vector<BaseAgent *> agents
		) const {
			_tacticalAgents.clear();
			//TODO 自定义初始化战术层信息
				
		}


		Menge::Math::Vector2 PLUGCLASS::computeNextGoal(){

			//TODO 自定义初始化战术层 目标点选择算法
		
			return Menge::Math::Vector2(0,0);
		}


		FACTORYPLUGCLASS::FACTORYPLUGCLASS() : TacticalPlanFactory() {

		}

		////////////////////////////////////////////////////////////////////////////
		

	}	// namespace Agents
}	// namespace Menge

extern "C" {

		TacticalPlanPlugin_API	Menge::Agents::TacticalPlanFactory * Export(void) {

			return new Menge::Agents::FACTORYPLUGCLASS();

	}

}