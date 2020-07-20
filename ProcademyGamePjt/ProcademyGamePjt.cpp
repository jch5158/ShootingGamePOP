#include <iostream>
#include <memory.h>
#include <Windows.h>
#include <time.h>

#include "Console.h"
#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"

#include "Title.h"
#include "Loading.h"
#include "PlayGame.h"
#include "EndGame.h"

#pragma comment(lib, "winmm")


//switch case문
enum switchScene {Title = 1,loading,GameStage,GameEnd};

// 스크린 버퍼
extern char szScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];


int main(void)
{
    
    timeBeginPeriod(1);

    // switch 문 전달할 매개변수
    int scene = 1;


   cs_Initial(); // 커서 없애기 

 
    while (1)
    {

        switch (scene) {
        case Title:

            TitleScene(&scene);

            break;
        case loading:

            LoadingScene(&scene);

            break;
        case GameStage:
    
            GameScene(&scene);
           
            break;
        case GameEnd:

            EndGameScene();

            break;
        }
        // 프레임 맞추기용 대기 60 Frame 
        Sleep(16);
    }
    timeEndPeriod(1);
}



