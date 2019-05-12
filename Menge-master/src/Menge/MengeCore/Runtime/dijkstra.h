/************************************************************/
/*                �������ߣ�Willam                          */
/*                �������ʱ�䣺2017/3/8                    */
/*                ���κ���������ϵ��2930526477@qq.com       */
/************************************************************/
//@����д�������ĳ���

#pragma once
//#pragma once��һ���Ƚϳ��õ�C/C++��ע��
//ֻҪ��ͷ�ļ����ʼ����������ע��
//���ܹ���֤ͷ�ļ�ֻ������һ�Ρ�

#include<iostream>
#include<string>
#include <map> 
#include "MengeCore/Agents/MapSets/MapVertexList.h"
using namespace std;

/*
��������ʹ��Dijkstra�㷨ʵ��������·��������
���õ��ڽӾ������洢ͼ
*/
//��¼��㵽ÿ����������·������Ϣ
struct Dis {
	string path;
	vector<int> pathPointIndex;//���ڱ������·�ߵ��м�㣨Connection���� ID
	std::vector<Menge::Math::Vector2> pathPointPos;//���ڱ������·�ߵ��м�� ������
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
	int vexnum;   //ͼ�Ķ������
	int edge;     //ͼ�ı���
	int **arc;   //�ڽӾ���
	Dis * dis;   //��¼�����������·������Ϣ
public:
	//���캯��
	Graph_DG_dijkstra(int vexnum, int edge);
	//��������
	~Graph_DG_dijkstra();
	// �ж�����ÿ������ĵıߵ���Ϣ�Ƿ�Ϸ�
	//�����1��ʼ���
	bool check_edge_value(int start, int end, int weight);
	//����ͼ
	void createGraph(map<int, Menge::Agents::Path > pathMap);
	//��ӡ�ڽӾ���
	void print();
	//�����·��
	void Dijkstra(int begin,map<int, Menge::Agents::Connection > conMap);
	//��ӡ���·��
	void print_path(int);
	int getPathDis(int);
	std::vector<Menge::Math::Vector2> getPathPoint(int);
};