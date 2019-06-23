#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <Common/Protocol.h>
#include <Common/exceptions.h>

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
    ui->selectPlayersMenu->show();
    ui->createOrJoinMenu->hide();
}

void MainWindow::on_selectAmmountPlayersButton_clicked()
{
    ui->selectMapMenu->show();
    ui->selectPlayersMenu->hide();
}

void MainWindow::on_selectMap_clicked()
{
    ui->startOrQuitMenu->show();
    ui->selectMapMenu->hide();
}

void MainWindow::on_startGameButton_clicked()
{
    // BUTTON PARA EMPEZAR
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
