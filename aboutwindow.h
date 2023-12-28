#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

namespace Ui {
class AboutWindow;
}

class AboutWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AboutWindow(QWidget *parent = nullptr);
    ~AboutWindow();
signals:
    void requestShowMain(); // 唤醒主界面

private slots:
    void on_backToMainButton_clicked();
private:
    Ui::AboutWindow *ui;
    QLabel* aboutTextLabel = nullptr;
    QPushButton* backToMainButton = nullptr;
    QPushButton* quitGameButton = nullptr;
    void initializeButtons();
    void closeEvent(QCloseEvent *event);
};

#endif // ABOUTWINDOW_H
