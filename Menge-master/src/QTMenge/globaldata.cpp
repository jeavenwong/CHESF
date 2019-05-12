#include "globaldata.h" 
#pragma once

//ȫ�ֱ����Ķ���
int globaldata_argc;
char * globaldata_argv[3];
std::string globaldata_model = "orca";

Menge::Agents::GlobalPlan *globalplan;  //��Ž����õ�ս�Բ�Ķ���
Menge::Agents::TacticalPlan *tacticalplan;  //��Ž����õ�ս����Ķ���
Menge::Agents::OperationPlan *operationplan;  //��Ž����õ�������Ķ���
std::vector<Menge::Agents::EnvironmentalChange *> environmentalChangeSet;

std::string globalplan_name; //ս�Բ�Ĳ������
std::string tacticalplan_name; //ս����Ĳ������
std::string operationplan_name; //������Ĳ������
std::vector<std::string> environment_name;  //������Ĳ������
std::string viewer_name = "openGL"; //���ӻ��������

std::string globalplan_info; //ս�Բ�����Ϣ
std::string tacticalplan_info; //ս��������Ϣ
std::string operationplan_info; //����������Ϣ
std::vector<std::string> environment_info_vector; //����������Ϣ
std::string viewer_info; //���ӻ�������Ϣ

std::map<std::string, std::string>  total_info;  //���ȫ����Ϣ

std::string show_info; //��ʾ��ȫ����Ϣ

//��Ҫʹ��ȫ�ֱ����ĵط� ���� #include "globaldata.h" ,����ʹ��
