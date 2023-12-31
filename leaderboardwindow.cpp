#include "leaderboardwindow.h"
#include "ui_leaderboardwindow.h"
#include "util.h"
#include <QDebug>
#include <QVector>
#include <QPair>
#include <QFile>
#include <QDir>
#include <QCoreApplication>
#include <QStandardPaths>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDebug>
#include "leaderboardlogic.h"

LeaderBoardWindow::LeaderBoardWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LeaderBoardWindow),
    leaderBoardLabel(new QLabel(this)),
    backToMainButton(nullptr),
    quitGameButton(nullptr)
{
    ui->setupUi(this);
    this->setWindowTitle("LeaderBoard");
    this->setWindowFlags(Qt::Window);
    Utils::setupBackground(this, ":/pic_sources/imgs/background.png");
    initializeButtons();
    // 设置QLabel属性
    QString text = "排行榜\n";
    qDebug() << "hahahahahah";
    text += LeaderBoardLogic::getInstance().getLeaderBoardString();

    Utils::setTextLabel(leaderBoardLabel, text, QRect(50, 100, 900, 300));
}

LeaderBoardWindow::~LeaderBoardWindow()
{
    delete ui;
}

void LeaderBoardWindow::initializeButtons() {
    // 初始化各个按钮
    QSize buttonSize(375, 106);

    backToMainButton = Utils::createButton(this, ":/pic_sources/imgs/backtoMain.png", buttonSize);
    backToMainButton->move(320, 450);
    connect(backToMainButton, &QPushButton::clicked, this, &LeaderBoardWindow::on_backToMainButton_clicked);

    quitGameButton = Utils::createButton(this, ":/pic_sources/imgs/quitGame.png", buttonSize);
    quitGameButton->move(320, 650);
    connect(quitGameButton, &QPushButton::clicked, this, [&](){Utils::on_quitGameButton_clicked(this);});

}

void LeaderBoardWindow::on_backToMainButton_clicked() {
    this->hide();
    emit requestShowMain();  // 发出信号
}
