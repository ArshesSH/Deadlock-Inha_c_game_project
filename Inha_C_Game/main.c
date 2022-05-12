#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include "Graphics.h"
#include "Character.h"
#include "Font.h"
#include "Projectile.h"
#include "Ground.h"
#include "Tank.h"
#include <math.h>
#include <time.h>

#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")


int main(int argc, char* argv[]) {
    SetConsoleFontSize( 1 );
    SetConsoleWindowSize( 1920, 1080 );
    HideCursor();

    srand( (unsigned int)time( NULL ) );


    bool isKeyInputed = false;


    


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
    Vec2 userPos = { 50, screenHeight - 47 - 30 };
    Vec2 aiPos = { 500,screenHeight - 47 - 30 };
    Surface aiProjSurf;
    MakeSurface( "src/images/bullet.bmp", &aiProjSurf );
    Projectile aiProj;
    MakeProjectile( &aiProj, aiPos, &aiProjSurf, MAGENTA );

    // Make Ground
    Vec2 groundPos = { 0, screenHeight - 47 };
    Surface groundSurf;
    MakeSurface( "src/images/GroundTile.bmp", &groundSurf );
    Ground testGround;
    MakeFlatGround( &testGround, &groundSurf, groundPos, 20, MAGENTA );
    DrawGround( &testGround );

    Tank tank;
    MakeTank( &tank, (int)HeavyTank, 30, groundPos );
    DrawTank( &tank );

    Tank tankAI;
    MakeTank( &tankAI, (int)MRLAI, 600, groundPos );
    DrawTank( &tankAI );

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

                    if ( key == VK_SPACE )
                    {
                        SetTankAI( &tankAI );
                    }

                    if (key == VK_LEFT )
                    {
                        if ( aiProj.isFired != true )
                        {
                            SetProjectileVelAI( &aiProj, userPos, aiPos, 50 );
                            StartProjectileFire( &aiProj );
                        }
                    }
                }
                
                UpdateTankAI( &tankAI );

                if (aiProj.isFired == true)
                {
                    if (IsInScreen( &aiProj ))
                    {
                        UpdatePrjectileAI( &aiProj );
                        if ( IsOverlapWithTarget( &aiProj, testGround.rect ) )
                        {
                            ResetProjectile( &aiProj );
                        }
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
                if (IsProjectFired( &aiProj ))
                {
                    DrawProjectileChroma( &aiProj );
                    Sleep( 10 );
                }

                if ( tankAI.isMoving == true )
                {
                    DrawTank( &tankAI );
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
    DestroyGround( &testGround );

    return 0;
}