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

// ���� �迭
Enemy enemy[MAX_ENEMY];

// ���Ͽ� ����� ���� ��ǥ �����͸� �о� ���� �迭�� �����մϴ�.
void CreateEnemy() {

	static int stage = 1;
	FILE* fp = nullptr;

	//���������� �ش��ϴ� ���� ������ �ؽ�Ʈ ���Ͽ��� �����´�
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

// ���� ������
void EnemyDraw() {
	
	for (int index = 0; index < MAX_ENEMY; index++) {
		if(enemy[index].eFlag == true)
		szScreenBuffer[enemy[index].EY][enemy[index].EX] = '#';
	}
}

// ������ �ϳ��� ���� ������ ������ �ٲ۴�.
// 
void EnemyAct() {

	static clock_t monetSpeedCheck=clock();
	
	if (clock()- monetSpeedCheck >= 1000/enemy[0].eSpeed) {

		for (int index = 0; index < MAX_ENEMY; index++) {
			if (enemy[index].eFlag == false)
				continue;

			//eDriction true�� ������ false�� ����
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

	// ������ ���ݼӵ� �ֱ�� �Ʒ� ������ �����մϴ�.
	if (clock() - monsterShotCheck >= 3000/enemy[0].attackSpeed) {

		for (int index = 0; index <MAX_ENEMY; index++) {
		
			//false�� ���� �ε����� Ȯ���մϴ�. 
			if (enemy[index].eFlag == false)
				continue;

			// �÷��̾�� x��ǥ�� �������� ���밪 7���Ϸ� ���̰� �� ��� �Ѿ��� �߻��մϴ�.
			if (abs(enemy[index].EX - user.PX) <= 7) {
				EnemyShot(index);
			}
		}
		monsterShotCheck = clock();
	}
}

// ���� ��ü �÷��� Ȯ��
void EnemyClean(int* scene) {
	static int EnemyCleanCheck;

	for (int index = 0; index < MAX_ENEMY; index++) {

		//���� �ϳ��� ��������� return
		if (enemy[index].eFlag == true)
			return;
	}

	//������ ��� �׾����� EnemyCleanCheck++;
	*scene = loading;
	EnemyCleanCheck++;


	//EnemyCleanCheck�� 3�� ��� ���� end
	if (EnemyCleanCheck == 3)
		*scene = GameEnd;
}