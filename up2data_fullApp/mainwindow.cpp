#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initSettings();

    ui->progressBar->setVisible(false);
    ui->progressBar_2->setVisible(false);

    ui->txtDestino->setText("C:/Users/Lorenzo/Documents/up2Data/20230102");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initSettings() {
    QString dirPath;
    //Pega o diretorio onde a aplicação está sendo salva
    dirPath = QApplication::applicationDirPath();

    //Remover a  última section
    dirPath = dirPath.section("/", 0, dirPath.count("/") - 1);
    //Concatena o caminho até o arquivo settings
    dirPath += "/config/settings.ini";

    settings = new QSettings(dirPath, QSettings::IniFormat);

}

void MainWindow::copiarFiles(QString pathDestino, QString nomeFile, QStringList toBeSend, int i)
{
    //Remove o .json da ultima parte que vai estar por exemplo _1.json ficando só _1
    QString nomeAlt = nomeFile.remove(".json");

    //Joga cada item separado por "_" em uma QStringList para então poder pegar o número no fim do arquivo
    QStringList pedacosNome = nomeAlt.split("_");

    //Pega o número no fim do nome do arquivo
    int numFile = pedacosNome.value(pedacosNome.length() - 1).toInt();
    nomeAlt.remove(QString::number(numFile));

    nomeAlt = nomeAlt + QString::number(numFile - 1) + ".json";

    if (QFile::exists(pathDestino + "/" + nomeAlt))
    {
        QFile::remove(pathDestino + "/" + nomeAlt);
        nomeFile += ".json";
        QFile::copy(toBeSend.value(i), pathDestino + "/" + nomeFile);
    }
    else
    {
        //Aqui ele faz atualização dos arquivos, apagando os existentes e copiando novamente
        if (QFile::exists(pathDestino + "/" + nomeFile))
        {
            QFile::remove(pathDestino + "/" + nomeFile);
            nomeFile += ".json";
            QFile::copy(toBeSend.value(i), pathDestino + "/" + nomeFile);
        }
        else
        {
            nomeFile += ".json";
            //Para copiar o arquivo efetivamente precisamos colocar o nome do arquivo iterado na nova pasta
            QFile::copy(toBeSend.value(i), pathDestino + "/" + nomeFile);
        }
    }

}

void MainWindow::copyFolder(QDir dirDestino, QString pathDestino, QString nomeFile, QStringList toBeSend, int i)
{
    //Se não tiver o diretório ele cria e depois copia os arquivos, se não ele só copia
    if (!dirDestino.exists())
    {
        dirDestino.mkpath(".");
        copiarFiles(pathDestino, nomeFile, toBeSend, i);
    }
    else
    {
        copiarFiles(pathDestino, nomeFile, toBeSend, i);
    }
}

void MainWindow::tratarFim()
{
    qDebug() << "Finalizou";

    QString ret = process->readAllStandardOutput();
    ui->plainTextEdit->setPlainText(ret);

    //Apaga o processo
    process = 0;
    process->deleteLater();
}

void MainWindow::verificarProcess()
{
    //Se houver um processo, fica rodando de 5 em 5 segundos para ver a situação dele
    if (process)
    {
        qDebug() << process->state();
        qDebug() << process->readAllStandardOutput();

        QTimer::singleShot(5000, this, &MainWindow::verificarProcess);
    }
}

void MainWindow::zipArquivo(QString finalFileName, QString path)
{
    qApp->processEvents();
    //Argumentos são os comandos do 7-zip para fazer com que o arquivo seja zipado
    QStringList arguments;
    QString program = "C:\\Program Files\\7-Zip\\7z.exe";

    //Zip arquivo
    process = new QProcess(this);

    //A conexão tem como cada parametro respectivamente: Quem envia o sinal, quando o processo acabar, este widget recebe o sinal de quando acabar, chama então a função tratar fim
    connect(process, &QProcess::finished, this, &MainWindow::tratarFim);

    //arguments.clear();
    arguments << "a" << "-t7z" << finalFileName + ".7z" << finalFileName + ".json";

    process->start(program, arguments);

   // QString cmd = "\"c:\Program Files\7-Zip\7z.exe\"a - t7z " + day + ".7z";

    ui->plainTextEdit->setPlainText("zipando arquivo...");

    verificarProcess();

    //Roda até terminar todo o processo
    process->waitForFinished();
}

void MainWindow::zipFolder(QString day, QString newDirPath)
{
    qApp->processEvents();
    QString program = "C:\\Program Files\\7-Zip\\7z.exe";

    //Zipar pasta
    process = new QProcess(this);
    //A conexão tem como cada parametro respectivamente: Quem envia o sinal, quando o processo acabar, este widget recebe o sinal de quando acabar, chama então a função tratar fim
    connect(process, &QProcess::finished, this, &MainWindow::tratarFim);

    //O ultimo parametro a ser adicionado é a pasta que precisa ser zipada, senão ele zipa o diretório inteiro
    QStringList argumentsFold;
    argumentsFold << "a" << "-t7z" << day + ".7z" << day;

    // QString cmd = "\"c:\Program Files\7-Zip\7z.exe\"a - t7z " + day + ".7z";
    process->start(program, argumentsFold);

    ui->plainTextEdit->setPlainText("zipando folder...");

    verificarProcess();
    process->waitForFinished();
}


/*--------------------------------------------------------------------------------------------------------------------------------------*/


void MainWindow::on_btnOrigem_clicked()
{
    QString folderName;
    //Abre os documentos para a seleção do arquivo desejado
        folderName =QFileDialog::getExistingDirectory(this, "Escolha a pasta");

        if (!folderName.isNull())
        {
            //Este código pega o caminho anterior a pasta selecionada
           /* QDir d = QFileInfo(folderName).absoluteDir();
            pathOrigem = d.absolutePath();
            ui->txtOrigem->setText(pathOrigem);*/

            //FolderName já tem o caminho completo da pasta
             ui->txtOrigem->setText(folderName);

        }
}


void MainWindow::on_btnDestino_clicked()
{
    QString folderName;
    //Abre os documentos para a seleção do arquivo desejado
        folderName =QFileDialog::getExistingDirectory(this, "Escolha a pasta");

        if (!folderName.isNull())
        {
            /*QDir d = QFileInfo(folderName).absoluteDir();
            pathDestinoOrg = d.absolutePath();
            ui->txtDestino->setText(pathDestinoOrg);*/

             ui->txtDestino->setText(folderName);


        }
}


void MainWindow::on_btnPasta_clicked()
{
    QString folderName;
    //Abre os documentos para a seleção do arquivo desejado
        folderName =QFileDialog::getExistingDirectory(this, "Escolha a pasta");

        if (!folderName.isNull())
        {
            /*QDir d = QFileInfo(folderName).absoluteDir();
            pathDestinoOrg = d.absolutePath();
            ui->txtDestino->setText(pathDestinoOrg);*/

             ui->txtDestino->setText(folderName);
        }
}



/*--------------------------------------------------------------------------------------------------------------------------------------*/


void MainWindow::on_btnLerFile_clicked()
{
    //QStringList inclusao;
    QStringList exclusao;

    //Este settings é criado no header e inicializado na função initSettings no começo do arquivo
    //dentro do arquivo o grupo é definido por [lista], ele pega apenas tudo o que tiver naquela sessão
    settings->beginGroup("lista");

    //pega todos os valores da variavel "exclusao" dentro deste grupo e converte me stringList
    exclusao = settings->value("exclusao").toStringList();

    //settings->setValue("inclusao", inclusao); Cria um valor inclusão dentro do grupo selecionado. O segundo inclusão é uma lista na qual jogamos os itens para serem adicionados

    settings->endGroup();



    //QString dir = pathOrigem;
    QString dir = ui->txtOrigem->text();

    //Cria um objeto do diretório no qual eu dei o caminho, onde o próprio diretório é manipulado diretamente através dele
    QDir dirObj(dir);
    //Ordena o diretório pelas pastas primeiro depois arquivos, tudo baseado no nome
    dirObj.setSorting(QDir::SortFlag::DirsFirst | QDir::SortFlag::Name);

    /*Constructs a QDirIterator that can iterate over path, using nameFilters and filters. You can pass options via flags to decide how the directory should be iterated.
    By default, flags is NoIteratorFlags, which provides the same behavior as QDir::entryList().*/
    QDirIterator iterador(dir, QStringList() << "*.json", QDir::Files, QDirIterator::Subdirectories);

    int numAnt = 0;

    QString pathAnt;
    QStringList pedacosFile;

    if (dir.contains("/"))
    {
        //Pega string e joga cada parte separada por "/" em um espaço da lista, para então pegar a data
        pedacosFile = dir.split("/");
    }
    else
    {
        QMessageBox::information(this, "Formato incorreto", "Precisa colocar o caminho do arquivo com \"/\"");
        return;
    }

    QStringList toBeSend;
    QStringList pedacosNome;

    int dataFolder = pedacosFile.value(pedacosFile.length()-1).toInt();

    pedacosFile.clear();


    //Enquanto tiver adiante mais arquivos do tipo específicado
    while(iterador.hasNext())
    {
        //É necessário dar next no começo para iniciar a iteração de todas as pastas. Caso não coloque o next, ele permanece
        //com um filePath vazio e a cópia não é possivel (não precisa colocar o qDebug
        qDebug() << iterador.next();
        qDebug() << "\n-------------------------------\n";
        qDebug() << iterador.fileName();

        bool forbid = false;

        QString path = iterador.filePath();

        QStringList pathSplit = path.split("/");

        //a pasta que preciso para checar, sempre está 3 posições antes do fim
        QString FirstfolderName = pathSplit.at(pathSplit.length() - 3);

        //A pasta antes de chegar nos arquivos json
        QString SecfolderName = pathSplit.at(pathSplit.length() - 2);

        for (int i = 0; i < exclusao.size(); i++)
        {
            if (FirstfolderName == exclusao[i] || SecfolderName == exclusao[i])
            {
                forbid = true;
            }
        }

        if (!forbid)
        {
            //Armazena o nome do arquivo em uma variável
            QString nomeFile = iterador.fileName();
            //nomeFile.replace(".json", "");

            //Remove o .json da ultima parte que vai estar por exemplo _1.json ficando só _1
            nomeFile.remove(".json");

            //Joga cada item separado por "_" em uma QStringList para então poder pegar o número no fim do arquivo
            pedacosNome = nomeFile.split("_");

            //Pega o número no fim do nome do arquivo
            int numAtual = pedacosNome.value(pedacosNome.length() - 1).toInt();

            //Compara o número atual com o numero anterior. Se numAtual for maior apenas armazena o caminho em uma variável
            if (numAtual > numAnt)
            {
                pathAnt = iterador.filePath();
            }
            else
            {
                //se for menor, significa que é um outro arquivo, e não o mesmo tipo com atualizações mais recentes
                //ex: Commodities_SettlementPriceFile_Futures_20220629_7.json e Commodities_SettlementPriceFile_Futures_AfterHours_20220629_1.json
                if (numAtual <= numAnt)
                {
                    //Envia para a lista o caminho do arquivo anterior
                    toBeSend.append(pathAnt);
                }
                //Atualiza para o caminho do arquivo atual. Caso o próximo seja igual ele enviará este caminho
                pathAnt = iterador.filePath();
            }

            //Atualiza o número antigo com o atual
            numAnt = numAtual;
        }

    }

    pedacosNome.clear();

    ui->progressBar->setVisible(true);
    ui->progressBar->setValue(0);

    ui->progressBar->setRange(0, toBeSend.length());


    for (int i = 0; i < toBeSend.length(); i++)
    {
        //QString pathDestino = "C:/Users/Lorenzo/Documents/up2Data/";
        QString pathDestino = ui->txtDestino->text() + "/";

        qApp->processEvents();
        ui->progressBar->setValue(i);

        //Pega o caminho no valor atual da lista com os arquivos filtrados, e separa cada item da string
        pedacosFile = toBeSend.value(i).split("/");

        //Pega o último item do pedacosFile, que é a parte do nome do arquivo
        QString nomeFile = pedacosFile.value(pedacosFile.length() - 1);

        //Separa todos os itens do nome
        pedacosNome = nomeFile.split("_");

        //pega a data que estará no nome do arquivo
        int dataFile = pedacosNome.value(pedacosNome.length() - 2).toInt();

        //É necessário fazer isso para apagar o nome do arquivo e não criar uma pasta lá na frente com o nome dele
        pedacosFile.remove(pedacosFile.length() - 1);

        for (int i = 4; i < pedacosFile.length(); i++)
        {
            //Atualiza a path já pré-definida com exatamente o pedaço em diante do pedacosFile para fazer a cópia corretamente
            pathDestino += pedacosFile.value(i) + "/";

        }

        //Remove o último "/"
        pathDestino.remove(pathDestino.length() - 1, 1);



        //Se a data do arquivo for de um dia anterior, ele altera o pathDestino para o caminho correto e depois copia todos os arquivos
        if (dataFile < dataFolder)
        {
            pathDestino.replace(QString::number(dataFolder), QString::number(dataFile));

            //Cria o objeto do diretorio destino que fará a manipulação no sistema
            QDir dirDestino(pathDestino);

            copyFolder(dirDestino, pathDestino, nomeFile, toBeSend, i);

            //Ordena o diretório pelas pastas primeiro depois arquivos, tudo baseado no nome
            dirDestino.setSorting(QDir::SortFlag::DirsFirst | QDir::SortFlag::Name);

        }
        else
        {
            //Cria o objeto do diretorio destino que fará a manipulação no sistema
            QDir dirDestino(pathDestino);

            copyFolder(dirDestino, pathDestino, nomeFile, toBeSend, i);

            //Ordena o diretório pelas pastas primeiro depois arquivos, tudo baseado no nome
            dirDestino.setSorting(QDir::SortFlag::DirsFirst | QDir::SortFlag::Name);

        }

        pathDestino.clear();
    }

    ui->progressBar->setVisible(false);
    QMessageBox::information(this, "Concluido", "Arquivos filtrados em novo diretório");
}


void MainWindow::on_btnJuntar_clicked()
{
    //QStringList inclusao;
    QStringList exclusao;

   //Este settings é criado no header e inicializado na função initSettings no começo do arquivo
   //dentro do arquivo o grupo é definido por [lista], ele pega apenas tudo o que tiver naquela sessão
   settings->beginGroup("lista");

   //pega todos os valores da variavel "exclusao" dentro deste grupo e converte me stringList
   exclusao = settings->value("exclusao").toStringList();

   //settings->setValue("inclusao", inclusao); Cria um valor inclusão dentro do grupo selecionado. O segundo inclusão é uma lista na qual jogamos os itens para serem adicionados

   settings->endGroup();



    //Pega o diretório selecionado na text box do destino
    QString dir = ui->txtPasta->text();

    //Cria um objeto do diretório no qual eu dei o caminho, onde o próprio diretório é manipulado diretamente através dele
    QDir dirObj(dir);
    //Ordena o diretório pelas pastas primeiro depois arquivos, tudo baseado no nome
    dirObj.setSorting(QDir::SortFlag::DirsFirst | QDir::SortFlag::Name);

    /*Constructs a QDirIterator that can iterate over path, using nameFilters and filters. You can pass options via flags to decide how the directory should be iterated.
    By default, flags is NoIteratorFlags, which provides the same behavior as QDir::entryList().*/
    QDirIterator iterador(dir, QStringList() << "*.json", QDir::Files, QDirIterator::Subdirectories);

    //Pré-define o array base para o merge
    QJsonArray jsonArrayDef;

    //Caminho do arquvio definitivo no primeiro loop
    QString pathDef;

    QStringList nameParts;

    //Enquanto ele se manter vazio, ele faz todo o processo para pegar o primeiro arquivo corretamente
    while (jsonArrayDef.isEmpty() && iterador.hasNext())
    {
        ui->plainTextEdit->setPlainText("Procurando Arquivo...");
        //É necessário dar next primeiro para pegar o primeiro diretório, senão o loop será sempre sobre um caminho vazio
        iterador.next();

        pathDef = iterador.filePath();
        QStringList pathCheck = pathDef.split("/");

        //percorre pela lista "exclusao" puxada do arquivo settings.ini
        for (int i = 0; i < exclusao.count(); i++)
        {
            //se o caminho do arquivo atual conter algum item de exclusao, esta lista é completamente limpa para não rodar os arquivos deste caminho
            if (pathCheck.contains(exclusao.at(i)))
            {
                pathCheck.clear();
            }
        }

        QString nameFile = iterador.fileName().remove(".json");
        nameParts = nameFile.split("_");

        //Se não for das pastas especificadas, então ele faz todo o processo para adicionar o conteúdo do arquivo para JsonArray
        //pathCheck.size() se ainda tiver alguma coisa no pathCheck ele entra e executa a busca pelos arquivos
        if (pathCheck.size())
        {
            //Abre o arquivo em uma variável
            QFile file(iterador.filePath());

            if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            {  // Tratar Erro
                QMessageBox::information(this, "Não aberto", file.errorString());
                return;
            }

            QTextStream file_text(&file);

            //Armazena todo o JSON do arquivo em uma variável
            QString json = file_text.readAll().trimmed();
            file.close();

            //Mostra se tem algum possível erro para abrir o json através do json document
            QJsonParseError err;

            //The QJsonDocument class provides a way to read and write JSON documents.
            QJsonDocument jsonDoc = QJsonDocument::fromJson(json.toUtf8(), &err);

            //Checa todos os possíveis erros que podem resultar em não abrir o json
            if (err.error != QJsonParseError::NoError)
            {
                QMessageBox::critical(this, "Error", err.errorString());
                return;
            }
            if (jsonDoc.isNull())
            {
                QMessageBox::information(this, "Vazio", "Documento Vazio.");
                QMessageBox::critical(this, "Error", err.errorString());
                return;
            }

            if (!jsonDoc.isArray())
            {
                QMessageBox::information(this, "Falha", "Não é Array.");
                return;
            }

            //Pega o json e transforma diretamente em array, pois todos os arquivo começam no formato de array
            jsonArrayDef = jsonDoc.array();
        }

        //Se chegar no ponto onde nenhum arquivo pode ser selecionado e não tem mais, então retona
        if (!iterador.hasNext())
        {
            QMessageBox::information(this, "Vazio", "Nenhum arquivo encontrado");
            ui->plainTextEdit->setPlainText("");
            return;
        }
    }

    ui->plainTextEdit->setPlainText("");

    //Pré-define todas as variáveis necessárias para a iteração
    QVariantMap jsonMapDef;
    QVariantMap jsonMapAtual;

    //Listas para pegar as chaves de cada objeto dos dois arrays
    QStringList keys;
    QStringList keysDef;

    //Listas para fazer as checagens
    QStringList insertedList;
    QStringList appendNonExistValue;
    QStringList minorValues;
    QStringList recentAdd;

    //Caminho dos novos arquivos à serem iterados
    QString pathNew;

    ui->progressBar->setVisible(true);
    ui->progressBar->setValue(0);
    ui->progressBar->setRange(0, jsonArrayDef.size());

    ui->progressBar_2->setVisible(true);

    while (iterador.hasNext())
    {
        iterador.next();

        pathNew = iterador.filePath();
        QStringList pathCheck = pathNew.split("/");

        //percorre pela lista "exclusao" puxada do arquivo settings.ini
        for (int i = 0; i < exclusao.count(); i++)
        {
            //se o caminho do arquivo atual conter algum item de exclusao, esta lista é completamente limpa para não rodar os arquivos deste caminho
            if (pathCheck.contains(exclusao.at(i)))
            {
                pathCheck.clear();
            }
        }

        //Faz o mesmo processo que para o anterior, porém dessa vez para todos os arquivos adiante
        //pathCheck.size() se ainda tiver alguma coisa no pathCheck ele entra e executa a busca pelos arquivos
        if (pathCheck.size())
        {
            //Cria um objeto do arquivo para através de cada caminho do QDirIterator
            QFile file(iterador.filePath());

            //Se não abrir mostra mensagem de erro
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            {  // Tratar Erro
                QMessageBox::information(this, "Não aberto", file.errorString());
                return;
            }

            //Armazena o texto do arquivo para ser lido ou escrito
            QTextStream file_text(&file);

            //Lê todo o conteúdo do arquivo e armazena em uma string
            QString json = file_text.readAll().trimmed();
            file.close();

            //para verificar err
            QJsonParseError err;

            //The QJsonDocument class provides a way to read and write JSON documents.
            QJsonDocument jsonDoc = QJsonDocument::fromJson(json.toUtf8(), &err);

            //Se tiver erro através do parseError
            if (err.error != QJsonParseError::NoError)
            {
                QMessageBox::critical(this, "Error", err.errorString());
                return;
            }
            //Se doc for vazio
            if (jsonDoc.isNull())
            {
                QMessageBox::information(this, "Vazio", "Documento Vazio.");
                QMessageBox::critical(this, "Error", err.errorString());
                return;
            }
            //Se doc não for array. Neste caso é o que devemos colocar, porque ele começa sendo um array.
            //Se colocassemos obj, ele sempre daria erro
            if (!jsonDoc.isArray())
            {
                QMessageBox::information(this, "Falha", "Não é Array.");
                return;
            }

            //Armazena em array o novo arquivo a ser comparado
            QJsonArray jsonArray = jsonDoc.array();

            //Pré-define um valor qualquer para não dar erro no loop
            QString tickerDefAnt = "0";
            QString tickerNextDef = "0";

            int pos = 0;

            bool secondCharBig, thirdCharBig, fourthCharBig;

            for (int i = 0; i < jsonArrayDef.size(); i++)
            {
                qApp->processEvents();

                ui->progressBar_2->setValue(0);
                ui->progressBar_2->setRange(0, jsonArray.size());

                secondCharBig = false;
                thirdCharBig = false;
                fourthCharBig = false;

                QJsonValue val = jsonArray.at(pos);

                QJsonValue valDef = jsonArrayDef.at(i);

                /*A JSON object is a list of key value pairs, where the keys are unique strings and the values are represented by a QJsonValue.
                A QJsonObject can be converted to and from a QVariantMap.
                You can query the number of (key, value) pairs with size(), insert(), and remove() entries from it and iterate over its content using the standard C++ iterator pattern.*/
                QJsonObject obj = val.toObject();
                QJsonObject objDef = valDef.toObject();

                keys = obj.keys();
                keysDef = objDef.keys();

                jsonMapAtual = obj.toVariantMap();
                jsonMapDef = objDef.toVariantMap();

                ui->progressBar->setValue(i);

                //Se os dois maps contém o tckrSymb
                if (jsonMapAtual.contains("TckrSymb") && jsonMapDef.contains("TckrSymb"))
                {
                    //Pega os primeiros tickers para analise
                    QString tickerAtual = jsonMapAtual["TckrSymb"].toString();
                    QString tickerDef = jsonMapDef["TckrSymb"].toString();

                    //como não é adicionado em ordem alfabetica, quando um tickerDef for menor que o anterior, significa que não terá os tickers necessários no jsonArray
                    //então ele restitui o array para para analisar desde o começo de novo
                    if (tickerDef.at(0) < tickerDefAnt.at(0) && !recentAdd.contains(tickerDef))
                    {
                        pos = 0;
                        jsonArray = jsonDoc.array();
                    }

                    //ui->plainTextEdit->setPlainText("Arquivo definitivo: " + pathDef + " \n\nArquivo atual: " + pathNew + "\n\ni:" + QString::number(i) + ", jsonMapDef : " + tickerDef + ", jsonMapAtual : " + tickerAtual);


                    //Percorre o array e pega cada objeto inteiro e não linha por linha dentro do objeto, enquanto a letra que o ticker atual começar for me que a do ticker definitivo e os ticker forem diferentes
                    for (int j = pos; j < jsonArray.size() && tickerAtual.at(0) <= tickerDef.at(0) && tickerDef != tickerAtual && secondCharBig == false && thirdCharBig == false && fourthCharBig == false && !recentAdd.contains(tickerDef); j++)
                    {
                        qApp->processEvents();

                        //limpa as chaves do objeto anterior
                        keys.clear();
                        //limpa o map do objeto anterior
                        jsonMapAtual.clear();

                        //pega o valor do array sendo analisado na posição j (geralmente vai ser sempre 0
                        QJsonValue val = jsonArray.at(j);
                        //Converte o valor em objeto
                        QJsonObject objAtual = val.toObject();

                        //pega as keys do objeto
                        keys = objAtual.keys();

                        //Converte o objeto em map
                        jsonMapAtual = objAtual.toVariantMap();
                        //atualiza o ticker atual
                        tickerAtual = jsonMapAtual["TckrSymb"].toString();

                        ui->progressBar_2->setValue(j);

                        ui->plainTextEdit->setPlainText("Arquivo definitivo: " + pathDef + " \n\nArquivo atual: " + pathNew + "\n\ni:" + QString::number(i) + ", j : " + QString::number(j) + " jsonMapDef : " + tickerDef + ", jsonMapAtual : " + tickerAtual);

                        //Se os dois tickers começarem com a mesma letra
                        if (tickerAtual.at(0) == tickerDef.at(0))
                        {
                            //se a segunda letra ticker atual for menor do que a do tickerDef e não foi apagado, é porque ele em algum ponto já foi adicionado no def, porém ainda não chegou na área que pode ter um insert
                            //é possível que tenha uma outra área do jsonArrayDef que comece com a mesma letra de novo. Se for o caso, o jsonArray já terá sido restituido e a analise pode acontecer novamente
                            if ((tickerAtual.at(1) < tickerDef.at(1) || tickerAtual.at(2) < tickerDef.at(2) || (tickerAtual.length() > 3 && tickerDef.length() > 3 && tickerAtual.at(3) < tickerDef.at(3))) && (appendNonExistValue.contains(tickerAtual) || minorValues.contains(tickerAtual)))
                            {
                                jsonArray.removeAt(j);
                                j--;
                            }
                            else
                            {
                                //Se a segunda letra do ticker atual for menor e nunca foi adicionada a nenhuma lista, significa que é a primeira vez que ele passa e nunca foi analizado
                                if ((tickerAtual.at(1) < tickerDef.at(1) || tickerAtual.at(2) < tickerDef.at(2) || (tickerAtual.length() > 3 && tickerDef.length() > 3 && tickerAtual.at(3) < tickerDef.at(3))) && !appendNonExistValue.contains(tickerAtual) && !minorValues.contains(tickerAtual))
                                {
                                    jsonArrayDef.append(QJsonObject::fromVariantMap(jsonMapAtual));
                                    appendNonExistValue.append(tickerAtual);
                                    recentAdd.append(tickerAtual);

                                    ui->progressBar->setRange(0, jsonArrayDef.size());

                                    jsonArray.removeAt(j);
                                    j--;
                                }
                                else
                                {


                                    //Se a segunda letra do atual for maior do que a do def, então não precisa ser analisada nesse momento
                                    if (tickerAtual.at(1) > tickerDef.at(1))
                                    {
                                        secondCharBig = true;
                                    }
                                    else
                                    {
                                        if (tickerAtual.at(2) > tickerDef.at(2))
                                        {
                                            thirdCharBig = true;
                                        }
                                        else
                                        {
                                            if (tickerAtual.length() > 3)
                                                fourthCharBig = true;
                                        }
                                    }
                                }
                            }

                            //Se os tickers por completo forem iguais
                            if (tickerDef == tickerAtual)
                            {
                                //adiciona na lista para checar os inseridos
                                insertedList.append(tickerAtual);
                                //Da insert no json map definitivo, de cada item do map atual
                                for (int cont = 0; cont < keys.length(); cont++)
                                {
                                    jsonMapDef.insert(keys[cont], jsonMapAtual.value(keys[cont]).toString());
                                }

                                //Remove na posição do array para evitar loop por elementos desnecessários
                                jsonArray.removeAt(j);
                                //volta uma posição para não pular a analise de nenhum elemento
                                j--;


                                ui->lblDef->setText(tickerDef + " X ");
                                ui->lblAt->setText(tickerAtual);

                            }
                            else
                            {
                                //Adiciona os tickers que tinha a SEGUNDA LETRA maior porem não foram analisados, baseado se o próximo ticker def for maior
                                //Não acredito que faça diferença ter isso ou não, mas vou manter
                                int nextPosDef = i + 1;

                                QJsonValue nextValDef = jsonArrayDef.at(nextPosDef);
                                QJsonObject objNextDef = nextValDef.toObject();

                                if (!objNextDef.isEmpty())
                                {
                                    QVariantMap jsonMapNextDef = objNextDef.toVariantMap();
                                    tickerNextDef = jsonMapNextDef["TckrSymb"].toString();

                                    //isso por algum motivo não continua no loop. Se o ticker do Array definitivo for CANQ22 é o próximo for EUPQ22, então Antes de mudar para o EUPQ22
                                    //ele deveria adicionar todos os depois dele que não tiveram match e ainda eram maiores que ele, como CHFN22, CHLN22, CNHN22, etc.
                                    //Só que por algum motivo ele quebra o loop e adiciona depois
                                    if (tickerNextDef.at(0) > tickerDef.at(0) && tickerAtual.at(0) == tickerDef.at(0) && !insertedList.contains(tickerAtual) && !appendNonExistValue.contains(tickerAtual) && !minorValues.contains(tickerAtual) && !tickerNextDef.isNull())
                                    {

                                        jsonArrayDef.append(QJsonObject::fromVariantMap(jsonMapAtual));
                                        appendNonExistValue.append(tickerAtual);
                                        recentAdd.append(tickerAtual);

                                        ui->progressBar->setRange(0, jsonArrayDef.size());

                                        jsonArray.removeAt(j);
                                        j--;
                                    }

                                }
                            }
                        }
                        else
                        {
                            //Se a PRIMEIRA letra do ticker atual for menor que a do ticker def, e não existir em nenhuma lista, adiciona no jsonArrayDef e depois apaga do jsonArray
                            if (tickerAtual.at(0) < tickerDef.at(0) && !insertedList.contains(tickerAtual) && !appendNonExistValue.contains(tickerAtual) && !minorValues.contains(tickerAtual))
                            {
                                jsonArrayDef.append(QJsonObject::fromVariantMap(jsonMapAtual));
                                minorValues.append(tickerAtual);
                                recentAdd.append(tickerAtual);

                                ui->progressBar->setRange(0, jsonArrayDef.size());

                                jsonArray.removeAt(j);
                                j--;
                            }
                            else
                            {
                                //Se forem itens que já existem, porém não estão na área que podem ser analisados, simplesmente apaga, porque o array será eventualmente restaurado e eles poderão ser analisados
                                if (tickerAtual.at(0) < tickerDef.at(0) && (insertedList.contains(tickerAtual) || appendNonExistValue.contains(tickerAtual) || minorValues.contains(tickerAtual)) && jsonArray.size() > 1)
                                {
                                    jsonArray.removeAt(j);
                                    j--;
                                }
                            }

                        }

                    }

                    //Para saber o ticker anterior
                    tickerDefAnt = tickerDef;

                    //No último elemento do jsonArrayDef, se ainda houver no jsonArray elementos maiores do que os que existem no Def, adiciona todos os maiores e iguais a eles
                    //Isso vale também para caso sobre os elementos com a segunda letra maiores
                    for (int z = 0; i == jsonArrayDef.size() - 1 && (tickerAtual.at(0) >= tickerDef.at(0) || (tickerAtual.at(0) == tickerDef.at(0) && tickerAtual.at(1) > tickerDef.at(1))) && !recentAdd.contains(tickerAtual) && !jsonArray.isEmpty(); z++)
                    {
                        jsonMapAtual.clear();

                        QJsonValue val = jsonArray.at(z);
                        QJsonObject objAtual = val.toObject();

                        jsonMapAtual = objAtual.toVariantMap();
                        tickerAtual = jsonMapAtual["TckrSymb"].toString();

                        jsonArrayDef.append(QJsonObject::fromVariantMap(jsonMapAtual));
                        appendNonExistValue.append(tickerAtual);
                        recentAdd.append(tickerAtual);

                        ui->progressBar->setRange(0, jsonArrayDef.size());

                        ui->plainTextEdit->setPlainText("Arquivo definitivo: " + pathDef + " \n\nArquivo atual: " + pathNew + "\n\ni:" + QString::number(i) + ", z : " + QString::number(z) + " jsonMapDef : " + tickerDef + ", jsonMapAtual : " + tickerAtual);

                        jsonArray.removeAt(z);
                        z--;
                    }

                   //limpa todas as listas a cada item do percorre do jsonArrayDef
                    jsonMapDef.clear();
                    keysDef.clear();

                    keys.clear();
                    jsonMapAtual.clear();
                }
            }

            //limpa as listas para analisar um novo arquivo
            insertedList.clear();
            recentAdd.clear();

        }
    }

    //Converte o array conluido em doc para transformar em string
    QJsonDocument docFinal;
    docFinal.setArray(jsonArrayDef);

    QString jsonFinal = docFinal.toJson();

    ui->progressBar->setVisible(false);
    ui->progressBar_2->setVisible(false);

    //Pega o dia do arquivo do jsonArrayDef armazenado na lista do loop
    QString day = nameParts.value(nameParts.length() - 2);

    QString finalFileName = "jsonDia_" + day;

    //O destino do arquivo é definido no próprio nome
    QFile finalFile(ui->txtDestino->text() + "/" + finalFileName + ".json");

    //Se não houver o arquivo ele cria, senão apenas edita
    if (finalFile.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QTextStream stream(&finalFile);
        stream << jsonFinal;

        finalFile.flush();
        finalFile.close();
    }
    else
    {
        QMessageBox::critical(this, "Erro", "Algo Deu errado.");
    }

    //escolhe o diretorio do dia para zipar o arquivo
    QString path = ui->txtDestino->text();
    QDir::setCurrent(path);


    zipArquivo(finalFileName, path);

    /*---------------------------------------------------------------------------------------*/

    //Para zipar a pasta por completo escolhe o diretorio up2Data, porém não entra na pasta de nenhum dia
    QString newDirPath = path.section("/", 0, path.count("/") - 1);
    QDir::setCurrent(newDirPath);

    zipFolder(day, newDirPath);

    tratarFim();
}


void MainWindow::on_btnEnviar_clicked()
{
    //O this significa que o mainWindow é o pai deste dialog
    dialogSQL = new mySql(this);
    dialogSQL->show();
}

