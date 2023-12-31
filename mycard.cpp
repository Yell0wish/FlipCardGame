#include "mycard.h"
#include "gamelogic.h"

MyCard::MyCard(int pic_index, QWidget *parent) :
    QLabel(parent),
    frontImage(":/pic_sources/imgs/card" + QString::number(pic_index) + ".png"),
    backImage(":/pic_sources/imgs/card_empty.png"),
    index(pic_index),
    survival(true),
    isFront(false)
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
    GameLogic::getInstance().cardStore(this); // 已经有单例了此时，不会再进行实例化 因此getInstance中的参数不影响
    QLabel::mousePressEvent(event);  // 确保也调用基类的方法
}
