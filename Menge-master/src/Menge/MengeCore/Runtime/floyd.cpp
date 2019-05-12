#include"Floyd.h"


//���캯��
Graph_DG_floyd::Graph_DG_floyd(int vexnum, int edge) {
    //��ʼ���������ͱ���
    this->vexnum = vexnum;
    this->edge = edge;
    //Ϊ�ڽӾ��󿪱ٿռ�͸���ֵ
    arc = new int*[this->vexnum];
    dis = new int*[this->vexnum];
    path = new int*[this->vexnum];
	pathPointPos = new Menge::Math::Vector2*[this->vexnum];
    for (int i = 0; i < this->vexnum; i++) {
        arc[i] = new int[this->vexnum];
        dis[i] = new int[this->vexnum];
        path[i] = new int[this->vexnum];
		pathPointPos[i] = new Menge::Math::Vector2[this->vexnum];
        for (int k = 0; k < this->vexnum; k++) {
            //�ڽӾ����ʼ��Ϊ�����
            arc[i][k] = INT_MAX;
        }
    }
}
//��������
Graph_DG_floyd::~Graph_DG_floyd() {

    for (int i = 0; i < this->vexnum; i++) {
        delete this->arc[i];
        delete this->dis[i];
        delete this->path[i];
		delete this->pathPointPos[i];

    }
    delete dis;
    delete arc;
    delete path;
	delete pathPointPos;
}

// �ж�����ÿ������ĵıߵ���Ϣ�Ƿ�Ϸ�
//�����1��ʼ���
bool Graph_DG_floyd::check_edge_value(int start, int end, int weight) {
    if (start<1 || end<1 || start>vexnum || end>vexnum || weight < 0) {
        return false;
    }
    return true;
}

void Graph_DG_floyd::createGraph(map<int, Menge::Agents::Path > pathMap) {
   // cout << "������ÿ���ߵ������յ㣨�����Ŵ�1��ʼ���Լ���Ȩ��" << endl;
    int start;
    int end;
    int weight;
    int count = 0;
    while (count != this->edge) {
		start = pathMap[count + 1].fromConID;
		end = pathMap[count + 1].toConID;
		weight = pathMap[count + 1].dis;
        //�����жϱߵ���Ϣ�Ƿ�Ϸ�
        while (!this->check_edge_value(start, end, weight)) {
            cout << "����ıߵ���Ϣ���Ϸ�������������" << endl;
           // cin >> start >> end >> weight;
			break;
        }
        //���ڽӾ����Ӧ�ϵĵ㸳ֵ
        arc[start - 1][end - 1] = weight;
        //����ͼ��������д���
        arc[end - 1][start - 1] = weight;
        ++count;
    }
}

void Graph_DG_floyd::print() {
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

void Graph_DG_floyd::Floyd(map<int, Menge::Agents::Connection > conMap) {
    int row = 0;
    int col = 0;
    for (row = 0; row < this->vexnum; row++) {
        for (col = 0; col < this->vexnum; col++) {
            //�Ѿ���D��ʼ��Ϊ�ڽӾ����ֵ
            this->dis[row][col] = this->arc[row][col];
            //����P�ĳ�ֵ��Ϊ�����ߵ��յ㶥����±�
            this->path[row][col] = col;
			this->pathPointPos[row][col] = conMap[col+1].pos;
        }
    }

    //����ѭ�������ڼ���ÿ����Ե����·��
    int temp = 0;
    int select = 0;
    for (temp = 0; temp < this->vexnum; temp++) {
        for (row = 0; row < this->vexnum; row++) {
            for (col = 0; col < this->vexnum; col++) {
                //Ϊ�˷�ֹ�����������Ҫ����һ��selectֵ
                select = (dis[row][temp] == INT_MAX || dis[temp][col] == INT_MAX) ? INT_MAX : (dis[row][temp] + dis[temp][col]);
                if (this->dis[row][col] > select) {
                    //�������ǵ�D����
                    this->dis[row][col] = select;
                    //�������ǵ�P����
                    this->path[row][col] = this->path[row][temp];
					this->pathPointPos[row][col] = conMap[this->path[row][temp]+1].pos;
                }
            }
        }
    }
}
/*
dis[vexnum-1][0~vexnum-2] �������Agent��ͼ����������ľ���
temp = path[row-1][col-1] temp��ʾ ��row���㵽��col��������·����Ҫ��������һ����
temp = path[temp][col] ��ͨ������temp��col�� ��һ���� ����ȷ��������·��
*/
void Graph_DG_floyd::print_path() {
    cout << "��������Ե����·����" << endl;
    int row = 0;
    int col = 0;
    int temp = 0;
    for (row = this->vexnum-1; row >=0; row--) {
        for (col = row - 1; col >= 0; col--) {
            cout << "v" << to_string(row + 1) << "---" << "v" << to_string(col+1) << " weight: "
                << this->dis[row][col] << " path: " << " v" << to_string(row + 1);
            temp = path[row][col];
            //ѭ�����;����ÿ��·����
            while (temp != col) {
                cout << "-->" << "v" << to_string(temp + 1);
                temp = path[temp][col];
            }
            cout << "-->" << "v" << to_string(col + 1) << endl;
        }

        cout << endl;
    }
}

int Graph_DG_floyd::getPathDis(int goal) {
	return this->dis[this->vexnum-1][goal];
}
std::vector<Menge::Math::Vector2> Graph_DG_floyd::getPathPoint(int goal) {
	vector<Menge::Math::Vector2> pathPos;
	int temp = path[this->vexnum - 1][goal];
	pathPos.push_back(pathPointPos[this->vexnum - 1][goal]);
	while (temp != goal) {
		pathPos.push_back(pathPointPos[temp][goal]);
		temp = path[temp][goal];
	}
	return pathPos;
}