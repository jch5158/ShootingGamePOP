#include <iostream>
#include "Console.h"

// ��ũ�� ����
extern char szScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];


void EndGameScene() {
	Buffer_Clear();

	//���� ������ ������
	strcpy_s(szScreenBuffer[10], dfSCREEN_WIDTH, "                                  End Game...");

	Buffer_Flip();
}