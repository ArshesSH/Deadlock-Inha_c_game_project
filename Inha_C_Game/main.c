#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include "Graphics.h"
#include "Character.h"
#include "Font.h"
#include "FrameTimer.h"
#include "Projectile.h"
#include <math.h>

#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")


int main(int argc, char* argv[]) {
    SetConsoleFontSize( 1 );
    SetConsoleWindowSize( 1280, 720 );
    HideCursor();

    time_t ft;
    StartFrameTimer( &ft );

    Vec2 pos = { 100,100 };
    Character link;
    MakeCharacter( &link, pos, 90, 90, 90, 90, 4, MAGENTA, "src/images/link90x90.bmp" );

    Vec2 lastPos = pos;
    bool isKeyInputed = false;
    
    Vec2 projStartPos = { 0, 200 };
    Projectile proj;
    Surface surf;
    MakeSurface( "src/images/awsom.bmp", &surf );
    MakeProjectile( &proj, projStartPos, 40, 50, &surf, MAGENTA );
    SetProjectileVel( &proj, 50, 100 );


    /*
    Vec2 pos = { 100, 100 };
    int speed = 5;
    Vec2 up = { 0, -speed };
    Vec2 down = { 0, speed };
    Vec2 left = { -(speed), 0 };
    Vec2 right = { (speed), 0 };
    int key;
    */


    int key;
    Vec2 fontPos = { 0, 0 };
    Font font;
    MakeFont( &font, 0, 0, 16, 28, 32, 3, WHITE, ' ', '~' );
    
    char* text = { 0, };
    char buf[BUFSIZ];
    Vec2 a;
    int angle = 40;
    int power = 50;
    float radian = angle * (3.14592 / 180.0);
    a = MakeVec2( power * cosf( radian ), power * sinf( radian ) );
    sprintf_s( buf, BUFSIZ, "angle %d, power %d => Vec(%.1f, %.1f)", angle, power, a.x, a.y );

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
                key = _getch();
                if ( key == VK_LEFT)
                {
                    dir.x -= 10;
                    isKeyInputed = true;
                    lastPos = pos;
                    Vec2AddEqual( &pos, dir );
                }
                else if ( key == VK_RIGHT)
                {
                    dir.x += 10;
                    isKeyInputed = true;
                    lastPos = pos;
                    Vec2AddEqual( &pos, dir );
                }
                if ( key == VK_UP)
                {
                    dir.y -= 10;
                    isKeyInputed = true;
                    lastPos = pos;
                    Vec2AddEqual( &pos, dir );
                }
                else if ( key == VK_DOWN)
                {
                    dir.y += 10;
                    isKeyInputed = true;
                    lastPos = pos;
                    Vec2AddEqual( &pos, dir );
                }
                if ( key == VK_SPACE )
                {
                    StartFire( &proj );
                    SetProjectileVel( &proj, 30, 50 );
                }
            }

            if ( proj.isFired == true )
            {
                if ( IsInScreen( &proj ) )
                {
                    UpdateProjectile( &proj );
                }
                else
                {
                    ResetProjectile( &proj );
                }
            }

        }

        // Compose Frame
        {
            if ( isKeyInputed )
            {
                DrawSpriteChroma( pos.x, pos.y, &surf, MAGENTA );
            }

            if ( proj.isFired == true )
            {
                DrawProjectileChroma( &proj );
                Sleep( 30 );
            }
        }
    }

    // End Game
    /*
    DestroySurface( &surf );
    DestroyFont( &font );
    */


    return 0;
}