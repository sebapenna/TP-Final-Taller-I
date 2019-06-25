//
// Created by jonathanmedina on 24/06/19.
//

#ifndef PORTAL_GUIRECEIVER_H
#define PORTAL_GUIRECEIVER_H


#include <QObject>
#include <QThread>
#include <Common/Protocol.h>

#define NEW_PLAYER_MESSAGE_ID 1
#define QUIT_PLAYER_MESSAGE_ID 2
#define NOW_YOU_ARE_THE_OWNER_MESSAGE_ID 3
#define START_THE_GAME_MESSAGE_ID 4
class GUIReceiver : public QObject
{
    Q_OBJECT
public:
    explicit GUIReceiver(QObject *parent=0);
    ~GUIReceiver();
    void start(Protocol* protocol);
signals:
    void messageToGUI(int name);
public slots:
    void stop();
private:
    bool mSTop;
};


#endif //PORTAL_GUIRECEIVER_H
