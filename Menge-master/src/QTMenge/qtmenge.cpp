#pragma execution_character_set("utf-8")
#include "qtmenge.h"
#include "QMenu"  
#include "QMenuBar"  
#include "QAction"  
#include "QMessageBox"  
#include "QFileDialog"  
#include "QDebug" 
#include <QTextCodec>

#include "mengemain.h"
#include "globaldata.h"   //包含定义的一些全局变量



QTMenge::QTMenge(int argc, char *argv[], QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	total_info.clear(); //初始化插件存储信息

	createAction();
	createMenu();
	createContentMenu();
	//this->resize(430, 170);
	//timer = new QTimer(this);
	//添加关联代码，必须放在 setupUi 函数之后,信号与槽机制  
	/*connect(ui.button_start, SIGNAL(clicked()), this, SLOT(startMenge()));*/
	//connect(this, SIGNAL(sendData()), newform, SLOT(receiveData()));
	//connect(this, &QTMenge::sendData, newform, &XmlEdittor::receiveData);
	//connect(this, &QTMenge::sendData, newform1, &testWindow::receiveData);
	connect(ui.actionXml, SIGNAL(triggered()), this, SLOT(openNewform()));
	connect(ui.actionTEST, SIGNAL(triggered()), this, SLOT(openTestForm()));
	connect(ui.select_pbn, SIGNAL(clicked()), this, SLOT(selectFile1()));
	connect(ui.strategic_pbn,SIGNAL(clicked()), this, SLOT(strategic_select1()));
	connect(ui.tactical_pbn, SIGNAL(clicked()), this, SLOT(tactical_select1()));
	connect(ui.operation_pbn, SIGNAL(clicked()), this, SLOT(operation_select1()));
	connect(ui.environment_selcet_pbn, SIGNAL(clicked()), this, SLOT(environment_select1()));
	connect(ui.startMengeButton, SIGNAL(clicked()), this, SLOT(startMenge()));
	connect(ui.GlobalPlanMaker, SIGNAL(triggered()),this, SLOT(makeGlobalPlanPlugin()));
	connect(ui.TacticPlanMaker, SIGNAL(triggered()), this, SLOT(makeTacticPlanPlugin()));
	connect(ui.OperationPlanMaker, SIGNAL(triggered()), this, SLOT(makeOperationPlanPlugin()));
	connect(ui.EnvironmentMaker, SIGNAL(triggered()), this, SLOT(makeEnvironmentPlugin()));
	
}



QTMenge::~QTMenge()
{
	
}

void QTMenge::createAction()
{

	//创建打开文件动作 
	//fileOpenAction = new QAction(QIcon(tr("images/open.ico")), tr("打开文件"), this);  //可以设置图标
	fileOpenAction = new QAction("\xE9\x80\x89\xE6\x8B\xA9\xE6\x96\x87\xE4\xBB\xB6", this);//选择文件
															   //摄者打开文件的快捷方式  
	fileOpenAction->setShortcut(tr("Ctrl+O"));
	//设置打开文件动作提示信息  
	fileOpenAction->setStatusTip("\xE5\x85\x88\xE9\x80\x89\xE6\x8B\xA9\xE4\xB8\x80\xE4\xB8\xAA\x78\x6D\x6C\xE6\x96\x87\xE4\xBB\xB6\x2C\xE6\x89\x8D\xE8\x83\xBD\xE5\xBC\x80\xE5\xA7\x8B\xE5\xAE\x9E\xE9\xAA\x8C\x21");//选择文件
																														 //关联打开文件动作的信号和槽  
	connect(fileOpenAction, SIGNAL(triggered()), this, SLOT(fileOpenActionSlot()));
	
}

void QTMenge::createMenu()
{
	//this->menuBar()->setGeometry(0, 0, this->width(), 23);
	//menu = this->menuBar()->addMenu(tr("\xE6\x96\x87\xE4\xBB\xB6\x0D\x0A"));//文件
	//menu->addAction(fileOpenAction);
	//menu->setStyleSheet(
	//	" QMenu {\
 // background-color: white; /* sets background of the menu 设置整个菜单区域的背景色，我用的是白色：white*/\
 // border: 1px solid white;/*整个菜单区域的边框粗细、样式、颜色*/\
 // }\
 // QMenu::item {\
 // /* sets background of menu item. set this to something non-transparent\
 // if you want menu color and menu item color to be different */\
 // background-color: transparent;\
 // padding:4px 16px;/*设置菜单项文字上下和左右的内边距，效果就是菜单中的条目左右上下有了间隔*/\
 // margin:0px 4px;/*设置菜单项的外边距*/\
 // border-bottom:1px solid #DBDBDB;/*为菜单项之间添加横线间隔*/\
 // }\
 // QMenu::item:selected { /* when user selects item using mouse or keyboard */\
 // background-color: #2dabf9;/*这一句是设置菜单项鼠标经过选中的样式*/\
 // }"

	//);
}

void QTMenge::createContentMenu()
{
	this->addAction(fileOpenAction);
	this->setContextMenuPolicy(Qt::ActionsContextMenu);
}

//打开新的界面
void QTMenge::openNewform() 
{
	//将字符串路径传递给下一个界面
	emit sendData(filePath, SfilePath, BfilePath, VfilePath);
	std::cout << "filePath: " << filePath << std::endl;
	std::cout << "SfilePath: " << SfilePath << std::endl;
	std::cout << "VfilePath: " << VfilePath << std::endl;
	std::cout << "BfilePath: " << BfilePath << std::endl;
	
	//newform->show();

}

//打开测试界面
void QTMenge::openTestForm()
{
	emit sendData(filePath, SfilePath, BfilePath, VfilePath);
	//newform1->show();
}

void QTMenge::fileOpenActionSlot()
{
	//QMessageBox::warning(this,tr("提示"),tr("打开文件"),QMessageBox::Yes|QMessageBox::No);  
	selectFile();
}
/****************************************
* Qt中使用文件选择对话框步骤如下：
* 1. 定义一个QFileDialog对象
* 2. 设置路径、过滤器等属性
*****************************************/
void QTMenge::selectFile()
{
	QString temp = "";
	////定义文件对话框类  
	QFileDialog *fileDialog = new QFileDialog(this);
	////定义文件对话框标题  
	fileDialog->setWindowTitle(tr("\xE9\x80\x89\xE6\x8B\xA9\xE6\x96\x87\xE4\xBB\xB6"));//选择文件
	////设置文件过滤器  
	fileDialog->setNameFilter(tr("Files(*.xml)"));
	////设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles  
	fileDialog->setFileMode(QFileDialog::ExistingFiles);
	////设置视图模式  
	fileDialog->setViewMode(QFileDialog::Detail);
	////设置默认打开位置																				   //设置默认文件路径  
	fileDialog->setDirectory("..\\..\\..\\examples\\core");
	////打印所有选择的文件的路径  
	QStringList fileNames;
	if (fileDialog->exec())
	{
		fileNames = fileDialog->selectedFiles();
	}
	for (auto tmp : fileNames) {
		qDebug() << tmp << endl;
		ui.filePathInput->setText(tmp);//设置单行文本的内容
		temp = tmp;
	QByteArray ba = tmp.toLatin1(); 
	strcpy(argv_global[2], ba.data());
	//QString str = ui.text_path->toPlainText();
	//获取内容
	}

	//得到文件的路径
	//filePath = temp;
	//std::string roughPath = SplitString(filePath.toStdString(), ".xml");


	////用正则表达式来提取路径字符串
	//std::string pathStr = temp.toStdString();
	//std::string xmlFileName = "";
	//std::string pattern = ".*\\/(\\w+\\.xml)";
	//std::regex re(pattern);
	//std::string xmlDir = "";
	//std::string fileProName = "";
	//std::smatch matchResult; // std::match_results<string::const_iterator> matchResult;
	//if (std::regex_match(pathStr, matchResult, re))
	//{
	//	//提取出链接中的"\\w+\\.xml"
	//	xmlFileName = matchResult[1].str();
	//	//获得提取出来的字符串的长度
	//	int strLength = xmlFileName.length();
	//	//从字符串最后开始开始删除strLength长度的字符串，结果就是目录
	//	pathStr.erase(pathStr.end() - strLength, pathStr.end());
	//	xmlDir = pathStr;  //目录
	//}

	//std::string::size_type length = xmlFileName.size();
	//length = length - 4;
	//fileProName = xmlFileName.substr(0, length);
	//filePath = temp.toStdString();
	//
	//SfilePath = xmlDir + fileProName + "/" + fileProName + "S.xml";
	//BfilePath = xmlDir + fileProName + "/" + fileProName + "B.xml";
	//VfilePath = xmlDir + fileProName + "/" + fileProName + "V.xml";
	
	delete fileDialog;
}

//selectFile1是槽函数，调用了selectFile函数来选择文件
void QTMenge::selectFile1()
{
	selectFile();
}





//战略选择 槽函数
void QTMenge::strategic_select1()
{
	strategic_select();

}

//战术选择 槽函数
void QTMenge::tactical_select1()
{
	tactical_select();
}

//操作选择 槽函数
void QTMenge::operation_select1()
{
	operation_select();
}

//环境选择 槽函数
void QTMenge::environment_select1()
{
	environment_select();
}



//战略层选择模块
void QTMenge::strategic_select()
{
	ui.strategic_lineEdit->setText(QString::fromStdString(""));

	std::cout << "strategic_select" << std::endl;
	//弹出一个界面来解析dll文件，从中提取出来我们需要的对象
	//newform2->show();

	////定义文件对话框类  
	QFileDialog *fileDialog = new QFileDialog(this);
	////定义文件对话框标题  
	fileDialog->setWindowTitle(tr("选择战略模块"));//选择文件
    //设置默认文件路径  
	fileDialog->setDirectory("..\\..\\..\\Exe\\DllPlugins\\GlobalPlan");
	////设置文件过滤器  
	fileDialog->setNameFilter(tr("Files(*.dll)"));
	////设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles  
	fileDialog->setFileMode(QFileDialog::ExistingFiles);
	////设置视图模式  
	fileDialog->setViewMode(QFileDialog::Detail);
	////打印所有选择的文件的路径  
	QStringList fileNames;
	if (fileDialog->exec())
	{
		fileNames = fileDialog->selectedFiles();
	}
	for (auto tmp : fileNames) {
		qDebug() << tmp;
		//获得插件的绝对路径
		strategic_path = tmp.toStdString();
	}

	//解析插件获得工厂类
	parse_globalplan_plugin(strategic_path);

	//显示在界面上
	ui.strategic_lineEdit->setText(QString::fromStdString(globalplan_name));

	delete fileDialog;

	
}

//战术层选择模块
void QTMenge::tactical_select()
{
	ui.tactical_lineEdit->setText(QString::fromStdString(""));

	std::cout << "tactical_select" << std::endl;
	//newform3->show();

	////定义文件对话框类  
	QFileDialog *fileDialog = new QFileDialog(this);
	////定义文件对话框标题  
	fileDialog->setWindowTitle(tr("选择战术模块"));//选择文件
																					   //																				   //设置默认文件路径  
	fileDialog->setDirectory("..\\..\\..\\Exe\\DllPlugins\\TacticalPlan");
	////设置文件过滤器  
	fileDialog->setNameFilter(tr("Files(*.dll)"));
	////设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles  
	fileDialog->setFileMode(QFileDialog::ExistingFiles);
	////设置视图模式  
	fileDialog->setViewMode(QFileDialog::Detail);
	////打印所有选择的文件的路径  
	QStringList fileNames;
	if (fileDialog->exec())
	{
		fileNames = fileDialog->selectedFiles();
	}
	for (auto tmp : fileNames) {
		qDebug() << tmp;
		//获得插件的绝对路径
		tactical_path = tmp.toStdString();
	}

	//解析插件获得工厂类
	parse_tacticalplan_plugin(tactical_path);

	//显示在界面上
	ui.tactical_lineEdit->setText(QString::fromStdString(tacticalplan_name));

	delete fileDialog;
}

//操作层选择模块
void QTMenge::operation_select()
{
	ui.operation_lineEdit->setText(QString::fromStdString(""));

	std::cout << "operation_select" << std::endl;
	//newform4->show();
	////定义文件对话框类  
	QFileDialog *fileDialog = new QFileDialog(this);
	////定义文件对话框标题  
	fileDialog->setWindowTitle(tr("选择操作模块"));//选择文件
	//设置默认文件路径  
	fileDialog->setDirectory("..\\..\\..\\Exe\\DllPlugins\\OperationPlan");
	////设置文件过滤器  
	fileDialog->setNameFilter(tr("Files(*.dll)"));
	////设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles  
	fileDialog->setFileMode(QFileDialog::ExistingFiles);
	////设置视图模式  
	fileDialog->setViewMode(QFileDialog::Detail);
	////打印所有选择的文件的路径  
	QStringList fileNames;
	if (fileDialog->exec())
	{
		fileNames = fileDialog->selectedFiles();
	}
	for (auto tmp : fileNames) {
		qDebug() << tmp;
		//获得插件的绝对路径
		operation_path = tmp.toStdString();
	}

	//解析插件获得工厂类
	parse_operationplan_plugin(operation_path);

	//显示在界面上
	ui.operation_lineEdit->setText(QString::fromStdString(operationplan_name));

	delete fileDialog;
}

//环境选择模块
void QTMenge::environment_select()
{
	ui.environment_lineEdit->clear();
	environment_path.clear();
	//environmentalChangeSet.clear();

	std::cout << "environment_select" << std::endl;
	////定义文件对话框类  
	//QFileDialog *fileDialog = new QFileDialog(this);
	QFileDialog fileDialog(this);
	////定义文件对话框标题  
	fileDialog.setWindowTitle(tr("选择环境模块"));//选择文件
	//设置默认文件路径  
	fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
	fileDialog.setDirectory(QString("..\\..\\..\\Exe\\DllPlugins\\EnvironmentalChange"));
	////设置文件过滤器  
	fileDialog.setNameFilter(tr("Files(*.dll)"));
	////设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles  
	fileDialog.setFileMode(QFileDialog::ExistingFiles);
	////设置视图模式  
	fileDialog.setViewMode(QFileDialog::Detail);
	////打印所有选择的文件的路径  
	QStringList fileNames;
	if (fileDialog.exec())
	{
		fileNames = fileDialog.selectedFiles();
	}
	for (auto tmp : fileNames) {
		qDebug() << tmp;
		//获得插件的绝对路径

		//这里可能有多个文件，文件是多选模式
		environment_path.push_back(tmp.toStdString());
		
	}

	//解析插件获得工厂类
	parse_environment_plugin(environment_path);

	//显示在界面上
	//ui.environment_lineEdit->setText(QString::fromStdString(environment_name));

	//delete fileDialog;



}



//解析战略层插件
void QTMenge::parse_globalplan_plugin(std::string path)
{
	//清空界面上显示的总的信息
	show_info = "";

	//清空插件存储信息
	total_info["globalplan_info"] = "";

	std::cout << "parse_plugin" << std::endl;
	// 获得当前的插件dll的路径
	std::string temp = path;
	const char *tempchar = temp.c_str();
	//std::cout << tmp.toStdString() << std::endl;
	//下面是解析插件的过程
	using pExport = Menge::Agents::GlobalPlanFactory* (*)(void); // 定义指向导出函数的指针类型

	const char *str = tempchar;
	//下面是将const char*转化为WCHAR类型的数
	WCHAR wszClassName[256];
	memset(wszClassName, 0, sizeof(wszClassName));
	MultiByteToWideChar(CP_ACP, 0, str, strlen(str) + 1, wszClassName, sizeof(wszClassName) / sizeof(wszClassName[0]));
	HINSTANCE hDll = LoadLibrary(wszClassName);// 加载DLL库文件，DLL名称和路径用自己的

	if (hDll == NULL) {
		std::cout << "load dll fail \n";
	}
	else {
		pExport Get = (pExport)GetProcAddress(hDll, "Export");// 将指针指向函数首地址
		if (Get == NULL) {
			std::cout << "load address fail \n";
		}
		else {
			Menge::Agents::GlobalPlanFactory* t = Get();// 调用导出函数获得抽象类指针
														//addFactory(t);
			Menge::Agents::GlobalPlan* tt = t->createInstance();
			globalplan = tt;  //将获得的工厂类保存在全局变量里面

							  //将战略层插件名字放在全局变量里，从而传递给主界面
			std::string showData = t->name();
			globalplan_name = showData;
			globalplan_info = t->description();
		}

	}
	
	//存储插件信息
	total_info["globalplan_info"] = "\xE6\x88\x98\xE7\x95\xA5\xE5\xB1\x82\xE8\xAF\xA6\xE6\x83\x85\xEF\xBC\x9A" + globalplan_info + "\n";

	//拼接最终显示的信息
	show_info = total_info["globalplan_info"] + total_info["tacticalplan_info"] + total_info["operationplan_info"] + total_info["environment_info"];

	//将插件信息显示在界面上
	ui.info_text->clear();
	ui.info_text->appendPlainText(QString::fromStdString(show_info));
}

//解析战术层插件
void QTMenge::parse_tacticalplan_plugin(std::string path)
{
	//清空显示信息
	show_info = "";

	//清空插件存储信息
	total_info["tacticalplan_info"] = "";

	std::cout << "parse_plugin" << std::endl;
	// 获得当前的插件dll的路径
	std::string temp = path;
	const char *tempchar = temp.c_str();
	//std::cout << tmp.toStdString() << std::endl;
	//下面是解析插件的过程
	using pExport = Menge::Agents::TacticalPlanFactory* (*)(void); // 定义指向导出函数的指针类型

	const char *str = tempchar;
	//下面是将const char*转化为WCHAR类型的数
	WCHAR wszClassName[256];
	memset(wszClassName, 0, sizeof(wszClassName));
	MultiByteToWideChar(CP_ACP, 0, str, strlen(str) + 1, wszClassName, sizeof(wszClassName) / sizeof(wszClassName[0]));
	HINSTANCE hDll = LoadLibrary(wszClassName);// 加载DLL库文件，DLL名称和路径用自己的

	if (hDll == NULL) {
		std::cout << "load dll fail \n";
	}
	else {
		pExport Get = (pExport)GetProcAddress(hDll, "Export");// 将指针指向函数首地址
		if (Get == NULL) {
			std::cout << "load address fail \n";
		}
		else {
			Menge::Agents::TacticalPlanFactory* t = Get();// 调用导出函数获得抽象类指针
														//addFactory(t);
			Menge::Agents::TacticalPlan* tt = t->createInstance();
			tacticalplan = tt;  //将获得的工厂类保存在全局变量里面

							  //将战略层插件名字放在全局变量里，从而传递给主界面
			std::string showData = t->name();
			tacticalplan_name = showData;
			tacticalplan_info = t->description();
		}

	}
	
	//存储插件信息
	total_info["tacticalplan_info"] = "\xE6\x88\x98\xE6\x9C\xAF\xE5\xB1\x82\xE8\xAF\xA6\xE6\x83\x85\xEF\xBC\x9A" + tacticalplan_info + "\n";

	//拼接最终显示的信息
	show_info = total_info["globalplan_info"] + total_info["tacticalplan_info"] + total_info["operationplan_info"] + total_info["environment_info"];

	//将插件信息显示在界面上
	ui.info_text->clear();
	ui.info_text->appendPlainText(QString::fromStdString(show_info));
}

//解析操作层插件
void QTMenge::parse_operationplan_plugin(std::string path)
{
	//清空显示的总的信息
	show_info = "";

	//清空插件存储信息
	total_info["operationplan_info"] = "";

	std::cout << "parse_plugin" << std::endl;
	// 获得当前的插件dll的路径
	std::string temp = path;
	const char *tempchar = temp.c_str();
	//std::cout << tmp.toStdString() << std::endl;
	//下面是解析插件的过程
	using pExport = Menge::Agents::OperationPlanFactory* (*)(void); // 定义指向导出函数的指针类型

	const char *str = tempchar;
	//下面是将const char*转化为WCHAR类型的数
	WCHAR wszClassName[256];
	memset(wszClassName, 0, sizeof(wszClassName));
	MultiByteToWideChar(CP_ACP, 0, str, strlen(str) + 1, wszClassName, sizeof(wszClassName) / sizeof(wszClassName[0]));
	HINSTANCE hDll = LoadLibrary(wszClassName);// 加载DLL库文件，DLL名称和路径用自己的

	if (hDll == NULL) {
		std::cout << "load dll fail \n";
	}
	else {
		pExport Get = (pExport)GetProcAddress(hDll, "Export");// 将指针指向函数首地址
		if (Get == NULL) {
			std::cout << "load address fail \n";
		}
		else {
			Menge::Agents::OperationPlanFactory* t = Get();// 调用导出函数获得抽象类指针
														//addFactory(t);
			Menge::Agents::OperationPlan* tt = t->createInstance();
			operationplan = tt;  //将获得的工厂类保存在全局变量里面

							  //将战略层插件名字放在全局变量里，从而传递给主界面
			std::string showData = t->name();
			operationplan_name = showData;
			operationplan_info = t->description();
		}

	}
	
	//存储插件信息
	total_info["operationplan_info"] = "\xE6\x93\x8D\xE4\xBD\x9C\xE5\xB1\x82\xE8\xAF\xA6\xE6\x83\x85\xEF\xBC\x9A" + operationplan_info + "\n";

	//拼接最终显示的信息
	show_info = total_info["globalplan_info"] + total_info["tacticalplan_info"] + total_info["operationplan_info"] + total_info["environment_info"];

	//将插件信息显示在界面上
	ui.info_text->clear();
	ui.info_text->appendPlainText(QString::fromStdString(show_info));
}

//解析环境层插件
void QTMenge::parse_environment_plugin(std::vector<std::string> path)
{
	//清空总的显示信息
	show_info = "";
	//清空信息
	environment_info_vector.clear();
	total_info["environment_info"] = "";
	environment_name.clear();

	for (auto it : path)
	{
		// 获得当前的插件dll的路径
		std::string temp = it;
		const char *tempchar = temp.c_str();
		//std::cout << tmp.toStdString() << std::endl;
		//下面是解析插件的过程
		using pExport = Menge::Agents::EnvironmentalChangeFactory* (*)(void); // 定义指向导出函数的指针类型

		const char *str = tempchar;
		//下面是将const char*转化为WCHAR类型的数
		WCHAR wszClassName[256];
		memset(wszClassName, 0, sizeof(wszClassName));
		MultiByteToWideChar(CP_ACP, 0, str, strlen(str) + 1, wszClassName, sizeof(wszClassName) / sizeof(wszClassName[0]));
		HINSTANCE hDll = LoadLibrary(wszClassName);// 加载DLL库文件，DLL名称和路径用自己的

		if (hDll == NULL) {
			std::cout << "load dll fail \n";
		}
		else {
			pExport Get = (pExport)GetProcAddress(hDll, "Export");// 将指针指向函数首地址
			if (Get == NULL) {
				std::cout << "load address fail \n";
			}
			else {
				Menge::Agents::EnvironmentalChangeFactory* t = Get();// 调用导出函数获得抽象类指针
				//addFactory(t);
				Menge::Agents::EnvironmentalChange* tt = t->createInstance();
				environmentalChangeSet.push_back(tt);  //将获得的工厂类保存在全局变量里面

				//将战略层插件名字放在全局变量里，从而传递给主界面
				std::string showData = t->name();
				environment_name.push_back(showData);
				environment_info_vector.push_back(t->description());
			}

		}
	}

	//拼接插件信息
	for (auto it : environment_info_vector)
	{
		total_info["environment_info"] +="\xE7\x8E\xAF\xE5\xA2\x83\xE5\xB1\x82\xE8\xAF\xA6\xE6\x83\x85\xEF\xBC\x9A"+ it + "\n";
	}
	
	//拼接最终显示的信息
	show_info = total_info["globalplan_info"] + total_info["tacticalplan_info"] + total_info["operationplan_info"] + total_info["environment_info"];

	//将插件信息显示在界面上
	ui.info_text->clear();
	ui.info_text->appendPlainText(QString::fromStdString(show_info));

	std::string temp = "";
	for (auto it : environment_name)
	{
		temp += '[' + it + ']';
	}

	//显示在界面上

	ui.environment_lineEdit->setText(QString::fromStdString(temp));
}




//制作战略层插件
void QTMenge::makeGlobalPlanPlugin()
{
	std::cout << "makeGlobalPlanPlugin" << std::endl;

	std::string pathStr = "C:\\Users\\lhb\\Desktop\\Menge-master315\\Menge-master\\projects\\VS2013\\globalPlanMaker.bat";
	system(pathStr.c_str());

}

//制作战术层插件
void QTMenge::makeTacticPlanPlugin()
{
	std::cout << "makeTacticalPlanPlugin" << std::endl;

	std::string pathStr = "C:\\Users\\lhb\\Desktop\\Menge-master315\\Menge-master\\projects\\VS2013\\TacticalPlanMaker.bat";
	system(pathStr.c_str());
}

//制作操作层插件
void QTMenge::makeOperationPlanPlugin()
{
	std::cout << "makeOperatinPlanPlugin" << std::endl;

	std::string pathStr ="C:\\Users\\lhb\\Desktop\\Menge-master315\\Menge-master\\projects\\VS2013\\OperationPlanMaker.bat";
	system(pathStr.c_str());
}

//制作环境层插件
void QTMenge::makeEnvironmentPlugin()
{
	std::string pathStr = "C:\\Users\\lhb\\Desktop\\Menge-master315\\Menge-master\\projects\\VS2013\\EnvironmentMaker.bat";
	system(pathStr.c_str());
}


void QTMenge::startMenge() {
	
	globaldata_model = "orca";
	////判断选择的实验文件
	const QString valueStr = ui.filePathInput->text();

	viewer_name = ui.viewer_lineEdit->text().toStdString();//字符串控制选择viewer

	if (!valueStr.isEmpty()) {
		QByteArray ba = valueStr.toLatin1();
		strcpy(argv_global[2], ba.data());
		strcpy(globaldata_argv[2], ba.data());
		mengemain(globaldata_argc, globaldata_argv);
	}
	else {

		QMessageBox::warning(this, "\xE6\x8F\x90\xE7\xA4\xBA", "\xE8\xAF\xB7\xE5\x85\x88\xE9\x80\x89\xE6\x8B\xA9\xE5\xAE\x9E\xE9\xAA\x8C\xE6\x96\x87\xE4\xBB\xB6\x21\x21", QMessageBox::Yes);
	}

	printf("获取路径");

}

