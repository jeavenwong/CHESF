

#include "NewObstacle.h"
#include "MengeCore\Agents\BaseAgent.h"


namespace Menge {

	namespace Agents {

		////////////////////////////////////////////////////////////////////////////
		//			Implementation of ConstProfileSelectorFactory
		////////////////////////////////////////////////////////////////////////////
		bool  PLUGCLASS::getEnvironmentalChange(std::map<int, Menge::Agents::Connection >  &connectionMapTemp,
												std::map<int, Menge::Agents::Path > & pathMapTemp,
												std::vector<BaseAgent*> &agents,
			Menge::Agents::ObstacleSet **ob,
												float _globalTime
			) const {
			bool isChanged = false;
			if (_globalTime >= _time && _globalTime < _time + 1) {
				*ob = _obSet;
				isChanged = true;
			}
			//enable = !isChanged;
			return isChanged;
		}
		std::vector<Menge::Math::Vector2>  PLUGCLASS::getVisVertex() {
			std::vector<Menge::Math::Vector2> visVertex;

			return visVertex;
		}
		FACTORYPLUGCLASS::FACTORYPLUGCLASS() : EnvironmentalChangeFactory() {
			//_name = _attrSet.addStringAttribute("type", true, "");
			//_time = _attrSet.addSizeTAttribute( "time", true, 0 );
			//_closedMapID = _attrSet.addSizeTAttribute("closedMapID", true, 0);
		}

		////////////////////////////////////////////////////////////////////////////

		bool FACTORYPLUGCLASS::setFromXML(EnvironmentalChange * sel, TiXmlElement * node,
													const std::string & specFldr ) const {
			PLUGCLASS * mChange = dynamic_cast< PLUGCLASS * >(sel);
			assert(mChange != 0x0 && "Trying to set attributes of a const state selector element on "
					"an incompatible object" );
			////这里可以添加一些必要的参数
			//if ( !EnvironmentalChangeFactory::setFromXML(mChange, node, specFldr ) ) return false;
			//mChange->setName( _attrSet.getString( _name ) );
			//mChange->setTime(_attrSet.getSizeT(_time));
			//mChange->setClosedMapID(_attrSet.getSizeT(_closedMapID));
			return true;
		}
	}	// namespace Agents
}	// namespace Menge

extern "C" {

	NewObstacleChange_API	Menge::Agents::EnvironmentalChangeFactory * Export(void) {
		
		return new Menge::Agents::FACTORYPLUGCLASS();

	}

}