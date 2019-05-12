

#ifndef __OperationHelbing_PLAN_H__
#define __OperationHelbing_PLAN_H__


#include "MengeCore/mengeCommon.h"
#include "MengeCore/OperationPlan/OperationPlan.h"
#include "MengeCore/OperationPlan/OperationPlanFactory.h"
#include "MengeCore/Math/geomQuery.h"

#include "HelbingPlugin.h"
#include "HelbingPluginConfig.h"

#define PLUGCLASS OperationHelbingPlug
#define FACTORYPLUGCLASS OperationHelbingPlugFactory
#define PLUGNAME "helbingPlug"


namespace Menge {

	namespace Agents {
		/*!
		 *	@brief		An initial state selector that stores a single state
		 *				and assigns that state to all agents.
		 */
		class  PLUGCLASS : public OperationPlan {
		public:
			/*!
			*	@brief		Constructor.
			*/
			PLUGCLASS();

			/*!
			*  @brief      Computes the new velocity of this agent.
			*/
			void computeNewVelocity(float);
			

			Menge::Math::Vector2 agentForce(const Menge::Agents::BaseAgent * other) const;

			Menge::Math::Vector2 obstacleForce(const Menge::Agents::Obstacle * obst) const;

			Menge::Math::Vector2 drivingForce() const;

			float _mass=80;



			virtual std::string getPlan() { return _planName; }
			void setPlanName(const std::string & name) { _planName = name; }
			virtual void initAgentInfo() const;
		protected:
			std::string _planName;
			float	AGENT_SCALE = 4000.f;
			float	OBST_SCALE = 2000.f;
			float	REACTION_TIME = 0.2f;
			float	BODY_FORCE = 1200.f;
			float	FRICTION = 2400.f;
			float	FORCE_DISTANCE = 0.02f;
		};
	
		class  FACTORYPLUGCLASS : public OperationPlanFactory {
		public:
			/*!
			*	@brief		Constructor
			*/
			FACTORYPLUGCLASS();


			virtual const char * name() const { return PLUGNAME; }

			virtual const char * description() const {
				return PLUGNAME;
			};

		protected:

			PLUGCLASS * instance() const { return new PLUGCLASS(); }


			virtual bool setFromXML(PLUGCLASS * sel, TiXmlElement * node,
				const std::string & specFldr) const;
			size_t _nameID;
		};

	}	// namespace Agents
}	// namespace Menge
#endif	