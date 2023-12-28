#include "mycard.h"

MyCard::MyCard(int pic_index, QWidget *parent) :
    QLabel(parent),
    frontImage(":/pic_sources/imgs/card" + QString::number(pic_index) + ".png"),
    backImage(":/pic_sources/imgs/card_empty.png"),
    index(pic_index)
{
    this -> setPixmap(backImage);
    this -> resize(195, 260);
}


void MyCard::switchImage() {
    if (isFront) {
        this->setPixmap(backImage);
        isFront = false;
    } else {
        this->setPixmap(frontImage);
        isFront = true;
    }
}

void MyCard::mousePressEvent(QMouseEvent *event)
{
    switchImage();
    QLabel::mousePressEvent(event);  // 确保也调用基类的方法
}
