#include "aboutwindow.h"
#include "ui_aboutwindow.h"
#include <QDebug>
#include <mainwindow.h>
#include <QMessageBox>
#include "util.h"

AboutWindow::AboutWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutWindow),
    aboutTextLabel(new QLabel(this))
{
    qDebug() << "yes";
    ui->setupUi(this);
    this->setWindowTitle("About");
    this->setWindowFlags(Qt::Window);
    Utils::setupBackground(this, ":/pic_sources/imgs/background.png");
    initializeButtons();
    // 设置QLabel属性
    aboutTextLabel->setStyleSheet("QLabel { color : #800000	; font-family: Arial; font-size: 14pt;}");
    aboutTextLabel->setWordWrap(true);
    aboutTextLabel->setText("本游戏由叶理炜开发 Github项目地址：");
    aboutTextLabel->setGeometry(QRect(50, 50, 400, 100));  // 设置位置和大小
    aboutTextLabel->show();  // 显示QLabel
}


void AboutWindow::initializeButtons() {
    // 初始化各个按钮
    QSize buttonSize(375, 106);

    backToMainButton = Utils::createButton(this, ":/pic_sources/imgs/backtoMain.png", buttonSize);
    backToMainButton->move(320, 450);
    connect(backToMainButton, &QPushButton::clicked, this, &AboutWindow::on_backToMainButton_clicked);

    quitGameButton = Utils::createButton(this, ":/pic_sources/imgs/quitGame.png", buttonSize);
    quitGameButton->move(320, 650);
    connect(quitGameButton, &QPushButton::clicked, this, &AboutWindow::on_quitGameButton_clicked);

}


AboutWindow::~AboutWindow()
{
    delete ui;
}

void AboutWindow::on_backToMainButton_clicked() {
    this->close();// 关闭后自动释放内存
    emit requestShowMain();  // 发出信号
}

void AboutWindow::on_quitGameButton_clicked() {
    // 显示一个对话框确认用户是否真的想要退出
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "退出游戏", "您确定要退出游戏吗?",
                                  QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // 如果用户确认，关闭应用程序
        this->close();
        QApplication::quit();
    }

}

void AboutWindow::closeEvent(QCloseEvent *event) {
    qDebug() << "deleteaaa";
}
