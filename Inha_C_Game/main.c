#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include "Graphics.h"
#include "Character.h"
#include "Font.h"
#include "Projectile.h"
#include <math.h>
#include <time.h>

#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")


int main(int argc, char* argv[]) {
    SetConsoleFontSize( 1 );
    SetConsoleWindowSize( 1920, 1080 );
    HideCursor();

    srand( (unsigned int)time( NULL ) );

    Vec2 pos = { 100,100 };
    Character link;
    MakeCharacter( &link, pos, 90, 90, 90, 90, 4, MAGENTA, "src/images/link90x90.bmp" );

    Vec2 lastPos = pos;
    bool isKeyInputed = false;
    
    Vec2 projStartPos = { 0, 200 };
    Projectile proj;
    Surface surf;
    MakeSurface( "src/images/awsom.bmp", &surf );
    MakeProjectile( &proj, projStartPos, &surf, MAGENTA );
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

    /************************
    *       Main Game       *
    *************************/

    /************************
    *       Init Game       *
    *************************/
    bool isDrawOnce = false;
    Vec2 userPos = { 50, 500 };
    Vec2 aiPos = { 500,500 };
    Projectile aiProj;
    MakeProjectile( &aiProj, aiPos, &surf, MAGENTA );

    while ( 1 )
    {
        /****************************
        *       Update Model        *
        *****************************/
        {
            /*
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
            */

            // Parabola Enemy Test
            {
                if (_kbhit())
                {
                    key = _getch();

                    if (key == VK_SPACE)
                    {
                        SetProjectileVelAI( &aiProj, userPos, aiPos, 50 );
                        StartProjectileFire( &aiProj );
                    }
                }
                
                if (aiProj.isFired == true)
                {
                    if (IsInScreen( &aiProj ))
                    {
                        UpdatePrjectileAI( &aiProj );
                    }
                    else
                    {
                        ResetProjectile( &aiProj );
                    }
                }
            }

        }

        /****************************
        *       Compose Frame       *
        *****************************/
        {
            /*
            DrawFontText( buf, fontPos, WHITE, &font );
            if ( isKeyInputed )
            {
                DrawSpriteChroma( pos.x, pos.y, &surf, MAGENTA );
            }

            if ( proj.isFired == true )
            {
                DrawProjectileChroma( &proj );
                Sleep( 30 );
            }
            */

            //Test Parabola Enemy
            {
                if (!isDrawOnce)
                {
                    DrawSpriteChroma( (float)userPos.x, (float)userPos.y, &surf, MAGENTA );
                    isDrawOnce = true;
                }
                if (IsProjectFired( &aiProj ))
                {
                    DrawProjectileChroma( &aiProj );
                }
            }
        }
    }

    /************************
    *       End Game        *
    *************************/
    /*
    DestroySurface( &surf );
    DestroyFont( &font );
    */


    return 0;
}