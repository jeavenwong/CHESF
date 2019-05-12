

#ifndef __TacticalFollow_PLAN_H__
#define __TacticalFollow_PLAN_H__

#include "MengeCore/mengeCommon.h"
#include "MengeCore/TacticalPlan/TacticalPlan.h"
#include "MengeCore/TacticalPlan/TacticalPlanFactory.h"
#include "MengeCore/TacticalPlan/TacticalPlanAgent.h"

#include "MengeCore/orca/ORCA.h"


namespace Menge {

	namespace Agents {
		/*!
		 *	@brief		An initial state selector that stores a single state
		 *				and assigns that state to all agents.
		 */
		class MENGE_API TacticalFollowPlan : public TacticalPlan {
		public:
			/*!
			 *	@brief		Constructor.
			 */
			TacticalFollowPlan() : _planName("TacticalFollow") {}

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
			void setPlanName( const std::string & name ) { _planName = name; }
			virtual Menge::Math::Vector2  computeNextGoal();

			int TacticalFollowPlan::findLeaderInNearAgent(size_t leaderID);


			float TacticalFollowPlan::computeDistanceSq_PosToGoal();

			//重写父类的三个方法
			//ORCA模型中 此方法 是 在附近的agent中 查找影响度最高的agent的ID
			size_t  getGoalInterface() const;
			size_t  getGoal();
			Menge::Math::Vector2 computeNextPrefSpeed();

			TacticalPlanAgent *_agent;//当前计算的个体
			mutable	std::map<int, TacticalPlanAgent *> _tacticalAgents;//个体的战术层属性信息
			virtual void initAgentInfo(std::vector<Agents::Map *> _maps,
				std::vector<BaseAgent *> agents
			) const;
		protected:
			/*!
			 *	@brief		The name of the profile to use.
			 */
			std::string _planName;

			Menge::Math::Vector2 TacticalFollowPlan::followLeaderBehavior();
			Menge::Math::Vector2 TacticalFollowPlan::exploreBehavior();

			Menge::Math::Vector2 TacticalFollowPlan::highEnvironmentFamiliarityBehavior();
			Menge::Math::Vector2 TacticalFollowPlan::middleEnvironmentFamiliarityBehavior();
			Menge::Math::Vector2 TacticalFollowPlan::lowEnvironmentFamiliarityBehavior();
		};

		//////////////////////////////////////////////////////////////////////////////

		/*!
		 *	@brief		The factory for the ConstStateSelector.
		 */
		class MENGE_API TacticalFollowPlanFactory : public TacticalPlanFactory {
		public:
			/*!
			 *	@brief		Constructor
			 */
			TacticalFollowPlanFactory();


			virtual const char * name() const { return "follow"; }

			virtual const char * description() const {
				return "TacticalFollow";
			};

			

		protected:

			TacticalFollowPlan * instance() const { return new TacticalFollowPlan(); }


			virtual bool setFromXML(TacticalPlan * sel, TiXmlElement * node,
									 const std::string & specFldr ) const;

			size_t _nameID;
		};

	}	// namespace Agents
}	// namespace Menge
#endif	// __CONST_STATE_SELECTOR_H__
