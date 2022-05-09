#include <stdio.h>
#include <conio.h>
#include "Graphics.h"
#include "Vec2.h"
#include "Game.h"

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
    Vec2 left = { -(speed * 2), 0 };
    Vec2 right = { (speed * 2), 0 };

    int key;


    /*
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // you can loop k higher to see more color choices
    for (int k = 1; k < 255; k++)
    {
        // pick the colorattribute k you want
        SetConsoleTextAttribute(hConsole, k);
        printf( "%d I want to be nice today!\n", k);
    }
    */

    Vec2 lastPos = pos;


    PutPixelInt(pos.x - 5, pos.y);
    PutPixelInt(pos.x - 4, pos.y);
    PutPixelInt(pos.x - 3, pos.y);
    PutPixelInt(pos.x+ 3, pos.y);
    PutPixelInt(pos.x +4, pos.y);
    PutPixelInt(pos.x +5, pos.y);
    PutPixelInt(pos.x, pos.y -5);
    PutPixelInt(pos.x, pos.y - 4);
    PutPixelInt(pos.x, pos.y - 3);
    PutPixelInt(pos.x, pos.y +5);
    PutPixelInt(pos.x, pos.y +4);
    PutPixelInt(pos.x, pos.y + 3);


    /*
    while (1)
    {
        if (_kbhit())
        {
            
            key = _getch();

            if (key == UP)
            {
                lastPos = pos;
                AddEqualVec2(&pos, up);
            }
            if (key == DOWN)
            {
                lastPos = pos;
                AddEqualVec2(&pos, down);
            }
            if (key == LEFT)
            {
                lastPos = pos;
                AddEqualVec2(&pos, left);
            }
            if (key == RIGHT)
            {
                lastPos = pos;
                AddEqualVec2(&pos, right);
            }
            PutPixelInt(pos.x, pos.y);
            DeletePixelInt(lastPos.x, lastPos.y);
        }
        
    }
    */
    


    return 0;
}