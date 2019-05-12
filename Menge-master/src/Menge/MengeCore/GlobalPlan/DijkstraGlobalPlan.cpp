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

#include "MengeCore/GlobalPlan/DijkstraGlobalPlan.h"



namespace Menge {

	namespace Agents {

		////////////////////////////////////////////////////////////////////////////
		//			Implementation of ConstProfileSelectorFactory
		////////////////////////////////////////////////////////////////////////////
	    std::vector<Menge::Math::Vector2>  DijkstraGlobalPlan::getGlobalPlan(std::map<int, Menge::Agents::Connection > connectionMapTemp,
																			 std::map<int, Menge::Agents::Path > pathMapTemp,
																			 std::vector<Agents::Map *> _maps,
																			 Math::Vector2 agentPos,
																			 int id
			) const {
			//��_agents�е�ĳ��Agentȫ�ֹ滮
			//map<int, Menge::Agents::Connection > connectionMapTemp(_connectionMap);
			//map<int, Menge::Agents::Path > pathMapTemp(_pathMap);

			//GlobalPlanAgent * currAgent = new GlobalPlanAgent();
			//currAgent->_id = id;
			//currAgent->_maps = _maps;
			////std::map<int, GlobalPlanAgent*> globalPlanAgents;
			//_globalPlanAgents.insert(std::pair<int, GlobalPlanAgent*>(currAgent->_id,currAgent));

			//����id�ҵ���Ӧ�����ݣ��ж����¹滮
			map<int, GlobalPlanAgent*>::iterator iter;
			iter = _globalPlanAgents.find(id);
			if (iter != _globalPlanAgents.end())
			{
				//����Agent�Ļ�����Ϥ�� �����Ƿ�Ҫȫ�ֹ滮
				if (iter->second->_environmentFamiliarity == 2) {
					//���˸���Ϥ�ȵ��ˣ�������ȫ�ֹ滮

					int vexnum = 0;
					int edge = 0;
					vexnum = connectionMapTemp.size();//maps.size();//ͼ�н��ĸ��� Ϊ ������ �� �ĸ���
					edge = pathMapTemp.size();//ͼ�бߵĸ���Ϊ������������ֱ�ӵ�·�ĸ���

											  //����Agent��ǰλ�����һ�� �µĽ�� 
					Menge::Agents::Connection agent;
					agent.pos = agentPos;
					agent.id = ++vexnum;
					connectionMapTemp[agent.id] = agent;
					//����� Agent���ڵ�Map�е��� ��Agent��λ�� Ϊ��ֹ��� path
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
								agentPathToConnection.dis = agent.pos.distance(_maps[m]->_connections[c].pos);//�����ľ���
								pathMapTemp[++edge] = agentPathToConnection;
								//edge++;
							}
							break;
						}
					}

					Graph_DG_dijkstra graph(connectionMapTemp.size(), pathMapTemp.size());
					graph.createGraph(pathMapTemp);
					//graph.print();
					graph.Dijkstra(vexnum, connectionMapTemp);
					//����Agent�������ŵľ���
					//graph.print_path(vexnum);

					//���·���Ѿ����棬Ҫɸѡ �������ڵ����·��
					//ȷ����Щ�ǳ���
					int minDis = INT_MAX;
					std::vector<Math::Vector2> plan;
					for (int v = 1; v <= vexnum; v++) {
						if (connectionMapTemp[v].nextMapId == -1) {
							// -1��ʾ �����ǳ��ڣ���ȫ����
							int tempDis = graph.getPathDis(v - 1);
							if (tempDis < minDis) {
								plan = graph.getPathPoint(v - 1);
								minDis = tempDis;
							}
						}
					}

					return plan;

				}
			}
			return  std::vector<Math::Vector2>();
		}


		void  DijkstraGlobalPlan::initAgentInfo(std::vector<Agents::Map *> _maps,
			                                    std::vector<BaseAgent *> agents
		) const {
		
				//����_agents ��������agent���ھ�id��Ϣ����ÿ��Agent���õ�ͼ��Ϣ
			for (size_t i = 0; i < agents.size(); i++) {
				GlobalPlanAgent * currAgent = new GlobalPlanAgent();
				currAgent->_id = agents[i]->_id;
				//currAgent->_maps = _maps;
				agents[i]->_maps = _maps;
				//std::map<int, GlobalPlanAgent*> globalPlanAgents;

				//��ʼ��Agent�Ļ������Զ�
				int familiarityCount = 0;
				const int mapsSize = _maps.size();
				for each (bool var in agents[i]->environmentFamiliaritySet)
				{
					if (var)familiarityCount++;
				}

				if (familiarityCount == 0) {
					currAgent->_environmentFamiliarity = 0;
				}
				else if (familiarityCount == mapsSize)
				{
					agents[i]->_needRePlan = true;
					currAgent->_environmentFamiliarity = 2;
				}
				else
				{
					currAgent->_environmentFamiliarity = 1;
				}
				//currAgent->_needRePlan = true;
				//computeNeighbors(currAgent);
				agents[i]->_groupAgents.clear();
				//currAgent->_influence = (rand() % 4);	//��ʼ��Ӱ����,���[0,9]

				//�Ի�����Ϥ��Ϊ �Ŷ�Ӱ����
				//currAgent->_influence = currAgent->_environmentFamiliarity;

				for (size_t j = 0; j < agents.size(); j++) {
					if (i == j)continue;
					//Agent * temp = &_agents[j];
					if (agents[i]->_class == agents[j]->_class)
						agents[i]->insertAgentGroup(agents[j]);
				}
				_globalPlanAgents.insert(std::pair<int, GlobalPlanAgent*>(currAgent->_id, currAgent));
			}
		}

		DijkstraGlobalPlanFactory::DijkstraGlobalPlanFactory() : GlobalPlanFactory() {
			_nameID = _attrSet.addStringAttribute( "type", true, "" );
		}

		////////////////////////////////////////////////////////////////////////////

		bool DijkstraGlobalPlanFactory::setFromXML(GlobalPlan * sel, TiXmlElement * node,
													const std::string & specFldr ) const {
			DijkstraGlobalPlan * dGP = dynamic_cast< DijkstraGlobalPlan * >( sel );
			assert(dGP != 0x0 && "Trying to set attributes of a const state selector element on "
					"an incompatible object" );
			//����������һЩ��Ҫ�Ĳ���
			if ( !GlobalPlanFactory::setFromXML(dGP, node, specFldr ) ) return false;
			dGP->setPlanName( _attrSet.getString( _nameID ) );

			return true;
		}
	}	// namespace Agents
}	// namespace Menge
