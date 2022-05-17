#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>

#include "Graphics.h"
#include "Game.h"

int main(int argc, char* argv[]) {
    SetConsoleFontSize( 1 );

    // 960 540
    int width = 1920;
    int height = 1080;

    /*
    * Can not Use this Now
    // If User Input screen Size, Change Screen Size
    if ( argc == 3 )
    {
        width = atoi(argv[1]);
        height = atoi(argv[2]);
    }
    */
    MoveConsoleWindow( 0, 0, width, height );
    SetConsoleWindowSize( width, height );

    HideCursor();

    srand( (unsigned int)time( NULL ) );

    /************************
    *       Init Game       *
    *************************/
    Game game;
    game.IsStageChanged = false;
    game.IsGameEnd = false;
    game.stage = StageStart;
    MakeStage( &game );

    /************************
    *       Init Draw        *
    *************************/

    while ( !game.IsGameEnd )
    {
        /****************************
        *       Update Model        *
        *****************************/
        {
            if (IsPlayerInput( VK_ESCAPE ))
            {
                break;
            }
            if (game.IsStageChanged)
            {
                MakeStage( &game );
            }
            UpdateModel( &game );
        }

        /****************************
        *       Compose Frame       *
        *****************************/
        {
            DrawFrame( &game );
        }
    }

    /************************
    *       End Game        *
    *************************/
    DestroyGame( &game );

    return 0;
}