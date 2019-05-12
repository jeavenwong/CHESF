

#ifndef __Tactical_PLAN_PLUGIN_H__
#define __Tactical_PLAN_PLUGIN_H__

#include "MengeCore/mengeCommon.h"
#include "MengeCore/TacticalPlan/TacticalPlan.h"
#include "MengeCore/TacticalPlan/TacticalPlanFactory.h"
#include <map>
#include "TacticalPlanPluginAgent.h"
#include "TacticalPlanPluginConfig.h"

//TODO  ���������Ͳ����
#define PLUGCLASS PlugClassName
#define FACTORYPLUGCLASS PlugFactoryClassName
#define PLUGNAME "PlugNameTODO"

namespace Menge {

	namespace Agents {
		/*!
		 *	@brief		An initial state selector that stores a single state
		 *				and assigns that state to all agents.
		 */
		class  PLUGCLASS : public TacticalPlan {
		public:
			/*!
			 *	@brief		Constructor.
			 */
			PLUGCLASS() : _planName(PLUGNAME) {}


			virtual std::string getPlan() { return _planName; }


			virtual Menge::Math::Vector2  computeNextGoal();

			virtual void initAgentInfo(std::vector<Agents::Map *> _maps,
				std::vector<BaseAgent *> agents
			) const;

		protected:
			/*!
			 *	@brief		The name of the profile to use.
			 */
			std::string _planName;
			FollowAgent *_agent;//��ǰ����ĸ���
			mutable	std::map<int, FollowAgent *> _tacticalAgents;//�����ս����������Ϣ
		};

		//////////////////////////////////////////////////////////////////////////////

		/*!
		 *	@brief		The factory for the ConstStateSelector.
		 */
		class  FACTORYPLUGCLASS : public TacticalPlanFactory {
		public:
			/*!
			 *	@brief		Constructor
			 */
			FACTORYPLUGCLASS();//11
			//xigou  11

			virtual const char * name() const { return PLUGNAME; }//�ؼ���

			virtual const char * description() const {
				//TODO ����Զ���Ĳ��������Ϣ
				return PLUGNAME;
			};

			

		protected:

			PLUGCLASS * instance() const { return new PLUGCLASS(); }//11

		};

	}	// namespace Agents
}	// namespace Menge
#endif	// __CONST_STATE_SELECTOR_H__
