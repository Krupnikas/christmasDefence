#pragma once

const int TypesOfCannon = 4;


//Burn cannon
// rotation speed, in angles
const qreal BurnCannonSmRotation = 2.3;
const qreal BurnCannonMidRotation = 2.6;
const qreal BurnCannonBigRotation = 2.9;

//fire speed in game tacts
const qreal BurnCannonSmFireSpeed = 53;
const qreal BurnCannonMidFireSpeed = 43;
const qreal BurnCannonBigFireSpeed = 35;

//fire radius, in local points
const qreal BurnCannonSmRadius = CellSize * 2.6;
const qreal BurnCannonMidRadius = CellSize * 3;
const qreal BurnCannonBigRadius = CellSize * 3.4;

const int BurnCannonSmCost = 12;
const int BurnCannonMidCost = 18;
const int BurnCannonBigCost = 25;


//Fast cannon
// rotation speed, in angles
const qreal FastCannonSmRotation = 2;
const qreal FastCannonMidRotation = 2;
const qreal FastCannonBigRotation = 2;

//fire speed in game tacts
const qreal FastCannonSmFireSpeed = 60;
const qreal FastCannonMidFireSpeed = 50;
const qreal FastCannonBigFireSpeed = 40;

//fire radius, in local points
const qreal FastCannonSmRadius = CellSize * 2;
const qreal FastCannonMidRadius = CellSize * 2.3;
const qreal FastCannonBigRadius = CellSize * 2.6;

const int FastCannonSmCost = 7;
const int FastCannonMidCost = 12;
const int FastCannonBigCost = 20;


//Monster cannon
// rotation speed, in angles
const qreal MonsterCannonSmRotation = 2.1;
const qreal MonsterCannonMidRotation = 2.4;
const qreal MonsterCannonBigRotation = 2.7;

//fire speed in game tacts
const qreal MonsterCannonSmFireSpeed = 60;
const qreal MonsterCannonMidFireSpeed = 50;
const qreal MonsterCannonBigFireSpeed = 40;

//fire radius, in local points
const qreal MonsterCannonSmRadius = CellSize * 2.2;
const qreal MonsterCannonMidRadius = CellSize * 2.5;
const qreal MonsterCannonBigRadius = CellSize * 2.7;

const int MonsterCannonSmCost = 9;
const int MonsterCannonMidCost = 14;
const int MonsterCannonBigCost = 22;



//Slow cannon
// rotation speed, in angles
const qreal SlowCannonSmRotation = 2.2;
const qreal SlowCannonMidRotation = 2.5;
const qreal SlowCannonBigRotation = 2.8;

//fire speed in game tacts
const qreal SlowCannonSmFireSpeed = 57;
const qreal SlowCannonMidFireSpeed = 47;
const qreal SlowCannonBigFireSpeed = 37;

//fire radius, in local points
const qreal SlowCannonSmRadius = CellSize * 2.4;
const qreal SlowCannonMidRadius = CellSize * 2.7;
const qreal SlowCannonBigRadius = CellSize * 3;

const int SlowCannonSmCost = 11;
const int SlowCannonMidCost = 17;
const int SlowCannonBigCost = 23;
