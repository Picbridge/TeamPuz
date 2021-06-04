#ifndef STAIR_H
#define STAIR_H

#include "Math.h"

class Stair
{
public:
	void Init(void);

	void SetStairPos(int i, float x, float y);
	Vector GetStairPos(int i) { return m_stairPos[i]; }
	float GetStairPosX(int i) { return m_stairPos[i].m_x; }
	float GetStairPosY(int i) { return m_stairPos[i].m_y; }

	bool StairCharacterCollisionCheck(int i);

	void SetNewCollision(void);
	void SetRotatedStairData(void);

private:
	Vector m_stairPos[2];
	float m_stairCollisionWidth;
	float m_stairCollisionHeight;
};

#endif /* STAIR_H */