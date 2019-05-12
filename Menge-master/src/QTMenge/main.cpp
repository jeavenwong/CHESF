
#include "qtmenge.h"
#include <QtWidgets/QApplication>
#include "globaldata.h"
//int main(int argc, char *argv[])
//{
//	QApplication a(argc, argv);
//	QTMenge w;
//	w.show();
//	return a.exec();
//}
int main(int argc, char *argv[])
{
	//QtApplication::argc_globe = argc;
	//QtApplication::argv_globe = argv;

	QApplication a(argc, argv);
	QTMenge w(argc, argv);

	globaldata_argc = argc;

	for (int i = 0; i < argc; i++) {
		globaldata_argv[i] = argv[i];
	}
	//strcpy(globedata_argv[0], argv[0]);
	//globedata_argv[0] = argv[0];
	//globedata_argv[1] = argv[1];
	//globedata_argv[2] = argv[2];
	//globedata_argv[3] = '\0';
	w.argv_global = argv;
	w.show();
	 
	//加载样式表
	QFile styleFile(":/QSS/stylesheet.qss");
	styleFile.open(QIODevice::ReadOnly);
	QString setStyleSheet(styleFile.readAll());
	a.setStyleSheet(setStyleSheet);
	
	return a.exec();
}


