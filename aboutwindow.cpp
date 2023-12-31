#include "aboutwindow.h"
#include "ui_aboutwindow.h"
#include <QDebug>
#include <mainwindow.h>
#include <QMessageBox>
#include "util.h"
#include <QStandardPaths>

AboutWindow::AboutWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutWindow),
    aboutTextLabel(new QLabel(this)),
    backToMainButton(nullptr),
    quitGameButton(nullptr)
{
    qDebug() << "yes";
    ui->setupUi(this);
    this->setWindowTitle("About");
    this->setWindowFlags(Qt::Window);
    Utils::setupBackground(this, ":/pic_sources/imgs/background.png");
    initializeButtons();
    // 设置QLabel属性
    QString dataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString text = "排行榜数据存储路径：\n" + dataPath  +  "\n\n 本游戏由叶理炜开发 \n Github项目地址：https://github.com/Yell0wish/FlipCardGame \n\n 喜欢的话可以点个星喵~";
    Utils::setTextLabel(aboutTextLabel, text, QRect(50, 100, 900, 300));
}


void AboutWindow::initializeButtons() {
    // 初始化各个按钮
    QSize buttonSize(375, 106);

    backToMainButton = Utils::createButton(this, ":/pic_sources/imgs/backtoMain.png", buttonSize);
    backToMainButton->move(320, 450);
    connect(backToMainButton, &QPushButton::clicked, this, &AboutWindow::on_backToMainButton_clicked);

    quitGameButton = Utils::createButton(this, ":/pic_sources/imgs/quitGame.png", buttonSize);
    quitGameButton->move(320, 650);
    connect(quitGameButton, &QPushButton::clicked, this, [&](){Utils::on_quitGameButton_clicked(this);});

}


AboutWindow::~AboutWindow()
{
    delete ui;
}

void AboutWindow::on_backToMainButton_clicked() {
    this->hide();
    emit requestShowMain();  // 发出信号
}


