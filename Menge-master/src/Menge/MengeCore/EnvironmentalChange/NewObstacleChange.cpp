

#include "MengeCore/EnvironmentalChange/NewObstacleChange.h"
#include "MengeCore/Agents/BaseAgent.h"
#include "MengeVis/SceneGraph/shapes.h"
#include "GL/gl.h"

namespace Menge {

	namespace Agents {

		////////////////////////////////////////////////////////////////////////////
		//			Implementation of ConstProfileSelectorFactory
		////////////////////////////////////////////////////////////////////////////
		bool  NewObstacleChange::getEnvironmentalChange(std::map<int, Menge::Agents::Connection >  &connectionMapTemp,
												std::map<int, Menge::Agents::Path > & pathMapTemp,
												std::vector<BaseAgent*> &agents,
			Menge::Agents::ObstacleSet **ob,
												float _globalTime
			) const {
			bool isChanged = false;
			if (_globalTime >= _time && _globalTime < _time + 1) {		
				*ob  = _obSet;
				isChanged = true;
			}
			enable = !isChanged;
			return isChanged;
		}

		std::vector<Menge::Math::Vector2>  NewObstacleChange::getVisVertex() {
			std::vector<Menge::Math::Vector2> visVertex;
			
			return visVertex;
		}

		NewObstacleChangeFactory::NewObstacleChangeFactory() : EnvironmentalChangeFactory() {
			//这里是记录个属性名称的位置信息
			_name = _attrSet.addStringAttribute("type", true, "");
			_time = _attrSet.addSizeTAttribute( "time", true, 0 );
			//_closedMapID = _attrSet.addSizeTAttribute("closedMapID", true, 0);
		}

		////////////////////////////////////////////////////////////////////////////

		bool NewObstacleChangeFactory::setFromXML(EnvironmentalChange * sel, TiXmlElement * node,
													const std::string & specFldr ) const {
			NewObstacleChange * mChange = dynamic_cast< NewObstacleChange * >( sel );
			assert(mChange != 0x0 && "Trying to set attributes of a const state selector element on "
					"an incompatible object" );
			//这里可以添加一些必要的参数 根据上面记录的位置信息查找 属性值
			if ( !EnvironmentalChangeFactory::setFromXML(mChange, node, specFldr ) ) return false;
			

			for (TiXmlElement * child = node->FirstChildElement();
				child;
				child = child->NextSiblingElement()) {
				if (child->ValueStr() == "ObstacleSet") {
					try {
						//pass through, try to get a generator, and then use it
						 _obSet = ObstacleSetDB::getInstance(child, specFldr);
						if (_obSet == 0x0) {
							logger << Logger::ERR_MSG << "Unable to instantiate obstacle set specifcation on "
								"line " << node->Row() << ".";
							return false;
						}
						else {
							//_sim->setSpatialQuery( spQuery );
							size_t index = 0;
							for (; index < _obSet->obstacleCount(); ++index) {
								//_sim->getSpatialQuery()->addObstacle(obSet->getObstacle(index));
							}

							
							//obSet->destroy();
							//return true;
						}
					}
					catch (ObstacleSetException) {
						return false;
					}
				}
				else {
					logger << Logger::WARN_MSG << "Found an unexpected child tag in an "
						"ObstacleSet on line " << node->Row() << ".  Ignoring the tag: ";
					logger << child->ValueStr() << ".";
				}
			}



			mChange->setName( _attrSet.getString( _name ) );
			mChange->setTime(_attrSet.getSizeT(_time));
			mChange->setObstacleSet(_obSet);

			//mChange->setClosedMapID(_attrSet.getSizeT(_closedMapID));
			return true;
		}


		ObstacleVertexList NewObstacleChangeFactory::parseObstacle(TiXmlElement * node) const {

			int iVal;
			ObstacleVertexList vList;
			vList.closed = false;
			if (node->Attribute("closed", &iVal)) {
				vList.closed = (iVal != 0);
			}

			if (!vList.closed) {
				logger << Logger::ERR_MSG << "This version of Menge does not support open "
					"obstacles.  Obstacle on line " << node->Row() << " is declared to be open.\n";
				throw ObstacleSetFatalException("Unsupported open obstacles");
			}

			double dVal;
			bool valid = true;

			for (TiXmlElement * vert = node->FirstChildElement();
				vert;
				vert = vert->NextSiblingElement()) {
				if (vert->ValueStr() == "Vertex") {
					float p_x = 0;
					float p_y = 0;
					if (vert->Attribute("p_x", &dVal)) {
						p_x = (float)dVal;
					}
					else {
						valid = false;
					}
					if (vert->Attribute("p_y", &dVal)) {
						p_y = (float)dVal;
					}
					else {
						valid = false;
					}

					if (!valid) {
						logger << Logger::ERR_MSG << "Obstacle vertex on line " << vert->Row();
						logger << " is missing the full x- and y-position specification.";
						throw ObstacleSetFatalException("Obstacle vertex missing full "
							"specification");

					}
					vList.vertices.push_back(Vector2(p_x, p_y));
				}
				else {
					logger << Logger::WARN_MSG << "Encountered unexpected tag inside an obstacle "
						"definition on line " << vert->Row() << ": " << vert->ValueStr() << ".  "
						"It will be ignored.";
				}

				if (!valid) {
					logger << Logger::ERR_MSG << "Incomplete obstacle definition on line ";
					logger << node->Row() << ".";
					throw ObstacleSetFatalException("Incomplete obstacle definition");
				}
			}

			return vList;
		};
	}	// namespace Agents
}	// namespace Menge
