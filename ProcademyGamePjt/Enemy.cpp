#include <iostream>
#include <Windows.h>
#include <time.h>
#include "Console.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Player.h"

extern char szScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];

extern enum switchScene { Title = 1, loading, GameStage, GameEnd };

extern Player user;

// 몬스터 배열
Enemy enemy[MAX_ENEMY];

// 파일에 저장된 몬스터 좌표 데이터를 읽어 몬스터 배열에 대입합니다.
void CreateEnemy() {

	static int stage = 1;
	FILE* fp = nullptr;

	//스테이지에 해당하는 몬스터 정보를 텍스트 파일에서 가져온다
	if (stage == 1) {
		if (fopen_s(&fp, "enemyList1.txt", "rt"))
			return;
		stage++;
	}
	else if (stage == 2) {
		if (fopen_s(&fp, "enemyList2.txt", "rt"))
			return;
		stage++;
	}
	else if (stage == 3) {
		if (fopen_s(&fp, "enemyList3.txt", "rt"))
			return;		
	}
	
	for (int index = 0; index < MAX_ENEMY; index++) {
		fscanf_s(fp, "X,Y : (%d,%d)\nattackSpeed: %d\neSpeed : %d\n", &enemy[index].EX, &enemy[index].EY,&enemy[index].attackSpeed,&enemy[index].eSpeed);
		enemy[index].eFlag = true;
		enemy[index].eDirection = true;
	}

	fclose(fp);
}

// 몬스터 랜더링
void EnemyDraw() {
	
	for (int index = 0; index < MAX_ENEMY; index++) {
		if(enemy[index].eFlag == true)
		szScreenBuffer[enemy[index].EY][enemy[index].EX] = '#';
	}
}

// 적군중 하나라도 벽에 닿으면 방향을 바꾼다.
// 
void EnemyAct() {

	static clock_t monetSpeedCheck=clock();
	
	if (clock()- monetSpeedCheck >= 1000/enemy[0].eSpeed) {

		for (int index = 0; index < MAX_ENEMY; index++) {
			if (enemy[index].eFlag == false)
				continue;

			//eDriction true면 오른쪽 false면 왼쪽
			  if (enemy[index].eDirection == true) {
					enemy[index].EX++;

					if (enemy[index].EX == dfSCREEN_WIDTH - 2) {
						
						for (int chIdx = 0; chIdx < MAX_ENEMY; chIdx++) {

							if (enemy[chIdx].eFlag == false)
								continue;

							if(chIdx > index)
								enemy[chIdx].EX++;

							enemy[chIdx].eDirection = false;
						}
						break;
					}	
			  }
			  else {
					enemy[index].EX--;

					if (enemy[index].EX == 1) {
						enemy[index].EX++;

						for (int x = 0; x < MAX_ENEMY; x++) {
							enemy[x].eDirection = true;
						}
						break;
					}
			  }
			  monetSpeedCheck = clock();
		}
	}
}

void EnemyShotting() {
	static clock_t monsterShotCheck = clock();

	// 몬스터의 공격속도 주기로 아래 로직을 수행합니다.
	if (clock() - monsterShotCheck >= 3000/enemy[0].attackSpeed) {

		for (int index = 0; index <MAX_ENEMY; index++) {
		
			//false면 다음 인덱스를 확인합니다. 
			if (enemy[index].eFlag == false)
				continue;

			// 플레이어와 x좌표를 기준으로 절대값 7이하로 차이가 날 경우 총알을 발사합니다.
			if (abs(enemy[index].EX - user.PX) <= 7) {
				EnemyShot(index);
			}
		}
		monsterShotCheck = clock();
	}
}

// 적군 전체 플래그 확인
void EnemyClean(int* scene) {
	static int EnemyCleanCheck;

	for (int index = 0; index < MAX_ENEMY; index++) {

		//적군 하나라도 살아있으면 return
		if (enemy[index].eFlag == true)
			return;
	}

	//적군이 모두 죽었으면 EnemyCleanCheck++;
	*scene = loading;
	EnemyCleanCheck++;


	//EnemyCleanCheck가 3일 경우 게임 end
	if (EnemyCleanCheck == 3)
		*scene = GameEnd;
}