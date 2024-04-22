/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionView_Network;
    QWidget *centralwidget;
    QPushButton *pushButton;
    QWidget *widget;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;
    QPushButton *pushButton_4;
    QProgressBar *progressBar_3;
    QLabel *label;
    QProgressBar *progressBar;
    QPushButton *pushButton_2;
    QProgressBar *progressBar_2;
    QWidget *widget_2;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_5;
    QPushButton *pushButton_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(2570, 1071);
        actionView_Network = new QAction(MainWindow);
        actionView_Network->setObjectName("actionView_Network");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(20, 20, 121, 51));
        pushButton->setStyleSheet(QString::fromUtf8("background-color:rgb(103, 162, 236)"));
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(10, 130, 191, 261));
        widget->setStyleSheet(QString::fromUtf8("background-color:rgb(50, 203, 255)"));
        checkBox = new QCheckBox(widget);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(10, 10, 121, 21));
        checkBox_2 = new QCheckBox(widget);
        checkBox_2->setObjectName("checkBox_2");
        checkBox_2->setGeometry(QRect(10, 40, 131, 21));
        checkBox_3 = new QCheckBox(widget);
        checkBox_3->setObjectName("checkBox_3");
        checkBox_3->setGeometry(QRect(10, 70, 121, 21));
        checkBox_4 = new QCheckBox(widget);
        checkBox_4->setObjectName("checkBox_4");
        checkBox_4->setGeometry(QRect(10, 100, 121, 21));
        pushButton_4 = new QPushButton(widget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(10, 130, 121, 51));
        pushButton_4->setStyleSheet(QString::fromUtf8("background-color:rgb(0, 165, 224)"));
        progressBar_3 = new QProgressBar(widget);
        progressBar_3->setObjectName("progressBar_3");
        progressBar_3->setGeometry(QRect(10, 190, 118, 23));
        progressBar_3->setStyleSheet(QString::fromUtf8("background-color:rgb(0, 165, 224)"));
        progressBar_3->setValue(0);
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(210, 10, 0, 0));
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(20, 80, 118, 23));
        progressBar->setStyleSheet(QString::fromUtf8("background-color:rgb(103, 162, 236)"));
        progressBar->setValue(0);
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(20, 420, 121, 51));
        pushButton_2->setStyleSheet(QString::fromUtf8("background-color:rgb(103, 162, 236)"));
        progressBar_2 = new QProgressBar(centralwidget);
        progressBar_2->setObjectName("progressBar_2");
        progressBar_2->setGeometry(QRect(20, 480, 118, 23));
        progressBar_2->setStyleSheet(QString::fromUtf8("background-color:rgb(103, 162, 236)"));
        progressBar_2->setValue(0);
        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(10, 530, 191, 241));
        widget_2->setStyleSheet(QString::fromUtf8("background-color:rgb(50, 203, 255)"));
        radioButton = new QRadioButton(widget_2);
        radioButton->setObjectName("radioButton");
        radioButton->setGeometry(QRect(10, 10, 89, 20));
        radioButton_2 = new QRadioButton(widget_2);
        radioButton_2->setObjectName("radioButton_2");
        radioButton_2->setGeometry(QRect(10, 40, 89, 20));
        radioButton_3 = new QRadioButton(widget_2);
        radioButton_3->setObjectName("radioButton_3");
        radioButton_3->setGeometry(QRect(10, 70, 89, 20));
        radioButton_4 = new QRadioButton(widget_2);
        radioButton_4->setObjectName("radioButton_4");
        radioButton_4->setGeometry(QRect(10, 100, 89, 20));
        radioButton_5 = new QRadioButton(widget_2);
        radioButton_5->setObjectName("radioButton_5");
        radioButton_5->setGeometry(QRect(10, 130, 89, 20));
        pushButton_3 = new QPushButton(widget_2);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(10, 170, 121, 51));
        pushButton_3->setStyleSheet(QString::fromUtf8("background-color:rgb(0, 165, 224)"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 2570, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionView_Network->setText(QCoreApplication::translate("MainWindow", "View Network", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Load Network", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "Run algorithm 1", nullptr));
        checkBox_2->setText(QCoreApplication::translate("MainWindow", "Run algorithm 2", nullptr));
        checkBox_3->setText(QCoreApplication::translate("MainWindow", "Run algorithm 3", nullptr));
        checkBox_4->setText(QCoreApplication::translate("MainWindow", "Run algorithm 4", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Run", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Load image here", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Create Graph", nullptr));
        radioButton->setText(QCoreApplication::translate("MainWindow", "Image 1", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MainWindow", "Image 2", nullptr));
        radioButton_3->setText(QCoreApplication::translate("MainWindow", "Image 3", nullptr));
        radioButton_4->setText(QCoreApplication::translate("MainWindow", "Image 4", nullptr));
        radioButton_5->setText(QCoreApplication::translate("MainWindow", "Image 5", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Load Image", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
