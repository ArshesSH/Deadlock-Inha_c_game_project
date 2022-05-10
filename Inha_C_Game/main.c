#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include "Graphics.h"
#include "Vec2.h"
#include "Rect.h"
#include "Surface.h"
#include "Font.h"

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

    Vec2 pos = { 100, 100 };
    int speed = 5;
    Vec2 up = { 0, -speed };
    Vec2 down = { 0, speed };
    Vec2 left = { -(speed), 0 };
    Vec2 right = { (speed), 0 };

    int key;

    Surface surf;
    MakeSurface( "src/images/LightTankResize20.bmp", &surf );

    Vec2 fontPos = { 200, 200 };
    Font font;
    MakeFont( &font, 0, 0, 16, 28, 32, 3, WHITE, ' ', '~' );


    Vec2 lastPos = pos;

    //PlaySound(TEXT("src/coin.wav"), NULL, SND_ASYNC);

    // Do Game
    while ( 1 )
    {
        // Update Model
        {
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
        }

        // Compose Frame
        {
            DrawSpriteNonChroma( pos.x, pos.y, &surf );
            DrawFontText( "A", fontPos, WHITE, &font );
            Sleep( 2 );
        }
    }

    DeleteSurface( &surf );

    return 0;
}