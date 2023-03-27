//
// Created by merhab on 2023/3/25.
//


#pragma once
/********************************************************************************
** Form generated from reading UI file 'ui_loginbBlCUG.ui'
**
** Created by: Qt User Interface Compiler version 6.0.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/


#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Window_login
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *txt_user;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *txt_pass;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btn_login;
    QPushButton *btn_close;

    void setupUi(QWidget *Window_login)
    {
        if (Window_login->objectName().isEmpty())
            Window_login->setObjectName(QString::fromUtf8("Window_login"));
        Window_login->resize(392, 122);
        Window_login->setLayoutDirection(Qt::LeftToRight);
        Window_login->setLocale(QLocale(QLocale::Arabic, QLocale::Algeria));
        verticalLayout = new QVBoxLayout(Window_login);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(Window_login);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        txt_user = new QLineEdit(Window_login);
        txt_user->setObjectName(QString::fromUtf8("txt_user"));

        horizontalLayout->addWidget(txt_user);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(Window_login);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        txt_pass = new QLineEdit(Window_login);
        txt_pass->setObjectName(QString::fromUtf8("txt_pass"));

        horizontalLayout_2->addWidget(txt_pass);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        btn_login = new QPushButton(Window_login);
        btn_login->setObjectName(QString::fromUtf8("btn_login"));

        horizontalLayout_3->addWidget(btn_login);

        btn_close = new QPushButton(Window_login);
        btn_close->setObjectName(QString::fromUtf8("btn_close"));

        horizontalLayout_3->addWidget(btn_close);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(Window_login);

        QMetaObject::connectSlotsByName(Window_login);
    } // setupUi

    void retranslateUi(QWidget *Window_login)
    {
        Window_login->setWindowTitle(QCoreApplication::translate("Window_login", "Login", nullptr));
        label->setText(QCoreApplication::translate("Window_login", "User", nullptr));
        label_2->setText(QCoreApplication::translate("Window_login", "Pass", nullptr));
        btn_login->setText(QCoreApplication::translate("Window_login", "Login", nullptr));
        btn_close->setText(QCoreApplication::translate("Window_login", "Quiter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Window_login: public Ui_Window_login {};
} // namespace Ui

QT_END_NAMESPACE

