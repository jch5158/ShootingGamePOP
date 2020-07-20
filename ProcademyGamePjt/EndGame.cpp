#include <iostream>
#include "Console.h"

// 스크린 버퍼
extern char szScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];


void EndGameScene() {
	Buffer_Clear();

	//게임 마지막 랜더링
	strcpy_s(szScreenBuffer[10], dfSCREEN_WIDTH, "                                  End Game...");

	Buffer_Flip();
}