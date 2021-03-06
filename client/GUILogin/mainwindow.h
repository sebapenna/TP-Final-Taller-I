#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Common/Protocol.h>
#include <QCloseEvent>
#include "GUIReceiver.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Protocol& protocol_client;
    bool& userWantsToPlay;
    void closeEvent(QCloseEvent *bar);
public:
    explicit MainWindow(Protocol& protocol_client, bool& userWantsToPlay, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_connectButton_clicked();

    void on_createButton_clicked();

    void on_selectAmmountPlayersButton_clicked();

    void on_startGameButton_clicked();

    void on_quitButton_clicked();

    void on_selectMap_clicked();

    void on_joinButton_clicked();
    void on_refreshButton_clicked();
    void on_selectMatchButton_clicked();
signals:
    void on_stop();

public slots:
    void messageFromReceiver(int message);
private:
    Ui::MainWindow *ui;
    GUIReceiver guiReceiver;
    bool owner;
    bool passedTheSelectMap;
};

#endif // MAINWINDOW_H
