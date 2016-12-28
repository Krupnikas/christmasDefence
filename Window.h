#pragma once

#include <QObject>
#include <QMouseEvent>
#include <QEvent>

class IWindow : public QObject
{
    Q_OBJECT

public:
    IWindow();
    virtual void create() = 0;
    virtual void show() = 0;
    virtual void hide() = 0;
    virtual void resize() = 0;
    virtual void close() = 0;

    virtual void mousePressEvent(QMouseEvent *event) = 0;
    virtual void mouseMoveEvent(QMouseEvent *event) = 0;
};
