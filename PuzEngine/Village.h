#ifndef VILLAGE_H
#define VILLAGE_H

#include "PuzApp.h"
#include "Math.h"

#define NUMOFNPC 3

class villageData
{
private:
	villageData(void) {}
	static villageData* m_instance;
	GraphicComponent* m_villageBG;
	GraphicComponent* m_character;

	Vector m_CharacterPos;
	Vector m_ChiefPos;
	Vector m_UncleJOEPos;
	Vector m_TroubleMakerTOMPos;

	bool Communication[NUMOFNPC];
	bool QuestClear[NUMOFNPC];
	int  m_QuestClearCount;
	
	/* If player talk with NPC, these will change */
	bool Stoptalking;
	bool keepTalking;

public:
	void DataInit(void);
	~villageData(void);

	/*communication*/
	int CommuCheck(void); // communication check
	int QuestClearCheck(void);

	void CommunicationTexture(void);
	void Talking(int i);

	bool GoToNextState(void);

	bool GetStoptalking(void) { return Stoptalking; }
	bool GetkeepTalking(void) { return keepTalking; }

	void CurrentSituation(void);
	/*Character*/
	float GetCharacterPosX(void) { return m_CharacterPos.m_x; }
	float GetCharacterPosY(void) { return m_CharacterPos.m_y; }
	void SetCharacterPos(float x, float y);
	/*Cheif*/
	float GetChiefPosX(void) { return m_ChiefPos.m_x; }
	float GetChiefPosY(void) { return m_ChiefPos.m_y; }
	void SetChiefPos(float x, float y);
	/* Uncle JOE */
	float GetUncleJOEPosX(void) { return m_UncleJOEPos.m_x; }
	float GetUncleJOEPosY(void) { return m_UncleJOEPos.m_y; }
	void SetUncleJOEPos(float x, float y);
	/* Trouble Maker TOM */
	float GetTroubleMakerTOMPosX(void) { return m_TroubleMakerTOMPos.m_x; }
	float GetTroubleMakerTOMPosY(void) { return m_TroubleMakerTOMPos.m_y; }
	void SetTroubleMakerTOMPos(float x, float y);

	GraphicComponent* GetBackground(void) { return m_villageBG; }
	GraphicComponent* GetCharacter(void) { return m_character; }

	GraphicComponent* m_cheif;
	GraphicComponent* m_uncleJOE;
	GraphicComponent* m_trubleMakerTOM;

	/*texture*/
	GraphicComponent* Hello;
	GraphicComponent* HI;
	GraphicComponent* Lastone;
	GraphicComponent* Notfinish;
	
	static villageData* GetInstance(void);
};

#endif /* VILLAGE_H */