

#ifndef __OperationFollow_PLAN_H__
#define __OperationFollow_PLAN_H__

#include "MengeCore/mengeCommon.h"
#include "MengeCore/OperationPlan/OperationPlan.h"
#include "MengeCore/OperationPlan/OperationPlanFactory.h"
#include "MengeCore/OperationPlan/OperationPlanAgent.h"
#include "MengeCore/Math/Line.h"


namespace Menge {

	namespace Agents {
		/*!
		 *	@brief		An initial state selector that stores a single state
		 *				and assigns that state to all agents.
		 */
		class MENGE_API OperationORCAPlan : public OperationPlan {
		public:
			/*!
			 *	@brief		Constructor.
			 */
			OperationORCAPlan();



			/*!
			*  @brief      Computes the new velocity of this agent.
			*/
			void computeNewVelocity(float);
			/*!

			*	@brief			Based on the neighbors, computes the ORCA lines
			*
			*	@returns		The total number of obstacle lines
			*/
			size_t computeORCALines();

			/*!
			*	@brief		The time horizon for agent-obstacle interactions.
			*/
			/*!
			*	@brief		The set of ORCA constraints.
			*/
			std::vector<Menge::Math::Line> _orcaLines;

			/*!
			*	@brief		The time horizon for inter-agent interactions.
			*/
			float _timeHorizon;
			/*!
			*	@brief		The time horizon for agent-obstacle interactions.
			*/
			float _timeHorizonObst;

			// DEFAULT VALUES FOR THE AGENT PARAMTERS
			/*!
			*	@brief		The default time horizon for inter-agent interactions.
			*/
			static const float TAU;

			/*!
			*	@brief		The default time horizon for agent-obstacle interactions.
			*/
			static const float TAU_OBST;

			/*! @brief	The name identifier for this agent type. */
			static const std::string NAME;

			virtual std::string getPlan() { return _planName; }


			void setPlanName( const std::string & name ) { _planName = name; }
			virtual void initAgentInfo() const;


		protected:
			/*!
			*	@brief		Constructs an ORCA line for the given obstacle
			*				under the assumption that the agent is on its right side.
			*				If appropriate, it adds the obstacle to the set of orca lines.
			*
			*	@param		obstNbrID		The index of the near-by obstacle to test.
			*	@param		invTau			1 / _timeHorizonObst - the inverse of the
			*								time horizon for obstacles.
			*	@param		flip			The agent is on the left side of this obstacle.
			*/
			void obstacleLine(size_t obstNbrID, const float invTau, bool flip);
			
			/*!
			 *	@brief		The name of the profile to use.
			 */
			std::string _planName;

		};

		/*!
		*  @brief      Solves a one-dimensional linear program on a specified line
		*              subject to linear constraints defined by lines and a circular
		*              constraint.
		*
		*  @param      lines         Lines defining the linear constraints.
		*  @param      lineNo        The specified line constraint.
		*  @param      radius        The radius of the circular constraint.
		*  @param      optVelocity   The optimization velocity.
		*  @param      directionOpt  True if the direction should be optimized.
		*  @param      result        A reference to the result of the linear program.
		*  @returns    True if successful.
		*/
		bool linearProgram1(const std::vector<Menge::Math::Line>& lines, size_t lineNo,
			float radius, const Menge::Math::Vector2 & optVelocity,
			bool directionOpt, Menge::Math::Vector2& result);

		/*!
		*  @brief      Solves a two-dimensional linear program subject to linear
		*              constraints defined by lines and a circular constraint.
		*
		*  @param      lines         Lines defining the linear constraints.
		*  @param      radius        The radius of the circular constraint.
		*  @param      optVelocity   The optimization velocity.
		*  @param      directionOpt  True if the direction should be optimized.
		*  @param      result        A reference to the result of the linear program.
		*  @returns    The number of the line it fails on, and the number of lines if successful.
		*/
		size_t linearProgram2(const std::vector<Menge::Math::Line>& lines, float radius,
			const Menge::Math::Vector2& optVelocity, bool directionOpt,
			Menge::Math::Vector2& result);

		/*!
		*  @brief      Solves a two-dimensional linear program subject to linear
		*              constraints defined by lines and a circular constraint.
		*
		*  @param      lines         Lines defining the linear constraints.
		*  @param      numObstLines  Count of obstacle lines.
		*  @param      beginLine     The line on which the 2-d linear program failed.
		*  @param      radius        The radius of the circular constraint.
		*  @param      result        A reference to the result of the linear program.
		*/
		void linearProgram3(const std::vector<Menge::Math::Line>& lines, size_t numObstLines,
			size_t beginLine, float radius, Menge::Math::Vector2& result);


		//////////////////////////////////////////////////////////////////////////////

		/*!
		 *	@brief		The factory for the ConstStateSelector.
		 */
		class MENGE_API OperationORCAPlanFactory : public OperationPlanFactory {
		public:
			/*!
			 *	@brief		Constructor
			 */
			OperationORCAPlanFactory();


			virtual const char * name() const { return "orca"; }

			virtual const char * description() const {
				return "orca";
			};

		protected:

			OperationORCAPlan * instance() const { return new OperationORCAPlan(); }


			virtual bool setFromXML(OperationPlan * sel, TiXmlElement * node,
									 const std::string & specFldr ) const;

			size_t _nameID;
		};

	}	// namespace Agents
}	// namespace Menge
#endif	// __CONST_STATE_SELECTOR_H__
