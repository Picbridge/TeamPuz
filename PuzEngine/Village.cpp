#include "Village.h"

static int camFirstLocationX = App::GetAppInstance()->CAM.GetCamX();
static int camFirstLocationY = App::GetAppInstance()->CAM.GetCamY();

villageData* villageData::m_instance = NULL;

villageData* villageData::GetInstance(void)
{
	if(!m_instance)
	{
		m_instance = new villageData;
	}

	return m_instance;
}

void villageData::DataInit(void)
{
	int* CAM_X = &(App::GetAppInstance()->CAM.GetCamX());
	int* CAM_Y = &(App::GetAppInstance()->CAM.GetCamY());

	m_villageBG      = new GraphicComponent(CAM_X, CAM_Y);
	m_character      = new GraphicComponent(CAM_X, CAM_Y);
	m_cheif          = new GraphicComponent(CAM_X, CAM_Y);
	m_uncleJOE       = new GraphicComponent(CAM_X, CAM_Y);
	m_trubleMakerTOM = new GraphicComponent(CAM_X, CAM_Y);

	/*texture*/
	Hello     = new GraphicComponent;
	HI        = new GraphicComponent;
	Lastone   = new GraphicComponent;
	Notfinish = new GraphicComponent;

	m_CharacterPos.m_x = 0;
	m_CharacterPos.m_y = 0;

	villageData::GetInstance()->SetChiefPos(600.f,300.f);
	villageData::GetInstance()->SetUncleJOEPos(300.f, 100.f);
	villageData::GetInstance()->SetTroubleMakerTOMPos(100.f, -200.f);

	for(int i = 0; i < NUMOFNPC; i++)
	{
		Communication[i] = false;
	}
	m_QuestClearCount = 0;
	Stoptalking = false;
	keepTalking = false;

	/*App::GetAppInstance()->CAM.SetCamX(villageData::GetInstance()->GetCharacterPosX());
	App::GetAppInstance()->CAM.SetCamY(villageData::GetInstance()->GetCharacterPosY());*/
}

villageData::~villageData(void)
{
	if(m_instance)
	{
		delete m_instance;
	}

	delete m_villageBG;
	delete m_character;
	delete m_cheif;
	delete m_uncleJOE;
	delete m_trubleMakerTOM;

	/*texture*/
	delete Hello;
	delete HI;
	delete Lastone;
	delete Notfinish;
}

int villageData::CommuCheck(void)
{
	for(int i = 0; i < NUMOFNPC; ++i)
	{
		if(Communication[i] == true)
			return i;
	}
	return -1;
}

int villageData::QuestClearCheck(void)
{
	for(int i = 0; i < NUMOFNPC; ++i)
	{
		if(QuestClear[i] != true)
			return i;
	}
	return -1;
}

void villageData::CommunicationTexture(void)
{
	int i;
	for(i = 0; i < NUMOFNPC; ++i)
	{
		if(Communication[i] == true)
			break;
	}

	switch(i)
	{
	case 0:
		{
			villageData::GetInstance()->Talking(i);
			break;
		}
	case 1:
		{
			villageData::GetInstance()->Talking(i);
			break;
		}
	case 2:
		{
			villageData::GetInstance()->Talking(i);
			break;
		}
	default:
		break;
	}
}

void villageData::Talking(int i)
{
	if(Stoptalking == false && keepTalking == false)
	{
		if(App::GetAppInstance()->Input.IsTriggered(App::GetAppInstance()->Input.PUZ_C))
			keepTalking = true;
	}
	else if(Stoptalking == false && keepTalking == true)
	{
		if(App::GetAppInstance()->Input.IsTriggered(App::GetAppInstance()->Input.PUZ_C))
			Stoptalking = true;
	}
	else if(Stoptalking == true)
	{
		Communication[i] = false;
		Stoptalking      = false;
		keepTalking      = false;
		QuestClear[i]    = true;
		++m_QuestClearCount;
	}
}

bool villageData::GoToNextState(void)
{
	if(QuestClearCheck() == -1 && m_QuestClearCount >= NUMOFNPC)
		return true;
	else
		return false;
}

void villageData::CurrentSituation(void)
{
	if(IsIntersecting(m_CharacterPos, 10, 10, m_ChiefPos, 10, 10)
		&& App::GetAppInstance()->Input.IsPressed(App::GetAppInstance()->Input.PUZ_Z))
			Communication[0] = true;

	else if(IsIntersecting(m_CharacterPos, 10, 10, m_UncleJOEPos, 10, 10)
		&& App::GetAppInstance()->Input.IsPressed(App::GetAppInstance()->Input.PUZ_Z))
			Communication[1] = true;

	else if(IsIntersecting(m_CharacterPos, 10, 10, m_TroubleMakerTOMPos, 10, 10)
		&& App::GetAppInstance()->Input.IsPressed(App::GetAppInstance()->Input.PUZ_Z))
			Communication[2] = true;
	
	/*texture*/
	villageData::GetInstance()->CommunicationTexture();
}

void villageData::SetCharacterPos(float x, float y)
{
	m_CharacterPos.m_x = x;
	m_CharacterPos.m_y = y;
}

void villageData::SetChiefPos(float x, float y)
{
	m_ChiefPos.m_x = x;
	m_ChiefPos.m_y = y;
}

void villageData::SetUncleJOEPos(float x, float y)
{
	m_UncleJOEPos.m_x = x;
	m_UncleJOEPos.m_y = y;
}

void villageData::SetTroubleMakerTOMPos(float x, float y)
{
	m_TroubleMakerTOMPos.m_x = x;
	m_TroubleMakerTOMPos.m_y = y;
}

void Village::Init()
{
	DEBUG_CREATE_CONSOLE();
	DEBUG_CLEAR();
	DEBUG_PRINT("This is Village State");

	villageData::GetInstance()->DataInit();
	villageData::GetInstance()->GetBackground()->LoadFromFile("VillageBG.png");
	villageData::GetInstance()->GetCharacter()->LoadFromFile("lever.png");
	villageData::GetInstance()->m_cheif->LoadFromFile("lever.png");
	villageData::GetInstance()->m_uncleJOE->LoadFromFile("lever.png");
	villageData::GetInstance()->m_trubleMakerTOM->LoadFromFile("lever.png");

	/*texture*/
	villageData::GetInstance()->Hello->LoadFromFile("Texture//Hello.png");
	villageData::GetInstance()->HI->LoadFromFile("Texture//HI.png");
	villageData::GetInstance()->Lastone->LoadFromFile("Texture//Lastone.png");
	villageData::GetInstance()->Notfinish->LoadFromFile("Texture//Notfinish.png");
	
}

void Village::Update(float dt)
{
	villageData::GetInstance()->CurrentSituation();

	if(villageData::GetInstance()->CommuCheck() == -1)
	{
		/*Input : Move up*/
		if (App::GetAppInstance()->Input.IsPressed(App::GetAppInstance()->Input.PUZ_ARROW_UP))
		{
			/*Update character image depend on direction*/
			villageData::GetInstance()->SetCharacterPos(villageData::GetInstance()->GetCharacterPosX(), villageData::GetInstance()->GetCharacterPosY() - 10);
			//App::GetAppInstance()->CAM.SetCamX(App::GetAppInstance()->CAM.GetCamX());
			//App::GetAppInstance()->CAM.SetCamY(App::GetAppInstance()->CAM.GetCamY() - 5);
		}
		/*Input : Move down*/
		else if(App::GetAppInstance()->Input.IsPressed(App::GetAppInstance()->Input.PUZ_ARROW_DOWN))
		{
			/*Update character image depend on direction*/
			villageData::GetInstance()->SetCharacterPos(villageData::GetInstance()->GetCharacterPosX(), villageData::GetInstance()->GetCharacterPosY() + 10);
			//App::GetAppInstance()->CAM.SetCamX(App::GetAppInstance()->CAM.GetCamX());
			//App::GetAppInstance()->CAM.SetCamY(App::GetAppInstance()->CAM.GetCamY() + 5);
		}
		/*Input : Move left*/
		else if(App::GetAppInstance()->Input.IsPressed(App::GetAppInstance()->Input.PUZ_ARROW_LEFT))
		{
			/*Update character image depend on direction*/
			villageData::GetInstance()->SetCharacterPos(villageData::GetInstance()->GetCharacterPosX() - 10, villageData::GetInstance()->GetCharacterPosY());
			//App::GetAppInstance()->CAM.SetCamX(App::GetAppInstance()->CAM.GetCamX() - 5);
			//App::GetAppInstance()->CAM.SetCamY(App::GetAppInstance()->CAM.GetCamY());
		}
		/*Input : Move right*/
		else if(App::GetAppInstance()->Input.IsPressed(App::GetAppInstance()->Input.PUZ_ARROW_RIGHT))
		{
			/*Update character image depend on direction*/
			villageData::GetInstance()->SetCharacterPos(villageData::GetInstance()->GetCharacterPosX() + 10, villageData::GetInstance()->GetCharacterPosY());
			//App::GetAppInstance()->CAM.SetCamX(App::GetAppInstance()->CAM.GetCamX() + 5);
			//App::GetAppInstance()->CAM.SetCamY(App::GetAppInstance()->CAM.GetCamY());
		}
	}

	if(App::GetAppInstance()->Input.IsTriggered(App::GetAppInstance()->Input.PUZ_ESCAPE))
		App::GetAppInstance()->StateMgr.ChangeNextState(App::GetAppInstance()->StateMgr.SHUTDOWN);

	if(App::GetAppInstance()->Input.IsTriggered(App::GetAppInstance()->Input.PUZ_R))
		App::GetAppInstance()->StateMgr.SetRestart(true);

	if(villageData::GetInstance()->GoToNextState() == true
		&& App::GetAppInstance()->Input.IsTriggered(App::GetAppInstance()->Input.PUZ_N))
		App::GetAppInstance()->StateMgr.ChangeNextState(App::GetAppInstance()->StateMgr.MENU);

	App::GetAppInstance()->CAM.SetCharToCenter(villageData::GetInstance()->GetCharacterPosX(),villageData::GetInstance()->GetCharacterPosY(),App::GetWidth(),App::GetHeight());

	App::GetAppInstance()->GFX.StartDraw();

	villageData::GetInstance()->GetBackground()->Render(0,0,NULL,5,5);
	villageData::GetInstance()->GetCharacter()->Render(/*App::GetAppInstance()->CAM.GetCamX(), App::GetAppInstance()->CAM.GetCamY());*/villageData::GetInstance()->GetCharacterPosX(), villageData::GetInstance()->GetCharacterPosY());
	villageData::GetInstance()->m_cheif->Render(villageData::GetInstance()->GetChiefPosX(), villageData::GetInstance()->GetChiefPosY(), NULL);
	villageData::GetInstance()->m_uncleJOE->Render(villageData::GetInstance()->GetUncleJOEPosX(), villageData::GetInstance()->GetUncleJOEPosY(), NULL);
	villageData::GetInstance()->m_trubleMakerTOM->Render(villageData::GetInstance()->GetTroubleMakerTOMPosX(), villageData::GetInstance()->GetTroubleMakerTOMPosY(), NULL);

	if(villageData::GetInstance()->CommuCheck() == 0)
	{
		if(villageData::GetInstance()->GetStoptalking() == false 
			&& villageData::GetInstance()->GetkeepTalking() == false)
			villageData::GetInstance()->HI->Render(640,600);

		else if(villageData::GetInstance()->GetStoptalking() == false 
			&& villageData::GetInstance()->GetkeepTalking() == true)
			villageData::GetInstance()->Hello->Render(640,600);
	}

	else if(villageData::GetInstance()->CommuCheck() == 1)
	{
		if(villageData::GetInstance()->GetStoptalking() == false 
			&& villageData::GetInstance()->GetkeepTalking() == false)
			villageData::GetInstance()->Hello->Render(640,600);

		else if(villageData::GetInstance()->GetStoptalking() == false 
			&& villageData::GetInstance()->GetkeepTalking() == true)
			villageData::GetInstance()->HI->Render(640,600);
	}

	else if(villageData::GetInstance()->CommuCheck() == 2)
	{
		if(villageData::GetInstance()->GetStoptalking() == false 
			&& villageData::GetInstance()->GetkeepTalking() == false)
			villageData::GetInstance()->Hello->Render(640,600);

		else if(villageData::GetInstance()->GetStoptalking() == false 
			&& villageData::GetInstance()->GetkeepTalking() == true)
			villageData::GetInstance()->Lastone->Render(640,600);
	}

	if(villageData::GetInstance()->GoToNextState() == false 
		&& App::GetAppInstance()->Input.IsTriggered(App::GetAppInstance()->Input.PUZ_N))
		villageData::GetInstance()->Notfinish->Render(640,600);

	App::GetAppInstance()->GFX.EndDraw();
}

void Village::Shutdown()
{
	DEBUG_DESTROY_CONSOLE();

	villageData::GetInstance()->GetBackground()->Free();
	villageData::GetInstance()->GetCharacter()->Free();
	villageData::GetInstance()->m_cheif->Free();
	villageData::GetInstance()->m_uncleJOE->Free();
	villageData::GetInstance()->m_trubleMakerTOM->Free();

	/*texture*/
	villageData::GetInstance()->Hello->Free();
	villageData::GetInstance()->HI->Free();
	villageData::GetInstance()->Lastone->Free();
	villageData::GetInstance()->Notfinish->Free();

	App::GetAppInstance()->CAM.SetCamX(camFirstLocationX);
	App::GetAppInstance()->CAM.SetCamY(camFirstLocationY);
}