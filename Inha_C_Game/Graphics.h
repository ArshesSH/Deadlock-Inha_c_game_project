#pragma once
#include <Windows.h>
#include <string.h>
#include "cful.h"
#include "Vec2.h"

void SetColor(WORD color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void HideCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void SetConsoleFontSize(int size)
{
    static CONSOLE_FONT_INFOEX  fontex;
    fontex.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetCurrentConsoleFontEx(hOut, 0, &fontex);
    fontex.dwFontSize.X = size;
    fontex.dwFontSize.Y = size;
    SetCurrentConsoleFontEx(hOut, NULL, &fontex);
}

void MoveCursor(int x, int y)
{
    COORD coord = { x , y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void SetConsoleWindowSize(int consoleWidth, int consoleHeight)
{
    const int halfWidth = consoleWidth / 2;
    const int halfHeight = consoleHeight / 2;

    DWORD dwWidth = GetSystemMetrics(SM_CXSCREEN);
    DWORD dwHeight = GetSystemMetrics(SM_CYSCREEN);

    //HWND wh = GetConsoleWindow();
    //MoveWindow(wh, 0, 0, consoleWidth, consoleHeight, TRUE);

    char strWidth[5];
    char strHeight[5];
    char consolSizeStr[64] = { "mode con:cols=" };
    sprintf_s(strWidth, 5, "%d", consoleWidth);
    sprintf_s(strHeight, 5, "%d", halfHeight);

    strcat_s(consolSizeStr, 64, strWidth);
    strcat_s(consolSizeStr, 64, " lines=");
    strcat_s(consolSizeStr, 64, strHeight);

    system(consolSizeStr);
}

void PutPixel(int x, int y)
{
    MoveCursor(x * 2, y);
    //SetColor(0xFF00);
    printf("бс");
}


void DeletePixelInt(int x, int y)
{
    MoveCursor(x * 2, y);
    printf("  ");
}