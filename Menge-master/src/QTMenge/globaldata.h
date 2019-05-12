#pragma once
#include <string>
#include "MengeCore/GlobalPlan/GlobalPlan.h"
#include "MengeCore/TacticalPlan/TacticalPlan.h"
#include "MengeCore/OperationPlan/OperationPlan.h"

/* #include "globaldata.h" */
#pragma once
//全局变量的声明,还需要定义
extern int   globaldata_argc;
extern char * globaldata_argv[3];
extern std::string globaldata_model;

extern std::string globalplan_name; //战略层的插件名字
extern std::string tacticalplan_name; //战术层的插件名字
extern std::string operationplan_name; //操作层的插件名字
extern std::vector<std::string> environment_name; //环境层的插件名字
extern std::string viewer_name; //可视化插件名字

extern	Menge::Agents::GlobalPlan *globalplan;  //存放解析得到战略层的对象
extern  Menge::Agents::TacticalPlan *tacticalplan;  //存放解析得到战术层的对象
extern  Menge::Agents::OperationPlan *operationplan;  //存放解析得到操作层的对象
extern std::vector<Menge::Agents::EnvironmentalChange *> environmentalChangeSet;

extern std::string globalplan_info; //战略层插件信息
extern std::string tacticalplan_info; //战术层插件信息
extern std::string operationplan_info; //操作层插件信息
extern std::vector<std::string> environment_info_vector; //环境层插件信息
extern std::string viewer_info; //可视化层插件信息

extern std::map<std::string, std::string>  total_info;  //存放全部信息
extern std::string show_info; //显示的全部信息

