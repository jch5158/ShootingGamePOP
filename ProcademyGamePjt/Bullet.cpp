#include <iostream>
#include <Windows.h>
#include <time.h>
#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include "Console.h"

Bullet bullet[MAX_BULLET];

extern char szScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];
extern Player user;
extern Enemy enemy[MAX_ENEMY];


// 총알 배열을 초기화하는 함수입니다.
void CreateBullet() {
	for (int index = 0; index < MAX_BULLET; index++) {	
		bullet[index].bulletX = 0;
		bullet[index].bulletY = 0;
		bullet[index].bulletFlag = false;
		bullet[index].bulletType = 0;
	}
}


// 아군이 총을 쏘는 함수입니다.
void PlayerShot() {
	for (int index = 0; index < MAX_BULLET; index++) {

		if (bullet[index].bulletFlag == true)
			continue;

		if (bullet[index].bulletFlag == false) {
			bullet[index].bulletX = user.PX;
			bullet[index].bulletY = user.PY-1;
			bullet[index].bulletFlag = true;
			bullet[index].bulletType = 0;
			return;
		}
	}
}

// 플레이어가 쏜 총알의 함수입니다.
// 총알의 위치가 화면밖을 나갈경우 bulletFlag값을 false로 바꾼다.
// bulletType == 0은 플레이어 총알, bulletType == 1은 적군 총알
// 총알의 속도는 0.05초마다 움직입니다.
void MoveBullet() {
	
	static clock_t bulletSpeedCheck = clock();

	if (clock() - bulletSpeedCheck >= 50) {
		for (int index = 0; index < MAX_BULLET; index++) { 
			
			if (bullet[index].bulletFlag == false)
			continue;
				
			if (bullet[index].bulletY == 0 || bullet[index].bulletY == dfSCREEN_HEIGHT - 1) {
				bullet[index].bulletFlag = false;
				continue;
			}

			//총알 위치 이동
			if (bullet[index].bulletType == 0)
				bullet[index].bulletY -= 1;
			else
				bullet[index].bulletY += 1;

		}
		bulletSpeedCheck = clock();
	}
}


//총알 랜더링
void BulletDraw() {

	for (int index = 0; index < MAX_BULLET; index++) {

		if (bullet[index].bulletFlag == false)
			continue;

		if(bullet[index].bulletType == 0)
			szScreenBuffer[bullet[index].bulletY][bullet[index].bulletX] = '^';
		else
			szScreenBuffer[bullet[index].bulletY][bullet[index].bulletX] = 'v';
	}
}



// 플레이어와 적군 그리고 총알의 위치에 따라서 총알을 맞았는지 체크합니다.
void hitBullet() {

	static clock_t hitCheck;


	//플레이어는 피격 후 최소 0.5초동안 무적입니다.
	if (clock() - hitCheck >= 500)
		hitCheck = 0;

	for (int bulletIdx = 0; bulletIdx < MAX_BULLET; bulletIdx++) {
		
		// 총알이 flag가  false일 경우 다음 index확인
		if (bullet[bulletIdx].bulletFlag == false)
			continue;
		

		//플레이어가 쏜 총알일 경우
		if (bullet[bulletIdx].bulletType == 0) {

			for (int enemyIdx = 0; enemyIdx < MAX_ENEMY; enemyIdx++) {
				
				// 적군 flag가 false일 경우 다음 index를 확인한다.
				if (enemy[enemyIdx].eFlag == false)
					continue;
				
				if (enemy[enemyIdx].EX == bullet[bulletIdx].bulletX && enemy[enemyIdx].EY == bullet[bulletIdx].bulletY) {
					enemy[enemyIdx].eFlag = false;
					bullet[bulletIdx].bulletFlag = false;
					break; //
				}
			}
		}
		else {
			if (bullet[bulletIdx].bulletX == user.PX && bullet[bulletIdx].bulletY == user.PY) {

				//플레이어는 피격 후 최소 0.5초동안 무적입니다.
				if (hitCheck == 0) {
					hitCheck = clock();
					user.pHp--;
				}	
			}
		}
	}
}


// 적군이 총을 쏘았을 때 실행되는 로직입니다.
void EnemyShot(int enemyIndex) {

	if (enemy[enemyIndex].eFlag == false)
		return;

	for (int index = 0; index < MAX_BULLET; index++) {

		if (bullet[index].bulletFlag == true)
			continue;

		if (bullet[index].bulletFlag == false) {
			bullet[index].bulletX = enemy[enemyIndex].EX;
			bullet[index].bulletY = enemy[enemyIndex].EY + 1;
			bullet[index].bulletFlag = true;
			bullet[index].bulletType = 1; 
			return;
		}
	}
}