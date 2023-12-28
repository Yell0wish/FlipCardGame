#include "gamelogic.h"
#include <algorithm>
#include <random>
#include <QDebug>

GameLogic::GameLogic(QWidget* widget) :
    running(true)
{
    initCards(widget);
}

GameLogic& GameLogic::getInstance(QWidget* widget)
{
   static GameLogic instance(widget);
   return instance;
}

void GameLogic::initCards(QWidget* widget)
{
    for (auto card : cards) { // vector存指针 指针所指的内存不会自己释放 需要手动释放
        delete card;
    }

    cards.clear();
    cards.reserve(12);
    for (int i = 0; i < 6; i++) { // 每种类型的有两个
        cards.push_back(new MyCard(i, widget));
        cards.push_back(new MyCard(i, widget));
    }

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(cards.begin(), cards.end(), g); // 将其打乱

    setPosition();
}

GameLogic::~GameLogic(){}

void GameLogic::setPosition()
{

    int column = 4, row = 3;// 一共3行4列
    int width = cards[0]->width();
    int height = cards[0]->height();

    // 确保cards的大小至少为row * column
    if (cards.size() < row * column) {
        // todo 抛出异常
    }

    //给已经打乱好的卡牌分配位置
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            cards[i * column + j]->move(cardStartPosition.x()  + j * (cardHorizontalSpacing + width), cardStartPosition.y() + i * (cardVerticalSpacing + height));
        }
    }
}

