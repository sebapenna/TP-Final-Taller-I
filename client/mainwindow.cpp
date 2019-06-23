#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QMessageBox msgHost;
    QMessageBox msgBoxPort;
    msgHost.setText(ui->HostInput->text().toUtf8().constData());
    msgHost.exec();
    msgBoxPort.setText(ui->portInput->text().toUtf8().constData());
    msgBoxPort.exec();
}
