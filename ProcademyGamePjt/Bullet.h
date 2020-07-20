#pragma once

#define MAX_BULLET 40


struct Bullet {

	// 불렛 생성 여부
	bool bulletFlag; 

	// 누가 쐈는지 0 == 플레이어, 1 == 적
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

