#pragma once

#include <QObject>

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
};
