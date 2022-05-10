#include "Game.h"

#include "Graphics.h"

void PlayGame()
{
	UpdateModel();
	ComposeFrame();
}

void InitGame()
{
	Vec2 up = { 0, -speed };
	Vec2 down = { 0, speed };
	Vec2 left = { -(speed), 0 };
	Vec2 right = { (speed), 0 };
    pos = MakeVec2( 100, 100 );
	lastPos = pos;

	MakeSurface( "src/images/awsom.bmp", &surf );
}

void UpdateModel()
{
    int key;

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

void ComposeFrame()
{
    DrawSpriteChroma( pos.x, pos.y, &surf, MAGENTA );
}

void EndGame()
{
    DeleteSurface( &surf );
}