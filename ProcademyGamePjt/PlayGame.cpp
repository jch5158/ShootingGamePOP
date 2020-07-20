#include <iostream>
#include <Windows.h>
#include <time.h>
#include "Console.h"
#include "Loading.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"


void GameScene(int *scene) {

    // ����� ��Ʈ�� �Լ�
    PlayerControl();

    // ����� ��Ʈ�� �Է� ó��
    PlayerAct();

    //�Ѿ� ������
    MoveBullet();

    // ���Ͱ� ������
    EnemyAct();

    //���� ���� ��
    EnemyShotting();

    // �Ѿ� �¾Ҵ��� üũ
    hitBullet();

    // ��ũ�� ���۸� ����     
    Buffer_Clear();

    //���� ���ۿ� ��� �Լ�
    EnemyDraw();

    //�÷��̾� ���ۿ� ��� �Լ�
    PlayerDraw();

    //�Ѿ� ���ۿ� ��� �Լ�
    BulletDraw();

    // �÷��̾� hp üũ
    HpZero(scene); // üũ

    // ���� �Ҹ��Ͽ����� üũ
    EnemyClean(scene); //üũ

    // ��ũ�� ���۸� ȭ������ ���         
    Buffer_Flip();

}