/********************************************************************************
** Form generated from reading UI file 'qtmenge.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTMENGE_H
#define UI_QTMENGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QTMengeClass
{
public:
    QAction *actionOpen;
    QAction *actionEdit;
    QAction *actionXml;
    QAction *actionTEST;
    QAction *GlobalPlanMaker;
    QAction *TacticPlanMaker;
    QAction *OperationPlanMaker;
    QAction *EnvironmentMaker;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *filePathInput;
    QPushButton *select_pbn;
    QGridLayout *gridLayout;
    QPushButton *strategic_pbn;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *tactical_pbn;
    QLabel *label_4;
    QLineEdit *operation_lineEdit;
    QPushButton *operation_pbn;
    QLabel *label_5;
    QLineEdit *environment_lineEdit;
    QPushButton *environment_selcet_pbn;
    QLineEdit *strategic_lineEdit;
    QLabel *label_6;
    QLineEdit *viewer_lineEdit;
    QPushButton *viewer_pbn;
    QLineEdit *tactical_lineEdit;
    QPushButton *startMengeButton;
    QLabel *label_7;
    QPlainTextEdit *info_text;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QTMengeClass)
    {
        if (QTMengeClass->objectName().isEmpty())
            QTMengeClass->setObjectName(QStringLiteral("QTMengeClass"));
        QTMengeClass->resize(655, 440);
        QTMengeClass->setStyleSheet(QStringLiteral(""));
        actionOpen = new QAction(QTMengeClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionEdit = new QAction(QTMengeClass);
        actionEdit->setObjectName(QStringLiteral("actionEdit"));
        actionXml = new QAction(QTMengeClass);
        actionXml->setObjectName(QStringLiteral("actionXml"));
        actionTEST = new QAction(QTMengeClass);
        actionTEST->setObjectName(QStringLiteral("actionTEST"));
        GlobalPlanMaker = new QAction(QTMengeClass);
        GlobalPlanMaker->setObjectName(QStringLiteral("GlobalPlanMaker"));
        TacticPlanMaker = new QAction(QTMengeClass);
        TacticPlanMaker->setObjectName(QStringLiteral("TacticPlanMaker"));
        OperationPlanMaker = new QAction(QTMengeClass);
        OperationPlanMaker->setObjectName(QStringLiteral("OperationPlanMaker"));
        EnvironmentMaker = new QAction(QTMengeClass);
        EnvironmentMaker->setObjectName(QStringLiteral("EnvironmentMaker"));
        centralWidget = new QWidget(QTMengeClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        filePathInput = new QLineEdit(centralWidget);
        filePathInput->setObjectName(QStringLiteral("filePathInput"));

        horizontalLayout->addWidget(filePathInput);

        select_pbn = new QPushButton(centralWidget);
        select_pbn->setObjectName(QStringLiteral("select_pbn"));

        horizontalLayout->addWidget(select_pbn);


        verticalLayout->addLayout(horizontalLayout);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        strategic_pbn = new QPushButton(centralWidget);
        strategic_pbn->setObjectName(QStringLiteral("strategic_pbn"));

        gridLayout->addWidget(strategic_pbn, 0, 2, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        tactical_pbn = new QPushButton(centralWidget);
        tactical_pbn->setObjectName(QStringLiteral("tactical_pbn"));

        gridLayout->addWidget(tactical_pbn, 2, 2, 1, 1);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        operation_lineEdit = new QLineEdit(centralWidget);
        operation_lineEdit->setObjectName(QStringLiteral("operation_lineEdit"));

        gridLayout->addWidget(operation_lineEdit, 3, 1, 1, 1);

        operation_pbn = new QPushButton(centralWidget);
        operation_pbn->setObjectName(QStringLiteral("operation_pbn"));

        gridLayout->addWidget(operation_pbn, 3, 2, 1, 1);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        environment_lineEdit = new QLineEdit(centralWidget);
        environment_lineEdit->setObjectName(QStringLiteral("environment_lineEdit"));

        gridLayout->addWidget(environment_lineEdit, 4, 1, 1, 1);

        environment_selcet_pbn = new QPushButton(centralWidget);
        environment_selcet_pbn->setObjectName(QStringLiteral("environment_selcet_pbn"));

        gridLayout->addWidget(environment_selcet_pbn, 4, 2, 1, 1);

        strategic_lineEdit = new QLineEdit(centralWidget);
        strategic_lineEdit->setObjectName(QStringLiteral("strategic_lineEdit"));

        gridLayout->addWidget(strategic_lineEdit, 0, 1, 1, 1);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 5, 0, 1, 1);

        viewer_lineEdit = new QLineEdit(centralWidget);
        viewer_lineEdit->setObjectName(QStringLiteral("viewer_lineEdit"));

        gridLayout->addWidget(viewer_lineEdit, 5, 1, 1, 1);

        viewer_pbn = new QPushButton(centralWidget);
        viewer_pbn->setObjectName(QStringLiteral("viewer_pbn"));

        gridLayout->addWidget(viewer_pbn, 5, 2, 1, 1);

        tactical_lineEdit = new QLineEdit(centralWidget);
        tactical_lineEdit->setObjectName(QStringLiteral("tactical_lineEdit"));

        gridLayout->addWidget(tactical_lineEdit, 2, 1, 1, 1);

        startMengeButton = new QPushButton(centralWidget);
        startMengeButton->setObjectName(QStringLiteral("startMengeButton"));

        gridLayout->addWidget(startMengeButton, 6, 0, 1, 3);


        verticalLayout->addLayout(gridLayout);

        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout->addWidget(label_7);

        info_text = new QPlainTextEdit(centralWidget);
        info_text->setObjectName(QStringLiteral("info_text"));
        info_text->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

        verticalLayout->addWidget(info_text);

        QTMengeClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QTMengeClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 655, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        QTMengeClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QTMengeClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QTMengeClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QTMengeClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QTMengeClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menu->menuAction());
        menuFile->addAction(actionXml);
        menuFile->addAction(actionTEST);
        menu->addAction(GlobalPlanMaker);
        menu->addAction(TacticPlanMaker);
        menu->addAction(OperationPlanMaker);
        menu->addAction(EnvironmentMaker);
        menu->addSeparator();

        retranslateUi(QTMengeClass);

        QMetaObject::connectSlotsByName(QTMengeClass);
    } // setupUi

    void retranslateUi(QMainWindow *QTMengeClass)
    {
        QTMengeClass->setWindowTitle(QApplication::translate("QTMengeClass", "\344\272\272\347\276\244\347\226\217\346\225\243\344\273\277\347\234\237", 0));
        actionOpen->setText(QApplication::translate("QTMengeClass", "Open", 0));
        actionEdit->setText(QApplication::translate("QTMengeClass", "Edit", 0));
        actionXml->setText(QApplication::translate("QTMengeClass", "XML", 0));
        actionTEST->setText(QApplication::translate("QTMengeClass", "TEST", 0));
        GlobalPlanMaker->setText(QApplication::translate("QTMengeClass", "\345\210\266\344\275\234\346\210\230\347\225\245\346\250\241\345\235\227", 0));
        TacticPlanMaker->setText(QApplication::translate("QTMengeClass", "\345\210\266\344\275\234\346\210\230\346\234\257\346\250\241\345\235\227", 0));
        OperationPlanMaker->setText(QApplication::translate("QTMengeClass", "\345\210\266\344\275\234\346\223\215\344\275\234\346\250\241\345\235\227", 0));
        EnvironmentMaker->setText(QApplication::translate("QTMengeClass", "\345\210\266\344\275\234\347\216\257\345\242\203\345\261\202\346\250\241\345\235\227", 0));
        label->setText(QApplication::translate("QTMengeClass", "\351\200\211\346\213\251\344\273\277\347\234\237\345\234\272\346\231\257", 0));
        select_pbn->setText(QApplication::translate("QTMengeClass", "\351\200\211\346\213\251\345\234\272\346\231\257", 0));
        strategic_pbn->setText(QApplication::translate("QTMengeClass", "\351\200\211\346\213\251\346\210\230\347\225\245\345\261\202\346\250\241\345\235\227", 0));
        label_2->setText(QApplication::translate("QTMengeClass", "\345\275\223\345\211\215\351\200\211\346\213\251\347\232\204\346\210\230\347\225\245\345\261\202\346\250\241\345\235\227\344\270\272\357\274\232", 0));
        label_3->setText(QApplication::translate("QTMengeClass", "\345\275\223\345\211\215\351\200\211\346\213\251\347\232\204\346\210\230\346\234\257\345\261\202\346\250\241\345\235\227\344\270\272\357\274\232", 0));
        tactical_pbn->setText(QApplication::translate("QTMengeClass", "\351\200\211\346\213\251\346\210\230\346\234\257\345\261\202\346\250\241\345\235\227", 0));
        label_4->setText(QApplication::translate("QTMengeClass", "\345\275\223\345\211\215\351\200\211\346\213\251\347\232\204\346\223\215\344\275\234\345\261\202\346\250\241\345\235\227\344\270\272\357\274\232", 0));
        operation_lineEdit->setText(QString());
        operation_pbn->setText(QApplication::translate("QTMengeClass", "\351\200\211\346\213\251\346\223\215\344\275\234\345\261\202\346\250\241\345\235\227", 0));
        label_5->setText(QApplication::translate("QTMengeClass", "\345\275\223\345\211\215\351\200\211\346\213\251\347\232\204\347\216\257\345\242\203\345\261\202\346\250\241\345\235\227\344\270\272\357\274\232", 0));
        environment_lineEdit->setText(QString());
        environment_selcet_pbn->setText(QApplication::translate("QTMengeClass", "\351\200\211\346\213\251\347\216\257\345\242\203\345\261\202\346\250\241\345\235\227", 0));
        strategic_lineEdit->setText(QString());
        label_6->setText(QApplication::translate("QTMengeClass", "\345\275\223\345\211\215\351\200\211\346\213\251\347\232\204\345\217\257\350\247\206\345\214\226\346\250\241\345\235\227\344\270\272\357\274\232", 0));
        viewer_pbn->setText(QApplication::translate("QTMengeClass", "\351\200\211\346\213\251\345\217\257\350\247\206\345\214\226\346\250\241\345\235\227", 0));
        tactical_lineEdit->setText(QString());
        startMengeButton->setText(QApplication::translate("QTMengeClass", "\345\274\200\345\247\213\344\273\277\347\234\237", 0));
        label_7->setText(QApplication::translate("QTMengeClass", "\345\267\262\351\200\211\346\250\241\345\235\227\350\257\246\346\203\205\357\274\232", 0));
        menuFile->setTitle(QString());
        menu->setTitle(QApplication::translate("QTMengeClass", "\345\267\245\345\205\267", 0));
    } // retranslateUi

};

namespace Ui {
    class QTMengeClass: public Ui_QTMengeClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTMENGE_H
