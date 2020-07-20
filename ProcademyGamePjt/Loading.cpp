#include <iostream>
#include <Windows.h>
#include <time.h>
#include "Console.h"
#include "Loading.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

extern char szScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];

void LoadingScene(int *scene) {

    // �ð� ���� ����
    static clock_t loadingCheck = clock();

    // �������� ���� ����
    static char stage = 1;

    // 100% �� ���� �÷��� ����
    static int percent;
 
    static int setCnt;


    // PlayerSet(), CreateBullet(), CreateEnemy() �Լ��� �ѹ��� ����� �� �ֵ��� �ϴ� ����
    if (setCnt == 0) { 

        //�÷��̾� ��ġ ����
        PlayerSet();

        // �Ѿ� ���� �� �ʱ�ȭ
        CreateBullet();

        // ���� ����
        CreateEnemy();
        setCnt += 1;
    }

    Buffer_Clear();


    // 0.02�ʸ��� üũ
    if (clock() - loadingCheck >= 20) {
        loadingCheck = clock();
        percent += 1;
    }


    // �ε� ȭ�� ������
    sprintf_s(szScreenBuffer[10], "                                 stage %d  Loading... %d %s", stage, percent, "%%");

    if (percent == 100) {
        *scene += 1;
        stage += 1;
        percent = 0;
        setCnt = 0;
    }

    Buffer_Flip();
}