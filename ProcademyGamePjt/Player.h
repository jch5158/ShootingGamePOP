#pragma once

struct Player {

    //플레이어 유뮤
    bool pFlag;

    //플레이어 hp
    char pHp;
    int PX;
    int PY;
};

void PlayerSet();

void PlayerDraw();

void PlayerControl();

void PlayerAct();

void HpZero(int * scene);

bool EnQueue(int message);

bool DeQueue(int *message);

bool IsFull();

bool IsEmpty();