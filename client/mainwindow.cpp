#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->createOrJoinMenu->hide();
    ui->selectPlayersMenu->hide();
    ui->startOrQuitMenu->hide();
    ui->selectMapMenu->hide();
    ui->selectMatchMenu->hide();
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
    ui->createOrJoinMenu->show();
    ui->connectHostPortMenu->hide();
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
