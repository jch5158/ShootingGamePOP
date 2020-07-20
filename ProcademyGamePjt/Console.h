#pragma once

#ifndef _CONSOLE_

#define dfSCREEN_WIDTH 81

#define dfSCREEN_HEIGHT 24

void cs_Initial(void);

void cs_MoveCursor(int iPosX, int iPosY);

void cs_ClearScreen(void);

void Buffer_Flip(void);

void Buffer_Clear(void);

bool Sprite_Draw(int iX, int iY, char chSprite);


#endif // !__CONSOLE__
