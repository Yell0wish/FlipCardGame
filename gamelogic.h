#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QVector>
#include "mycard.h"
#include <QPoint>
#include <QObject>
#include <QTimer>
#include <QVector>

class GameLogic : public QObject // 单例模式
{
    Q_OBJECT
public:
    ~GameLogic();

    static GameLogic& getInstance(QWidget *widget = nullptr);
    void initCards(QWidget *widget);
    const QVector<MyCard*>& getCards() const {return cards;}
    void cardStore(MyCard*);
    void cardsMatch();
    bool hasFinished() const{return finished;}
    void setFinished(bool flag) {finished = flag;}
    int calculateScore(int time) const;

signals:
    void gameEnd();

private slots:
    void onCardsCheck();  // 用于检查卡片是否匹配的槽

private:
    GameLogic(QWidget *widget);
    GameLogic(const GameLogic&) = delete;
    GameLogic(GameLogic&&) = delete;
    GameLogic& operator=(const GameLogic&) = delete;
    GameLogic& operator=(GameLogic&&) = delete;

    QVector<MyCard*> cards;
    QPoint cardStartPosition{70, 40}; // 卡牌的最左上角坐标
    int cardVerticalSpacing = 20; // 卡牌之间上下间隔
    int cardHorizontalSpacing = 40; // 卡牌之间的左右间隔
    QVector<MyCard*> cardsPair;
    bool finished = false;
    QTimer* checkTimer;  // 用于延迟检查的定时器

    void setPosition();
    void setNoClick();
    void recoverClick();
};

#endif // GAMELOGIC_H
