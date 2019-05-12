/************************************************************/
/*                程序作者：Willam                          */
/*                程序完成时间：2017/3/8                    */
/*                有任何问题请联系：2930526477@qq.com       */
/************************************************************/
//@尽量写出完美的程序

#pragma once
//#pragma once是一个比较常用的C/C++杂注，
//只要在头文件的最开始加入这条杂注，
//就能够保证头文件只被编译一次。

#include<iostream>
#include<string>
#include <map> 
#include "MengeCore/Agents/MapSets/MapVertexList.h"
using namespace std;

/*
本程序是使用Dijkstra算法实现求解最短路径的问题
采用的邻接矩阵来存储图
*/
//记录起点到每个顶点的最短路径的信息
struct Dis {
	string path;
	vector<int> pathPointIndex;//用于保存最短路线的中间点（Connection）的 ID
	std::vector<Menge::Math::Vector2> pathPointPos;//用于保存最短路线的中间点 的坐标
	int value;
	bool visit;
	Dis() {
		visit = false;
		value = 0;
		path = "";
	}
};

class Graph_DG_dijkstra {
private:
	int vexnum;   //图的顶点个数
	int edge;     //图的边数
	int **arc;   //邻接矩阵
	Dis * dis;   //记录各个顶点最短路径的信息
public:
	//构造函数
	Graph_DG_dijkstra(int vexnum, int edge);
	//析构函数
	~Graph_DG_dijkstra();
	// 判断我们每次输入的的边的信息是否合法
	//顶点从1开始编号
	bool check_edge_value(int start, int end, int weight);
	//创建图
	void createGraph(map<int, Menge::Agents::Path > pathMap);
	//打印邻接矩阵
	void print();
	//求最短路径
	void Dijkstra(int begin,map<int, Menge::Agents::Connection > conMap);
	//打印最短路径
	void print_path(int);
	int getPathDis(int);
	std::vector<Menge::Math::Vector2> getPathPoint(int);
};