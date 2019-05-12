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
#include "globaldata.h"   //���������һЩȫ�ֱ���



QTMenge::QTMenge(int argc, char *argv[], QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	total_info.clear(); //��ʼ������洢��Ϣ

	createAction();
	createMenu();
	createContentMenu();
	//this->resize(430, 170);
	//timer = new QTimer(this);
	//��ӹ������룬������� setupUi ����֮��,�ź���ۻ���  
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

	//�������ļ����� 
	//fileOpenAction = new QAction(QIcon(tr("images/open.ico")), tr("���ļ�"), this);  //��������ͼ��
	fileOpenAction = new QAction("\xE9\x80\x89\xE6\x8B\xA9\xE6\x96\x87\xE4\xBB\xB6", this);//ѡ���ļ�
															   //���ߴ��ļ��Ŀ�ݷ�ʽ  
	fileOpenAction->setShortcut(tr("Ctrl+O"));
	//���ô��ļ�������ʾ��Ϣ  
	fileOpenAction->setStatusTip("\xE5\x85\x88\xE9\x80\x89\xE6\x8B\xA9\xE4\xB8\x80\xE4\xB8\xAA\x78\x6D\x6C\xE6\x96\x87\xE4\xBB\xB6\x2C\xE6\x89\x8D\xE8\x83\xBD\xE5\xBC\x80\xE5\xA7\x8B\xE5\xAE\x9E\xE9\xAA\x8C\x21");//ѡ���ļ�
																														 //�������ļ��������źźͲ�  
	connect(fileOpenAction, SIGNAL(triggered()), this, SLOT(fileOpenActionSlot()));
	
}

void QTMenge::createMenu()
{
	//this->menuBar()->setGeometry(0, 0, this->width(), 23);
	//menu = this->menuBar()->addMenu(tr("\xE6\x96\x87\xE4\xBB\xB6\x0D\x0A"));//�ļ�
	//menu->addAction(fileOpenAction);
	//menu->setStyleSheet(
	//	" QMenu {\
 // background-color: white; /* sets background of the menu ���������˵�����ı���ɫ�����õ��ǰ�ɫ��white*/\
 // border: 1px solid white;/*�����˵�����ı߿��ϸ����ʽ����ɫ*/\
 // }\
 // QMenu::item {\
 // /* sets background of menu item. set this to something non-transparent\
 // if you want menu color and menu item color to be different */\
 // background-color: transparent;\
 // padding:4px 16px;/*���ò˵����������º����ҵ��ڱ߾࣬Ч�����ǲ˵��е���Ŀ�����������˼��*/\
 // margin:0px 4px;/*���ò˵������߾�*/\
 // border-bottom:1px solid #DBDBDB;/*Ϊ�˵���֮����Ӻ��߼��*/\
 // }\
 // QMenu::item:selected { /* when user selects item using mouse or keyboard */\
 // background-color: #2dabf9;/*��һ�������ò˵�����꾭��ѡ�е���ʽ*/\
 // }"

	//);
}

void QTMenge::createContentMenu()
{
	this->addAction(fileOpenAction);
	this->setContextMenuPolicy(Qt::ActionsContextMenu);
}

//���µĽ���
void QTMenge::openNewform() 
{
	//���ַ���·�����ݸ���һ������
	emit sendData(filePath, SfilePath, BfilePath, VfilePath);
	std::cout << "filePath: " << filePath << std::endl;
	std::cout << "SfilePath: " << SfilePath << std::endl;
	std::cout << "VfilePath: " << VfilePath << std::endl;
	std::cout << "BfilePath: " << BfilePath << std::endl;
	
	//newform->show();

}

//�򿪲��Խ���
void QTMenge::openTestForm()
{
	emit sendData(filePath, SfilePath, BfilePath, VfilePath);
	//newform1->show();
}

void QTMenge::fileOpenActionSlot()
{
	//QMessageBox::warning(this,tr("��ʾ"),tr("���ļ�"),QMessageBox::Yes|QMessageBox::No);  
	selectFile();
}
/****************************************
* Qt��ʹ���ļ�ѡ��Ի��������£�
* 1. ����һ��QFileDialog����
* 2. ����·����������������
*****************************************/
void QTMenge::selectFile()
{
	QString temp = "";
	////�����ļ��Ի�����  
	QFileDialog *fileDialog = new QFileDialog(this);
	////�����ļ��Ի������  
	fileDialog->setWindowTitle(tr("\xE9\x80\x89\xE6\x8B\xA9\xE6\x96\x87\xE4\xBB\xB6"));//ѡ���ļ�
	////�����ļ�������  
	fileDialog->setNameFilter(tr("Files(*.xml)"));
	////���ÿ���ѡ�����ļ�,Ĭ��Ϊֻ��ѡ��һ���ļ�QFileDialog::ExistingFiles  
	fileDialog->setFileMode(QFileDialog::ExistingFiles);
	////������ͼģʽ  
	fileDialog->setViewMode(QFileDialog::Detail);
	////����Ĭ�ϴ�λ��																				   //����Ĭ���ļ�·��  
	fileDialog->setDirectory("..\\..\\..\\examples\\core");
	////��ӡ����ѡ����ļ���·��  
	QStringList fileNames;
	if (fileDialog->exec())
	{
		fileNames = fileDialog->selectedFiles();
	}
	for (auto tmp : fileNames) {
		qDebug() << tmp << endl;
		ui.filePathInput->setText(tmp);//���õ����ı�������
		temp = tmp;
	QByteArray ba = tmp.toLatin1(); 
	strcpy(argv_global[2], ba.data());
	//QString str = ui.text_path->toPlainText();
	//��ȡ����
	}

	//�õ��ļ���·��
	//filePath = temp;
	//std::string roughPath = SplitString(filePath.toStdString(), ".xml");


	////��������ʽ����ȡ·���ַ���
	//std::string pathStr = temp.toStdString();
	//std::string xmlFileName = "";
	//std::string pattern = ".*\\/(\\w+\\.xml)";
	//std::regex re(pattern);
	//std::string xmlDir = "";
	//std::string fileProName = "";
	//std::smatch matchResult; // std::match_results<string::const_iterator> matchResult;
	//if (std::regex_match(pathStr, matchResult, re))
	//{
	//	//��ȡ�������е�"\\w+\\.xml"
	//	xmlFileName = matchResult[1].str();
	//	//�����ȡ�������ַ����ĳ���
	//	int strLength = xmlFileName.length();
	//	//���ַ������ʼ��ʼɾ��strLength���ȵ��ַ������������Ŀ¼
	//	pathStr.erase(pathStr.end() - strLength, pathStr.end());
	//	xmlDir = pathStr;  //Ŀ¼
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

//selectFile1�ǲۺ�����������selectFile������ѡ���ļ�
void QTMenge::selectFile1()
{
	selectFile();
}





//ս��ѡ�� �ۺ���
void QTMenge::strategic_select1()
{
	strategic_select();

}

//ս��ѡ�� �ۺ���
void QTMenge::tactical_select1()
{
	tactical_select();
}

//����ѡ�� �ۺ���
void QTMenge::operation_select1()
{
	operation_select();
}

//����ѡ�� �ۺ���
void QTMenge::environment_select1()
{
	environment_select();
}



//ս�Բ�ѡ��ģ��
void QTMenge::strategic_select()
{
	ui.strategic_lineEdit->setText(QString::fromStdString(""));

	std::cout << "strategic_select" << std::endl;
	//����һ������������dll�ļ���������ȡ����������Ҫ�Ķ���
	//newform2->show();

	////�����ļ��Ի�����  
	QFileDialog *fileDialog = new QFileDialog(this);
	////�����ļ��Ի������  
	fileDialog->setWindowTitle(tr("ѡ��ս��ģ��"));//ѡ���ļ�
    //����Ĭ���ļ�·��  
	fileDialog->setDirectory("..\\..\\..\\Exe\\DllPlugins\\GlobalPlan");
	////�����ļ�������  
	fileDialog->setNameFilter(tr("Files(*.dll)"));
	////���ÿ���ѡ�����ļ�,Ĭ��Ϊֻ��ѡ��һ���ļ�QFileDialog::ExistingFiles  
	fileDialog->setFileMode(QFileDialog::ExistingFiles);
	////������ͼģʽ  
	fileDialog->setViewMode(QFileDialog::Detail);
	////��ӡ����ѡ����ļ���·��  
	QStringList fileNames;
	if (fileDialog->exec())
	{
		fileNames = fileDialog->selectedFiles();
	}
	for (auto tmp : fileNames) {
		qDebug() << tmp;
		//��ò���ľ���·��
		strategic_path = tmp.toStdString();
	}

	//���������ù�����
	parse_globalplan_plugin(strategic_path);

	//��ʾ�ڽ�����
	ui.strategic_lineEdit->setText(QString::fromStdString(globalplan_name));

	delete fileDialog;

	
}

//ս����ѡ��ģ��
void QTMenge::tactical_select()
{
	ui.tactical_lineEdit->setText(QString::fromStdString(""));

	std::cout << "tactical_select" << std::endl;
	//newform3->show();

	////�����ļ��Ի�����  
	QFileDialog *fileDialog = new QFileDialog(this);
	////�����ļ��Ի������  
	fileDialog->setWindowTitle(tr("ѡ��ս��ģ��"));//ѡ���ļ�
																					   //																				   //����Ĭ���ļ�·��  
	fileDialog->setDirectory("..\\..\\..\\Exe\\DllPlugins\\TacticalPlan");
	////�����ļ�������  
	fileDialog->setNameFilter(tr("Files(*.dll)"));
	////���ÿ���ѡ�����ļ�,Ĭ��Ϊֻ��ѡ��һ���ļ�QFileDialog::ExistingFiles  
	fileDialog->setFileMode(QFileDialog::ExistingFiles);
	////������ͼģʽ  
	fileDialog->setViewMode(QFileDialog::Detail);
	////��ӡ����ѡ����ļ���·��  
	QStringList fileNames;
	if (fileDialog->exec())
	{
		fileNames = fileDialog->selectedFiles();
	}
	for (auto tmp : fileNames) {
		qDebug() << tmp;
		//��ò���ľ���·��
		tactical_path = tmp.toStdString();
	}

	//���������ù�����
	parse_tacticalplan_plugin(tactical_path);

	//��ʾ�ڽ�����
	ui.tactical_lineEdit->setText(QString::fromStdString(tacticalplan_name));

	delete fileDialog;
}

//������ѡ��ģ��
void QTMenge::operation_select()
{
	ui.operation_lineEdit->setText(QString::fromStdString(""));

	std::cout << "operation_select" << std::endl;
	//newform4->show();
	////�����ļ��Ի�����  
	QFileDialog *fileDialog = new QFileDialog(this);
	////�����ļ��Ի������  
	fileDialog->setWindowTitle(tr("ѡ�����ģ��"));//ѡ���ļ�
	//����Ĭ���ļ�·��  
	fileDialog->setDirectory("..\\..\\..\\Exe\\DllPlugins\\OperationPlan");
	////�����ļ�������  
	fileDialog->setNameFilter(tr("Files(*.dll)"));
	////���ÿ���ѡ�����ļ�,Ĭ��Ϊֻ��ѡ��һ���ļ�QFileDialog::ExistingFiles  
	fileDialog->setFileMode(QFileDialog::ExistingFiles);
	////������ͼģʽ  
	fileDialog->setViewMode(QFileDialog::Detail);
	////��ӡ����ѡ����ļ���·��  
	QStringList fileNames;
	if (fileDialog->exec())
	{
		fileNames = fileDialog->selectedFiles();
	}
	for (auto tmp : fileNames) {
		qDebug() << tmp;
		//��ò���ľ���·��
		operation_path = tmp.toStdString();
	}

	//���������ù�����
	parse_operationplan_plugin(operation_path);

	//��ʾ�ڽ�����
	ui.operation_lineEdit->setText(QString::fromStdString(operationplan_name));

	delete fileDialog;
}

//����ѡ��ģ��
void QTMenge::environment_select()
{
	ui.environment_lineEdit->clear();
	environment_path.clear();
	//environmentalChangeSet.clear();

	std::cout << "environment_select" << std::endl;
	////�����ļ��Ի�����  
	//QFileDialog *fileDialog = new QFileDialog(this);
	QFileDialog fileDialog(this);
	////�����ļ��Ի������  
	fileDialog.setWindowTitle(tr("ѡ�񻷾�ģ��"));//ѡ���ļ�
	//����Ĭ���ļ�·��  
	fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
	fileDialog.setDirectory(QString("..\\..\\..\\Exe\\DllPlugins\\EnvironmentalChange"));
	////�����ļ�������  
	fileDialog.setNameFilter(tr("Files(*.dll)"));
	////���ÿ���ѡ�����ļ�,Ĭ��Ϊֻ��ѡ��һ���ļ�QFileDialog::ExistingFiles  
	fileDialog.setFileMode(QFileDialog::ExistingFiles);
	////������ͼģʽ  
	fileDialog.setViewMode(QFileDialog::Detail);
	////��ӡ����ѡ����ļ���·��  
	QStringList fileNames;
	if (fileDialog.exec())
	{
		fileNames = fileDialog.selectedFiles();
	}
	for (auto tmp : fileNames) {
		qDebug() << tmp;
		//��ò���ľ���·��

		//��������ж���ļ����ļ��Ƕ�ѡģʽ
		environment_path.push_back(tmp.toStdString());
		
	}

	//���������ù�����
	parse_environment_plugin(environment_path);

	//��ʾ�ڽ�����
	//ui.environment_lineEdit->setText(QString::fromStdString(environment_name));

	//delete fileDialog;



}



//����ս�Բ���
void QTMenge::parse_globalplan_plugin(std::string path)
{
	//��ս�������ʾ���ܵ���Ϣ
	show_info = "";

	//��ղ���洢��Ϣ
	total_info["globalplan_info"] = "";

	std::cout << "parse_plugin" << std::endl;
	// ��õ�ǰ�Ĳ��dll��·��
	std::string temp = path;
	const char *tempchar = temp.c_str();
	//std::cout << tmp.toStdString() << std::endl;
	//�����ǽ�������Ĺ���
	using pExport = Menge::Agents::GlobalPlanFactory* (*)(void); // ����ָ�򵼳�������ָ������

	const char *str = tempchar;
	//�����ǽ�const char*ת��ΪWCHAR���͵���
	WCHAR wszClassName[256];
	memset(wszClassName, 0, sizeof(wszClassName));
	MultiByteToWideChar(CP_ACP, 0, str, strlen(str) + 1, wszClassName, sizeof(wszClassName) / sizeof(wszClassName[0]));
	HINSTANCE hDll = LoadLibrary(wszClassName);// ����DLL���ļ���DLL���ƺ�·�����Լ���

	if (hDll == NULL) {
		std::cout << "load dll fail \n";
	}
	else {
		pExport Get = (pExport)GetProcAddress(hDll, "Export");// ��ָ��ָ�����׵�ַ
		if (Get == NULL) {
			std::cout << "load address fail \n";
		}
		else {
			Menge::Agents::GlobalPlanFactory* t = Get();// ���õ���������ó�����ָ��
														//addFactory(t);
			Menge::Agents::GlobalPlan* tt = t->createInstance();
			globalplan = tt;  //����õĹ����ౣ����ȫ�ֱ�������

							  //��ս�Բ������ַ���ȫ�ֱ�����Ӷ����ݸ�������
			std::string showData = t->name();
			globalplan_name = showData;
			globalplan_info = t->description();
		}

	}
	
	//�洢�����Ϣ
	total_info["globalplan_info"] = "\xE6\x88\x98\xE7\x95\xA5\xE5\xB1\x82\xE8\xAF\xA6\xE6\x83\x85\xEF\xBC\x9A" + globalplan_info + "\n";

	//ƴ��������ʾ����Ϣ
	show_info = total_info["globalplan_info"] + total_info["tacticalplan_info"] + total_info["operationplan_info"] + total_info["environment_info"];

	//�������Ϣ��ʾ�ڽ�����
	ui.info_text->clear();
	ui.info_text->appendPlainText(QString::fromStdString(show_info));
}

//����ս������
void QTMenge::parse_tacticalplan_plugin(std::string path)
{
	//�����ʾ��Ϣ
	show_info = "";

	//��ղ���洢��Ϣ
	total_info["tacticalplan_info"] = "";

	std::cout << "parse_plugin" << std::endl;
	// ��õ�ǰ�Ĳ��dll��·��
	std::string temp = path;
	const char *tempchar = temp.c_str();
	//std::cout << tmp.toStdString() << std::endl;
	//�����ǽ�������Ĺ���
	using pExport = Menge::Agents::TacticalPlanFactory* (*)(void); // ����ָ�򵼳�������ָ������

	const char *str = tempchar;
	//�����ǽ�const char*ת��ΪWCHAR���͵���
	WCHAR wszClassName[256];
	memset(wszClassName, 0, sizeof(wszClassName));
	MultiByteToWideChar(CP_ACP, 0, str, strlen(str) + 1, wszClassName, sizeof(wszClassName) / sizeof(wszClassName[0]));
	HINSTANCE hDll = LoadLibrary(wszClassName);// ����DLL���ļ���DLL���ƺ�·�����Լ���

	if (hDll == NULL) {
		std::cout << "load dll fail \n";
	}
	else {
		pExport Get = (pExport)GetProcAddress(hDll, "Export");// ��ָ��ָ�����׵�ַ
		if (Get == NULL) {
			std::cout << "load address fail \n";
		}
		else {
			Menge::Agents::TacticalPlanFactory* t = Get();// ���õ���������ó�����ָ��
														//addFactory(t);
			Menge::Agents::TacticalPlan* tt = t->createInstance();
			tacticalplan = tt;  //����õĹ����ౣ����ȫ�ֱ�������

							  //��ս�Բ������ַ���ȫ�ֱ�����Ӷ����ݸ�������
			std::string showData = t->name();
			tacticalplan_name = showData;
			tacticalplan_info = t->description();
		}

	}
	
	//�洢�����Ϣ
	total_info["tacticalplan_info"] = "\xE6\x88\x98\xE6\x9C\xAF\xE5\xB1\x82\xE8\xAF\xA6\xE6\x83\x85\xEF\xBC\x9A" + tacticalplan_info + "\n";

	//ƴ��������ʾ����Ϣ
	show_info = total_info["globalplan_info"] + total_info["tacticalplan_info"] + total_info["operationplan_info"] + total_info["environment_info"];

	//�������Ϣ��ʾ�ڽ�����
	ui.info_text->clear();
	ui.info_text->appendPlainText(QString::fromStdString(show_info));
}

//������������
void QTMenge::parse_operationplan_plugin(std::string path)
{
	//�����ʾ���ܵ���Ϣ
	show_info = "";

	//��ղ���洢��Ϣ
	total_info["operationplan_info"] = "";

	std::cout << "parse_plugin" << std::endl;
	// ��õ�ǰ�Ĳ��dll��·��
	std::string temp = path;
	const char *tempchar = temp.c_str();
	//std::cout << tmp.toStdString() << std::endl;
	//�����ǽ�������Ĺ���
	using pExport = Menge::Agents::OperationPlanFactory* (*)(void); // ����ָ�򵼳�������ָ������

	const char *str = tempchar;
	//�����ǽ�const char*ת��ΪWCHAR���͵���
	WCHAR wszClassName[256];
	memset(wszClassName, 0, sizeof(wszClassName));
	MultiByteToWideChar(CP_ACP, 0, str, strlen(str) + 1, wszClassName, sizeof(wszClassName) / sizeof(wszClassName[0]));
	HINSTANCE hDll = LoadLibrary(wszClassName);// ����DLL���ļ���DLL���ƺ�·�����Լ���

	if (hDll == NULL) {
		std::cout << "load dll fail \n";
	}
	else {
		pExport Get = (pExport)GetProcAddress(hDll, "Export");// ��ָ��ָ�����׵�ַ
		if (Get == NULL) {
			std::cout << "load address fail \n";
		}
		else {
			Menge::Agents::OperationPlanFactory* t = Get();// ���õ���������ó�����ָ��
														//addFactory(t);
			Menge::Agents::OperationPlan* tt = t->createInstance();
			operationplan = tt;  //����õĹ����ౣ����ȫ�ֱ�������

							  //��ս�Բ������ַ���ȫ�ֱ�����Ӷ����ݸ�������
			std::string showData = t->name();
			operationplan_name = showData;
			operationplan_info = t->description();
		}

	}
	
	//�洢�����Ϣ
	total_info["operationplan_info"] = "\xE6\x93\x8D\xE4\xBD\x9C\xE5\xB1\x82\xE8\xAF\xA6\xE6\x83\x85\xEF\xBC\x9A" + operationplan_info + "\n";

	//ƴ��������ʾ����Ϣ
	show_info = total_info["globalplan_info"] + total_info["tacticalplan_info"] + total_info["operationplan_info"] + total_info["environment_info"];

	//�������Ϣ��ʾ�ڽ�����
	ui.info_text->clear();
	ui.info_text->appendPlainText(QString::fromStdString(show_info));
}

//������������
void QTMenge::parse_environment_plugin(std::vector<std::string> path)
{
	//����ܵ���ʾ��Ϣ
	show_info = "";
	//�����Ϣ
	environment_info_vector.clear();
	total_info["environment_info"] = "";
	environment_name.clear();

	for (auto it : path)
	{
		// ��õ�ǰ�Ĳ��dll��·��
		std::string temp = it;
		const char *tempchar = temp.c_str();
		//std::cout << tmp.toStdString() << std::endl;
		//�����ǽ�������Ĺ���
		using pExport = Menge::Agents::EnvironmentalChangeFactory* (*)(void); // ����ָ�򵼳�������ָ������

		const char *str = tempchar;
		//�����ǽ�const char*ת��ΪWCHAR���͵���
		WCHAR wszClassName[256];
		memset(wszClassName, 0, sizeof(wszClassName));
		MultiByteToWideChar(CP_ACP, 0, str, strlen(str) + 1, wszClassName, sizeof(wszClassName) / sizeof(wszClassName[0]));
		HINSTANCE hDll = LoadLibrary(wszClassName);// ����DLL���ļ���DLL���ƺ�·�����Լ���

		if (hDll == NULL) {
			std::cout << "load dll fail \n";
		}
		else {
			pExport Get = (pExport)GetProcAddress(hDll, "Export");// ��ָ��ָ�����׵�ַ
			if (Get == NULL) {
				std::cout << "load address fail \n";
			}
			else {
				Menge::Agents::EnvironmentalChangeFactory* t = Get();// ���õ���������ó�����ָ��
				//addFactory(t);
				Menge::Agents::EnvironmentalChange* tt = t->createInstance();
				environmentalChangeSet.push_back(tt);  //����õĹ����ౣ����ȫ�ֱ�������

				//��ս�Բ������ַ���ȫ�ֱ�����Ӷ����ݸ�������
				std::string showData = t->name();
				environment_name.push_back(showData);
				environment_info_vector.push_back(t->description());
			}

		}
	}

	//ƴ�Ӳ����Ϣ
	for (auto it : environment_info_vector)
	{
		total_info["environment_info"] +="\xE7\x8E\xAF\xE5\xA2\x83\xE5\xB1\x82\xE8\xAF\xA6\xE6\x83\x85\xEF\xBC\x9A"+ it + "\n";
	}
	
	//ƴ��������ʾ����Ϣ
	show_info = total_info["globalplan_info"] + total_info["tacticalplan_info"] + total_info["operationplan_info"] + total_info["environment_info"];

	//�������Ϣ��ʾ�ڽ�����
	ui.info_text->clear();
	ui.info_text->appendPlainText(QString::fromStdString(show_info));

	std::string temp = "";
	for (auto it : environment_name)
	{
		temp += '[' + it + ']';
	}

	//��ʾ�ڽ�����

	ui.environment_lineEdit->setText(QString::fromStdString(temp));
}




//����ս�Բ���
void QTMenge::makeGlobalPlanPlugin()
{
	std::cout << "makeGlobalPlanPlugin" << std::endl;

	std::string pathStr = "C:\\Users\\lhb\\Desktop\\Menge-master315\\Menge-master\\projects\\VS2013\\globalPlanMaker.bat";
	system(pathStr.c_str());

}

//����ս������
void QTMenge::makeTacticPlanPlugin()
{
	std::cout << "makeTacticalPlanPlugin" << std::endl;

	std::string pathStr = "C:\\Users\\lhb\\Desktop\\Menge-master315\\Menge-master\\projects\\VS2013\\TacticalPlanMaker.bat";
	system(pathStr.c_str());
}

//������������
void QTMenge::makeOperationPlanPlugin()
{
	std::cout << "makeOperatinPlanPlugin" << std::endl;

	std::string pathStr ="C:\\Users\\lhb\\Desktop\\Menge-master315\\Menge-master\\projects\\VS2013\\OperationPlanMaker.bat";
	system(pathStr.c_str());
}

//������������
void QTMenge::makeEnvironmentPlugin()
{
	std::string pathStr = "C:\\Users\\lhb\\Desktop\\Menge-master315\\Menge-master\\projects\\VS2013\\EnvironmentMaker.bat";
	system(pathStr.c_str());
}


void QTMenge::startMenge() {
	
	globaldata_model = "orca";
	////�ж�ѡ���ʵ���ļ�
	const QString valueStr = ui.filePathInput->text();

	viewer_name = ui.viewer_lineEdit->text().toStdString();//�ַ�������ѡ��viewer

	if (!valueStr.isEmpty()) {
		QByteArray ba = valueStr.toLatin1();
		strcpy(argv_global[2], ba.data());
		strcpy(globaldata_argv[2], ba.data());
		mengemain(globaldata_argc, globaldata_argv);
	}
	else {

		QMessageBox::warning(this, "\xE6\x8F\x90\xE7\xA4\xBA", "\xE8\xAF\xB7\xE5\x85\x88\xE9\x80\x89\xE6\x8B\xA9\xE5\xAE\x9E\xE9\xAA\x8C\xE6\x96\x87\xE4\xBB\xB6\x21\x21", QMessageBox::Yes);
	}

	printf("��ȡ·��");

}

