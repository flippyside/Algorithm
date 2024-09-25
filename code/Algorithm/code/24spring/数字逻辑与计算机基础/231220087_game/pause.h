#ifndef PAUSE_H
#define PAUSE_H
#include <QObject>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "qwidget.h"
#include <QPainter>
#include <QPixmap>
#include <QPushButton>
class FloatingWidget : public QWidget {
public:
    FloatingWidget(QWidget *parent = nullptr) : QWidget(parent) {
        setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint); // 设置窗口为无边框且置顶
        setAttribute(Qt::WA_TranslucentBackground); // 设置窗口背景透明
        setWindowOpacity(0.8); // 设置窗口不透明度
        setFixedSize(200, 100);

        QPushButton *button = new QPushButton("Click me", this);
        QHBoxLayout *layout = new QHBoxLayout(this);
        layout->addWidget(button);
        setLayout(layout);

        connect(button, &QPushButton::clicked, this, &QWidget::close);
    }
};

#endif // PAUSE_H
