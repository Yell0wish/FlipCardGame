#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "aboutwindow.h"
#include "mycard.h"
#include "gamewindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    GameWindow *gameWindow = nullptr;

    // 开始游戏按钮
    QPushButton* startGameButton = nullptr;
    // 排行榜按钮
    QPushButton* leaderboardButton = nullptr;
    // 关于按钮
    QPushButton* aboutButton = nullptr;
    // 退出按钮
    QPushButton* quitGameButton = nullptr;
    // 函数
    void initializeButtons(); // 按钮加载
    void closeEvent(QCloseEvent *event);
private slots:// 槽函数声明
    void on_startGameButton_clicked();
    void on_leaderboardButton_clicked();
    void on_aboutButton_clicked();
    void handleShowMain();
};

#endif // MAINWINDOW_H
