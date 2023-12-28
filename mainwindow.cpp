#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutwindow.h"
#include <QPixmap>
#include <QPalette>
#include <QDebug>
#include"util.h"
#include "leaderboardwindow.h"
#include "gamewindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    startGameButton(nullptr),
    leaderboardButton(nullptr),
    aboutButton(nullptr)
{
    ui->setupUi(this);
    this->setWindowTitle("FlipCard");
    Utils::setupBackground(this, ":/pic_sources/imgs/background.png");
    initializeButtons();
}


void MainWindow::initializeButtons() {
    // 初始化各个按钮
    QSize buttonSize(375, 106);

    startGameButton = Utils::createButton(this, ":/pic_sources/imgs/startGameImage.png", buttonSize);
    startGameButton->move(320, 200);
    connect(startGameButton, &QPushButton::clicked, this, &MainWindow::on_startGameButton_clicked);

    leaderboardButton = Utils::createButton(this, ":/pic_sources/imgs/leaderBoardImage.png", buttonSize);
    leaderboardButton->move(320, 350);
    connect(leaderboardButton, &QPushButton::clicked, this, &MainWindow::on_leaderboardButton_clicked);

    aboutButton = Utils::createButton(this, ":/pic_sources/imgs/aboutImage.png", buttonSize);
    aboutButton->move(320, 500);
    connect(aboutButton, &QPushButton::clicked, this, &MainWindow::on_aboutButton_clicked);

    quitGameButton = Utils::createButton(this, ":/pic_sources/imgs/quitGame.png", buttonSize);
    quitGameButton->move(320, 650);
    connect(quitGameButton, &QPushButton::clicked, this, [&](){Utils::on_quitGameButton_clicked(this);});
}


MainWindow::~MainWindow()
{
    qDebug() << "com";
    delete ui;
    // 根据父子关系会删除QPushButton* 无需手动删除
}

void MainWindow::on_startGameButton_clicked() {
    qDebug() << "Start Game button clicked";
    this->hide();// 关闭后自动释放内存
    if (gameWindow == nullptr) {
        gameWindow = new GameWindow(this);  // 创建新窗口
        gameWindow->setAttribute(Qt::WA_DeleteOnClose);
        // 连接AboutWindow的信号到MainWindow的自定义槽
        connect(gameWindow, &GameWindow::requestShowMain, this, &MainWindow::handleShowMain);

    }
    gameWindow->show();  // 显示关于窗口

}

void MainWindow::on_leaderboardButton_clicked() {
//    qDebug() << "Leaderboard button clicked";
    this->hide();// 关闭后自动释放内存

    LeaderBoardWindow *leaderBoardWindow = new LeaderBoardWindow(this);  // 创建新窗口
    leaderBoardWindow->setAttribute(Qt::WA_DeleteOnClose);

    // 连接AboutWindow的信号到MainWindow的自定义槽
    connect(leaderBoardWindow, &LeaderBoardWindow::requestShowMain, this, &MainWindow::handleShowMain);

    leaderBoardWindow->show();  // 显示关于窗口
}

void MainWindow::on_aboutButton_clicked() {
    this->hide();// 关闭后自动释放内存

    AboutWindow *aboutWindow = new AboutWindow(this);  // 创建新窗口
    aboutWindow->setAttribute(Qt::WA_DeleteOnClose);

    // 连接AboutWindow的信号到MainWindow的自定义槽
    connect(aboutWindow, &AboutWindow::requestShowMain, this, &MainWindow::handleShowMain);

    aboutWindow->show();  // 显示关于窗口

}


void MainWindow::closeEvent(QCloseEvent *event) {
    qDebug() << "delete main";
}

void MainWindow::handleShowMain() {
    this->show();  // 显示主窗口
}
