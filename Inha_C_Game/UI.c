#include "UI.h"

#include "Graphics.h"

void MakeUI( UI* ui, Status* target, Vec2 pos )
{
	// Init UI var
	ui->UIPos = pos;
	ui->healthPos = pos;
	ui->anglePos = MakeVec2( pos.x, pos.y + 20 );
	ui->powerPos = MakeVec2( pos.x, ui->anglePos.y + 20 );
	ui->targetStatus = target;
	MakeFont( &(ui->textFont), FontSmall );
}


void UpdateUI( UI* ui )
{
	if ( ui->targetStatus->statusChange == ChangeHealth )
	{
		sprintf_s( ui->text, BUFSIZ, "Health : %.f", ui->targetStatus->health );
	}
	else if ( ui->targetStatus->statusChange == ChangeAngle )
	{
		sprintf_s( ui->text, BUFSIZ, "angle : %d", ui->targetStatus->angle );
	}
	else if ( ui->targetStatus->statusChange == ChangePower )
	{
		sprintf_s( ui->text, BUFSIZ, "Power : %d", ui->targetStatus->power );
	}

}

void DrawUI( UI* ui )
{
	if ( ui->targetStatus->statusChange == ChangeHealth )
	{
		DrawFontText( ui->text, ui->healthPos, WHITE, &(ui->textFont) );
	}
	else if ( ui->targetStatus->statusChange == ChangeAngle )
	{
		DrawFontText( ui->text, ui->anglePos, WHITE, &(ui->textFont) );
	}
	else if ( ui->targetStatus->statusChange == ChangePower )
	{
		DrawFontText( ui->text, ui->powerPos, WHITE, &(ui->textFont) );
	}
}

void DrawPlayerUI( UI* ui )
{
	sprintf_s( ui->text, BUFSIZ, "Health : %.f", ui->targetStatus->health );
	DrawFontText( ui->text, ui->healthPos, WHITE, &(ui->textFont) );
	sprintf_s( ui->text, BUFSIZ, "angle : %d", ui->targetStatus->angle );
	DrawFontText( ui->text, ui->anglePos, WHITE, &(ui->textFont) );
	sprintf_s( ui->text, BUFSIZ, "Power : %d", ui->targetStatus->power );
	DrawFontText( ui->text, ui->powerPos, WHITE, &(ui->textFont) );
}

void DrawHealth( UI* ui )
{
	sprintf_s( ui->text, BUFSIZ, "Health : %.f", ui->targetStatus->health );
	DrawFontText( ui->text, ui->healthPos, WHITE, &(ui->textFont) );
}

void DestroyUI( UI* ui )
{
	DestroyFont( &(ui->textFont) );
}