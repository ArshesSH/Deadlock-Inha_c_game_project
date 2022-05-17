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
		sprintf_s( ui->text, BUFSIZ, "Health : %3.f", ui->targetStatus->health );
	}
	else if ( ui->targetStatus->statusChange == ChangeAngle )
	{
		sprintf_s( ui->text, BUFSIZ, "angle : %3d", ui->targetStatus->angle );
	}
	else if ( ui->targetStatus->statusChange == ChangePower )
	{
		sprintf_s( ui->text, BUFSIZ, "Power : %3d", ui->targetStatus->power );
	}

}

void DrawUI( UI* ui )
{
	if ( ui->targetStatus->statusChange == ChangeHealth )
	{
		DeleteRect( ui->healthRect );
		DrawFontText( ui->text, ui->healthPos, WHITE, &(ui->textFont) );
		ChangeStatusState( ui->targetStatus, NoChange );
	}
	else if ( ui->targetStatus->statusChange == ChangeAngle )
	{
		DeleteRect( ui->angleRect );
		DrawFontText( ui->text, ui->anglePos, WHITE, &(ui->textFont) );
		ChangeStatusState( ui->targetStatus, NoChange );
	}
	else if ( ui->targetStatus->statusChange == ChangePower )
	{
		DeleteRect( ui->powerRect );
		DrawFontText( ui->text, ui->powerPos, WHITE, &(ui->textFont) );
		ChangeStatusState( ui->targetStatus, NoChange );
	}
}

void DrawPlayerUI( UI* ui )
{
	sprintf_s( ui->text, BUFSIZ, "Health : %3.f", ui->targetStatus->health );
	DrawFontText( ui->text, ui->healthPos, WHITE, &(ui->textFont) );
	ui->healthRect = ui->textFont.textRect;
	sprintf_s( ui->text, BUFSIZ, "angle : %3d", ui->targetStatus->angle );
	DrawFontText( ui->text, ui->anglePos, WHITE, &(ui->textFont) );
	ui->angleRect = ui->textFont.textRect;
	sprintf_s( ui->text, BUFSIZ, "Power : %3d", ui->targetStatus->power );
	DrawFontText( ui->text, ui->powerPos, WHITE, &(ui->textFont) );
	ui->powerRect = ui->textFont.textRect;
}

void DrawHealth( UI* ui )
{
	sprintf_s( ui->text, BUFSIZ, "Health : %3.f", ui->targetStatus->health );
	DrawFontText( ui->text, ui->healthPos, WHITE, &(ui->textFont) );
	ui->healthRect = ui->textFont.textRect;
}

void DestroyUI( UI* ui )
{
	DestroyFont( &(ui->textFont) );
}