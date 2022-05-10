#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include "Graphics.h"
#include "Character.h"
#include "Font.h"
#include "FrameTimer.h"

#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80

int main(int argc, char* argv[]) {
    SetConsoleFontSize( 1 );
    SetConsoleWindowSize( 1280, 720 );
    HideCursor();

    time_t ft;
    StartFrameTimer( &ft );

    Vec2 pos = { 100,100 };
    Character link;
    MakeCharacter( &link, pos, 90, 90, 90, 90, 4, MAGENTA, "src/images/link90x90.bmp" );

    
    /*
    Vec2 pos = { 100, 100 };
    int speed = 5;
    Vec2 up = { 0, -speed };
    Vec2 down = { 0, speed };
    Vec2 left = { -(speed), 0 };
    Vec2 right = { (speed), 0 };
    int key;
    */


    /*
    Vec2 fontPos = { 200, 200 };
    Font font;
    MakeFont( &font, 0, 0, 16, 28, 32, 3, WHITE, ' ', '~' );
    */

    //Vec2 lastPos = pos;

    //PlaySound(TEXT("src/coin.wav"), NULL, SND_ASYNC);

    // Do Game
    while ( 1 )
    {
        // Update Model
        {
            /*
            
             if ( _kbhit() )
            {
                key = _getch();

                if ( key == UP )
                {
                    DeleteRect( SurfaceGetRect( &surf ), pos.x, pos.y );
                    lastPos = pos;
                    Vec2AddEqual( &pos, up );
                }
                if ( key == DOWN )
                {
                    DeleteRect( SurfaceGetRect( &surf ), pos.x, pos.y );
                    lastPos = pos;
                    Vec2AddEqual( &pos, down );
                }
                if ( key == LEFT )
                {
                    DeleteRect( SurfaceGetRect( &surf ), pos.x, pos.y );
                    lastPos = pos;
                    Vec2AddEqual( &pos, left );
                }
                if ( key == RIGHT )
                {
                    DeleteRect( SurfaceGetRect( &surf ), pos.x, pos.y );
                    lastPos = pos;
                    Vec2AddEqual( &pos, right );
                }
            }
            */


            Vec2 dir = { 0, 0 };

            if (_kbhit())
            {
                if (_getch() == LEFT)
                {
                    dir.x -= 1;
                }
                else if (_getch() == RIGHT)
                {
                    dir.x += 1;
                }
                if (_getch() == UP)
                {
                    dir.y += 1;
                }
                else if (_getch() == DOWN)
                {
                    dir.y -= 1;
                }
            }

            SetCharacterDirection( &link, dir );
            UpdateCharacter( &link, MarkFrameTimer( &ft ) );
        }

        // Compose Frame
        {
            /*
            DrawSpriteNonChroma( pos.x, pos.y, &surf );
            DrawFontText( "I want go HOME!", fontPos, WHITE, &font );
            Sleep( 2 );
            */

            DrawCharacter( &link );

        }
    }

    // End Game
    /*
    DestroySurface( &surf );
    DestroyFont( &font );
    */


    return 0;
}