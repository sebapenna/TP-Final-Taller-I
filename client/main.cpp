
#include <iostream>
#include <string>
#include <exception>
#include <QtWidgets/QApplication>
#include <Common/exceptions.h>
#include "SDL_Runner.h"
#include "../Common/SafeQueue.h"
#include "ClientSender.h"
#include "ClientReceiver.h"
#include "mainwindow.h"
#include "GameController.h"


#define KNOWN_ERROR 1
#define UNKNOWN_ERROR 2

int main(int argc, char** argv){
    try {
        Protocol protocol;
        QApplication app(argc, argv);
        bool userWantsToPlay = false;
        MainWindow mainWindow(protocol, userWantsToPlay);
        mainWindow.show();

        app.exec();
        app.quit();

        std::setlocale(LC_NUMERIC, "C");
        if (!userWantsToPlay) return 1;

        std::string title("Portal");

        bool done = false;

        ProtectedBlockingQueue<std::shared_ptr<ProtocolDTO>> blockingQueue;
        SafeQueue<std::shared_ptr<ProtocolDTO>> safeQueue;

        ClientSender clientSender(protocol, blockingQueue, done);
        clientSender.start();
        ClientReceiver clientReceiver(protocol, safeQueue, done);
        clientReceiver.start();

        SDL_Runner sdlRunner(title, safeQueue, done);
        sdlRunner.start();

        GameController gameController(sdlRunner, blockingQueue, done);
        gameController.play();

        protocol.disconnect();
        sdlRunner.join();
        blockingQueue.setFinishedAdding();

        clientSender.join();
        clientReceiver.join();

        return 0;
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return KNOWN_ERROR;
    }  catch(...) {
        std::cout << UnknownException().what();
        return UNKNOWN_ERROR;
    }
}
