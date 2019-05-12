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

#ifndef __SIMULATOR_BASE_H__
#define __SIMULATOR_BASE_H__

/*!
 *  @file       SimulatorBase.h
 *  @brief      Contains the SimulatorBase class - the common, generic simulator to
 *				work with different types of agents.  It is templated on the Agent type.
 */

#include "MengeCore/mengeCommon.h"
#include "MengeCore/Agents/AgentInitializer.h"
#include "MengeCore/Agents/SimulatorInterface.h"
#include "MengeCore/Agents/SpatialQueries/SpatialQuery.h"
#include "MengeCore/Runtime/Utils.h"
#include <vector>
#include <map> 
#include "MengeCore/Agents/MapSets/MapVertexList.h"
#include "MengeCore/GlobalPlan/GlobalPlanDatabase.h"
#include "MengeCore/TacticalPlan/TacticalPlanDatabase.h"
#include "MengeCore/Agents/Map.h"	
#include "MengeCore/Runtime/dijkstra.h"
#include "MengeCore/EnvironmentalChange/EnvironmentalChange.h"
#include "MengeCore/OperationPlan/OperationPlanDatabase.h"
#if HAVE_OPENMP || _OPENMP
#include <omp.h>
#endif

namespace Menge {

	namespace Agents {

		/*!
		 *  @brief      Defines the basic simulator.  It is responsible for tracking agents and
		 *				obstacles as well as initializing such from files.
		 */
		template < class Agent >
		class SimulatorBase : public SimulatorInterface {
		public:
			/*!
			 *  @brief      Constructs a simulator instance.
			 */
			SimulatorBase();

			/*!
			 *  @brief      Destorys a simulator instance.
			 */
			~SimulatorBase();

			/*!
			 *  @brief      Lets the simulator perform a simulation step and updates the
			 *              two-dimensional _p and two-dimensional velocity of
			 *              each agent.
			 */
			void doStep();

			/*!
			 *	@brief		Initalize spatial query structure.
			 */
			virtual bool initSpatialQuery();

			/*!
			 *	@brief	After all agents and all obstacles have been added to the scene
			 *			does the work to finish preparing the simulation to be run.
			 *
			 *	This work is performed when the simulator is done being initialized.
			 *	If a particular new pedestrian simulator requires particular finalization
			 *	work, this function should be sub-classed and the parent class's
			 *	version of the function should be explicitly called before any additional
			 *	work is performed.
			 */
			virtual void finalize();
			virtual void initGroupInfo();
			virtual void testEnvironment();
			virtual bool AgentGlobalPlan(int agentIndex);
			virtual bool AgentTacticalPlan(int agentIndex);
			virtual bool AgentOperationPlan(int agentIndex);
			/*!
			 *  @brief      Accessor for agents.
			 *
			 *  @param      agentNo         The number of the agent who is to be retrieved.
			 *								This is *not* the same as the agent identifier.
			 *								It is merely the local index of the agent in the
			 *								simulator's local store.
			 *  @returns    A pointer to the agent.
			 */
			virtual BaseAgent * getAgent(size_t agentNo) { return &_agents[agentNo]; }

			/*!
			 *  @brief      Const accessor for agents.
			 *
			 *  @param      agentNo         The number of the agent who is to be retrieved.
			 *								This is *not* the same as the agent identifier.
			 *								It is merely the local index of the agent in the
			 *								simulator's local store.
			 *  @returns    A pointer to the agent.
			 */
			virtual const BaseAgent * getAgent(size_t agentNo) const {
				return &_agents[agentNo];
			}

			/*!
			 *	@brief		Add an agent with specified position to the simulator whose properties
			 *				are defined by the given agent initializer.
			 *
			 *	It uses the agent initializer to define the values of the remaining agent
			 *	parameters.
			 *
			 *	@param		pos			The 2d vector representing the agent's position
			 *	@param		agentInit	The AgentInitializer necessary to parse AgentSet properties
			 *	@returns	A pointer to the agent (if initialization was succesful) or NULL if
			 *				failed.
			 */
			virtual BaseAgent * addAgent(const Vector2 & pos, AgentInitializer * agentInit);

			/*!
			 *  @brief      Returns the count of agents in the simulation.
			 *
			 *  @returns    The count of agents in the simulation.
			 */
			virtual size_t getNumAgents() const { return _agents.size(); }

			/*!
			 *	@brief			Reports if there are non-common Experiment parameters that
			 *					this simulator requires in the XML file.
			 *
			 *	@returns		By default, the simulator base ONLY uses common parameters.
			 *					Always returns false.
			 */
			virtual bool hasExpTarget() { return false; }

			/*!
			 *	@brief			Reports if the given Experiment attribute tag name belongs to this
			 *					simulator.
			 *
			 *	@param			tagName			The name of the candidate experiment XML tag.
			 *	@returns		By default, the simulator base ONLY uses common parameters.
			 *					Always returns false.
			 */
			virtual bool isExpTarget(const std::string & tagName) { return false; }

			/*!
			 *	@brief			Given an Experiment parameter name and value, sets the appropriate
			 *					simulator parameter.
			 *
			 *	// TODO: Define the conditions of success/failure.
			 *
			 *	@param			paramName		A string containing the parameter name for the
			 *									experiment.
			 *	@param			value			A string containing the value for the parameter.
			 *	@returns		True if the parameter was successfully set, false otherwise.
			 */
			virtual bool setExpParam(const std::string & paramName, const std::string & value)
				throw(XMLParamException);

		protected:

			/*!
			 *	@brief		Computes the neighbors for the given agent.
			 *
			 *	@param		agent		The agent whose neighbors are to be computed.
			 */
			void computeNeighbors(Agent * agent);

			/*!
			 *	@brief		The collection of agents in the simulation
			 */
			std::vector< Agent > _agents;
			std::map<int, Menge::Agents::Connection > _connectionMap;//以ID为关键字 保存所有Connect信息 ID从1开始
			std::map<int, Menge::Agents::Path > _pathMap;//以ID为关键字 保存所有Path信息 ID从1开始
		};

		////////////////////////////////////////////////////////////////
		//					Implementation of SimulatorBase
		////////////////////////////////////////////////////////////////

		template < class Agent >
		SimulatorBase<Agent>::SimulatorBase() : SimulatorInterface(), _agents() {
		}

		////////////////////////////////////////////////////////////////

		template < class Agent >
		SimulatorBase<Agent>::~SimulatorBase() {
			_agents.clear();
		}

		////////////////////////////////////////////////////////////////

		template < class Agent >
		void SimulatorBase<Agent>::doStep() {
			assert(_spatialQuery != 0x0 && "Can't run without a spatial query instance defined");

			_spatialQuery->updateAgents();
			int AGT_COUNT = static_cast<int>(_agents.size());
#pragma omp parallel for
			for (int i = 0; i < AGT_COUNT; ++i) {
				AgentGlobalPlan(i);
				//计算当前的邻居
				computeNeighbors(&(_agents[i]));

				AgentTacticalPlan(i);//计算下一步的目标
				
				//_agents[i]._nextGoal=_agents[i].computeNextGoal();
				_agents[i]._nextPrefSpeed = _agents[i].computeNextPrefSpeed();//根据目标计算最优速度
				//_agents[i].computeNewVelocity();//计算最新速度
				AgentOperationPlan(i);
			}

#pragma omp parallel for
			for (int i = 0; i < AGT_COUNT; ++i) {
				_agents[i].update(TIME_STEP);//更新位置
			}

			_globalTime += TIME_STEP;

		}

		////////////////////////////////////////////////////////////////

		template < class Agent >
		bool SimulatorBase<Agent>::initSpatialQuery() {
			assert(_spatialQuery != 0x0 && "Can't run without a spatial query instance defined");

			const size_t AGT_COUNT = _agents.size();
			std::vector< BaseAgent * > agtPointers(AGT_COUNT);
			for (size_t a = 0; a < AGT_COUNT; ++a) {
				agtPointers[a] = &_agents[a];
			}
			_spatialQuery->setAgents(agtPointers);

			_spatialQuery->processObstacles();

			return true;
		}

		////////////////////////////////////////////////////////////////

		template < class Agent >
		void SimulatorBase<Agent>::finalize() {
			SimulatorInterface::finalize();

			// initialize agents
			for (size_t i = 0; i < _agents.size(); ++i) {
				_agents[i].initialize();
			}
		}

		template < class Agent >
		void SimulatorBase<Agent>::initGroupInfo() {//虚函数，在不同的子类simulator中要实现不同的算法
			SimulatorInterface::initGroupInfo();
			//先统计_maps中的所有Path和Connetion
			const int mapsSize = _maps.size();
			int pathIndex = 1;
			for (int j = 0; j < mapsSize; j++) {
				int pCount = _maps[j]->_paths.size();
				for (int p = 0; p < pCount; p++) {
					_pathMap[pathIndex++] = _maps[j]->_paths[p];
				}
				int cCount = _maps[j]->_connections.size();
				for (int c = 0; c < cCount; c++) {
					_connectionMap[_maps[j]->_connections[c].id] = _maps[j]->_connections[c];
				}
			}


			std::vector< BaseAgent *> baseagents;
			for (int i = 0; i < _agents.size(); i++) {
				const int mapsSize = _maps.size();
				BaseAgent *temp = (BaseAgent *)&_agents[i];
				for (int j = 0; j < mapsSize; j++) {
					temp->environmentFamiliaritySet.push_back(rand() % 2);//随机[0,1]
				}
				baseagents.push_back(temp);
			}

			_globalPlan->initAgentInfo(_maps, baseagents);
			_tacticalPlan->initAgentInfo(_maps, baseagents);
			_operationPlan->initAgentInfo();
		}

		template < class Agent >
		void SimulatorBase<Agent>::testEnvironment() {//虚函数，在不同的子类simulator中要实现不同的算法
			SimulatorInterface::testEnvironment();
			int count = _environmentalChangeSet.size();
			for (int i = 0; i < count; i++) {
				Menge::Agents::EnvironmentalChange * ec = _environmentalChangeSet[i];
				if (ec->enable) {
					//this->getSpatialQuery
					vector<Menge::Agents::BaseAgent *> agents;
					for (size_t j = 0; j < _agents.size(); j++) {
						agents.push_back((Menge::Agents::BaseAgent *)&_agents[j]);
					}
					Menge::Agents::ObstacleSet *ob = NULL;
					ec->getEnvironmentalChange(_connectionMap, _pathMap, agents, &ob, _globalTime);
					if (ob != NULL) {
						for (int index = 0; index < ob->obstacleCount(); ++index) {
							this->getSpatialQuery()->addObstacle(ob->getObstacle(index));
						}
						this->initSpatialQuery();
						return;
					}

				}

			}
		}

		template < class Agent >
		bool SimulatorBase<Agent>::AgentGlobalPlan(int agentIndex) {
			SimulatorInterface::AgentGlobalPlan(agentIndex);
			if (_agents[agentIndex]._needRePlan) {
				_agents[agentIndex]._globalGoals = _globalPlan->getGlobalPlan(_connectionMap, _pathMap, _maps, _agents[agentIndex]._pos, _agents[agentIndex]._id);
				_agents[agentIndex]._needRePlan = false;

				for (int m = 0; m < _maps.size(); m++) {
					bool inMap = _maps[m]->pointInMap(_agents[agentIndex]._pos);
					if (inMap) {
						_agents[agentIndex].currentMapID = _maps[m]->_id;
						break;
					}
				}
				return true;
			}
			return false;
		}
		template < class Agent >
		bool SimulatorBase<Agent>::AgentTacticalPlan(int agentIndex) {
			SimulatorInterface::AgentTacticalPlan(agentIndex);
			_tacticalPlan->_baseAgent = (Agent*)&_agents[agentIndex];
			Vector2 goal = _tacticalPlan->computeNextGoal();
			_agents[agentIndex]._nextGoal= goal;				
			return true;

		}
		template < class Agent >
		bool SimulatorBase<Agent>::AgentOperationPlan(int agentIndex) {
			SimulatorInterface::AgentOperationPlan(agentIndex);
			_operationPlan->_baseAgent = (Agent*)&_agents[agentIndex];
			//Vector2 goal = _operationPlan->computeNew();
			 _operationPlan->computeNewVelocity(TIME_STEP);
			return true;

		}

		////////////////////////////////////////////////////////////////

		template < class Agent >
		BaseAgent * SimulatorBase<Agent>::addAgent(const Vector2 & pos,
			AgentInitializer * agentInit) {
			Agent agent;

			agent._pos = pos;
			agent._id = _agents.size();
			if (!agentInit->setProperties(&agent)) {
				logger << Logger::ERR_MSG << "Error initializing agent " << agent._id << "\n";
				return 0x0;
			}
			_agents.push_back(agent);

			return &_agents[_agents.size() - 1];
		}

		////////////////////////////////////////////////////////////////

		template < class Agent >
		bool SimulatorBase<Agent>::setExpParam(const std::string & paramName,
			const std::string & value)
			throw(XMLParamException) {

			if (paramName == "time_step") {
				try {
					LOGICAL_TIME_STEP = toFloat(value);
				}
				catch (UtilException) {
					throw XMLParamException(
						std::string("Common parameters \"time_step\" value couldn't be converted "
							"to a float.  Found the value: ") + value);
				}
			}
			else {
				return false;
			}

			return true;
		}

		////////////////////////////////////////////////////////////////

		template< class Agent >
		void SimulatorBase<Agent>::computeNeighbors(Agent * agent) {
			// obstacles
			agent->startQuery();
			_spatialQuery->obstacleQuery(agent);

			// agents
			if (agent->_maxNeighbors > 0) {
				_spatialQuery->agentQuery(agent);
			}
		}
	}	// namespace Agents
}	// namespace Menge
#endif	// __SIMULATOR_BASE_H__
