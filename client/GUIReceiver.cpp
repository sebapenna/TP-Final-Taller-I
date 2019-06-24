//
// Created by jonathanmedina on 24/06/19.
//

//#include <qt5/QtCore/QArgument>
#include "GUIReceiver.h"
#include "ui_mainwindow.h"

GUIReceiver::GUIReceiver(Protocol &protocol, Ui::MainWindow *ui) : protocol(protocol), ui(ui) {
    ui->errorLabel->setText("HOLA PERON");
    ui->errorLabel->show();
}
void GUIReceiver::doSomething() {

}
void GUIReceiver::run() {

}
