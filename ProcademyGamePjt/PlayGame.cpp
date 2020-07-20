#include <iostream>
#include <Windows.h>
#include <time.h>
#include "Console.h"
#include "Loading.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"


void GameScene(int *scene) {

    // 사용자 컨트롤 함수
    PlayerControl();

    // 사용자 컨트롤 입력 처리
    PlayerAct();

    //총알 움직임
    MoveBullet();

    // 몬스터가 움직임
    EnemyAct();

    //적이 총을 쏨
    EnemyShotting();

    // 총알 맞았는지 체크
    hitBullet();

    // 스크린 버퍼를 지움     
    Buffer_Clear();

    //적군 버퍼에 담는 함수
    EnemyDraw();

    //플레이어 버퍼에 담는 함수
    PlayerDraw();

    //총알 버퍼에 담는 함수
    BulletDraw();

    // 플레이어 hp 체크
    HpZero(scene); // 체크

    // 적군 소멸하였는지 체크
    EnemyClean(scene); //체크

    // 스크린 버퍼를 화면으로 출력         
    Buffer_Flip();

}