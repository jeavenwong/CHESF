#ifndef QTMENGE_H
#define QTMENGE_H

#include <QtWidgets/QMainWindow>
#include "ui_qtmenge.h"

#include <regex> //������ʽ
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
	void createAction();     //��������  
	void createMenu();       //�����˵�  
	void createContentMenu();//���������Ĳ˵�  
	void selectFile();       //����ѡ���ļ��Ի���  

	void strategic_select();  //ս��ѡ��ģ��
	void tactical_select();  //ս��ѡ��ģ��
	void operation_select();  //����ѡ��ģ��
	void environment_select(); //����ѡ��ģ��

	void parse_globalplan_plugin(std::string path); //����ս�Բ���
	void parse_tacticalplan_plugin(std::string path); //����ս������
	void parse_operationplan_plugin(std::string path); //������������
	void parse_environment_plugin(std::vector<std::string> path); //������������
private:
	QAction *fileOpenAction; //����һ��QActionָ�룬���ļ�����  
	QMenu *menu;             //����һ��QMenuָ��  

							 //�����һ�δ���  
	public slots://�ۺ���������־  
	void startMenge();
	void fileOpenActionSlot();//���ļ�������Ӧ�Ĳۺ���  
	void openNewform(); //���µĽ���
	void openTestForm();  //�򿪲��Խ���
	void selectFile1();   //����ѡ���ļ��Ի��� 

	void strategic_select1();  //ս��ѡ��
	void tactical_select1();  //ս��ѡ��
	void operation_select1();  //����ѡ��
	void environment_select1(); //����ѡ��

	void makeGlobalPlanPlugin();  //����ս�Բ���
	void makeTacticPlanPlugin();  //����ս������
	void makeOperationPlanPlugin();  //������������
	void makeEnvironmentPlugin();  //������������

private:	//����ļ�·��
	std::string filePath;
	std::string SfilePath;
	std::string BfilePath;
	std::string VfilePath;

	std::string strategic_path; //ս�Բ�·��
	std::string tactical_path;  //ս����·��
	std::string operation_path;  //������·��
	std::vector<std::string> environment_path;  //������·��
signals: //�����ļ�·��
	void sendData(std::string filePath, std::string SfilePath, std::string BfilePath, std::string VfilePath);
};


#endif // QTMENGE_H
