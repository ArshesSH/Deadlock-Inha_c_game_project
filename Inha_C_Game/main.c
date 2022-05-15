#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>

#include "Graphics.h"
#include "Game.h"

int main(int argc, char* argv[]) {
    SetConsoleFontSize( 1 );
    // 960 540
    SetConsoleWindowSize( 1920, 1080 );
    HideCursor();

    srand( (unsigned int)time( NULL ) );

    /************************
    *       Init Game       *
    *************************/
    Game game;
    game.IsStageChanged = false;
    game.stage = StageStart;
    MakeStage( &game );

    /************************
    *       Init Draw        *
    *************************/

    while ( 1 )
    {
        /****************************
        *       Update Model        *
        *****************************/
        {
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

    return 0;
}