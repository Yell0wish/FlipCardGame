#ifndef MYCARD_H
#define MYCARD_H

#include <QLabel>
#include <QPixmap>
#include <QPropertyAnimation>

class MyCard : public QLabel
{
    Q_OBJECT

public:
    MyCard(int pic_index, QWidget* parent = nullptr);
    void switchImage();  // 用于在正面和背面图像之间切换
    bool isSurvival() const{return survival;}
    int getIndex() const{return index;}

protected:
    void mousePressEvent(QMouseEvent *event) override;  // 重写mousePressEvent


private:
    QPixmap backImage;
    QPixmap frontImage;
    bool isFront = false;  // 当前是否显示正面
    int index;
    bool survival = true;

};

#endif // MYCARD_H
