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
			int id;//Connection��ID ��Ҫȫ��Ψһ
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
			std::vector<Connection> connections;//Ҫ���ýṹ�塣�����ŵ�id ������
			std::vector<Path> paths;
			std::vector<int> nextMapIdOfConnection;//ÿ��connection��nextMapId��˳�򱣳�һ��
		};

	}	// namespace Agents
}	// namespace Menge

#endif	// __Map_VERTEX_LIST__
