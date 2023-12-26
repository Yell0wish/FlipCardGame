#include "util.h"
#include <vector>

void Utils::setupBackground(QWidget *widget, const QString &imagePath) {
    QPixmap backgroundImage(imagePath);
    widget->setFixedSize(backgroundImage.size());
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(backgroundImage));
    widget->setPalette(palette);
}

QPushButton *Utils::createButton(QWidget *parent, const QString &imagePath, const QSize &size) {
    QPixmap pixmap(imagePath);
    QPushButton *button = new QPushButton(parent);
    button->setIcon(QIcon(pixmap));
    button->setIconSize(size);
    button->setFixedSize(size);
    return button;
}

//void MainWindow::initializeButtons(QWidget* widget, QSize size, std::vector buttons) {
//    // 初始化各个按钮
//    QSize buttonSize(375, 106);

//    startGameButton = Utils::createButton(this, ":/pic_sources/imgs/startGameImage.png", buttonSize);
//    startGameButton->move(320, 200);
//    connect(startGameButton, &QPushButton::clicked, this, &MainWindow::on_startGameButton_clicked);

//    leaderboardButton = Utils::createButton(this, ":/pic_sources/imgs/leaderBoardImage.png", buttonSize);
//    leaderboardButton->move(320, 350);
//    connect(leaderboardButton, &QPushButton::clicked, this, &MainWindow::on_leaderboardButton_clicked);

//    aboutButton = Utils::createButton(this, ":/pic_sources/imgs/aboutImage.png", buttonSize);
//    aboutButton->move(320, 500);
//    connect(aboutButton, &QPushButton::clicked, this, &MainWindow::on_aboutButton_clicked);
//}
