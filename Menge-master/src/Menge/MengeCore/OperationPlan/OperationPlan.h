
#ifndef __OperationPlan_H__
#define	__OperationPlan_H__


#include "MengeCore/mengeCommon.h"
#include "MengeCore/PluginEngine/Element.h"
#include "MengeCore/Agents/BaseAgent.h"

namespace Menge {

	namespace Agents {
		// forward declaration
		class BaseAgent;

		/*!
		 *	@brief		Exception class for state selector computation.
		 */
		class MENGE_API OperationPlanException : public virtual MengeException {
		public:
			/*!
			 *	@brief		Default constructor.
			 */
			OperationPlanException() : MengeException() {}

			/*!
			 *	@brief		Constructor with message.
			 *
			 *	@param		s		The exception-specific message.
			 */
			OperationPlanException( const std::string & s ): MengeException(s) {}
		};

		/*!
		 *	@brief		The fatal state selector exception.
		 */
		class MENGE_API OperationPlanFatalException : public OperationPlanException,
													  public MengeFatalException {
		public:
			/*!
			 *	@brief		Default constructor.
			 */
			OperationPlanFatalException() : MengeException(), OperationPlanException(),
											MengeFatalException() {}

			/*!
			 *	@brief		Constructor with message.
			 *
			 *	@param		s		The exception-specific message.
			 */
			OperationPlanFatalException( const std::string & s ): MengeException(s),
				                                                 OperationPlanException(),
																  MengeFatalException() {}
		};




		class MENGE_API OperationPlan : public Element {
		public:
			/*!
			 *	@brief		Constructor
			 */
			OperationPlan();
			BaseAgent * _baseAgent;
			
		protected:
			/*!
			 *	@brief		Virtual destructor.
			 */
			virtual ~OperationPlan();

		public:
			/*!
			 *	@brief		Provides the name of a plan.
			 *
			 *	Ths must be overriden by child classes.
			 *
			 *	@returns:		The name of the plan.
			 */
			virtual std::string getPlan() = 0;
			virtual void initAgentInfo() const = 0;
			virtual void computeNewVelocity(float)=0;
			
		};

	} // namespace Agents
}	// namespace Menge
#endif // __STATE_SELECTOR_H__
