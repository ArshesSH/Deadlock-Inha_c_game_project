#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>

#include "Graphics.h"
#include "Game.h"

BOOL IsElevated();

int main(int argc, char* argv[])
{
    int width = 1920;
    int height = 1080;

    if (IsElevated() == false)
    {
		printf( "This program requires administrator privileges to run.\n" );
		printf( "Please run the program as an administrator.\n" );
		printf( "Press any key to continue..." );
		getchar();
		return 0;
    }

    SetConsoleFontSize( 1 );
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

BOOL IsElevated()
{
    BOOL fRet = FALSE;
    HANDLE hToken = NULL;
    if (OpenProcessToken( GetCurrentProcess(), TOKEN_QUERY, &hToken )) {
        TOKEN_ELEVATION Elevation;
        DWORD cbSize = sizeof( TOKEN_ELEVATION );
        if (GetTokenInformation( hToken, TokenElevation, &Elevation, sizeof( Elevation ), &cbSize )) {
            fRet = Elevation.TokenIsElevated;
        }
    }
    if (hToken) {
        CloseHandle( hToken );
    }
    return fRet;
}