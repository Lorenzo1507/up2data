#ifndef MYSQL_H
#define MYSQL_H

#include <QDialog>
#include<QtSql>
#include<QSqlDatabase>
#include<QMessageBox>
#include<QSqlQuery>
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QSettings>

namespace Ui {
class mySql;
}

class mySql : public QDialog
{
    Q_OBJECT

public:
    explicit mySql(QWidget *parent = nullptr);
    ~mySql();

private slots:
    void on_btnGetJson_clicked();

    void on_btnEnviar_clicked();

private:
    Ui::mySql *ui;

    //define o objeto para estabelecer a conexão com o banco
    QSqlDatabase database;

    //cria o modelo da tabela. Envolve a definição de cada coluna e cada linha
    QAbstractItemModel *modelDespesas;

    //Guarda os nomes de cada coluna atrelado a um número inteiro, podendo então estabelecer cada header no model através dos inteiros
    QMap<QString, int> headModelDespesas;

    //Pré-define as configurações
    QSettings* settings;

    QString fileName;

    QList<QString> headers;

    QStringList pathCheck;

    void initSettings();

    void updateBanco();

    void inserirDados();
};

#endif // MYSQL_H
