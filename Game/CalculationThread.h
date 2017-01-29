#pragma once

#include <Resource.h>

class CGame;

class CCalculationThread : public QThread
{
public:
    CCalculationThread(CGame* game);
    
    void run() override;
    
private:
    CGame* game;
};
