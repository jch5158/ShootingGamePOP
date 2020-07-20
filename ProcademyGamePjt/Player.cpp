#include <iostream>
#include <Windows.h>
#include <time.h>
#include "Console.h"
#include "Player.h"
#include "Bullet.h"
#define QUEUE_MAX 30

enum playerKey { PLAYERUP = 1, PLAYERDOWN, PLAYERRIGHT, PLAYERLEFT,SHOTBULLET };

static int messageQueue[QUEUE_MAX];

static int front = 0;
static int rear = 0;

extern enum switchScene { Title = 1, loading, GameStage, GameEnd };
extern char szScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];
extern Bullet bullet[MAX_BULLET];

Player user = { 40,15,5,true };

void PlayerDraw() {
    szScreenBuffer[user.PY][user.PX] = 'A';
}

void PlayerControl() {
    static clock_t shotSpeed = 0;

    if (GetAsyncKeyState(VK_UP) && user.PY > 0)
        EnQueue(PLAYERUP);

    if (GetAsyncKeyState(VK_DOWN) && user.PY < dfSCREEN_HEIGHT - 1)
        EnQueue(PLAYERDOWN);

    if (GetAsyncKeyState(VK_LEFT) && user.PX > 2)
        EnQueue(PLAYERLEFT);

    // 마지막 문자는 NULL이기 때문에 dfSCREEN_WIDTH - 2 이전까지 접근
    if (GetAsyncKeyState(VK_RIGHT) && user.PX < dfSCREEN_WIDTH - 2) 
        EnQueue(PLAYERRIGHT);

    if (GetAsyncKeyState(VK_SPACE)) {      
        if(shotSpeed == 0)
        shotSpeed = clock();


        // 0.05초 주기로 총알 발사가 가능합니다.
        if (clock() - shotSpeed >= 50) {
            EnQueue(SHOTBULLET);
            shotSpeed = 0;
        }
    }
}

void PlayerAct() {
    int num;

    while (1) {

        if (IsEmpty())
            break;
        
        DeQueue(&num);

        if (num == PLAYERUP) {
            user.PY--;
        }
        else if (num == PLAYERDOWN ) {
            user.PY++;
        }
        else if (num == PLAYERRIGHT) {
            user.PX++;
        }
        else if (num == PLAYERLEFT && user.PX > 0) {
            user.PX--;
        }
        else if (num == SHOTBULLET) {
            PlayerShot();
        }
    }
}


// 플레이어 체력이 0인지 확인하는 함수입니다.
void HpZero(int* scene) {

    if (user.pHp == 0) {
        *scene = GameEnd;
    }
}

//플레이어 default 위치입니다.
void PlayerSet() {
    user.PX = 40;
    user.PY = 15;
}


bool IsFull() {
    // dummy 값 위치에 있을 때 원형 큐는 Full 이다
    if ((rear + 1) % QUEUE_MAX == front){ 
        return true;
    }
    else {
        return false;
    }
}

bool IsEmpty() {
    if (front == rear) {
        return true;
    }
    else
        return false;
}

bool EnQueue(int message) {

    // 큐가 꽉찼으면 isFull 함수는 true를 return
    if (IsFull() == true) { 
        return false;
    }
    else {
        // 인덱스의 길이로 나누어 최대 길이를 벗어나지 않는다.
        rear = ++rear % QUEUE_MAX; 
        messageQueue[rear] = message;
        return true;
    } 
}

bool DeQueue(int *message) {

    // 스택이 비었으면 true를 return
    if (IsEmpty() == true) 
        return false;
    else {

        // 인덱스의 길이로 나누어 최대 길이를 벗어나지 않는다.d
        front = ++front % QUEUE_MAX; 
        *message = messageQueue[front];
        return true;
    }
}