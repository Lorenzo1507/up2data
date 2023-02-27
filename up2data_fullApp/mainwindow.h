#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QMessageBox>
#include <QDirIterator>
#include <QDir>
#include <QFileDialog>
#include <QCoreApplication>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QVariantMap>
#include <QByteArray>
#include <QSettings>
#include <QMetaType>
#include <QProcess>
#include <QTimer>

#include "mysql.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnOrigem_clicked();

    void on_btnDestino_clicked();

    void on_btnPasta_clicked();

    void on_btnLerFile_clicked();


    void on_btnJuntar_clicked();

    void on_btnEnviar_clicked();

private:
    Ui::MainWindow *ui;

    QMap<QString, QMap<QString, QString>> securitiesDesc;

    QSettings* settings;

    QProcess* process;

    void initSettings();

    void copiarFiles(QString pathDestino, QString nomeFile, QStringList toBeSend, int i);

    void copyFolder(QDir dirDestino, QString pathDestino, QString nomeFile, QStringList toBeSend, int i);

    void tratarFim();

    void verificarProcess();

    void zipArquivo(QString finalFileName, QString path);

    void zipFolder(QString day, QString newDirPath);

    mySql *dialogSQL;

};
#endif // MAINWINDOW_H
