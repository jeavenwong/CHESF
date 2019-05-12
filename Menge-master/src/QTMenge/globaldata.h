#pragma once
#include <string>
#include "MengeCore/GlobalPlan/GlobalPlan.h"
#include "MengeCore/TacticalPlan/TacticalPlan.h"
#include "MengeCore/OperationPlan/OperationPlan.h"

/* #include "globaldata.h" */
#pragma once
//ȫ�ֱ���������,����Ҫ����
extern int   globaldata_argc;
extern char * globaldata_argv[3];
extern std::string globaldata_model;

extern std::string globalplan_name; //ս�Բ�Ĳ������
extern std::string tacticalplan_name; //ս����Ĳ������
extern std::string operationplan_name; //������Ĳ������
extern std::vector<std::string> environment_name; //������Ĳ������
extern std::string viewer_name; //���ӻ��������

extern	Menge::Agents::GlobalPlan *globalplan;  //��Ž����õ�ս�Բ�Ķ���
extern  Menge::Agents::TacticalPlan *tacticalplan;  //��Ž����õ�ս����Ķ���
extern  Menge::Agents::OperationPlan *operationplan;  //��Ž����õ�������Ķ���
extern std::vector<Menge::Agents::EnvironmentalChange *> environmentalChangeSet;

extern std::string globalplan_info; //ս�Բ�����Ϣ
extern std::string tacticalplan_info; //ս��������Ϣ
extern std::string operationplan_info; //����������Ϣ
extern std::vector<std::string> environment_info_vector; //����������Ϣ
extern std::string viewer_info; //���ӻ�������Ϣ

extern std::map<std::string, std::string>  total_info;  //���ȫ����Ϣ
extern std::string show_info; //��ʾ��ȫ����Ϣ

