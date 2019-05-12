
#include "GlobalPlanPlug.h"



namespace Menge {

	namespace Agents {

		std::vector<Menge::Math::Vector2>  PLUGCLASS::getGlobalPlan(std::map<int, Menge::Agents::Connection > connectionMapTemp,
			std::map<int, Menge::Agents::Path > pathMapTemp,
			std::vector<Agents::Map *> _maps,
			Math::Vector2 agentPos,
			int id
		) const {
			//TODO 自定义战略层路线规划算法

			std::vector<Math::Vector2> res;

			return  res;
		}

		void  PLUGCLASS::initAgentInfo(std::vector<Agents::Map *> _maps,
			std::vector<BaseAgent *> agents
		) const {

			//TODO 自定义战略层初始化信息算法
		}


		FACTORYPLUGCLASS::FACTORYPLUGCLASS() : GlobalPlanFactory() {
		}

	}	// namespace Agents
}	// namespace Menge

extern "C" {

	GlobalPlanPlug_API	Menge::Agents::GlobalPlanFactory * Export(void) {//战略层统一导出宏

		return new Menge::Agents::FACTORYPLUGCLASS();

	}

}