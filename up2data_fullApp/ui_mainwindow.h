/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *btnOrigem;
    QLineEdit *txtOrigem;
    QPlainTextEdit *plainTextEdit;
    QLineEdit *txtDestino;
    QPushButton *btnDestino;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnLerFile;
    QPushButton *btnJuntar;
    QPushButton *btnEnviar;
    QProgressBar *progressBar;
    QProgressBar *progressBar_2;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLabel *lblDef;
    QLabel *lblAt;
    QPushButton *btnPasta;
    QLineEdit *txtPasta;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1063, 739);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        btnOrigem = new QPushButton(centralwidget);
        btnOrigem->setObjectName(QString::fromUtf8("btnOrigem"));
        btnOrigem->setGeometry(QRect(290, 30, 131, 24));
        txtOrigem = new QLineEdit(centralwidget);
        txtOrigem->setObjectName(QString::fromUtf8("txtOrigem"));
        txtOrigem->setGeometry(QRect(30, 30, 251, 22));
        plainTextEdit = new QPlainTextEdit(centralwidget);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(30, 120, 551, 301));
        txtDestino = new QLineEdit(centralwidget);
        txtDestino->setObjectName(QString::fromUtf8("txtDestino"));
        txtDestino->setGeometry(QRect(30, 80, 251, 22));
        btnDestino = new QPushButton(centralwidget);
        btnDestino->setObjectName(QString::fromUtf8("btnDestino"));
        btnDestino->setGeometry(QRect(290, 80, 131, 24));
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 540, 1021, 81));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        btnLerFile = new QPushButton(horizontalLayoutWidget);
        btnLerFile->setObjectName(QString::fromUtf8("btnLerFile"));

        horizontalLayout_2->addWidget(btnLerFile);

        btnJuntar = new QPushButton(horizontalLayoutWidget);
        btnJuntar->setObjectName(QString::fromUtf8("btnJuntar"));

        horizontalLayout_2->addWidget(btnJuntar);

        btnEnviar = new QPushButton(horizontalLayoutWidget);
        btnEnviar->setObjectName(QString::fromUtf8("btnEnviar"));

        horizontalLayout_2->addWidget(btnEnviar);

        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(20, 640, 251, 23));
        progressBar->setValue(24);
        progressBar->setTextVisible(true);
        progressBar_2 = new QProgressBar(centralwidget);
        progressBar_2->setObjectName(QString::fromUtf8("progressBar_2"));
        progressBar_2->setGeometry(QRect(20, 670, 251, 23));
        progressBar_2->setValue(24);
        progressBar_2->setTextVisible(true);
        horizontalLayoutWidget_2 = new QWidget(centralwidget);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(600, 120, 401, 41));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(horizontalLayoutWidget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        lblDef = new QLabel(horizontalLayoutWidget_2);
        lblDef->setObjectName(QString::fromUtf8("lblDef"));
        lblDef->setEnabled(true);

        horizontalLayout_3->addWidget(lblDef);

        lblAt = new QLabel(horizontalLayoutWidget_2);
        lblAt->setObjectName(QString::fromUtf8("lblAt"));

        horizontalLayout_3->addWidget(lblAt);

        btnPasta = new QPushButton(centralwidget);
        btnPasta->setObjectName(QString::fromUtf8("btnPasta"));
        btnPasta->setGeometry(QRect(710, 30, 131, 24));
        txtPasta = new QLineEdit(centralwidget);
        txtPasta->setObjectName(QString::fromUtf8("txtPasta"));
        txtPasta->setGeometry(QRect(450, 30, 251, 22));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 10, 251, 16));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(30, 60, 251, 16));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(450, 10, 271, 16));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1063, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btnOrigem->setText(QCoreApplication::translate("MainWindow", "Escolher origem", nullptr));
        btnDestino->setText(QCoreApplication::translate("MainWindow", "Escolher destino", nullptr));
        btnLerFile->setText(QCoreApplication::translate("MainWindow", "Ler arquivo", nullptr));
        btnJuntar->setText(QCoreApplication::translate("MainWindow", "Juntar JSONs do dia", nullptr));
        btnEnviar->setText(QCoreApplication::translate("MainWindow", "Enviar para banco", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Match:", nullptr));
        lblDef->setText(QCoreApplication::translate("MainWindow", "item", nullptr));
        lblAt->setText(QCoreApplication::translate("MainWindow", "item", nullptr));
        btnPasta->setText(QCoreApplication::translate("MainWindow", "Escolher pasta", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Caminho da pasta para ser filtrada:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Local onde a pasta filtrada ser\303\241 criada:", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Escolher a pasta do dia para juntar todos os json:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
