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
	CONSOLE_CURSOR_INFO stConsoleCursor; // Ŀ�� ����ü

	stConsoleCursor.bVisible = FALSE; // Ŀ�� �Ⱥ��̰�
	stConsoleCursor.dwSize = 1; // Ŀ���� �ּ� ũ��

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(hConsole, &stConsoleCursor);
}

void cs_MoveCursor(int iPosX, int iPosY) {
	COORD stCoord;
	stCoord.X = iPosX;
	stCoord.Y = iPosY;

	SetConsoleCursorPosition(hConsole, stCoord);
}

void cs_ClearScreen(void) { // ���� �б�
	unsigned long dw;
	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', 100 * 100, { 0,0 }, &dw);
}



//--------------------------------------------------------------------
// ������ ������ ȭ������ ����ִ� �Լ�.
//
// ����,�Ʊ�,�Ѿ� ���� szScreenBuffer �� �־��ְ�,
// 1 �������� ������ �������� �� �Լ��� ȣ���Ͽ� ���� -> ȭ�� ���� �׸���.
//--------------------------------------------------------------------
void Buffer_Flip(void)
{
    cs_MoveCursor(0, 0);

    printf_s(" ü�� : %d ", user.pHp);

    for (int iCnt = 0; iCnt < dfSCREEN_HEIGHT; iCnt++)
    {
        cs_MoveCursor(0, iCnt+1);
        printf(szScreenBuffer[iCnt]);
    }
}

//--------------------------------------------------------------------
// ȭ�� ���۸� �����ִ� �Լ�
//
// �� ������ �׸��� �׸��� ������ ���۸� ���� �ش�.
// �ȱ׷��� ���� �������� �ܻ��� �����ϱ�
//--------------------------------------------------------------------
void Buffer_Clear(void)
{
   
    memset(szScreenBuffer, ' ', dfSCREEN_WIDTH * dfSCREEN_HEIGHT);

    for (int iCnt = 0; iCnt < dfSCREEN_HEIGHT; iCnt++)
    {
        szScreenBuffer[iCnt][dfSCREEN_WIDTH - 1] = '\0'; // �� ���������� null�� �����մϴ�. 
    }
}

//--------------------------------------------------------------------
// ������ Ư�� ��ġ�� ���ϴ� ���ڸ� ���.
//
// �Է� ���� X,Y ��ǥ�� �ƽ�Ű�ڵ� �ϳ��� ����Ѵ�. (���ۿ� �׸�)
//--------------------------------------------------------------------
bool Sprite_Draw(int iX, int iY, char chSprite)
{
    if (iX < 0 || iY < 0 || iX >= dfSCREEN_WIDTH - 1 || iY >= dfSCREEN_HEIGHT)
        return false;

    szScreenBuffer[iY][iX] = chSprite;

    return true;
}


