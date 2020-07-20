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

    // ������ ���ڴ� NULL�̱� ������ dfSCREEN_WIDTH - 2 �������� ����
    if (GetAsyncKeyState(VK_RIGHT) && user.PX < dfSCREEN_WIDTH - 2) 
        EnQueue(PLAYERRIGHT);

    if (GetAsyncKeyState(VK_SPACE)) {      
        if(shotSpeed == 0)
        shotSpeed = clock();


        // 0.05�� �ֱ�� �Ѿ� �߻簡 �����մϴ�.
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


// �÷��̾� ü���� 0���� Ȯ���ϴ� �Լ��Դϴ�.
void HpZero(int* scene) {

    if (user.pHp == 0) {
        *scene = GameEnd;
    }
}

//�÷��̾� default ��ġ�Դϴ�.
void PlayerSet() {
    user.PX = 40;
    user.PY = 15;
}


bool IsFull() {
    // dummy �� ��ġ�� ���� �� ���� ť�� Full �̴�
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

    // ť�� ��á���� isFull �Լ��� true�� return
    if (IsFull() == true) { 
        return false;
    }
    else {
        // �ε����� ���̷� ������ �ִ� ���̸� ����� �ʴ´�.
        rear = ++rear % QUEUE_MAX; 
        messageQueue[rear] = message;
        return true;
    } 
}

bool DeQueue(int *message) {

    // ������ ������� true�� return
    if (IsEmpty() == true) 
        return false;
    else {

        // �ε����� ���̷� ������ �ִ� ���̸� ����� �ʴ´�.d
        front = ++front % QUEUE_MAX; 
        *message = messageQueue[front];
        return true;
    }
}