

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
			//TODO �Զ����ʼ��ս������Ϣ
				
		}


		Menge::Math::Vector2 PLUGCLASS::computeNextGoal(){

			//TODO �Զ����ʼ��ս���� Ŀ���ѡ���㷨
		
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