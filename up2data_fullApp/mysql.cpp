#include "mysql.h"
#include "ui_mysql.h"

mySql::mySql(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mySql)
{
    ui->setupUi(this);

    //initSettings();

    modelDespesas = new QStandardItemModel(0, 0, this);

    ui->progressBar->setVisible(false);

    //ui->lblErro->setVisible(false);
    ui->lblInfo->setVisible(false);

    qDebug() << QSqlDatabase::drivers();
}

mySql::~mySql()
{
    delete ui;
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void mySql::initSettings()
{
    QString dirPath;
    //Pega o diretorio onde a aplicação está sendo salva
    dirPath = QApplication::applicationDirPath();

    //Remover a  última section
    dirPath = dirPath.section("/", 0, dirPath.count("/") - 1);
    //Concatena o caminho até o arquivo settings
    dirPath += "/config/settings.ini";

    settings = new QSettings(dirPath, QSettings::IniFormat);
}


void mySql::inserirDados()
{
    QSqlQuery qry(QSqlDatabase::database("MyConnect"));

    ui->progressBar->setValue(0);
    ui->progressBar->setRange(0, modelDespesas->rowCount());

    QString SQLin;
    //lista que haverá o comando para adicionar todas as linhas de uma só vez
    QList<QString> comando;

    //int incluidas = 0;

    //SQLin += "INSERT INTO json_ativos.dados_ativos (ETF_INDEX, TICKER, DATA_INI, DATA_FIM, NAME, SECTOR, COUNTRY, PORC_OF_ETF_HOLDINS, CONTINENT) VALUES";

    int incluidas = 0, inicio =  0;

    for (int i = 0; i < modelDespesas->rowCount(); i++)
    {
        qApp->processEvents();
        ui->progressBar->setValue(i);

        if (inicio == 0)
        {
            SQLin += "INSERT INTO risk_db.B3ativos (B3_id, B3_vcto, B3_TckrSymb, B3_Sgmt, B3_Mkt, B3_Optintp, B3_ExrcPric, B3_XprtnCd, B3_Currnc, B3_CtrctMltplr, B3_Objto, B3_ISIN, B3_ExrcStyle, B3_AsstQtnQty, B3_AllcnRndLot, B3_desc, B3_TradgCcy";

            /*for (int i = 0; i < headModelDespesas.size(); i++)
            {
                SQLin += headModelDespesas.key(i) + ", ";
            }*/

            /*//Chama duas vezes para tirar a vírgula e o espaço
            SQLin.remove(SQLin.length() - 1, 1);
            SQLin.remove(SQLin.length() - 1, 1);*/

            SQLin += ") VALUES";

            inicio = 1;
        }

        /*Quando se coloca o a key no headModelDespesas, ele retorna o index daquela key. Logo não precisamos fazer 2 fors, assim conseguimos atrlar cada célula de cada linha e coluna
        e guardamos o comando para adicionar várias linhas em uma só string. Então ao invés de executarmos, por exemplo, 100 linhas em 100 comandos de insert,
        executamos 1 comando para as 100 linhas de uma vez só*/
        SQLin += "(";

        for (int j = 0; j < modelDespesas->columnCount(); j++)
        {
            if (!headModelDespesas.contains("OPTNTP") && j == 6)
            {
                SQLin += "'NONE', ";
            }
            else
            {
                SQLin += "'" + modelDespesas->data(modelDespesas->index(i, headModelDespesas.value("OPTNTP"), QModelIndex())).toString().trimmed().toUtf8() + "', ";
            }
            
            if (!headModelDespesas.contains("EXRCPRIC") && j == 7)
            {
                SQLin += "'0', ";
            }
            else
            {
                SQLin += "'" + modelDespesas->data(modelDespesas->index(i, headModelDespesas.value("EXRCPRIC"), QModelIndex())).toString().trimmed().toUtf8() + "', ";
            }

            if (!headModelDespesas.contains("EXRCSTYLE") && j == 13)
            {
                SQLin += "'', ";
            }
            else
            {
                SQLin += "'" + modelDespesas->data(modelDespesas->index(i, headModelDespesas.value("EXRCSTYLE"), QModelIndex())).toString().trimmed().toUtf8() + "', ";
            }

            if (headModelDespesas.contains("ALLCNRNDLOT") && j == 15)
            {
                SQLin += "'" + modelDespesas->data(modelDespesas->index(i, headModelDespesas.value("ALLCNRNDLOT"), QModelIndex())).toString().trimmed().toUtf8() + "', ";
            }

            if (headModelDespesas.contains("ASSTQTNQTY") && j == 14)
            {
                SQLin += "'" + modelDespesas->data(modelDespesas->index(i, headModelDespesas.value("ASSTQTNQTY"), QModelIndex())).toString().trimmed().toUtf8() + "', ";
            }

            if (headModelDespesas.contains("CTRCTMLTPLR") && j == 10)
            {
                SQLin += "'" + modelDespesas->data(modelDespesas->index(i, headModelDespesas.value("CTRCTMLTPLR"), QModelIndex())).toString().trimmed().toUtf8() + "', ";
            }

            if (headModelDespesas.contains("DESC") && j == 16)
            {
                SQLin += "'" + modelDespesas->data(modelDespesas->index(i, headModelDespesas.value("DESC"), QModelIndex())).toString().trimmed().toUtf8() + "', ";
            }

            if (headModelDespesas.contains("ISIN") && j == 12)
            {
                SQLin += "'" + modelDespesas->data(modelDespesas->index(i, headModelDespesas.value("ISIN"), QModelIndex())).toString().trimmed().toUtf8() + "', ";
            }

            if (headModelDespesas.contains("MKT") && j == 5)
            {
                SQLin += "'" + modelDespesas->data(modelDespesas->index(i, headModelDespesas.value("MKT"), QModelIndex())).toString().trimmed().toUtf8() + "', ";
            }

            if (headModelDespesas.contains("SCTYID") && j == 1)
            {
                SQLin += "'" + modelDespesas->data(modelDespesas->index(i, headModelDespesas.value("SCTYID"), QModelIndex())).toString().trimmed().toUtf8() + "', ";
            }

            if (headModelDespesas.contains("SGMT") && j == 4)
            {
                SQLin += "'" + modelDespesas->data(modelDespesas->index(i, headModelDespesas.value("SGMT"), QModelIndex())).toString().trimmed().toUtf8() + "', ";
            }

            if (headModelDespesas.contains("TCKRSYMB") && j == 3)
            {
                SQLin += "'" + modelDespesas->data(modelDespesas->index(i, headModelDespesas.value("TCKRSYMB"), QModelIndex())).toString().trimmed().toUtf8() + "', ";
            }

            if (headModelDespesas.contains("TRAGGCCY") && j == 17)
            {
                SQLin += "'" + modelDespesas->data(modelDespesas->index(i, headModelDespesas.value("TRAGGCCY"), QModelIndex())).toString().trimmed().toUtf8() + "', ";
            }

            if (headModelDespesas.contains("TRADGENDDT") && j == 2)
            {
                SQLin += "'" + modelDespesas->data(modelDespesas->index(i, headModelDespesas.value("TRADGENDDT"), QModelIndex())).toString().trimmed().toUtf8() + "', ";
            }

            if (headModelDespesas.contains("XPRTNCD") && j == 8)
            {
                SQLin += "'" + modelDespesas->data(modelDespesas->index(i, headModelDespesas.value("XPRTNCD"), QModelIndex())).toString().trimmed().toUtf8() + "', ";
            }

          

            /*if (modelDespesas->data(modelDespesas->index(i, j, QModelIndex())).toString() != "NULL")
            {
                SQLin += "'" + modelDespesas->data(modelDespesas->index(i, j, QModelIndex())).toString().trimmed().toUtf8() + "', ";
            }
            else
            {
                SQLin += modelDespesas->data(modelDespesas->index(i, j, QModelIndex())).toString().trimmed().toUtf8() + ", ";
            }*/

        }

        //Para remover o último aspas simples e a última virgula
        SQLin.remove(SQLin.length() - 1, 1);
        SQLin.remove(SQLin.length() - 1, 1);

        SQLin += "),";

        incluidas++;

        if (incluidas == 999)
        {
            inicio = 0;
            incluidas = 0;
            SQLin.remove(SQLin.length() - 1, 1);
            SQLin += ";";
            comando << SQLin;
            SQLin.clear();
        }
    }

    //removemos a última vírgula e colocamos um ";"
    SQLin.remove(SQLin.length() - 1, 1);
    SQLin += ";";
    comando << SQLin;

    ui->progressBar->setValue(0);
    ui->progressBar->setRange(0, comando.count());



    for (int i = 0; i < comando.count(); i++)
    {
        //executa o comando em cada espaço da list
        if (qry.exec(comando.at(i)))
        {
            //mostra todas as alterações
            ui->lblInfo->setVisible(true);
            ui->lblInfo->setText(fileName + " adicionado " + QString::number(qry.numRowsAffected()) + " linhas em " + QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss"));
            ui->progressBar->setValue(i);
        }
        else
        {
            QMessageBox::critical(this, "Erro", qry.lastError().text());
            return;
        }

    }
    comando.clear();
    ui->progressBar->setVisible(false);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/




void mySql::on_btnGetJson_clicked()
{
    //Vai pegar o caminho completo até o arquivo
    QString filePath;

    //Abre os documentos para a seleção do arquivo desejado
    filePath = QFileDialog::getOpenFileName(this,
        tr("Abrir Arquivos Json"),"","(*.json)");


    pathCheck = filePath.split("/");

    if (!filePath.isNull())
    {
        QStringList pathSplit = filePath.split("/");

        fileName = pathSplit.value(pathSplit.length() - 1);

        //ui->tableView->model = (modelDespesas ? modelDespesas : QAbstractItemModelPrivate::staticEmptyModel());
        ui->tableView->setModel(nullptr);

        modelDespesas->removeColumns(0, modelDespesas->columnCount());
        modelDespesas->removeRows(0, modelDespesas->rowCount());

        //Pega o arquivo selecionado em uma variável
        QFile file(filePath);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {  // Tratar Erro
            QMessageBox::information(this, "Não aberto", file.errorString());
            return;
        }
        //Conteúdo dentro do arquivo
        QTextStream in(&file);

        QString json  = in.readAll().trimmed();
        file.close();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(json.toUtf8());

        if(!jsonDoc.isArray())
        {
            QMessageBox::critical(this, "Erro", "Não é um array");
            return;
        }
        if(jsonDoc.isNull())
        {
            QMessageBox::information(this, "Vazio", "Documento Vazio.");
            return;
        }

        QJsonArray jsonArray = jsonDoc.array();


        headModelDespesas.clear();
        headers.clear();


        QStringList keys;
        //QStringList oldKeys;
        QVariantMap jsonMap;
        int headerCont = 0;

        ui->progressBar->setVisible(true);

        ui->progressBar->setValue(0);
        ui->progressBar->setRange(0, 88);

        for (int i = 0; i < jsonArray.size(); i++)
        {
            keys.clear();
            jsonMap.clear();

            QJsonValue val = jsonArray.at(i);
            QJsonObject obj = val.toObject();

            keys = obj.keys();

            //Se a lista de chaves anterior for menor ou maior que a lista atual, checamos para ver se não tem nenhuma chave diferente
            for (int k = 0; k < keys.length(); k++)
            {
                if (!headers.contains(keys[k]))
                {
                    headers << keys[k];

                    headModelDespesas[headers[headerCont].toUpper().trimmed()] = headerCont;

                    //vai inserindo a quantidade de colunas que haverá na tabela
                    modelDespesas->insertColumn(headerCont);
                    //adiciona todos os nomes em cada header
                    modelDespesas->setHeaderData(headerCont, Qt::Horizontal, headers[headerCont].toUpper().trimmed());

                    headerCont++;
                }
            }

            ui->progressBar->setValue(i);
        }


        ui->progressBar->setValue(0);
        ui->progressBar->setRange(0, modelDespesas->rowCount());

        for (int linha = 0; linha < jsonArray.size(); linha++)
        {
            keys.clear();
            jsonMap.clear();

            QJsonValue val = jsonArray.at(linha);
            QJsonObject obj = val.toObject();

            keys = obj.keys();
            jsonMap = obj.toVariantMap();

            modelDespesas->insertRow(linha);
            //ui->progressBar->setRange(0, modelDespesas->rowCount());

            int headCont = 0;

            bool lastItemFill = false;

            for (int j = 0; j < jsonMap.size(); j++)
            {
                //Se a key do jsonMap for igual a key que está na lista do headers
                if (keys[j] == headers[headCont])
                {
                    QString value = jsonMap.value(keys[j]).toString();
                    //Se o valor no jsonMap para aquela key específica for vazio então adiciona null, senão adiciona o próprio valor do json
                    if (value == "")
                    {
                        modelDespesas->setData(modelDespesas->index(linha, headCont), "NULL");
                    }
                    else
                    {
                        //headCont é o número da coluna do header da tabela, quando o item do keys for igual ao do headers significa que o headCont percorreu por toda a lista do header e encontrou
                        //a posição da coluna onde aquele item deve ser adicionado
                        modelDespesas->setData(modelDespesas->index(linha, headCont), jsonMap.value(keys[j]).toString().trimmed());

                        if (headCont == headers.size() - 1)
                        {
                            lastItemFill = true;
                        }
                    }
                   //Para o headCont não estourar o tamanho do headers
                    if (headCont < headers.size() - 1)
                    {
                        headCont++;
                    }
                }
                else
                {
                    //Caso nenhum elemento tenha sido encontrado ainda e headCont já está no fim de headers, então zera para analisar do começo, porque a key sempre estará em algum lugar do headers
                    if (headCont == headers.size() - 1)
                    {
                        headCont = 0;
                        j--;
                    }
                    else
                    {
                        //Se ainda não estiver no fim do headers e a key dentro de keys for diferente da key no header
                        //As keys estão organizadas por ordem alfabética porém o header pode ter muitas keys entre uma key do jsonMap e outra. Se for o caso de não encontrar, então é porque a key não existe no map
                        //Logo aquela área da tabela onde tem a coluna daquela key será vazia
                        if (!keys.contains(headers[headCont]))
                        {
                            modelDespesas->setData(modelDespesas->index(linha, headCont), "NULL");
                        }

                        headCont++;
                        j--;
                    }
                }

                if (j == jsonMap.size() - 1 && lastItemFill == false)
                {
                    while (headCont < headers.size())
                    {
                        modelDespesas->setData(modelDespesas->index(linha, headCont), "NULL");

                        headCont++;
                    }
                }

            }

            //oldKeys = keys;
            qApp->processEvents();
        }

        ui->progressBar->setRange(0, modelDespesas->rowCount());
        for(int i = 0; i < modelDespesas->rowCount(); i++)
        {
             ui->progressBar->setValue(i);
             qApp->processEvents();
        }

        //por aqui joga todo o conteúdo criado de modelDespesas para a tabela no ui
        ui->tableView->setModel(modelDespesas);
        //deixa as linhas alternando entre branco e cinza
        ui->tableView->setAlternatingRowColors(true);
        //Ordena a tabela
        ui->tableView->setSortingEnabled(true);

        ui->progressBar->setVisible(false);
    }
}



void mySql::on_btnEnviar_clicked()
{
    if (pathCheck.contains("SecurityList"))
    {
        database = QSqlDatabase::addDatabase("QMYSQL");

        /*database.setHostName("127.0.0.1");
        database.setPort(3307);
        database.setUserName("ativos");
        database.setPassword("password");
        database.setDatabaseName("json_ativos");*/

        database.setHostName("dev.mboituva.app.br");
        database.setUserName("devs");
        database.setPassword("mboituva");
        database.setDatabaseName("risk_db");

        if (database.open())
        {
            QSqlQuery qryUpdate(QSqlDatabase::database("MyConnect"));

            bool matchHappened = false, updateExec = false, endQuery = false;

            QStringList comandUpdate;

            QString tickerTabela;
            //QString dataTabela = modelDespesas->data(modelDespesas->index(0, headModelDespesas.value("RPTDT"), QModelIndex())).toString();
            QString dataTabela = modelDespesas->data(modelDespesas->index(0, headModelDespesas.value("TRADGENDDT"), QModelIndex())).toString();

            //qryUpdate.prepare("SELECT * FROM json_ativos.dados_ativos WHERE RPTDT = '" + dataTabela + "';");
            qryUpdate.prepare("SELECT * FROM risk_db.B3ativos WHERE B3_vcto = '" + dataTabela + "';");


            //Se a consulta com os valores não executar, mostra mensagem de erro
            if (!qryUpdate.exec())
            {
                QMessageBox::information(this, "Falhou", "A consulta não foi possível");
                QMessageBox::information(this, "Erro no prepare do update", qryUpdate.lastError().text());
            }
            else
            {
                int cont = 0;
                ui->progressBar->setVisible(true);
                ui->progressBar->setRange(0, modelDespesas->rowCount());

                //checa todos os itens do banco e pega apenas os valores do ETF_INDEX
                while (qryUpdate.next())
                {
                    qApp->processEvents();

                    //QString dataBanco = qryUpdate.value(6).toString();
                    //QString tickerBanco = qryUpdate.value(9).toString();
                    QString dataBanco = qryUpdate.value(1).toString();
                    QString tickerBanco = qryUpdate.value(2).toString();

                    tickerTabela = modelDespesas->data(modelDespesas->index(cont, headModelDespesas.value("TCKRSYMB"), QModelIndex())).toString();
                    //dataTabela = modelDespesas->data(modelDespesas->index(cont, headModelDespesas.value("RPTDT"), QModelIndex())).toString();
                    dataTabela = modelDespesas->data(modelDespesas->index(cont, headModelDespesas.value("TRADGENDDT"), QModelIndex())).toString();


                    ui->progressBar->setValue(cont);

                    int inicio = 0;

                    if (tickerBanco == tickerTabela && dataTabela == dataBanco)
                    {
                        QString SQL;

                        for (int column = 0; column < modelDespesas->columnCount(); column++)
                        {
                            QString variavelBanco = qryUpdate.value(column + 1).toString();
                            QString variavelTabela = modelDespesas->data(modelDespesas->index(cont, column, QModelIndex())).toString();

                            if (variavelBanco != variavelTabela && (!variavelBanco.isNull() && variavelTabela != "NULL"))
                            {
                                if (inicio == 0)
                                {
                                    SQL = "UPDATE risk_db.B3ativos SET ";
                                }

                             //----------------------------------------------------------------------------------------------------------------------------------------------------------------
                                
                                if (!headModelDespesas.contains("OPTNTP") && column == 6)
                                {
                                    SQL += "B3_Optntp = 'NONE', ";
                                }
                                else
                                {
                                    SQL += "B3_Optntp = '" + modelDespesas->data(modelDespesas->index(cont, headModelDespesas.value("OPTNTP"), QModelIndex())).toString().trimmed().toUtf8() + "', ";
                                }

                                if (!headModelDespesas.contains("EXRCPRIC") && column == 7)
                                {
                                    SQL += "B3_ExrcPric = '0', ";
                                }
                                else
                                {
                                    SQL += "B3_ExrcPric = '" + modelDespesas->data(modelDespesas->index(cont, headModelDespesas.value("EXRCPRIC"), QModelIndex())).toString().trimmed().toUtf8() + "', ";
                                }

                                if (!headModelDespesas.contains("EXRCSTYLE") && column == 13)
                                {
                                    SQL += "B3_ExrcStyle = '', ";
                                }
                                else
                                {
                                    SQL += "B3_ExrcStyle = '" + modelDespesas->data(modelDespesas->index(cont, headModelDespesas.value("EXRCSTYLE"), QModelIndex())).toString().trimmed().toUtf8() + "', ";
                                }

                                if (headModelDespesas.contains("ALLCNRNDLOT") && column == 15)
                                {
                                    SQL += "B3_AllcnRndLot = '" + modelDespesas->data(modelDespesas->index(cont, headModelDespesas.value("ALLCNRNDLOT"), QModelIndex())).toString().trimmed().toUtf8() + "', ";
                                }

                                if (headModelDespesas.contains("ASSTQTNQTY") && column == 14)
                                {
                                    SQL += "B3_AsstQtnQty = '" + modelDespesas->data(modelDespesas->index(cont, headModelDespesas.value("ASSTQTNQTY"), QModelIndex())).toString().trimmed().toUtf8() + "', ";
                                }

                                if (headModelDespesas.contains("CTRCTMLTPLR") && column == 10)
                                {
                                    SQL += "B3_CtrctMltplr = '" + modelDespesas->data(modelDespesas->index(cont, headModelDespesas.value("CTRCTMLTPLR"), QModelIndex())).toString().trimmed().toUtf8() + "', ";
                                }

                                if (headModelDespesas.contains("DESC") && column == 16)
                                {
                                    SQL += "B3_desc = '" + modelDespesas->data(modelDespesas->index(cont, headModelDespesas.value("DESC"), QModelIndex())).toString().trimmed().toUtf8() + "', ";
                                }

                                if (headModelDespesas.contains("ISIN") && column == 12)
                                {
                                    SQL += "B3_ISIN = '" + modelDespesas->data(modelDespesas->index(cont, headModelDespesas.value("ISIN"), QModelIndex())).toString().trimmed().toUtf8() + "', ";
                                }

                                if (headModelDespesas.contains("MKT") && column == 5)
                                {
                                    SQL += "B3_Mkt = '" + modelDespesas->data(modelDespesas->index(cont, headModelDespesas.value("MKT"), QModelIndex())).toString().trimmed().toUtf8() + "', ";
                                }

                                if (headModelDespesas.contains("SCTYID") && column == 1)
                                {
                                    SQL += "B3_id = '" + modelDespesas->data(modelDespesas->index(cont, headModelDespesas.value("SCTYID"), QModelIndex())).toString().trimmed().toUtf8() + "', ";
                                }

                                if (headModelDespesas.contains("SGMT") && column == 4)
                                {
                                    SQL += "B3_Sgmt = '" + modelDespesas->data(modelDespesas->index(cont, headModelDespesas.value("SGMT"), QModelIndex())).toString().trimmed().toUtf8() + "', ";
                                }

                                if (headModelDespesas.contains("TCKRSYMB") && column == 3)
                                {
                                    SQL += "B3_TckrSymb = '" + modelDespesas->data(modelDespesas->index(cont, headModelDespesas.value("TCKRSYMB"), QModelIndex())).toString().trimmed().toUtf8() + "', ";
                                }

                                if (headModelDespesas.contains("TRAGGCCY") && column == 17)
                                {
                                    SQL += "B3_TradgCcy = '" + modelDespesas->data(modelDespesas->index(cont, headModelDespesas.value("TRAGGCCY"), QModelIndex())).toString().trimmed().toUtf8() + "', ";
                                }

                                if (headModelDespesas.contains("TRADGENDDT") && column == 2)
                                {
                                    SQL += "B3_vcto = '" + modelDespesas->data(modelDespesas->index(cont, headModelDespesas.value("TRADGENDDT"), QModelIndex())).toString().trimmed().toUtf8() + "', ";
                                }

                                if (headModelDespesas.contains("XPRTNCD") && column == 8)
                                {
                                    SQL += "B3_XprtnCd = '" + modelDespesas->data(modelDespesas->index(cont, headModelDespesas.value("XPRTNCD"), QModelIndex())).toString().trimmed().toUtf8() + "', ";
                                }

                                /*if (modelDespesas->data(modelDespesas->index(cont, column, QModelIndex())).toString() != "NULL")
                                {
                                    SQL += headModelDespesas.key(column) + " = '" + modelDespesas->data(modelDespesas->index(cont, column, QModelIndex())).toString() + "', ";
                                }
                                else
                                {
                                    SQL += headModelDespesas.key(column) + " = " + modelDespesas->data(modelDespesas->index(cont, column, QModelIndex())).toString() + ", ";
                                }*/

                                updateExec = true;

                            }
                        }

                        matchHappened = true;

                        if (updateExec == true)
                        {
                            updateExec = false;
                            //Remove última virgula e espaço
                            SQL.remove(SQL.length() - 1, 1);
                            SQL.remove(SQL.length() - 1, 1);

                            //SQL += " WHERE RPTDT = '" + dataTabela + "' AND TCKRSYMB = '" + tickerBanco + "'; ";
                            SQL += " WHERE B3_vcto = '" + dataTabela + "' AND B3_tckrsymb = '" + tickerBanco + "'; ";
                            comandUpdate << SQL;
                            SQL.clear();

                            endQuery = true;
                        }


                        cont++;
                    }
                }


                for (int i = 0; i < comandUpdate.count() && endQuery == true; i++)
                {
                    //executa o comando em cada espaço da list
                    if (qryUpdate.exec(comandUpdate.at(i)))
                    {
                        //mostra todas as alterações
                        ui->lblInfo->setVisible(true);
                        ui->lblInfo->setText(fileName + " atualizado " + QString::number(qryUpdate.numRowsAffected()) + " linhas em " + QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss"));
                    }
                    else
                    {
                        QMessageBox::critical(this, "Erro", qryUpdate.lastError().text());
                        return;
                    }
                }
                comandUpdate.clear();
            }

            if (matchHappened == false)
            {
                inserirDados();
            }
        }
        else
        {
            QMessageBox::critical(this, "Não conectado", database.lastError().text());
        }
    }
    else
    {
        QMessageBox::information(this, "Incorreto", "Este arquivo não é faz parte de um Security List");
    }
    
}

