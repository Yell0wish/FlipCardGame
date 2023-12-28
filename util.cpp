#include "util.h"
#include <vector>
#include <QMessageBox>
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>



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

void Utils::setTextLabel(QLabel* label, const QString& text, const QRect& geometry) {
    label->setStyleSheet("QLabel { color : #800000	; font-family: Arial; font-size: 15pt;}");
    label->setAlignment(Qt::AlignCenter);
    label->setText(text);
    label->setGeometry(geometry);  // 设置位置和大小
    label->show();  // 显示QLabel
}

void Utils::on_quitGameButton_clicked(QWidget* widget) {
    // 显示一个对话框确认用户是否真的想要退出
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(widget, "退出游戏", "您确定要退出游戏吗?",
                                  QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // 如果用户确认，关闭应用程序
        widget->close();
        QApplication::quit();
    }

}



