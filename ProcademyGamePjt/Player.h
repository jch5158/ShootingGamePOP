#pragma once

struct Player {

    //�÷��̾� ����
    bool pFlag;

    //�÷��̾� hp
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