#ifndef UTIL_H
#define UTIL_H

#include <QPixmap>
#include <QPalette>
#include <QPushButton>

class Utils {
public:
    static void setupBackground(QWidget *widget, const QString &imagePath);
    static QPushButton *createButton(QWidget *parent, const QString &imagePath, const QSize &size);
};

#endif // UTIL_H
