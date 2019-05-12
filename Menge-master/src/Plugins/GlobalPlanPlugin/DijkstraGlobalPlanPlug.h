
#pragma execution_character_set("utf-8")
#ifndef __DIJKSTRA_GL0BAL_PLUG_PLAN_H__
#define __DIJKSTRA_GL0BAL_PLUG_PLAN_H__

#include "MengeCore/mengeCommon.h"
#include "MengeCore/GlobalPlan/GlobalPlan.h"
#include "MengeCore/GlobalPlan/GlobalPlanFactory.h"
#include "dijkstra.h"
#include "DijkstraGlobalPlanPlugConfig.h"

#define PLUGCLASS DijkstraGlobalPlanPlug
#define FACTORYPLUGCLASS DijkstraGlobalPlanPlugFactory
#define PLUGNAME "dijkstraPlug"
#define PLUGDESC "使用迪杰斯特拉算法给熟悉环境的个体规划最短疏散路线"

//char * plugName = PLUGNAME;

namespace Menge {

	namespace Agents {
		/*!
		 *	@brief		An initial state selector that stores a single state
		 *				and assigns that state to all agents.
		 */
		class  PLUGCLASS : public GlobalPlan {
		public:
			/*!
			 *	@brief		Constructor.
			 */
			PLUGCLASS() : _planName(PLUGNAME) {}

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

			virtual std::vector<Menge::Math::Vector2>  getGlobalPlan(std::map<int, Menge::Agents::Connection > connectionMapTemp,
				std::map<int, Menge::Agents::Path > pathMapTemp,
				std::vector<Agents::Map *> _maps,
				Math::Vector2 agentPos,
				int id
			) const;

			virtual void initAgentInfo(std::vector<Agents::Map *> _maps,
				std::vector<BaseAgent *> agents
			) const;

		protected:
			/*!
			 *	@brief		The name of the profile to use.
			 */
			std::string _planName;
		};

		//////////////////////////////////////////////////////////////////////////////

		/*!
		 *	@brief		The factory for the ConstStateSelector.
		 */
		class FACTORYPLUGCLASS : public GlobalPlanFactory {
		public:
			/*!
			 *	@brief		Constructor
			 */
			FACTORYPLUGCLASS();


			virtual const char * name() const { return PLUGNAME; }

			virtual const char * description() const {
				return PLUGDESC;
			};

			

		protected:

			GlobalPlan * instance() const { return new PLUGCLASS(); }

		};

	}	// namespace Agents
}	// namespace Menge
#endif	// __CONST_STATE_SELECTOR_H__
