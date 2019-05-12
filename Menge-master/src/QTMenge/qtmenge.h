#ifndef QTMENGE_H
#define QTMENGE_H

#include <QtWidgets/QMainWindow>
#include "ui_qtmenge.h"

#include <regex> //正则表达式
#include <QTimer>

class QTMenge : public QMainWindow
{
	Q_OBJECT

public:
	QTMenge(int argc, char *argv[], QWidget *parent = 0);
	~QTMenge();
	// int argc_globe=3;
	char **argv_global;

private:

	Ui::QTMengeClass ui;
	void createAction();     //创建动作  
	void createMenu();       //创建菜单  
	void createContentMenu();//创建上下文菜单  
	void selectFile();       //弹出选择文件对话框  

	void strategic_select();  //战略选择模块
	void tactical_select();  //战术选择模块
	void operation_select();  //操作选择模块
	void environment_select(); //环境选择模块

	void parse_globalplan_plugin(std::string path); //解析战略层插件
	void parse_tacticalplan_plugin(std::string path); //解析战术层插件
	void parse_operationplan_plugin(std::string path); //解析操作层插件
	void parse_environment_plugin(std::vector<std::string> path); //解析环境层插件
private:
	QAction *fileOpenAction; //创建一个QAction指针，打开文件动作  
	QMenu *menu;             //创建一个QMenu指针  

							 //添加这一段代码  
	public slots://槽函数声明标志  
	void startMenge();
	void fileOpenActionSlot();//打开文件动作对应的槽函数  
	void openNewform(); //打开新的界面
	void openTestForm();  //打开测试界面
	void selectFile1();   //弹出选择文件对话框 

	void strategic_select1();  //战略选择
	void tactical_select1();  //战术选择
	void operation_select1();  //操作选择
	void environment_select1(); //环境选择

	void makeGlobalPlanPlugin();  //制作战略层插件
	void makeTacticPlanPlugin();  //制作战术层插件
	void makeOperationPlanPlugin();  //制作操作层插件
	void makeEnvironmentPlugin();  //制作操作层插件

private:	//存放文件路径
	std::string filePath;
	std::string SfilePath;
	std::string BfilePath;
	std::string VfilePath;

	std::string strategic_path; //战略层路径
	std::string tactical_path;  //战术层路径
	std::string operation_path;  //操作层路径
	std::vector<std::string> environment_path;  //环境层路径
signals: //传递文件路径
	void sendData(std::string filePath, std::string SfilePath, std::string BfilePath, std::string VfilePath);
};


#endif // QTMENGE_H
