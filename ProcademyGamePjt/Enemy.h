#pragma once

#define MAX_ENEMY 20


struct Enemy {

    // 생성 유무
    bool eFlag;

    // true 오른쪽 false 왼쪽
    bool eDirection;

    //체력
    int attackSpeed;

    //몬스터 속력
    int eSpeed;

    //X좌표
    int EX;

    //Y좌표
    int EY;

};

void CreateEnemy();

void EnemyDraw();

void EnemyAct();

void EnemyShotting();

void EnemyClean(int *scene);