#ifndef LV1_H
#define LV1_H

#include "Math.h"
#include "Physics.h"
#include "GraphicComponent.h"
#include "Tile.h"
#include "PuzApp.h"

class Level1Data
{
public:
	void DataInit(void);
	~Level1Data(void);
	static Level1Data* GetInstance(void);

	void SetMousePos(float x, float y);
	Vector GetMousePos(void) { return m_Mouse; }

public:
	CollisionComponent* collisionData[NUM_OF_TILE];
	GraphicComponent* graphicData[NUM_OF_TILE];
	int m_Lv1BGM;

	GraphicComponent* Background;
	GraphicComponent* character;
	GraphicComponent* curtain;
	GraphicComponent* Downstair;
	GraphicComponent* Upstair;
	GraphicComponent* Key;
	GraphicComponent* leverHUDTest;

private:
	Level1Data(void) {}
	static Level1Data* m_instance;

private:
	Vector m_Mouse;
};

#endif /* LV1_H */
