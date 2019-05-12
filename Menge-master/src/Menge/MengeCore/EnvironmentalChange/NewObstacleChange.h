

#ifndef __NewObstacle_Change_H__
#define __NewObstacle_Change_H__

#include "MengeCore/mengeCommon.h"
#include "MengeCore/EnvironmentalChange/EnvironmentalChange.h"
#include "MengeCore/EnvironmentalChange/EnvironmentalChangeFactory.h"

namespace Menge {

	namespace Agents {
		/*!
		 *	@brief		An initial state selector that stores a single state
		 *				and assigns that state to all agents.
		 */
		class MENGE_API NewObstacleChange : public EnvironmentalChange {
		public:
			/*!
			 *	@brief		Constructor.
			 */
			NewObstacleChange() : _name("NewObstacle") {}

			/*!
			 *	@brief		Provides the name of a state.
			 *
			 *	Ths must be overriden by child classes.
			 *
			 *	@returns:		The name of the state.
			 */
			virtual std::string getName() { return _name; }

			/*!
			 *	@brief		Sets the name of the state.
			 *
			 *	@param		name		The name of the selector's state.
			 */
			void setName( const std::string & name ) { _name = name; }
			void setTime(const std::size_t & time) { _time = time; }
			void setObstacleSet(ObstacleSet * obSet) { _obSet = obSet; }
			//void setSpecialArea(const std::size_t & mapId) { _closedMapID = mapId; }
			virtual bool  getEnvironmentalChange(std::map<int, Menge::Agents::Connection > & connectionMapTemp,
												 std::map<int, Menge::Agents::Path > & pathMapTemp,
												 std::vector<BaseAgent*> &agents,
				Menge::Agents::ObstacleSet **ob,
												 float _globalTime													   
			) const;

			virtual std::vector<Menge::Math::Vector2> getVisVertex();
		protected:
			/*!
			 *	@brief		The name of the profile to use.
			 */
			std::string _name;
			size_t _time;
			//ObstacleSet * _obSet;
			
		};

		//////////////////////////////////////////////////////////////////////////////

		/*!
		 *	@brief		The factory for the ConstStateSelector.
		 */
		class MENGE_API NewObstacleChangeFactory : public EnvironmentalChangeFactory {
		public:
			/*!
			 *	@brief		Constructor
			 */
			NewObstacleChangeFactory();


			virtual const char * name() const { return "NewObstacle"; }

			virtual const char * description() const {
				return "Map--EnvironmentalChange";
			};

			

		protected:

			EnvironmentalChange * instance() const { return new NewObstacleChange(); }


			virtual bool setFromXML( EnvironmentalChange * sel, TiXmlElement * node,
									 const std::string & specFldr ) const;
			ObstacleVertexList parseObstacle(TiXmlElement * node) const;
			size_t _name;
			size_t _time;
			mutable ObstacleSet * _obSet;

		};

	}	// namespace Agents
}	// namespace Menge
#endif	// __CONST_STATE_SELECTOR_H__
