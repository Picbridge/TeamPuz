#include "Debug.h"
#include "PuzApp.h"

static Uint8 alpha = 0;
static bool isFadingOut = false;

static GraphicComponent DigiLogo(&(App::GetAppInstance()->CAM.GetCamX()),&(App::GetAppInstance()->CAM.GetCamY()));

void Logo::Init()
{
	DEBUG_CREATE_CONSOLE();
	DEBUG_CLEAR();
	DEBUG_PRINT("This is Logo State");

	DigiLogo.LoadFromFile("DigiLogo.png");
}

void Logo::Update(float dt)
{
	if(App::GetAppInstance()->Input.IsTriggered(App::GetAppInstance()->Input.PUZ_ESCAPE))
		App::GetAppInstance()->StateMgr.ChangeNextState(App::GetAppInstance()->StateMgr.SHUTDOWN);

	if(App::GetAppInstance()->Input.IsTriggered(App::GetAppInstance()->Input.PUZ_L))
		App::GetAppInstance()->StateMgr.ChangeNextState(App::GetAppInstance()->StateMgr.LV1);

	App::GetAppInstance()->GFX.StartDraw();
//----------------------------Logo render
	DigiLogo.setAlpha(alpha);
	if(isFadingOut==false)
	{
		alpha+=5;
		if(alpha>=255)
			isFadingOut = true;
	}
	else
	{
		alpha-=5;
		if(alpha<=0)
			App::GetAppInstance()->StateMgr.ChangeNextState(App::GetAppInstance()->StateMgr.VILLAGE);
	}
	DigiLogo.Render();
//---------------------------------------
	App::GetAppInstance()->GFX.EndDraw();	
}

void Logo::Shutdown()
{
	DigiLogo.Free();
	DEBUG_DESTROY_CONSOLE();
}