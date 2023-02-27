/********************************************************************************
** Form generated from reading UI file 'mysql.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYSQL_H
#define UI_MYSQL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mySql
{
public:
    QProgressBar *progressBar;
    QTableView *tableView;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *lblInfo;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnGetJson;
    QPushButton *btnEnviar;

    void setupUi(QDialog *mySql)
    {
        if (mySql->objectName().isEmpty())
            mySql->setObjectName(QString::fromUtf8("mySql"));
        mySql->resize(1071, 678);
        progressBar = new QProgressBar(mySql);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(780, 560, 271, 23));
        progressBar->setValue(24);
        tableView = new QTableView(mySql);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(25, 11, 1021, 511));
        verticalLayoutWidget = new QWidget(mySql);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 630, 1051, 41));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lblInfo = new QLabel(verticalLayoutWidget);
        lblInfo->setObjectName(QString::fromUtf8("lblInfo"));

        verticalLayout->addWidget(lblInfo);

        horizontalLayoutWidget = new QWidget(mySql);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(260, 530, 511, 91));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        btnGetJson = new QPushButton(horizontalLayoutWidget);
        btnGetJson->setObjectName(QString::fromUtf8("btnGetJson"));

        horizontalLayout->addWidget(btnGetJson);

        btnEnviar = new QPushButton(horizontalLayoutWidget);
        btnEnviar->setObjectName(QString::fromUtf8("btnEnviar"));

        horizontalLayout->addWidget(btnEnviar);


        retranslateUi(mySql);

        QMetaObject::connectSlotsByName(mySql);
    } // setupUi

    void retranslateUi(QDialog *mySql)
    {
        mySql->setWindowTitle(QCoreApplication::translate("mySql", "Dialog", nullptr));
        lblInfo->setText(QCoreApplication::translate("mySql", "info", nullptr));
        btnGetJson->setText(QCoreApplication::translate("mySql", "Pegar Json", nullptr));
        btnEnviar->setText(QCoreApplication::translate("mySql", "Enviar para o banco", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mySql: public Ui_mySql {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYSQL_H
