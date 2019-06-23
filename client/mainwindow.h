#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Common/Protocol.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Protocol& protocol_client;
public:
    explicit MainWindow(Protocol& protocol_client,QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_connectButton_clicked();

    void on_createButton_clicked();

    void on_selectAmmountPlayersButton_clicked();

    void on_startGameButton_clicked();

    void on_quitButton_clicked();

    void on_selectMap_clicked();

    void on_joinButton_clicked();

    void on_selectMatchButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
