//
// Created by jonathanmedina on 24/06/19.
//

#ifndef PORTAL_GUIRECEIVER_H
#define PORTAL_GUIRECEIVER_H


#include <Common/Thread.h>
#include <Common/Protocol.h>
//#include <ui_mainwindow.h>
//#include "mainwindow.h"

class GUIReceiver : public Thread {
private:

    Protocol& protocol;
    //Ui::MainWindow *ui;
public:
    GUIReceiver(Protocol &protocol);
    void run() override;
    static void doSomething();
    //void putUI(Ui::MainWindow *pWindow);
};


#endif //PORTAL_GUIRECEIVER_H
