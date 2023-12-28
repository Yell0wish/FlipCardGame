#ifndef UTIL_H
#define UTIL_H

#include <QPixmap>
#include <QPalette>
#include <QPushButton>
#include <QLabel>
#include <QVector>
#include <QPair>

class Utils {
public:
    static void setupBackground(QWidget *widget, const QString &imagePath);
    static QPushButton *createButton(QWidget *parent, const QString &imagePath, const QSize &size);
    static void setTextLabel(QLabel* label, const QString& text, const QRect& geometry);
    static void on_quitGameButton_clicked(QWidget* widget);
};

#endif // UTIL_H
