
#include "DijkstraGlobalPlanPlug.h"



namespace Menge {

	namespace Agents {

		std::vector<Menge::Math::Vector2>  PLUGCLASS::getGlobalPlan(std::map<int, Menge::Agents::Connection > connectionMapTemp,
			std::map<int, Menge::Agents::Path > pathMapTemp,
			std::vector<Agents::Map *> _maps,
			Math::Vector2 agentPos,
			int id
		) const {
			//给_agents中的某个Agent全局规划
			//map<int, Menge::Agents::Connection > connectionMapTemp(_connectionMap);
			//map<int, Menge::Agents::Path > pathMapTemp(_pathMap);

			//GlobalPlanAgent * currAgent = new GlobalPlanAgent();
			//currAgent->_id = id;
			//currAgent->_maps = _maps;
			////std::map<int, GlobalPlanAgent*> globalPlanAgents;
			//_globalPlanAgents.insert(std::pair<int, GlobalPlanAgent*>(currAgent->_id,currAgent));

			//根据id找到对应的数据，判断重新规划
			map<int, GlobalPlanAgent*>::iterator iter;
			iter = _globalPlanAgents.find(id);
			if (iter != _globalPlanAgents.end())
			{
				//根据Agent的环境熟悉度 决定是否要全局规划
				if (iter->second->_environmentFamiliarity == 2) {
					//除了高熟悉度的人，都不做全局规划

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

					Graph_DG_dijkstra graph(connectionMapTemp.size(), pathMapTemp.size());
					graph.createGraph(pathMapTemp);
					//graph.print();
					graph.Dijkstra(vexnum, connectionMapTemp);
					//计算Agent到各个门的距离
					//graph.print_path(vexnum);

					//最短路线已经保存，要筛选 包含出口的最短路线
					//确定哪些是出口
					int minDis = INT_MAX;
					std::vector<Math::Vector2> plan;
					for (int v = 1; v <= vexnum; v++) {
						if (connectionMapTemp[v].nextMapId == -1) {
							// -1表示 这里是出口（安全区）
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

		void  PLUGCLASS::initAgentInfo(std::vector<Agents::Map *> _maps,
			std::vector<BaseAgent *> agents
		) const {

			//遍历_agents 保存所有agent的邻居id信息，给每个Agent设置地图信息
			_globalPlanAgents.clear();
			for (size_t i = 0; i < agents.size(); i++) {
				GlobalPlanAgent * currAgent = new GlobalPlanAgent();
				currAgent->_id = agents[i]->_id;
				//currAgent->_maps = _maps;
				agents[i]->_maps = _maps;
				//std::map<int, GlobalPlanAgent*> globalPlanAgents;

				//初始化Agent的环境属性度
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
				//currAgent->_influence = (rand() % 4);	//初始化影响力,随机[0,9]

				//以环境熟悉度为 团队影响力
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


		FACTORYPLUGCLASS::FACTORYPLUGCLASS() : GlobalPlanFactory() {
		
		}
	}	// namespace Agents
}	// namespace Menge

extern "C" {

	DijkstraGlobalPlanPlug_API	Menge::Agents::GlobalPlanFactory * Export(void) {

		return new Menge::Agents::FACTORYPLUGCLASS();

	}

}