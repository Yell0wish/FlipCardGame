#ifndef LEADERBOARDWINDOW_H
#define LEADERBOARDWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

namespace Ui {
class LeaderBoardWindow;
}

class LeaderBoardWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LeaderBoardWindow(QWidget *parent = 0);
    ~LeaderBoardWindow();

private:
    Ui::LeaderBoardWindow *ui;
    QLabel* leaderBoardLabel = nullptr;
    QPushButton* backToMainButton = nullptr;
    QPushButton* quitGameButton = nullptr;
    void initializeButtons();

signals:
    void requestShowMain(); // 唤醒主界面

private slots:
    void on_backToMainButton_clicked();

};

#endif // LEADERBOARDWINDOW_H
