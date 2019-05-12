#include "globaldata.h" 
#pragma once

//全局变量的定义
int globaldata_argc;
char * globaldata_argv[3];
std::string globaldata_model = "orca";

Menge::Agents::GlobalPlan *globalplan;  //存放解析得到战略层的对象
Menge::Agents::TacticalPlan *tacticalplan;  //存放解析得到战术层的对象
Menge::Agents::OperationPlan *operationplan;  //存放解析得到操作层的对象
std::vector<Menge::Agents::EnvironmentalChange *> environmentalChangeSet;

std::string globalplan_name; //战略层的插件名字
std::string tacticalplan_name; //战术层的插件名字
std::string operationplan_name; //操作层的插件名字
std::vector<std::string> environment_name;  //环境层的插件名字
std::string viewer_name = "openGL"; //可视化插件名字

std::string globalplan_info; //战略层插件信息
std::string tacticalplan_info; //战术层插件信息
std::string operationplan_info; //操作层插件信息
std::vector<std::string> environment_info_vector; //环境层插件信息
std::string viewer_info; //可视化层插件信息

std::map<std::string, std::string>  total_info;  //存放全部信息

std::string show_info; //显示的全部信息

//在要使用全局变量的地方 引用 #include "globaldata.h" ,即可使用
