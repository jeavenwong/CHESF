#include"Dijkstra.h"

//���캯��
Graph_DG_dijkstra::Graph_DG_dijkstra(int vexnum, int edge) {
	//��ʼ���������ͱ���
	this->vexnum = vexnum;
	this->edge = edge;
	//Ϊ�ڽӾ��󿪱ٿռ�͸���ֵ
	arc = new int*[this->vexnum];
	dis = new Dis[this->vexnum];
	for (int i = 0; i < this->vexnum; i++) {
		arc[i] = new int[this->vexnum];
		for (int k = 0; k < this->vexnum; k++) {
			//�ڽӾ����ʼ��Ϊ�����
			arc[i][k] = INT_MAX;
		}
	}
}
//��������
Graph_DG_dijkstra::~Graph_DG_dijkstra() {
	delete[] dis;
	for (int i = 0; i < this->vexnum; i++) {
		delete this->arc[i];
	}
	delete arc;
}

// �ж�����ÿ������ĵıߵ���Ϣ�Ƿ�Ϸ�
//�����1��ʼ���
bool Graph_DG_dijkstra::check_edge_value(int start, int end, int weight) {
	if (start<1 || end<1 || start>vexnum || end>vexnum || weight < 0) {
		return false;
	}
	return true;
}

void Graph_DG_dijkstra::createGraph(map<int, Menge::Agents::Path > pathMap) {
	//cout << "������ÿ���ߵ������յ㣨�����Ŵ�1��ʼ���Լ���Ȩ��" << endl;
	int start;
	int end;
	int weight;
	int count = 0;
	while (count != this->edge) {
		start = pathMap[count+1].fromConID;
		end = pathMap[count+1].toConID;
		weight = pathMap[count+1].dis;

		//�����жϱߵ���Ϣ�Ƿ�Ϸ�
		while (!this->check_edge_value(start, end, weight)) {
			cout << "����ıߵ���Ϣ���Ϸ�������������" << endl;
			break;
		}
		//���ڽӾ����Ӧ�ϵĵ㸳ֵ
		arc[start - 1][end - 1] = weight;
		//����ͼ��������д���
		arc[end - 1][start - 1] = weight;
		++count;
	}



}

void Graph_DG_dijkstra::print() {
	cout << "ͼ���ڽӾ���Ϊ��" << endl;
	int count_row = 0; //��ӡ�еı�ǩ
	int count_col = 0; //��ӡ�еı�ǩ
	//��ʼ��ӡ
	while (count_row != this->vexnum) {
		count_col = 0;
		while (count_col != this->vexnum) {
			if (arc[count_row][count_col] == INT_MAX)
				cout << "��" << " ";
			else
				cout << arc[count_row][count_col] << " ";
			++count_col;
		}
		cout << endl;
		++count_row;
	}
}
void Graph_DG_dijkstra::Dijkstra(int begin, map<int, Menge::Agents::Connection > conMap){
	//���ȳ�ʼ�����ǵ�dis����
	int i;
	for (i = 0; i < this->vexnum; i++) {
		//���õ�ǰ��·��
		dis[i].path = "v" + to_string(begin) + "-->v" + to_string(i + 1);
		dis[i].pathPointIndex.push_back(i+1);
		dis[i].pathPointPos.push_back(conMap[i + 1].pos);
		dis[i].value = arc[begin - 1][i];
	}
	//�������ĵ�����·��Ϊ0
	dis[begin - 1].value = 0;
	dis[begin - 1].visit = true;

	int count = 1;
	//����ʣ��Ķ�������·����ʣ��this->vexnum-1�����㣩
	while (count != this->vexnum) {
		//temp���ڱ��浱ǰdis��������С���Ǹ��±�
		//min��¼�ĵ�ǰ����Сֵ
		int temp = 0;
		int min = INT_MAX;
		for (i = 0; i < this->vexnum; i++) {
			if (!dis[i].visit && dis[i].value<min) {
				min = dis[i].value;
				temp = i;
			}
		}
		//cout << temp + 1 << "  "<<min << endl;
		//��temp��Ӧ�Ķ�����뵽�Ѿ��ҵ������·���ļ�����
		dis[temp].visit = true;
		++count;
 		for (i = 0; i < this->vexnum; i++) {
			//ע�����������arc[temp][i]!=INT_MAX����ӣ���Ȼ�����������Ӷ���ɳ����쳣
			if (!dis[i].visit && arc[temp][i] != INT_MAX && (dis[temp].value + arc[temp][i]) < dis[i].value) {
				//����µõ��ı߿���Ӱ������Ϊ���ʵĶ��㣬�Ǿ;͸����������·���ͳ���
				dis[i].value = dis[temp].value + arc[temp][i];
				dis[i].path = dis[temp].path + "-->v" + to_string(i + 1);

				dis[i].pathPointIndex = dis[temp].pathPointIndex;
				dis[i].pathPointIndex.push_back(i + 1);

				dis[i].pathPointPos = dis[temp].pathPointPos; 
				dis[i].pathPointPos.push_back(conMap[i + 1].pos);
			}
		}
	}

}
void Graph_DG_dijkstra::print_path(int begin) {
	string str;
	str = "v" + to_string(begin);
	cout << "��" << str << "Ϊ����ͼ�����·��Ϊ��" << endl;
	for (int i = 0; i != this->vexnum; i++) {
		if (dis[i].value != INT_MAX)
			cout << dis[i].path << "=" << dis[i].value << endl;
		else {
			cout << dis[i].path << "�������·����" << endl;
		}
	}
}

int Graph_DG_dijkstra::getPathDis(int goal) {
	return dis[goal].value;
}

std::vector<Menge::Math::Vector2> Graph_DG_dijkstra::getPathPoint(int goal) {
	return dis[goal].pathPointPos;
}