#pragma once

#define MAX_BULLET 40


struct Bullet {

	// �ҷ� ���� ����
	bool bulletFlag; 

	// ���� ������ 0 == �÷��̾�, 1 == ��
	char bulletType; 
	int bulletX;
	int bulletY;
};

void CreateBullet();

void PlayerShot();

void EnemyShot(int enemyIndex);

void MoveBullet();

void hitBullet();

void BulletDraw();

