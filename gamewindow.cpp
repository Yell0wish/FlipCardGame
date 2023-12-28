#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "util.h"
#include "gamelogic.h"
#include <QDebug>
#include <QMessageBox>

GameWindow::GameWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow),
    isFirstShow(true),
    timer(new QTimer(this)),
    timeLabel(new QLabel(this)),
    elapsedSeconds(0)
{
    ui->setupUi(this);
    this->setWindowTitle("LeaderBoard");
    this->setWindowFlags(Qt::Window);
    Utils::setupBackground(this, ":/pic_sources/imgs/background.png");
    initializeButtons();
    GameLogic& gameLogic = GameLogic::getInstance(this);
    cardShow(gameLogic.getCards());

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
    } else {
        // 窗口是从隐藏状态被再次显示出来
        qDebug() <<  "Window visible:" << this->isVisible();
        // 显示一个对话框确认用户是否真的想要退出
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "继续游戏", "您需要继续游戏?",
                                      QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::No) {
            // 如果用户不继续游戏 重启游戏
            GameLogic& gameLogic = GameLogic::getInstance(this);
            gameLogic.initCards(this);
            cardShow(gameLogic.getCards());
            elapsedSeconds = 0;
            timeLabel->setText("Time: " + QString::number(elapsedSeconds));
        }
        timer->start(1000);

    }
    QWidget::showEvent(event);  // 调用基类的 showEvent
}

void GameWindow::hideEvent(QHideEvent *event)
{
    GameLogic::getInstance(this).pauseGame();
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
        card -> show();
    }
}

void GameWindow::on_backToMainButton_clicked() {
    this->hide();// 关闭后自动释放内存
    emit requestShowMain();  // 发出信号
}

void GameWindow::updateTimer() {
    elapsedSeconds++;
    timeLabel->setText("Time: " + QString::number(elapsedSeconds));
}
