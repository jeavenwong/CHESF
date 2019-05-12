/************************************************************/
/*                �������ߣ�Willam                          */
/*                �������ʱ�䣺2017/3/11                   */
/*                ���κ���������ϵ��2930526477@qq.com       */
/************************************************************/
//@����д�������ĳ���

#pragma once
//#pragma once��һ���Ƚϳ��õ�C/C++��ע��
//ֻҪ��ͷ�ļ����ʼ����������ע��
//���ܹ���֤ͷ�ļ�ֻ������һ�Ρ�

/*
��ʼ��Floyd�㷨��ʹ���ڽӾ���ʵ�ֵ�
*/

#include<iostream>
#include<string>
#include <map> 
#include "MengeCore/Agents/MapSets/MapVertexList.h"
using namespace std;

class Graph_DG_floyd {
private:
    int vexnum;   //ͼ�Ķ������
    int edge;     //ͼ�ı���
    int **arc;   //�ڽӾ���
    int ** dis;   //��¼�����������·������Ϣ
    int ** path;  //��¼�������·������Ϣ
	Menge::Math::Vector2 ** pathPointPos;//��¼�������·������Ϣ�еĵ������
public:
    //���캯��
	Graph_DG_floyd(int vexnum, int edge);
    //��������
    ~Graph_DG_floyd();
    // �ж�����ÿ������ĵıߵ���Ϣ�Ƿ�Ϸ�
    //�����1��ʼ���
    bool check_edge_value(int start, int end, int weight);
    //����ͼ
    void createGraph(map<int, Menge::Agents::Path > pathMap);
    //��ӡ�ڽӾ���
    void print();
    //�����·��
    void Floyd(map<int, Menge::Agents::Connection > conMap);
    //��ӡ���·��
    void print_path();

	int getPathDis(int);
	std::vector<Menge::Math::Vector2> getPathPoint(int);
};
