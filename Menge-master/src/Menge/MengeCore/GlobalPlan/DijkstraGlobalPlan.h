

#ifndef __DIJKSTRA_GL0BAL_PLAN_H__
#define __DIJKSTRA_GL0BAL_PLAN_H__

#include "MengeCore/mengeCommon.h"
#include "MengeCore/GlobalPlan/GlobalPlan.h"
#include "MengeCore/GlobalPlan/GlobalPlanFactory.h"

#include "MengeCore/Runtime/dijkstra.h"

namespace Menge {

	namespace Agents {
		/*!
		 *	@brief		An initial state selector that stores a single state
		 *				and assigns that state to all agents.
		 */
		class MENGE_API DijkstraGlobalPlan : public GlobalPlan {
		public:
			/*!
			 *	@brief		Constructor.
			 */
			DijkstraGlobalPlan() : _planName("Dijkstra") {}

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

		   // mutable	std::map<int, GlobalPlanAgent*> _globalPlanAgents;
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
		class MENGE_API DijkstraGlobalPlanFactory : public GlobalPlanFactory {
		public:
			/*!
			 *	@brief		Constructor
			 */
			DijkstraGlobalPlanFactory();


			virtual const char * name() const { return "dijkstra"; }

			virtual const char * description() const {
				return "Dijkstra--GlobalPlan";
			};

			

		protected:

			GlobalPlan * instance() const { return new DijkstraGlobalPlan(); }


			virtual bool setFromXML( GlobalPlan * sel, TiXmlElement * node,
									 const std::string & specFldr ) const;

			size_t _nameID;
		};

	}	// namespace Agents
}	// namespace Menge
#endif	// __CONST_STATE_SELECTOR_H__
