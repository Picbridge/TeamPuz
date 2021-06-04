/******************************************************************************/
/*!
file    Lose.cpp
\author Seonghak Kim
\par    email: ksh1994kr@gmail.com
\par    GAM200
\par    Lose state
\date   2014/11/06

   This file will call if player loses this game.
*/
/******************************************************************************/
#include "Debug.h"
#include "PuzApp.h"
#include "Math.h"

static GraphicComponent LoseTexture(&(App::GetAppInstance()->CAM.GetCamX()),&(App::GetAppInstance()->CAM.GetCamY()));
static GraphicComponent Dog(&(App::GetAppInstance()->CAM.GetCamX()),&(App::GetAppInstance()->CAM.GetCamY()));

void Lose::Init()
{
	DEBUG_CREATE_CONSOLE();
	DEBUG_CLEAR();
	DEBUG_PRINT("This is Lose State");

	LoseTexture.LoadFromFile("");
	Dog.LoadFromFile("charDog.png");
}

void Lose::Update(float dt)
{
	if(App::GetAppInstance()->Input.IsTriggered(App::GetAppInstance()->Input.PUZ_ESCAPE))
		App::GetAppInstance()->StateMgr.ChangeNextState(App::GetAppInstance()->StateMgr.SHUTDOWN);

	if(App::GetAppInstance()->Input.IsTriggered(App::GetAppInstance()->Input.PUZ_M))
		App::GetAppInstance()->StateMgr.ChangeNextState(App::GetAppInstance()->StateMgr.MENU);

	App::GetAppInstance()->GFX.StartDraw();
	LoseTexture.Render(450,350);
	Dog.Render(1050,400);
	App::GetAppInstance()->GFX.EndDraw();
}

void Lose::Shutdown()
{
	LoseTexture.Free();
	Dog.Free();
	DEBUG_DESTROY_CONSOLE();
}