#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <time.h>
#include "Console.h"
#include "Player.h"

HANDLE hConsole;


char szScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];
extern Player user;

extern enum switchScene  { Title = 1, loading, GameStage, GameEnd };

void cs_Initial(void) {
	CONSOLE_CURSOR_INFO stConsoleCursor; // 커서 구조체

	stConsoleCursor.bVisible = FALSE; // 커서 안보이게
	stConsoleCursor.dwSize = 1; // 커서의 최소 크기

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(hConsole, &stConsoleCursor);
}

void cs_MoveCursor(int iPosX, int iPosY) {
	COORD stCoord;
	stCoord.X = iPosX;
	stCoord.Y = iPosY;

	SetConsoleCursorPosition(hConsole, stCoord);
}

void cs_ClearScreen(void) { // 버퍼 밀기
	unsigned long dw;
	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', 100 * 100, { 0,0 }, &dw);
}



//--------------------------------------------------------------------
// 버퍼의 내용을 화면으로 찍어주는 함수.
//
// 적군,아군,총알 등을 szScreenBuffer 에 넣어주고,
// 1 프레임이 끝나는 마지막에 본 함수를 호출하여 버퍼 -> 화면 으로 그린다.
//--------------------------------------------------------------------
void Buffer_Flip(void)
{
    cs_MoveCursor(0, 0);

    printf_s(" 체력 : %d ", user.pHp);

    for (int iCnt = 0; iCnt < dfSCREEN_HEIGHT; iCnt++)
    {
        cs_MoveCursor(0, iCnt+1);
        printf(szScreenBuffer[iCnt]);
    }
}

//--------------------------------------------------------------------
// 화면 버퍼를 지워주는 함수
//
// 매 프레임 그림을 그리기 직전에 버퍼를 지워 준다.
// 안그러면 이전 프레임의 잔상이 남으니까
//--------------------------------------------------------------------
void Buffer_Clear(void)
{
   
    memset(szScreenBuffer, ' ', dfSCREEN_WIDTH * dfSCREEN_HEIGHT);

    for (int iCnt = 0; iCnt < dfSCREEN_HEIGHT; iCnt++)
    {
        szScreenBuffer[iCnt][dfSCREEN_WIDTH - 1] = '\0'; // 맨 마지막에만 null을 삽입합니다. 
    }
}

//--------------------------------------------------------------------
// 버퍼의 특정 위치에 원하는 문자를 출력.
//
// 입력 받은 X,Y 좌표에 아스키코드 하나를 출력한다. (버퍼에 그림)
//--------------------------------------------------------------------
bool Sprite_Draw(int iX, int iY, char chSprite)
{
    if (iX < 0 || iY < 0 || iX >= dfSCREEN_WIDTH - 1 || iY >= dfSCREEN_HEIGHT)
        return false;

    szScreenBuffer[iY][iX] = chSprite;

    return true;
}


