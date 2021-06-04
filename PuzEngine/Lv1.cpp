#include "Lv1.h"

#include "Debug.h"
#include "PuzApp.h"
#include "Tile.h"
#include "Physics.h"
#include "Character.h"
#include "TileFactory.h"
#include "Stair.h"
#include "Lever.h"

#define CHARACTER_ANIMATION_FRAME 4
extern enum fade{FADEIN,FADEOUT,NONE};

static Uint8 alpha = 0;
extern fade isFading = NONE;

extern TileData tileData;
extern CharacterData characterData;
extern LeverData leverData;

TileFactory factory;
Stair StairData;

static bool cPressed = false;
extern bool CamYGoingUp = true;
static int camFirstLocation = App::GetAppInstance()->CAM.GetCamY();
static int currentCharacterFrame = 0;

static PuzAnimate CharacterAnime[4];

Level1Data* Level1Data::m_instance = NULL;

Level1Data* Level1Data::GetInstance(void)
{
	if(!m_instance)
	{
		m_instance = new Level1Data;
	}

	return m_instance;
}

void Level1Data::DataInit(void)
{
	TileEntity* temp[NUM_OF_TILE];
	
	temp[0] = factory.GetEntityList()["FIR_First Tile"];
	temp[1] = factory.GetEntityList()["FIR_Second Tile"];
	temp[2] = factory.GetEntityList()["FIR_Third Tile"];
	temp[3] = factory.GetEntityList()["FIR_Fourth Tile"];
	temp[4] = factory.GetEntityList()["FIR_Fifth Tile"];
	temp[5] = factory.GetEntityList()["FIR_Sixth Tile"];
	temp[6] = factory.GetEntityList()["FIR_Seventh Tile"];
	temp[7] = factory.GetEntityList()["FIR_Eighth Tile"];
	temp[8] = factory.GetEntityList()["FIR_Nineth Tile"];

	temp[9]  = factory.GetEntityList()["SEC_First Tile"];
	temp[10] = factory.GetEntityList()["SEC_Second Tile"];
	temp[11] = factory.GetEntityList()["SEC_Third Tile"];
	temp[12] = factory.GetEntityList()["SEC_Fourth Tile"];
	temp[13] = factory.GetEntityList()["SEC_Fifth Tile"];
	temp[14] = factory.GetEntityList()["SEC_Sixth Tile"];
	temp[15] = factory.GetEntityList()["SEC_Seventh Tile"];
	temp[16] = factory.GetEntityList()["SEC_Eighth Tile"];
	temp[17] = factory.GetEntityList()["SEC_Nineth Tile"];

	for(int i = 0; i < NUM_OF_TILE; ++i)
	{
		if(temp[i] != NULL)
		{
			collisionData[i] = dynamic_cast<CollisionComponent*>(temp[i]->getComponent("Collision Type"));
			graphicData[i] = dynamic_cast<GraphicComponent*>(temp[i]->getComponent("Graphic Type"));
		}
	}

	int* CAM_X = &(App::GetAppInstance()->CAM.GetCamX());
	int* CAM_Y = &(App::GetAppInstance()->CAM.GetCamY());

	Background   = new GraphicComponent(CAM_X, CAM_Y);
	character    = new GraphicComponent(CAM_X, CAM_Y);
	curtain      = new GraphicComponent(CAM_X, CAM_Y);
	Downstair    = new GraphicComponent(CAM_X, CAM_Y);
	Upstair      = new GraphicComponent(CAM_X, CAM_Y);
	Key          = new GraphicComponent(CAM_X, CAM_Y);
	leverHUDTest = new GraphicComponent;
}

Level1Data::~Level1Data(void)
{
	if(m_instance)
	{
		delete m_instance;
	}

	delete Background;
	delete character; 
	delete curtain;  
	delete Downstair;
	delete Upstair;  
	delete Key;    
	delete leverHUDTest;
}

void Level1Data::SetMousePos(float x, float y)
{
	m_Mouse.m_x = x;
	m_Mouse.m_y = y;
}

void Lv1::Init()
{
	DEBUG_CREATE_CONSOLE();
	DEBUG_CLEAR();
	DEBUG_PRINT("This is Lv1 State");

	tileData.Init();

	leverData.Init();

	factory.registerCreator();

	factory.LoadEntity("Level1.ini");

	factory.TileInit();

	StairData.Init();

	characterData.Init();

	Level1Data::GetInstance()->DataInit();

	Level1Data::GetInstance()->Background->LoadFromFile("Background.png");
	Level1Data::GetInstance()->character->LoadFromFile("char_down.png");
	Level1Data::GetInstance()->curtain->LoadFromFile("MenuBackground.png");
	Level1Data::GetInstance()->Downstair->LoadFromFile("Downstair.png");
	Level1Data::GetInstance()->Upstair->LoadFromFile("Upstair.png");
	Level1Data::GetInstance()->Key->LoadFromFile("Key.png");
	Level1Data::GetInstance()->leverHUDTest->LoadFromFile("lever.png");
	//Set sprite clips
	App::GetAppInstance()->GFX.Animation(CharacterAnime,4,Level1Data::GetInstance()->character->GetWidth(),Level1Data::GetInstance()->character->GetHeight());

	Level1Data::GetInstance()->m_Lv1BGM = App::GetAppInstance()->PuzSound.LoadLoop("BGM.mp3"); // This code should go into load state
	
	App::GetAppInstance()->PuzSound.Play(Level1Data::GetInstance()->m_Lv1BGM); // This code should go into init state
}

void Lv1::Update(float dt)
{
	DEBUG_CLEAR();
	DEBUG_PRINT("Frame : %d\n", currentCharacterFrame);
	DEBUG_PRINT("Mouse X, Mouse Y : %f, %f\n", Level1Data::GetInstance()->GetMousePos().m_x, Level1Data::GetInstance()->GetMousePos().m_y);
	//DEBUG_PRINT("Mouse Collision Check : %d\n", collisionData->MouseCollisionCheck());
	//DEBUG_PRINT("Shrinked Check : %d\n", tileData.GetShrinkedInfo());
	
	DEBUG_PRINT("Character Position X Check : %f\n", characterData.GetCharPosX());
	DEBUG_PRINT("CharX : %f\n", characterData.GetCharPosX());
	DEBUG_PRINT("CharY : %f\n", characterData.GetCharPosY());

	if(App::GetAppInstance()->Input.IsTriggered(App::GetAppInstance()->Input.PUZ_S))
		App::GetAppInstance()->PuzSound.PauseAndResume(Level1Data::GetInstance()->m_Lv1BGM);

	if(App::GetAppInstance()->Input.IsTriggered(App::GetAppInstance()->Input.PUZ_ESCAPE))
		App::GetAppInstance()->StateMgr.ChangeNextState(App::GetAppInstance()->StateMgr.SHUTDOWN);

	if(App::GetAppInstance()->Input.IsTriggered(App::GetAppInstance()->Input.PUZ_M))
		App::GetAppInstance()->StateMgr.ChangeNextState(App::GetAppInstance()->StateMgr.MENU);

	if(App::GetAppInstance()->Input.IsTriggered(App::GetAppInstance()->Input.PUZ_R))
		App::GetAppInstance()->StateMgr.SetRestart(true);

	if(App::GetAppInstance()->Input.IsTriggered(App::GetAppInstance()->Input.PUZ_C))
	{
		if(cPressed == false)
		isFading = FADEIN;

		cPressed =true;
	}
	
	characterData.Update();

	tileData.Update();
	
	clip currentClip = &CharacterAnime[currentCharacterFrame];

	Level1Data::GetInstance()->curtain->setAlpha(alpha);
	if(isFading==FADEIN)
	{
		if(App::GetAppInstance()->CAM.GetCamY()<=App::GetAppInstance()->sdlWndInfo.GetwindowHeight()&&CamYGoingUp==true)
		{
			App::GetAppInstance()->CAM.SetCamY(App::GetAppInstance()->CAM.GetCamY() + App::GetAppInstance()->sdlWndInfo.GetwindowHeight()/34);
		}
		else if(CamYGoingUp == false)
		{
			App::GetAppInstance()->CAM.SetCamY(App::GetAppInstance()->CAM.GetCamY() - App::GetAppInstance()->sdlWndInfo.GetwindowHeight()/34);
		}
		alpha+=15;
		if(alpha>=255)
		{
			isFading = FADEOUT;
		}
	}
	else if(isFading==FADEOUT)
	{
		if(App::GetAppInstance()->CAM.GetCamY()<=App::GetAppInstance()->sdlWndInfo.GetwindowHeight()&&CamYGoingUp==true)
			App::GetAppInstance()->CAM.SetCamY(App::GetAppInstance()->CAM.GetCamY() + App::GetAppInstance()->sdlWndInfo.GetwindowHeight()/34);
		else if(CamYGoingUp == false)
		{
			App::GetAppInstance()->CAM.SetCamY(App::GetAppInstance()->CAM.GetCamY() - App::GetAppInstance()->sdlWndInfo.GetwindowHeight()/34);
			
		}
		alpha-=15;
		if(alpha<=0)
		{
			
			isFading = NONE;
			if(App::GetAppInstance()->CAM.GetCamY()!=camFirstLocation)
			{
				CamYGoingUp = false;
			}
			else if(App::GetAppInstance()->CAM.GetCamY()==camFirstLocation)
			{
				CamYGoingUp=true;
			}
			cPressed = false;
		}
	}
	
	if((characterData.GetCharPosX() < tileData.GetTilePosX(14) + 15.f)
	 &&(characterData.GetCharPosX() > tileData.GetTilePosX(14) - 15.f)
	 &&(characterData.GetCharPosY() < tileData.GetTilePosY(14) + 15.f)
	 &&(characterData.GetCharPosY() > tileData.GetTilePosY(14) - 15.f))
	{
		App::GetAppInstance()->StateMgr.ChangeNextState(App::GetAppInstance()->StateMgr.WIN);
	}
	
	//--------------------------------------
	App::GetAppInstance()->GFX.StartDraw();

	Level1Data::GetInstance()->Background->Render();
	
	Level1Data::GetInstance()->graphicData[0]->Render(tileData.GetTilePosX(0), tileData.GetTilePosY(0), 0, tileData.GetTileScaleX(0), tileData.GetTileScaleY(0), tileData.GetTileAngle(0));
	Level1Data::GetInstance()->graphicData[1]->Render(tileData.GetTilePosX(1), tileData.GetTilePosY(1), 0, tileData.GetTileScaleX(1), tileData.GetTileScaleY(1), tileData.GetTileAngle(1));
	Level1Data::GetInstance()->graphicData[2]->Render(tileData.GetTilePosX(2), tileData.GetTilePosY(2), 0, tileData.GetTileScaleX(2), tileData.GetTileScaleY(2), tileData.GetTileAngle(2));
	Level1Data::GetInstance()->graphicData[3]->Render(tileData.GetTilePosX(3), tileData.GetTilePosY(3), 0, tileData.GetTileScaleX(3), tileData.GetTileScaleY(3), tileData.GetTileAngle(3));
	Level1Data::GetInstance()->graphicData[4]->Render(tileData.GetTilePosX(4), tileData.GetTilePosY(4), 0, tileData.GetTileScaleX(4), tileData.GetTileScaleY(4), tileData.GetTileAngle(4));
	Level1Data::GetInstance()->graphicData[5]->Render(tileData.GetTilePosX(5), tileData.GetTilePosY(5), 0, tileData.GetTileScaleX(5), tileData.GetTileScaleY(5), tileData.GetTileAngle(5));
	Level1Data::GetInstance()->graphicData[6]->Render(tileData.GetTilePosX(6), tileData.GetTilePosY(6), 0, tileData.GetTileScaleX(6), tileData.GetTileScaleY(6), tileData.GetTileAngle(6));
	Level1Data::GetInstance()->graphicData[7]->Render(tileData.GetTilePosX(7), tileData.GetTilePosY(7), 0, tileData.GetTileScaleX(7), tileData.GetTileScaleY(7), tileData.GetTileAngle(7));
	Level1Data::GetInstance()->graphicData[8]->Render(tileData.GetTilePosX(8), tileData.GetTilePosY(8), 0, tileData.GetTileScaleX(8), tileData.GetTileScaleY(8), tileData.GetTileAngle(8));
	
	Level1Data::GetInstance()->graphicData[9] ->Render(tileData.GetTilePosX(9),  tileData.GetTilePosY(9),  0, tileData.GetTileScaleX(9),  tileData.GetTileScaleY(9),  tileData.GetTileAngle(9));
	Level1Data::GetInstance()->graphicData[10]->Render(tileData.GetTilePosX(10), tileData.GetTilePosY(10), 0, tileData.GetTileScaleX(10), tileData.GetTileScaleY(10), tileData.GetTileAngle(10));
	Level1Data::GetInstance()->graphicData[11]->Render(tileData.GetTilePosX(11), tileData.GetTilePosY(11), 0, tileData.GetTileScaleX(11), tileData.GetTileScaleY(11), tileData.GetTileAngle(11));
	Level1Data::GetInstance()->graphicData[12]->Render(tileData.GetTilePosX(12), tileData.GetTilePosY(12), 0, tileData.GetTileScaleX(12), tileData.GetTileScaleY(12), tileData.GetTileAngle(12));
	Level1Data::GetInstance()->graphicData[13]->Render(tileData.GetTilePosX(13), tileData.GetTilePosY(13), 0, tileData.GetTileScaleX(13), tileData.GetTileScaleY(13), tileData.GetTileAngle(13));
	Level1Data::GetInstance()->graphicData[14]->Render(tileData.GetTilePosX(14), tileData.GetTilePosY(14), 0, tileData.GetTileScaleX(14), tileData.GetTileScaleY(14), tileData.GetTileAngle(14));
	Level1Data::GetInstance()->graphicData[15]->Render(tileData.GetTilePosX(15), tileData.GetTilePosY(15), 0, tileData.GetTileScaleX(15), tileData.GetTileScaleY(15), tileData.GetTileAngle(15));
	Level1Data::GetInstance()->graphicData[16]->Render(tileData.GetTilePosX(16), tileData.GetTilePosY(16), 0, tileData.GetTileScaleX(16), tileData.GetTileScaleY(16), tileData.GetTileAngle(16));
	Level1Data::GetInstance()->graphicData[17]->Render(tileData.GetTilePosX(17), tileData.GetTilePosY(17), 0, tileData.GetTileScaleX(17), tileData.GetTileScaleY(17), tileData.GetTileAngle(17));

	//GFX.PuzGraphicsSetViewport(0,0,sdlWndInfo.GetwindowWidth()/2,sdlWndInfo.GetwindowHeight()/2);
	
	Level1Data::GetInstance()->Downstair->Render(tileData.GetTilePosX(8),  tileData.GetTilePosY(8),  0, tileData.GetTileScaleX(8),  tileData.GetTileScaleY(8),  tileData.GetTileAngle(8));
	Level1Data::GetInstance()->Upstair->Render  (tileData.GetTilePosX(17), tileData.GetTilePosY(17), 0, tileData.GetTileScaleX(17), tileData.GetTileScaleY(17), tileData.GetTileAngle(17));
	
	Level1Data::GetInstance()->character->Render(characterData.GetCharPosX(), characterData.GetCharPosY(), currentClip);

	Level1Data::GetInstance()->Key->Render(tileData.GetTilePosX(14), tileData.GetTilePosY(14), 0, tileData.GetTileScaleX(14), tileData.GetTileScaleY(14), tileData.GetTileAngle(14));
	
	Level1Data::GetInstance()->leverHUDTest->Render(leverData.GetPos().m_x,leverData.GetPos().m_y,0,2,2);
	
	if(characterData.GetWalkingInfo() == true)
	{
		++currentCharacterFrame;
		characterData.GetWalkingInfo() == false;
	}
	if(currentCharacterFrame==CHARACTER_ANIMATION_FRAME)
	{
		currentCharacterFrame = 0;
	}
	Level1Data::GetInstance()->curtain->Render();
//-----------------------------------
	App::GetAppInstance()->GFX.EndDraw();
	App::GetAppInstance()->PuzSound.Update(); // This code should go into update state
}

void Lv1::Shutdown()
{
	Level1Data::GetInstance()->Background->Free();
	Level1Data::GetInstance()->character->Free();
	Level1Data::GetInstance()->curtain->Free();
	Level1Data::GetInstance()->Downstair->Free();
	Level1Data::GetInstance()->Upstair->Free();
	Level1Data::GetInstance()->Key->Free();
	Level1Data::GetInstance()->leverHUDTest->Free();
	for(int i = 0; i < NUM_OF_TILE; ++i)
		Level1Data::GetInstance()->graphicData[i]->Free();
	
	factory.ReleaseFactory();

	App::GetAppInstance()->CAM.SetCamY(camFirstLocation);
	CamYGoingUp = true;

	DEBUG_DESTROY_CONSOLE();

	App::GetAppInstance()->PuzSound.Stop(Level1Data::GetInstance()->m_Lv1BGM);    // This code should go into shutdown state
	App::GetAppInstance()->PuzSound.Release(); // This code should go into unload state
}