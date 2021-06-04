#include "Debug.h"
#include "PuzApp.h"

void ShutDown::Init()
{
}

void ShutDown::Update(float dt)
{
	App::GetAppInstance()->StateMgr.StateMgrSetQuit(true);
}

void ShutDown::Shutdown()
{
}