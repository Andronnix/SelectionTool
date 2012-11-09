/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu 8. Nov 22:13:33 2012
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *prevButton;
    QPushButton *nextButton;
    QPushButton *removeButton;
    QGraphicsView *gestureView;
    QGraphicsView *typeGestureView;
    QLabel *gestureNameLabel;
    QPushButton *nextType;
    QPushButton *prevType;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(694, 527);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        prevButton = new QPushButton(centralWidget);
        prevButton->setObjectName(QString::fromUtf8("prevButton"));
        prevButton->setGeometry(QRect(340, 430, 51, 51));
        nextButton = new QPushButton(centralWidget);
        nextButton->setObjectName(QString::fromUtf8("nextButton"));
        nextButton->setGeometry(QRect(480, 430, 51, 51));
        removeButton = new QPushButton(centralWidget);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));
        removeButton->setGeometry(QRect(410, 430, 51, 51));
        gestureView = new QGraphicsView(centralWidget);
        gestureView->setObjectName(QString::fromUtf8("gestureView"));
        gestureView->setGeometry(QRect(180, 30, 511, 391));
        typeGestureView = new QGraphicsView(centralWidget);
        typeGestureView->setObjectName(QString::fromUtf8("typeGestureView"));
        typeGestureView->setGeometry(QRect(10, 30, 161, 141));
        gestureNameLabel = new QLabel(centralWidget);
        gestureNameLabel->setObjectName(QString::fromUtf8("gestureNameLabel"));
        gestureNameLabel->setGeometry(QRect(10, 10, 161, 16));
        nextType = new QPushButton(centralWidget);
        nextType->setObjectName(QString::fromUtf8("nextType"));
        nextType->setGeometry(QRect(90, 190, 81, 23));
        prevType = new QPushButton(centralWidget);
        prevType->setObjectName(QString::fromUtf8("prevType"));
        prevType->setGeometry(QRect(10, 190, 75, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 694, 21));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        prevButton->setText(QApplication::translate("MainWindow", "Prev", 0, QApplication::UnicodeUTF8));
        nextButton->setText(QApplication::translate("MainWindow", "Next", 0, QApplication::UnicodeUTF8));
        removeButton->setText(QApplication::translate("MainWindow", "Remove", 0, QApplication::UnicodeUTF8));
        gestureNameLabel->setText(QApplication::translate("MainWindow", "gestureType", 0, QApplication::UnicodeUTF8));
        nextType->setText(QApplication::translate("MainWindow", "nextGesture", 0, QApplication::UnicodeUTF8));
        prevType->setText(QApplication::translate("MainWindow", "prevGesture", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
