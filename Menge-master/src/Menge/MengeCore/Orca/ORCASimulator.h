/*
 Menge Crowd Simulation Framework

 Copyright and trademark 2012-17 University of North Carolina at Chapel Hill

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0
 or
	LICENSE.txt in the root of the Menge repository.

 Any questions or comments should be sent to the authors menge@cs.unc.edu

 <http://gamma.cs.unc.edu/Menge/>
*/

/*!
 *  @file       ORCASimulator.h
 *  @brief      Contains the ORCA::Simulator class.
 */

#ifndef __ORCA_SIMULATOR_H__
#define __ORCA_SIMULATOR_H__

#include "MengeCore/mengeCommon.h"
#include "MengeCore/Agents/SimulatorBase.h"	
#include "MengeCore/Orca/ORCAAgent.h"
 //#include "MengeCore/Agents/BaseAgent.h"
#include "MengeCore/Agents/SpatialQueries/SpatialQuery.h"
#include "MengeCore/EnvironmentalChange/NewObstacleChange.h"
#include "MengeCore/Agents/ObstacleSets/ListObstacleSet.h"
#include "MengeCore/Agents/ObstacleSets/ObstacleSetDatabase.h"
  /*!
   *	@namespace	ORCA
   *	@brief		The namespace for the ORCA local collision avoidance model.
   */
namespace ORCA {
	/*!
	*  @brief      Defines the simulator operating on ORCA::Agent.
	*/

	class Simulator : public Menge::Agents::SimulatorBase< Agent > {
	public:
		/*!
		 *  @brief      Constructs a simulator instance.
		 */
		 //map<int, Menge::Agents::Connection > connectionMap;//��IDΪ�ؼ��� ��������Connect��Ϣ ID��1��ʼ
		 //map<int, Menge::Agents::Path > pathMap;//��IDΪ�ؼ��� ��������Path��Ϣ ID��1��ʼ

		Simulator() : Menge::Agents::SimulatorBase< Agent >() {}

		//virtual void testEnvironment() {
		//	Menge::Agents::SimulatorBase< Agent >::testEnvironment();
		//	int count = _environmentalChangeSet.size();
		//	for (int i = 0; i < count; i++) {
		//		Menge::Agents::EnvironmentalChange * ec = _environmentalChangeSet[i];
		//		if (ec->enable) {
		//			//this->getSpatialQuery
		//			vector<Menge::Agents::BaseAgent *> agents;
		//			for (size_t j = 0; j < _agents.size(); j++) {
		//				agents.push_back((Menge::Agents::BaseAgent *)&_agents[j]);
		//			}
		//			Menge::Agents::ObstacleSet *ob=NULL;
		//			ec->getEnvironmentalChange(_connectionMap, _pathMap, agents, &ob,_globalTime);
		//			if (ob!=NULL) {
		//					for (int index=0; index < ob->obstacleCount(); ++index) {
		//						this->getSpatialQuery()->addObstacle(ob->getObstacle(index));
		//					}
		//					this->initSpatialQuery();
		//					return;
		//			}

		//		}

		//	}

		//}
		//virtual void initGroupInfo() {
		//	Menge::Agents::SimulatorBase< Agent >::initGroupInfo();
		//	//����_agents ��������agent���ھ�id��Ϣ����ÿ��Agent���õ�ͼ��Ϣ
		//	for (size_t i = 0; i < _agents.size(); i++) {
		//		Agent * currAgent = (Agent *)&_agents[i];
		//		currAgent->_maps = _maps;//��ÿ��Agent���õ�ͼ��Ϣ,�����и�����ķ�Χ����ÿ�����������Ϣ
		//		//AgentGlobalPlan(i);//��ÿ��Agent��ȫ�ֹ滮

		//		//��ʼ��Agent�Ļ������Զ�
		//		int familiarityCount = 0;
		//		const int mapsSize = _maps.size();
		//		for (int j = 0; j < mapsSize; j++) {
		//			int temp = rand() % 2;
		//			if (temp) {
		//				familiarityCount++;
		//			}
		//			currAgent->environmentFamiliaritySet.push_back(temp);//���[0,1]
		//		}

		//		if (familiarityCount == 0) {
		//			currAgent->_environmentFamiliarity = 0;
		//		}
		//		else if (familiarityCount == mapsSize)
		//		{
		//			currAgent->_needRePlan = true;
		//			currAgent->_environmentFamiliarity = 2;
		//		}
		//		else
		//		{
		//			currAgent->_environmentFamiliarity = 1;
		//		}
		//		//currAgent->_needRePlan = true;
		//		//computeNeighbors(currAgent);
		//		currAgent->_groupAgents.clear();
		//		//currAgent->_influence = (rand() % 4);	//��ʼ��Ӱ����,���[0,9]
		//		//�Ի�����Ϥ��Ϊ �Ŷ�Ӱ����
		//		currAgent->_influence = currAgent->_environmentFamiliarity;

		//		for (size_t j = 0; j < _agents.size(); j++) {
		//			if (i == j)continue;
		//			Agent * temp = &_agents[j];
		//			if (currAgent->_class == temp->_class)
		//				currAgent->insertAgentGroup(temp);
		//		}



		//	}

		//}
		//virtual bool  AgentGlobalPlan(int agentIndex) {
		//	//����Agent�Ļ�����Ϥ�� �����Ƿ�Ҫȫ�ֹ滮
		//	if (_agents[agentIndex]._environmentFamiliarity != 2) {
		//		_agents[agentIndex]._needRePlan = false;//���˸���Ϥ�ȵ��ˣ�������ȫ�ֹ滮
		//	}
		//	if (Menge::Agents::SimulatorBase< Agent >::AgentGlobalPlan(agentIndex)) {

		//		for (int m = 0; m < _maps.size(); m++) {
		//			bool inMap = _maps[m]->pointInMap(_agents[agentIndex]._pos);
		//			if (inMap) {
		//				_agents[agentIndex].currentMapID = _maps[m]->_id;
		//				break;
		//			}
		//		}
		//		return true;
		//	}
		//	return false;
		//}

		bool check(int Vexnum, int edge) {
			if (Vexnum <= 0 || edge <= 0 || ((Vexnum*(Vexnum - 1)) / 2) < edge)
				return false;
			return true;
		}


	private:
		friend class Agent;
	};
}	// namespace ORCA
#endif
