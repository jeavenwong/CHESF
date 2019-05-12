

#include "MengeCore/EnvironmentalChange/SpecialAreaChange.h"
#include "MengeCore/Agents/BaseAgent.h"
#include "MengeVis/SceneGraph/shapes.h"
#include "GL/gl.h"
namespace Menge {

	namespace Agents {

		////////////////////////////////////////////////////////////////////////////
		//			Implementation of ConstProfileSelectorFactory
		////////////////////////////////////////////////////////////////////////////
		bool  SpecialAreaChange::getEnvironmentalChange(std::map<int, Menge::Agents::Connection >  &connectionMapTemp,
												std::map<int, Menge::Agents::Path > & pathMapTemp,
												std::vector<BaseAgent*> &agents,
			Menge::Agents::ObstacleSet **ob,
												float _globalTime
			) const {

			if (_globalTime >= _time) {
				_show = true;
				for (int i = 0; i < agents.size(); i++) {
					//����agent �����ڷ�Χ�ڵ���Ⱥ
					float dis = _center.distance(agents[i]->_pos);
					if (dis <= _radius) {
						if (agents[i]->_maxSpeedOriginal == -1 && agents[i]->_maxSpeed != -1) {
							agents[i]->_maxSpeedOriginal = agents[i]->_maxSpeed;//ֻ����һ��
						}

						agents[i]->_maxSpeed = agents[i]->_maxSpeedOriginal*0.3;
					}
					else {
						if (agents[i]->_maxSpeedOriginal > 0)
							agents[i]->_maxSpeed = agents[i]->_maxSpeedOriginal;
					}

				}
				return true;
			}
			return false;
		}

		 std::vector<Menge::Math::Vector2>  SpecialAreaChange::getVisVertex() {
			 std::vector<Menge::Math::Vector2> visVertex;
			 if (_show) {
				 const GLfloat pi = 3.1415926f;
				 const int n = 50;//��nΪ3ʱΪ�����Σ�nΪ4ʱ���ı��Σ�nΪ5ʱΪ����Ρ���������
				 const GLfloat R = _radius;//Բ�İ뾶
				 for (int i = 0; i < n; i++)
				 {
					 Vector2 temp(_center._x + (R*cos(2 * pi / n*i)), _center._y + (R*sin(2 * pi / n*i)));
					 visVertex.push_back(temp);
				 }
				
			 }
			 return visVertex;
		}


		SpecialAreaChangeFactory::SpecialAreaChangeFactory() : EnvironmentalChangeFactory() {
			//�����Ǽ�¼���������Ƶ�λ����Ϣ
			_name = _attrSet.addStringAttribute("type", true, "");
			_time = _attrSet.addSizeTAttribute( "time", true, 0 );
			_center_X = _attrSet.addFloatAttribute("center_x", true, 0.f);
			_center_Y = _attrSet.addFloatAttribute("center_y", true, 0.f);
			_radius = _attrSet.addFloatAttribute("radius", true, 0.f);
			//_closedMapID = _attrSet.addSizeTAttribute("closedMapID", true, 0);
		}

		////////////////////////////////////////////////////////////////////////////

		bool SpecialAreaChangeFactory::setFromXML(EnvironmentalChange * sel, TiXmlElement * node,
													const std::string & specFldr ) const {
			SpecialAreaChange * mChange = dynamic_cast< SpecialAreaChange * >( sel );
			assert(mChange != 0x0 && "Trying to set attributes of a const state selector element on "
					"an incompatible object" );
			//����������һЩ��Ҫ�Ĳ��� ���������¼��λ����Ϣ���� ����ֵ
			if ( !EnvironmentalChangeFactory::setFromXML(mChange, node, specFldr ) ) return false;
			mChange->setName( _attrSet.getString( _name ) );
			mChange->setTime(_attrSet.getSizeT(_time));
			mChange->setCenter(Vector2(_attrSet.getFloat(_center_X), _attrSet.getFloat(_center_Y)));
			mChange->setRadius(_attrSet.getFloat(_radius));

			//mChange->setClosedMapID(_attrSet.getSizeT(_closedMapID));
			return true;
		}
	}	// namespace Agents
}	// namespace Menge
