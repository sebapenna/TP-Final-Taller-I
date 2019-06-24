#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "GUIReceiver.h"

#include <QMessageBox>
#include <Common/Protocol.h>
#include <Common/exceptions.h>
#include <Common/ProtocolTranslator/GameStateDTO/BeginDTO.h>
#include <Common/ProtocolTranslator/GameStateDTO/QuitDTO.h>

MainWindow::MainWindow(Protocol& protocol_client, bool& userWantsToPlay, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), protocol_client(protocol_client), userWantsToPlay(userWantsToPlay)
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

    //connect(reinterpret_cast<const QObject *>(&a), SIGNAL(doSomething()), ui->errorLabel, SLOT(setText()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

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
    this->userWantsToPlay = true;
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
    this->close();
}


void MainWindow::on_joinButton_clicked()
{
    protocol_client << (uint8_t)1;
    std::string information;
    uint8_t server_response;
    uint8_t server_response2;
    protocol_client>>server_response;

    // REFRESH LOOP
    protocol_client>>information;
    ui->informationLabel->setText(information.c_str());

    protocol_client << (int16_t)-1;

    information.clear();
    server_response = -1;
    protocol_client>>server_response2;

    // END REFRESH LOOP
    uint32_t n_games;
    protocol_client>>n_games;
    protocol_client>>information;
    for (size_t i = 0; i < n_games; ++i) {
        std::string server_message123;
        protocol_client >> server_message123;   // Recibo listado partidas
        server_message123.erase(0, 3); // elimino el \t y -
        server_message123 = server_message123.substr(0,server_message123.length()-1); // Elimino el \n final
        ui->listMatch->addItem(QString::fromStdString(server_message123));
    }
    // PARTIDAS LISTADAS
    ui->informationLabel->setText(information.c_str());

    ui->selectMatchMenu->show();
    ui->createOrJoinMenu->hide();
}

void MainWindow::on_selectMatchButton_clicked()
{
    std::string delimiter(": ");
    std::string currentItem = ui->listMatch->currentItem()->text().toStdString();
    currentItem.erase(0, currentItem.find(delimiter) + delimiter.length());
    currentItem = currentItem.substr(0, currentItem.find(" | "));
    protocol_client << (int16_t) atoi(currentItem.c_str());
    uint8_t server_response;
    protocol_client >> server_response;

    std::string server_msg;
    uint8_t server_response2;
    protocol_client >> server_msg;   // Recibo informacion de lo sucedido

    ui->errorLabel->setText(server_msg.c_str());
    ui->errorLabel->show();
    server_msg.clear();
    protocol_client >> server_response;

    if (server_response == 1) {
        GUIReceiver guiReceiver(protocol_client, ui);

        ui->startOrQuitMenu->show();
        ui->selectMatchMenu->hide();
    } else {
        protocol_client >> server_msg;
        protocol_client << (int16_t)-1;

        protocol_client>>server_response2;
        uint32_t n_games;
        protocol_client>>n_games;
        ui->listMatch->clear();
        protocol_client>>server_msg;
        for (size_t i = 0; i < n_games; ++i) {
            std::string server_message123;
            protocol_client >> server_message123;   // Recibo listado partidas
            server_message123.erase(0, 3); // elimino el \t y -
            server_message123 = server_message123.substr(0,server_message123.length()-1); // Elimino el \n final
            ui->listMatch->addItem(QString::fromStdString(server_message123));
        }

    }
}

void MainWindow::on_refreshButton_clicked()
{
    std::string information;
    uint8_t server_response2;
    ui->listMatch->clear();

    protocol_client << (int16_t)-1;

    information.clear();

    protocol_client>>server_response2;
    uint32_t n_games;
    protocol_client>>n_games;
    protocol_client>>information;
    for (size_t i = 0; i < n_games; ++i) {
        std::string server_message123;
        protocol_client >> server_message123;   // Recibo listado partidas
        server_message123.erase(0, 3); // elimino el \t y -
        server_message123 = server_message123.substr(0,server_message123.length()-1); // Elimino el \n final
        ui->listMatch->addItem(QString::fromStdString(server_message123));
    }
    ui->informationLabel->setText(information.c_str());
    //ui->listMatch->removeRows( 0, ui->listMatch->rowCount() );
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (!this->userWantsToPlay) {
        QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Portal",
                                                                    tr("Are you sure?\n"),
                                                                    QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                    QMessageBox::Yes);
        if (resBtn != QMessageBox::Yes) {
            event->ignore();
        } else {
            std::shared_ptr<ProtocolDTO> dto(new QuitDTO()); // Asi no hago el free
            protocol_client << *dto.get();
            protocol_client.disconnect();
            event->accept();
        }
    }
}