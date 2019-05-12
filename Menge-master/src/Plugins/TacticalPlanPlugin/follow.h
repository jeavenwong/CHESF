

#ifndef __TacticalFollow_PLAN_H__
#define __TacticalFollow_PLAN_H__

#include "MengeCore/mengeCommon.h"
#include "MengeCore/TacticalPlan/TacticalPlan.h"
#include "MengeCore/TacticalPlan/TacticalPlanFactory.h"
#include "MengeCore/orca/ORCA.h"

#include "followAgent.h"
#include "followPluginConfig.h"
namespace Menge {

	namespace Agents {
		/*!
		 *	@brief		An initial state selector that stores a single state
		 *				and assigns that state to all agents.
		 */
		class  TacticalPlanFollowPlugin : public TacticalPlan {
		public:
			/*!
			 *	@brief		Constructor.
			 */
			TacticalPlanFollowPlugin() : _planName("TacticalFollowPlugin") {}

			/*!
			 *	@brief		Provides the name of a state.
			 *
			 *	Ths must be overriden by child classes.
			 *
			 *	@returns:		The name of the state.
			 */
			virtual std::string getPlan() { return _planName; }

			/*!
			 *	@brief		Sets the name of the state.
			 *
			 *	@param		name		The name of the selector's state.
			 */
			void setPlanName( const std::string & name ) { _planName = name; }//11
			virtual Menge::Math::Vector2  computeNextGoal();

			int TacticalPlanFollowPlugin::findLeaderInNearAgent(size_t leaderID);


			float TacticalPlanFollowPlugin::computeDistanceSq_PosToGoal();

			//��д�������������
			//ORCAģ���� �˷��� �� �ڸ�����agent�� ����Ӱ�����ߵ�agent��ID
			size_t  getGoalInterface() const;
			size_t  getGoal();
			Menge::Math::Vector2 computeNextPrefSpeed();

			FollowAgent *_agent;//��ǰ����ĸ���
			mutable	std::map<int, FollowAgent *> _tacticalAgents;//�����ս����������Ϣ
			virtual void initAgentInfo(std::vector<Agents::Map *> _maps,
				std::vector<BaseAgent *> agents
			) const;
		protected:
			/*!
			 *	@brief		The name of the profile to use.
			 */
			std::string _planName;

			Menge::Math::Vector2 TacticalPlanFollowPlugin::followLeaderBehavior();
			Menge::Math::Vector2 TacticalPlanFollowPlugin::exploreBehavior();

			Menge::Math::Vector2 TacticalPlanFollowPlugin::highEnvironmentFamiliarityBehavior();
			Menge::Math::Vector2 TacticalPlanFollowPlugin::middleEnvironmentFamiliarityBehavior();
			Menge::Math::Vector2 TacticalPlanFollowPlugin::lowEnvironmentFamiliarityBehavior();
		};

		//////////////////////////////////////////////////////////////////////////////

		/*!
		 *	@brief		The factory for the ConstStateSelector.
		 */
		class  TacticalPlanFollowPluginFactory : public TacticalPlanFactory {
		public:
			/*!
			 *	@brief		Constructor
			 */
			TacticalPlanFollowPluginFactory();//11
			//xigou  11

			virtual const char * name() const { return "followPlug"; }//�ؼ���//11

			virtual const char * description() const {//11
				return "TacticalFollow";
			};

			

		protected:

			TacticalPlanFollowPlugin * instance() const { return new TacticalPlanFollowPlugin(); }//11


			virtual bool setFromXML(TacticalPlan * sel, TiXmlElement * node,
									 const std::string & specFldr ) const;

			size_t _nameID;
		};

	}	// namespace Agents
}	// namespace Menge
#endif	// __CONST_STATE_SELECTOR_H__
