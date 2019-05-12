

#include "MengeCore/EnvironmentalChange/MapChange.h"
#include "MengeCore\Agents\BaseAgent.h"


namespace Menge {

	namespace Agents {

		////////////////////////////////////////////////////////////////////////////
		//			Implementation of ConstProfileSelectorFactory
		////////////////////////////////////////////////////////////////////////////
		bool  MapChange::getEnvironmentalChange(std::map<int, Menge::Agents::Connection >  &connectionMapTemp,
												std::map<int, Menge::Agents::Path > & pathMapTemp,
												std::vector<BaseAgent*> &agents,
			Menge::Agents::ObstacleSet **ob,
												float _globalTime
			) const {
			//如果形参 不带 &，则是值传递，不对实参产生影响
			bool isChanged=false;
			if (_globalTime >= _time && _globalTime < _time+1) {
				//将区域3设为事故区域 在这一时刻关闭4号门
				//遍历connectionMap和pathMap，去除4号门相关的信息
				isChanged = true;
				int cCount = connectionMapTemp.size();
				int pCount = pathMapTemp.size();
				for (int c = 1; c <= cCount; c++) {
					if (connectionMapTemp[c].id == _closedMapID) {
						connectionMapTemp[c].open = 0;
						break;
					}
				}
				for (int p = 1; p <= pCount; p++) {
					if (pathMapTemp[p].fromConID == _closedMapID || 
						pathMapTemp[p].toConID == _closedMapID) {
						for (int i = p; i < pCount; i++) {
							pathMapTemp[i] = pathMapTemp[i + 1];
						}
						pathMapTemp.erase(pCount);
						pCount--;
						p--;
					}
				}
			}
			if (isChanged) {
				for (int i = 0; i < agents.size();i++) {
					BaseAgent * a=(Menge::Agents::BaseAgent *)agents[i];
					a->_needRePlan = true;				
				}
			}
			enable = !isChanged;
			return isChanged;
		}
		std::vector<Menge::Math::Vector2>  MapChange::getVisVertex() {
			std::vector<Menge::Math::Vector2> visVertex;

			return visVertex;
		}

		MapChangeFactory::MapChangeFactory() : EnvironmentalChangeFactory() {
			_name = _attrSet.addStringAttribute("type", true, "");
			_time = _attrSet.addSizeTAttribute( "time", true, 0 );
			_closedMapID = _attrSet.addSizeTAttribute("closedMapID", true, 0);
		}

		////////////////////////////////////////////////////////////////////////////

		bool MapChangeFactory::setFromXML(EnvironmentalChange * sel, TiXmlElement * node,
													const std::string & specFldr ) const {
			MapChange * mChange = dynamic_cast< MapChange * >( sel );
			assert(mChange != 0x0 && "Trying to set attributes of a const state selector element on "
					"an incompatible object" );
			//这里可以添加一些必要的参数
			if ( !EnvironmentalChangeFactory::setFromXML(mChange, node, specFldr ) ) return false;
			mChange->setName( _attrSet.getString( _name ) );
			mChange->setTime(_attrSet.getSizeT(_time));
			mChange->setClosedMapID(_attrSet.getSizeT(_closedMapID));
			return true;
		}
	}	// namespace Agents
}	// namespace Menge
