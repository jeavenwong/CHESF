
#include "GlobalPlanPlug.h"



namespace Menge {

	namespace Agents {

		std::vector<Menge::Math::Vector2>  PLUGCLASS::getGlobalPlan(std::map<int, Menge::Agents::Connection > connectionMapTemp,
			std::map<int, Menge::Agents::Path > pathMapTemp,
			std::vector<Agents::Map *> _maps,
			Math::Vector2 agentPos,
			int id
		) const {
			//TODO �Զ���ս�Բ�·�߹滮�㷨

			std::vector<Math::Vector2> res;

			return  res;
		}

		void  PLUGCLASS::initAgentInfo(std::vector<Agents::Map *> _maps,
			std::vector<BaseAgent *> agents
		) const {

			//TODO �Զ���ս�Բ��ʼ����Ϣ�㷨
		}


		FACTORYPLUGCLASS::FACTORYPLUGCLASS() : GlobalPlanFactory() {
		}

	}	// namespace Agents
}	// namespace Menge

extern "C" {

	GlobalPlanPlug_API	Menge::Agents::GlobalPlanFactory * Export(void) {//ս�Բ�ͳһ������

		return new Menge::Agents::FACTORYPLUGCLASS();

	}

}