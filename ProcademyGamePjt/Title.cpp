#include <iostream>
#include <Windows.h>
#include "Title.h"
#include "Console.h"
#include "Player.h"

extern char szScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];


void TitleScene(int *scene) {

    Buffer_Clear();

    strcpy_s(szScreenBuffer[10], dfSCREEN_WIDTH, "                            Press enter key....");

    Buffer_Flip();

    if (GetAsyncKeyState(VK_RETURN)) {
        *scene += 1;
    }
}