/********************************************************************************
** Form generated from reading UI file 'KeyCounter.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KEYCOUNTER_H
#define UI_KEYCOUNTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KeyCounterClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *KeyCounterClass)
    {
        if (KeyCounterClass->objectName().isEmpty())
            KeyCounterClass->setObjectName(QStringLiteral("KeyCounterClass"));
        KeyCounterClass->resize(600, 400);
        menuBar = new QMenuBar(KeyCounterClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        KeyCounterClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(KeyCounterClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        KeyCounterClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(KeyCounterClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        KeyCounterClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(KeyCounterClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        KeyCounterClass->setStatusBar(statusBar);

        retranslateUi(KeyCounterClass);

        QMetaObject::connectSlotsByName(KeyCounterClass);
    } // setupUi

    void retranslateUi(QMainWindow *KeyCounterClass)
    {
        KeyCounterClass->setWindowTitle(QApplication::translate("KeyCounterClass", "KeyCounter", 0));
    } // retranslateUi

};

namespace Ui {
    class KeyCounterClass: public Ui_KeyCounterClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KEYCOUNTER_H
