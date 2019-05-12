/*

License

Menge
Copyright ?and trademark ?2012-14 University of North Carolina at Chapel Hill. 
All rights reserved.

Permission to use, copy, modify, and distribute this software and its documentation 
for educational, research, and non-profit purposes, without fee, and without a 
written agreement is hereby granted, provided that the above copyright notice, 
this paragraph, and the following four paragraphs appear in all copies.

This software program and documentation are copyrighted by the University of North 
Carolina at Chapel Hill. The software program and documentation are supplied "as is," 
without any accompanying services from the University of North Carolina at Chapel 
Hill or the authors. The University of North Carolina at Chapel Hill and the 
authors do not warrant that the operation of the program will be uninterrupted 
or error-free. The end-user understands that the program was developed for research 
purposes and is advised not to rely exclusively on the program for any reason.

IN NO EVENT SHALL THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL OR THE AUTHORS 
BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL 
DAMAGES, INCLUDING LOST PROFITS, ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS 
DOCUMENTATION, EVEN IF THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL OR THE 
AUTHORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL AND THE AUTHORS SPECIFICALLY 
DISCLAIM ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE AND ANY STATUTORY WARRANTY 
OF NON-INFRINGEMENT. THE SOFTWARE PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND 
THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL AND THE AUTHORS HAVE NO OBLIGATIONS 
TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

Any questions or comments should be sent to the authors {menge,geom}@cs.unc.edu

*/

#include "MengeCore/GlobalPlan/FloydGlobalPlan.h"



namespace Menge {

	namespace Agents {

		////////////////////////////////////////////////////////////////////////////
		//			Implementation of ConstProfileSelectorFactory
		////////////////////////////////////////////////////////////////////////////
	    std::vector<Menge::Math::Vector2>  FloydGlobalPlan::getGlobalPlan(std::map<int, Menge::Agents::Connection > connectionMapTemp,
																			 std::map<int, Menge::Agents::Path > pathMapTemp,
																			 std::vector<Agents::Map *> _maps,
																			 Math::Vector2 agentPos,
																			 int id
			) const {
		   //给_agents中的某个Agent全局规划
			//map<int, Menge::Agents::Connection > connectionMapTemp(_connectionMap);
			//map<int, Menge::Agents::Path > pathMapTemp(_pathMap);

			int vexnum = 0;
			int edge = 0;
			vexnum = connectionMapTemp.size();//maps.size();//图中结点的个数 为 场景中 门 的个数
			edge = pathMapTemp.size();//图中边的个数为场景中相邻门直接的路的个数

									  //根据Agent当前位置添加一个 新的结点 
			Menge::Agents::Connection agent;
			agent.pos = agentPos;
			agent.id = ++vexnum;
			connectionMapTemp[agent.id] = agent;
			//再添加 Agent所在的Map中的门 与Agent的位置 为起止点的 path
			//int mapIndex = findAgentInMap(agentPos.pos,_maps);
			for (int m = 0; m < _maps.size(); m++) {
				bool inMap = _maps[m]->pointInMap(agent.pos);
				if (inMap) {
					//_agents[agentIndex].currentMapID = _maps[m]->_id;
					for (int c = 0; c < _maps[m]->_connections.size(); c++) {
						if (!_maps[m]->_connections[c].open) continue;
						Menge::Agents::Path agentPathToConnection;
						agentPathToConnection.fromConID = vexnum;
						agentPathToConnection.toConID = _maps[m]->_connections[c].id;
						agentPathToConnection.dis = agent.pos.distance(_maps[m]->_connections[c].pos);//两点间的距离
						pathMapTemp[++edge] = agentPathToConnection;
						//edge++;
					}
					break;
				}
			}

			Graph_DG_floyd graph(connectionMapTemp.size(), pathMapTemp.size());
			graph.createGraph(pathMapTemp);
			//graph.print();
			graph.Floyd(connectionMapTemp);
			//graph.print_path();
			//计算Agent到各个门的距离
			//graph.print_path(vexnum);

			//最短路线已经保存，要筛选 包含出口的最短路线
			//确定哪些是出口
			int minDis = INT_MAX;
			std::vector<Math::Vector2> plan;
			for (int v = 1; v <= vexnum; v++) {
				if (connectionMapTemp[v].nextMapId == -1) {
					// -1表示 这里是出口（安全区）
					int tempDis = graph.getPathDis(v-1);
					if (tempDis < minDis) {
						plan = graph.getPathPoint(v - 1);
						minDis = tempDis;
					}
				}
			}

			return plan;
		}
		void FloydGlobalPlan::initAgentInfo(std::vector<Agents::Map *> _maps,  std::vector<BaseAgent *> agents
		) const {
		
		}
		FloydGlobalPlanFactory::FloydGlobalPlanFactory() : GlobalPlanFactory() {
			_nameID = _attrSet.addStringAttribute( "type", true, "" );
		}

		////////////////////////////////////////////////////////////////////////////

		bool FloydGlobalPlanFactory::setFromXML(GlobalPlan * sel, TiXmlElement * node,
													const std::string & specFldr ) const {
			FloydGlobalPlan * dGP = dynamic_cast< FloydGlobalPlan * >( sel );
			assert(dGP != 0x0 && "Trying to set attributes of a const state selector element on "
					"an incompatible object" );
			//这里可以添加一些必要的参数
			if ( !GlobalPlanFactory::setFromXML(dGP, node, specFldr ) ) return false;
			dGP->setPlanName( _attrSet.getString( _nameID ) );

			return true;
		}
	}	// namespace Agents
}	// namespace Menge
