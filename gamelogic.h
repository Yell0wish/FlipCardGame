#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QVector>
#include "mycard.h"
#include <QPoint>
#include <QObject>
#include <QTimer>

class GameLogic  // 单例模式
{
public:
    static GameLogic& getInstance(QWidget *widget);
    void initCards(QWidget *widget);
    ~GameLogic();
    const QVector<MyCard*>& getCards() const {return cards;}
    bool isRunning(){return running;}
    void pauseGame() {running = false;}


private:
    GameLogic(QWidget *widget);
    GameLogic(const GameLogic&) = delete;
    GameLogic(GameLogic&&) = delete;
    GameLogic& operator=(const GameLogic&) = delete;
    GameLogic& operator=(GameLogic&&) = delete;

    QVector<MyCard*> cards;

    bool running = false;

    void setPosition();

    QPoint cardStartPosition{70, 40}; // 卡牌的最左上角坐标
    int cardVerticalSpacing = 20; // 卡牌之间上下间隔
    int cardHorizontalSpacing = 40; // 卡牌之间的左右间隔

};

#endif // GAMELOGIC_H
