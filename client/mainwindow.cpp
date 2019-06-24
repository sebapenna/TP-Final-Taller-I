#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <Common/Protocol.h>
#include <Common/exceptions.h>
#include <Common/ProtocolTranslator/GameStateDTO/BeginDTO.h>

MainWindow::MainWindow(Protocol& protocol_client, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), protocol_client(protocol_client)
{
    ui->setupUi(this);
    ui->createOrJoinMenu->hide();
    ui->selectPlayersMenu->hide();
    ui->startOrQuitMenu->hide();
    ui->selectMapMenu->hide();
    ui->selectMatchMenu->hide();
    ui->errorLabel->setStyleSheet("QLabel { color : red; }");
    ui->errorLabel->hide();
    ui->informationLabel->setStyleSheet("QLabel { color : blue; }");
    ui->informationLabel->hide();

}

MainWindow::~MainWindow()
{
    delete ui;
}
/*
void MainWindow::on_pushButton_clicked()
{
    QMessageBox msgHost;
    QMessageBox msgBoxPort;
    msgHost.setText(ui->HostInput->text().toUtf8().constData());
    msgHost.exec();
    msgBoxPort.setText(ui->portInput->text().toUtf8().constData());
    msgBoxPort.exec();
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->label->hide();
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->label->show();
}

void MainWindow::on_pushButton_4_clicked()
{
    QMessageBox msgData;
    msgData.setText(ui->comboBox->currentText());
    msgData.exec();

}
*/
/*
void MainWindow::on_pushButton_5_clicked()
{
    ui->listWidget->addItem("1");
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->listWidget->addItem("2");
}

void MainWindow::on_pushButton_6_clicked()
{
    QMessageBox::information(this,"title", ui->listWidget->currentItem()->text());
}*/


void MainWindow::on_connectButton_clicked()
{
	try {
        Protocol protocol(ui->HostInput->text().toStdString(), ui->portInput->text().toStdString());
        this->protocol_client = std::move(protocol);
        ui->createOrJoinMenu->show();
        ui->connectHostPortMenu->hide();
        ui->errorLabel->hide();
        std::string information;
        protocol_client>>information;
        ui->informationLabel->setText(information.c_str());
        ui->informationLabel->show();

    } catch (CantConnectException& e) {
        ui->errorLabel->setText("Error while connecting to the server. Please try again");
        ui->errorLabel->show();
    }
    /*
    ui->errorLabel->setText("CONECTADO AMEO");
    ui->errorLabel->show();

    ui->informationLabel->setText("THIS IS AN INFORMATION LABEL");
    ui->informationLabel->show();

    ui->createOrJoinMenu->show();
    ui->connectHostPortMenu->hide();*/
}

void MainWindow::on_createButton_clicked()
{
    protocol_client << (uint8_t)0;
    std::string information;
    uint8_t server_response;
    protocol_client>>server_response;
    protocol_client>>information;
    ui->informationLabel->setText(information.c_str());

    ui->selectPlayersMenu->show();
    ui->createOrJoinMenu->hide();
}

void MainWindow::on_selectAmmountPlayersButton_clicked()
{
    uint8_t amountPlayers = (uint8_t) atoi(ui->selectAmountList->currentText().toUtf8().data());
    protocol_client << amountPlayers;
    std::string information;
    uint8_t server_response;
    protocol_client>>server_response;
    protocol_client>>information;
    ui->informationLabel->setText(information.c_str());

    std::string delimiter = "\n\t";
    std::string delimiterForNumbers = ": ";

    information.erase(0,information.find(delimiter) + delimiter.length()); // El mensaje inicial
    size_t pos = 0;
    std::string token;
    while ((pos = information.find(delimiter)) != std::string::npos) {
        token = information.substr(0, pos);
        token.erase(0, token.find(delimiterForNumbers) + delimiterForNumbers.length());
        ui->listMap->addItem(QString::fromStdString(token));
        information.erase(0, pos + delimiter.length());
    }
    information.erase(0, information.find(delimiterForNumbers) + delimiterForNumbers.length());
    information = information.substr(0,information.length()-1); // Elimino el \n final
    ui->listMap->addItem(QString::fromStdString(information));

    ui->selectMapMenu->show();
    ui->selectPlayersMenu->hide();
}

void MainWindow::on_selectMap_clicked()
{
    int index_selected = ui->listMap->currentIndex().row();
    protocol_client << (uint8_t)index_selected;
    std::string information;
    uint8_t server_response;
    protocol_client>>server_response;
    protocol_client>>information;
    ui->informationLabel->setText(information.c_str());

    ui->startOrQuitMenu->show();
    ui->selectMapMenu->hide();
}

void MainWindow::on_startGameButton_clicked()
{
    std::shared_ptr<ProtocolDTO> dto(new BeginDTO()); // Empiezo el juego
    protocol_client << *dto.get();

    std::string information;
    uint8_t server_response;
    protocol_client>>information;
    protocol_client>>server_response;
    ui->informationLabel->setText(information.c_str());

    this->close();
}

void MainWindow::on_quitButton_clicked()
{
    // BUTON PARA CERRAR
    this->close();
}


void MainWindow::on_joinButton_clicked()
{
    ui->selectMatchMenu->show();
    ui->createOrJoinMenu->hide();
}

void MainWindow::on_selectMatchButton_clicked()
{
    ui->startOrQuitMenu->show();
    ui->selectMatchMenu->hide();
}
