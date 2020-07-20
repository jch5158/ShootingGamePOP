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

    // 시간 저장 변수
    static clock_t loadingCheck = clock();

    // 스테이지 저장 변수
    static char stage = 1;

    // 100% 시 게임 플레이 시작
    static int percent;
 
    static int setCnt;


    // PlayerSet(), CreateBullet(), CreateEnemy() 함수가 한번만 실행될 수 있도록 하는 로직
    if (setCnt == 0) { 

        //플레이어 위치 조정
        PlayerSet();

        // 총알 생성 및 초기화
        CreateBullet();

        // 적군 생성
        CreateEnemy();
        setCnt += 1;
    }

    Buffer_Clear();


    // 0.02초마다 체크
    if (clock() - loadingCheck >= 20) {
        loadingCheck = clock();
        percent += 1;
    }


    // 로딩 화면 랜더링
    sprintf_s(szScreenBuffer[10], "                                 stage %d  Loading... %d %s", stage, percent, "%%");

    if (percent == 100) {
        *scene += 1;
        stage += 1;
        percent = 0;
        setCnt = 0;
    }

    Buffer_Flip();
}