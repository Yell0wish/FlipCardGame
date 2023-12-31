#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QPushButton>
#include "mycard.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();

protected:
    void showEvent(QShowEvent* event) override;
    void hideEvent(QHideEvent *event) override;
private:
    Ui::GameWindow *ui;

    QPushButton* backToMainButton = nullptr;
    QPushButton* quitGameButton = nullptr;
    QTimer* timer;
    int elapsedSeconds;
    QLabel* timeLabel = nullptr;
    bool isFirstShow = false;

    void initializeButtons();
    void cardShow(const QVector<MyCard*>& cards);
    void resetGame();
    void showEndGameDialog(int score);
signals:
    void requestShowMain(); // 唤醒主界面

public slots:
    void updateTimer();
    void finishedShow();

private slots:
    void on_backToMainButton_clicked();
};

#endif // GAMEWINDOW_H
