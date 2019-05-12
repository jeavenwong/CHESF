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
 *	@file		MapVertexList.h
 *	@brief		The definition of the set of vertices for an explicit Map definition.
 */

#ifndef __MAP_VERTEX_LIST__
#define __MAP_VERTEX_LIST__

#include "MengeCore/mengeCommon.h"

#include <vector>

namespace Menge {

	/*!
	 *  @file       MapVertexList.h
	 *  @brief      Defines a struct for passing around Maps as lists of vertices.
	 */
	namespace Agents {
		/*!
		 *    @brief     A strcuture for passing vertices and closed tags for Maps
		 */
		struct Connection {

			Math::Vector2 pos;
			int id;//Connection的ID 需要全局唯一
			int nextMapId;
			bool open=1;
		};
		struct Path {
			int fromConID;
			int toConID;
			float dis;
		};
		struct MapVertexList {
			/*!
			 *	@brief		The list of vertices for the Map.
			 */
			std::vector<Math::Vector2> vertices;

			/*! 
			 *	@brief		Indicates if the Map is closed (true) or open (false).
			 */
			bool closed;

			int mapID;
			bool hasExist;			
			std::vector<Connection> connections;//要设置结构体。保存门的id 和坐标
			std::vector<Path> paths;
			std::vector<int> nextMapIdOfConnection;//每个connection的nextMapId，顺序保持一致
		};

	}	// namespace Agents
}	// namespace Menge

#endif	// __Map_VERTEX_LIST__
