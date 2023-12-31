#include "gamelogic.h"
#include <algorithm>
#include <random>
#include <QDebug>
#include <QMessageBox>


GameLogic::GameLogic(QWidget* widget) :
    finished(false)
{
    checkTimer = new QTimer(this);
    checkTimer->setSingleShot(true);  // 设置定时器只触发一次
    connect(checkTimer, &QTimer::timeout, this, &GameLogic::onCardsCheck);
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

    for (auto card : cardsPair) { // vector存指针 指针所指的内存不会自己释放 需要手动释放
        delete card;
    }

    cardsPair.clear(); // 用来存配对的两个
    cardsPair.reserve(2);

    for (int i = 0; i < 6; i++) { // 每种类型的有两个
        cards.push_back(new MyCard(i, widget));
        cards.push_back(new MyCard(i, widget));
    }

    std::random_shuffle(cards.begin(), cards.end()); // 将其打乱

    setPosition();
}

GameLogic::~GameLogic(){}

void GameLogic::cardStore(MyCard* card)
{
    setNoClick();
    if (cardsPair.size() >= 2) {
        return;
    }
    cardsPair.push_back(card);
    if (cardsPair.size() == 2) {
        cardsMatch();
    } else {
        recoverClick();
    }
}

void GameLogic::cardsMatch()
{
    checkTimer->start(800);  // 延迟时间，例如1000毫秒

}



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

void GameLogic::onCardsCheck() {
    int index = cardsPair[0]->getIndex();
    if (index == cardsPair[1]->getIndex()) {
        delete cardsPair[0];
        delete cardsPair[1];
        for (QVector<MyCard*>::iterator iterator = cards.begin(); iterator != cards.end();) {
            // 将vector中的指针删除 内存前面已经释放 这里就不用释放了
            if ((*iterator)->getIndex() == index) {
                iterator = cards.erase(iterator);
            } else {
                iterator++;
            }
        }

        if (cards.size() == 0) {
            finished = true;
            emit gameEnd();
        }

    } else {
        cardsPair[0]->switchImage();
        cardsPair[1]->switchImage();
    }
    cardsPair.clear();
    recoverClick();
}

void GameLogic::setNoClick() {
    for (MyCard* card : cards) {
        card->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    }
}

void GameLogic::recoverClick() {
    for (MyCard* card : cards) {
        card->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    }
}


int GameLogic::calculateScore(int time) const {
    int maxScore = 115514;  // 最大分数
    int timePenalty = 10; // // 每过一秒减少的分数
    int score = maxScore - timePenalty * time;
    return std::max(score, 0);  // 确保分数不会低于0
}
