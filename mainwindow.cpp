#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutwindow.h"
#include <QPixmap>
#include <QPalette>
#include <QDebug>
#include"util.h"

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
}


MainWindow::~MainWindow()
{
    qDebug() << "com";
    delete ui;
    // 根据父子关系会删除QPushButton* 无需手动删除
}

void MainWindow::on_startGameButton_clicked() {
    qDebug() << "Start Game button clicked";
}

void MainWindow::on_leaderboardButton_clicked() {
    qDebug() << "Leaderboard button clicked";
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
