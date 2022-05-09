#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include "Graphics.h"
#include "Vec2.h"
#include "Rect.h"


#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80


int main(int argc, char* argv[]) {

    SetConsoleFontSize(1);
    SetConsoleWindowSize(1280, 720);
    HideCursor();

    Vec2 pos = { 100, 100 };
    int speed = 10;
    Vec2 up = { 0, -speed };
    Vec2 down = { 0, speed };
    Vec2 left = { -(speed), 0 };
    Vec2 right = { (speed), 0 };

    int key;

    Rect testRect = MakeRect( 10, 10, 10, 10 );

    Vec2 lastPos = pos;

    //PlaySound(TEXT("src/coin.wav"), NULL, SND_ASYNC);


    while (1)
    {
        //Update
        {
            if (_kbhit())
            {
                key = _getch();

                if (key == UP)
                {
                    lastPos = pos;
                    Vec2AddEqual( &pos, up );
                }
                if (key == DOWN)
                {
                    lastPos = pos;
                    Vec2AddEqual( &pos, down );
                }
                if (key == LEFT)
                {
                    lastPos = pos;
                    Vec2AddEqual( &pos, left );
                }
                if (key == RIGHT)
                {
                    lastPos = pos;
                    Vec2AddEqual( &pos, right );
                }
            }
        }

        // ComposeFrame
        {
            DrawRect( pos.x+100, pos.y+ 100, pos.x + 150, pos.y + 150, RED );
        }
    }


    


    _getch();

    return 0;
}