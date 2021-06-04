/******************************************************************************/
/*!
file    Win.cpp
\author Seonghak Kim
\par    email: ksh1994kr@gmail.com
\par    GAM200
\par    Win state
\date   2014/11/06

   This file will call if player wins this game.
*/
/******************************************************************************/
#include "Debug.h"
#include "PuzApp.h"
#include "Math.h"

static GraphicComponent WinTexture(&(App::GetAppInstance()->CAM.GetCamX()),&(App::GetAppInstance()->CAM.GetCamY()));

void Win::Init()
{
	DEBUG_CREATE_CONSOLE();
	DEBUG_CLEAR();
	DEBUG_PRINT("This is Win State");

	WinTexture.LoadFromFile("Win.png");
}

void Win::Update(float dt)
{
	if(App::GetAppInstance()->Input.IsTriggered(App::GetAppInstance()->Input.PUZ_ESCAPE))
		App::GetAppInstance()->StateMgr.ChangeNextState(App::GetAppInstance()->StateMgr.SHUTDOWN);

	if(App::GetAppInstance()->Input.IsTriggered(App::GetAppInstance()->Input.PUZ_M))
		App::GetAppInstance()->StateMgr.ChangeNextState(App::GetAppInstance()->StateMgr.MENU);

	App::GetAppInstance()->GFX.StartDraw();
	WinTexture.Render(650,400);
	App::GetAppInstance()->GFX.EndDraw();
}

void Win::Shutdown()
{
	WinTexture.Free();
	DEBUG_DESTROY_CONSOLE();
}