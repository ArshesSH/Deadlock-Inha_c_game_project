#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include "Graphics.h"
#include "Vec2.h"
#include "Rect.h"
#include "Surface.h"
#include "Game.h"

#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

int main(int argc, char* argv[]) {

    SetConsoleFontSize(1);
    SetConsoleWindowSize(1280, 720);
    HideCursor();

    //PlaySound(TEXT("src/coin.wav"), NULL, SND_ASYNC);

    InitGame();
    while (1)
    {
        UpdateModel();
        ComposeFrame();
    }
    EndGame();
    
    _getch();

    return 0;
}