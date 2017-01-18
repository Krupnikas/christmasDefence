#pragma once

namespace m
{

qreal BulletDisappearStart = 1.2;
qreal BulletDisappearEnd = 1.4;

//Burn bullet
int BurnBulletSizeX;
int BurnBulletSizeY;

qreal BurnBulletStep; // in local points

int BurnBulletSmHit = 23;
int BurnBulletMidHit = 33;
int BurnBulletBigHit = 42;


//Fast bullet
int FastBulletSizeX;
int FastBulletSizeY;

qreal FastBulletStep; // in local points

int FastBulletSmHit = 3;
int FastBulletMidHit = 6;
int FastBulletBigHit = 9;


//Monster bullet
int MonsterBulletSizeX;
int MonsterBulletSizeY;

qreal MonsterBulletStep; // in local points

int MonsterBulletSmHit = 18;
int MonsterBulletMidHit = 27;
int MonsterBulletBigHit = 37;


//Slow bullet
int SlowBulletSizeX;
int SlowBulletSizeY;
qreal SlowBulletStep; // in local points

int SlowBulletSmHit = 21;
int SlowBulletMidHit = 31;
int SlowBulletBigHit = 40;

}
