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


// �Ѿ� �迭�� �ʱ�ȭ�ϴ� �Լ��Դϴ�.
void CreateBullet() {
	for (int index = 0; index < MAX_BULLET; index++) {	
		bullet[index].bulletX = 0;
		bullet[index].bulletY = 0;
		bullet[index].bulletFlag = false;
		bullet[index].bulletType = 0;
	}
}


// �Ʊ��� ���� ��� �Լ��Դϴ�.
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

// �÷��̾ �� �Ѿ��� �Լ��Դϴ�.
// �Ѿ��� ��ġ�� ȭ����� ������� bulletFlag���� false�� �ٲ۴�.
// bulletType == 0�� �÷��̾� �Ѿ�, bulletType == 1�� ���� �Ѿ�
// �Ѿ��� �ӵ��� 0.05�ʸ��� �����Դϴ�.
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

			//�Ѿ� ��ġ �̵�
			if (bullet[index].bulletType == 0)
				bullet[index].bulletY -= 1;
			else
				bullet[index].bulletY += 1;

		}
		bulletSpeedCheck = clock();
	}
}


//�Ѿ� ������
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



// �÷��̾�� ���� �׸��� �Ѿ��� ��ġ�� ���� �Ѿ��� �¾Ҵ��� üũ�մϴ�.
void hitBullet() {

	static clock_t hitCheck;


	//�÷��̾�� �ǰ� �� �ּ� 0.5�ʵ��� �����Դϴ�.
	if (clock() - hitCheck >= 500)
		hitCheck = 0;

	for (int bulletIdx = 0; bulletIdx < MAX_BULLET; bulletIdx++) {
		
		// �Ѿ��� flag��  false�� ��� ���� indexȮ��
		if (bullet[bulletIdx].bulletFlag == false)
			continue;
		

		//�÷��̾ �� �Ѿ��� ���
		if (bullet[bulletIdx].bulletType == 0) {

			for (int enemyIdx = 0; enemyIdx < MAX_ENEMY; enemyIdx++) {
				
				// ���� flag�� false�� ��� ���� index�� Ȯ���Ѵ�.
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

				//�÷��̾�� �ǰ� �� �ּ� 0.5�ʵ��� �����Դϴ�.
				if (hitCheck == 0) {
					hitCheck = clock();
					user.pHp--;
				}	
			}
		}
	}
}


// ������ ���� ����� �� ����Ǵ� �����Դϴ�.
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