#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "util.h"
#include "gamelogic.h"
#include <QDebug>
#include <QMessageBox>
#include <leaderboardlogic.h>
#include <QInputDialog>
#include <QLineEdit>
#include <QDir>

GameWindow::GameWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow),
    isFirstShow(true),
    timer(new QTimer(this)),
    timeLabel(new QLabel(this)),
    elapsedSeconds(0)
{
    ui->setupUi(this);
    this->setWindowTitle("Game");
    this->setWindowFlags(Qt::Window);
    Utils::setupBackground(this, ":/pic_sources/imgs/background.png");
    initializeButtons();
    GameLogic& gameLogic = GameLogic::getInstance(this);
    cardShow(gameLogic.getCards());
    connect(&gameLogic, &GameLogic::gameEnd, this, &finishedShow);
    timer->start(1000);
    connect(timer, &QTimer::timeout, this, &GameWindow::updateTimer);
    Utils::setTextLabel(timeLabel, "Time: " + QString::number(elapsedSeconds), QRect(50, -130, 900, 300));
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::showEvent(QShowEvent *event)
{
    if (isFirstShow) {
        // 这是窗口第一次显示
        isFirstShow = false;
    } else if (GameLogic::getInstance(this).hasFinished()) {
        resetGame();
    } else {
        // 窗口是从隐藏状态被再次显示出来
        qDebug() <<  "Window visible:" << this->isVisible();
        // 显示一个对话框确认用户是否真的想要退出
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "继续游戏", "您需要继续游戏?",
                                      QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::No) {
            // 如果用户不继续游戏 重启游戏
            resetGame();
        } else {
            timer->start();
        }


    }
    QWidget::showEvent(event);  // 调用基类的 showEvent
}

void GameWindow::hideEvent(QHideEvent *event)
{
    QWidget::hideEvent(event);
    timer->stop();
}

void GameWindow::initializeButtons()
{
    // 初始化各个按钮
    QSize buttonSize(375, 106);

    backToMainButton = Utils::createButton(this, ":/pic_sources/imgs/backtoMain.png", buttonSize);
    backToMainButton->move(70, 870);
    connect(backToMainButton, &QPushButton::clicked, this, &GameWindow::on_backToMainButton_clicked);

    quitGameButton = Utils::createButton(this, ":/pic_sources/imgs/quitGame.png", buttonSize);
    quitGameButton->move(600, 870);
    connect(quitGameButton, &QPushButton::clicked, this, [&](){Utils::on_quitGameButton_clicked(this);});
}

void GameWindow::cardShow(const QVector<MyCard *> &cards)
{
    for (auto card : cards) {
        if (card -> isSurvival()) {
            card -> show();
        }
    }
}

void GameWindow::resetGame()
{
    // 重置游戏逻辑、卡片、时间和UI等
    GameLogic& gameLogic = GameLogic::getInstance(this);
    gameLogic.setFinished(false);
    gameLogic.initCards(this);
    cardShow(gameLogic.getCards());
    elapsedSeconds = 0;
    timeLabel->setText("Time: " + QString::number(elapsedSeconds));
    timer->start(1000);
}

void GameWindow::on_backToMainButton_clicked() {
    this->hide();
    emit requestShowMain();  // 发出信号
}

void GameWindow::updateTimer() {
    elapsedSeconds++;
    timeLabel->setText("Time: " + QString::number(elapsedSeconds));
}

void GameWindow::finishedShow()
{
    timer->stop();
    int time = this->elapsedSeconds;
    GameLogic& logic = GameLogic::getInstance(this);
    showEndGameDialog(logic.calculateScore(time));
    on_backToMainButton_clicked();
}

void GameWindow::showEndGameDialog(int score) {
    LeaderBoardLogic& leaderBoardLogic = LeaderBoardLogic::getInstance();
    int rank = leaderBoardLogic.rankInLeaderBoard(score);
    if (rank >= 0 && rank <= 4) {
        // 分数足够高，提示用户输入名字
        bool ok;
        QString name = QInputDialog::getText(this, "高分达成",
                                             "恭喜你达到了高分！请输入你的名字:", QLineEdit::Normal,
                                             QDir::home().dirName(), &ok);
        if (ok && !name.isEmpty()) {
            // 用户输入了名字且点击了OK，这里可以记录分数和名字
            leaderBoardLogic.insertIntoLeaderBoard(name, score, rank);
        }
    } else {
        // 分数不够高，只显示分数
        QMessageBox::information(this, "游戏结束",
                                 "游戏结束了！你的分数是: " + QString::number(score));
    }
}
