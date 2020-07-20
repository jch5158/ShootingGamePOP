#pragma once

#define MAX_ENEMY 20


struct Enemy {

    // ���� ����
    bool eFlag;

    // true ������ false ����
    bool eDirection;

    //ü��
    int attackSpeed;

    //���� �ӷ�
    int eSpeed;

    //X��ǥ
    int EX;

    //Y��ǥ
    int EY;

};

void CreateEnemy();

void EnemyDraw();

void EnemyAct();

void EnemyShotting();

void EnemyClean(int *scene);