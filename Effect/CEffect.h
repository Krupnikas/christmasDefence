#pragma once

#include <Resource.h>

class CEffect
{
public:
    CEffect();
    virtual void beforeEffect() = 0;
    virtual void onEffect() = 0;
    virtual void afterEffect() = 0;
};

