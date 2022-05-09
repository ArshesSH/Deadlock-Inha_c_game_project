#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include "Graphics.h"
#include "Vec2.h"
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
            PutPixel( pos.x, pos.y, CYAN );

            PutPixel( pos.x - 5, pos.y, RED );
            PutPixel( pos.x - 4, pos.y, RED );
            PutPixel( pos.x - 3, pos.y, RED );
            PutPixel( pos.x + 3, pos.y, RED );
            PutPixel( pos.x + 4, pos.y, RED );
            PutPixel( pos.x + 5, pos.y, RED );
            PutPixel( pos.x, pos.y - 5, RED );
            PutPixel( pos.x, pos.y - 4, RED );
            PutPixel( pos.x, pos.y - 3, RED );
            PutPixel( pos.x, pos.y + 5, RED );
            PutPixel( pos.x, pos.y + 4, RED );
            PutPixel( pos.x, pos.y + 3, RED );
        }
    }


    


    _getch();

    return 0;
}