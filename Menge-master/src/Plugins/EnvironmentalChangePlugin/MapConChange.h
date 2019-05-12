

#ifndef __MapCon_Change_H__
#define __MapCon_Change_H__

#include "MengeCore/mengeCommon.h"
#include "MengeCore/EnvironmentalChange/EnvironmentalChange.h"
#include "MengeCore/EnvironmentalChange/EnvironmentalChangeFactory.h"
#include "MapConChangeConfig.h"

#define PLUGCLASS MapConChange
#define FACTORYPLUGCLASS MapConChangeFactory
#define PLUGNAME "MapCon"


namespace Menge {

	namespace Agents {
		/*!
		 *	@brief		An initial state selector that stores a single state
		 *				and assigns that state to all agents.
		 */
		class PLUGCLASS : public EnvironmentalChange {
		public:
			/*!
			 *	@brief		Constructor.
			 */
			PLUGCLASS() : _name(PLUGNAME) {
				_time = 15;
				_closedMapID = 4;

				ExplicitObstacleSet * eSet = new ExplicitObstacleSet();//障碍物集合
				eSet->setClass(1);//2虚或1实

				ObstacleVertexList vlist;
				vlist.closed = 1;
				vlist.vertices.push_back(Vector2(4,-16));
				vlist.vertices.push_back(Vector2(8, -16));
				eSet->addObstacle(vlist);
				_obSet = eSet;

			}

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
			void setClosedMapID(const std::size_t & mapId) { _closedMapID = mapId; }
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
			size_t _closedMapID;
		};

		//////////////////////////////////////////////////////////////////////////////

		/*!
		 *	@brief		The factory for the ConstStateSelector.
		 */
		class  FACTORYPLUGCLASS : public EnvironmentalChangeFactory {
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

			EnvironmentalChange * instance() const { return new PLUGCLASS(); }


			virtual bool setFromXML( EnvironmentalChange * sel, TiXmlElement * node,
									 const std::string & specFldr ) const;

			size_t _name;
			size_t _time;
			size_t _closedMapID;

		};

	}	// namespace Agents
}	// namespace Menge
#endif	// __CONST_STATE_SELECTOR_H__
