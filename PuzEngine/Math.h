/******************************************************************************/
/*!
\file   Math.h
\author Taehoon Kwon
\par    email: kth2242\@gmail.com
\par    class: GAM200S14KR
\par    Team name : Puz
\par    Project name : Detect Dog
\brief  
This file contains basic mathematical functions.

\copyright 
All content © 2014 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef MATH_H
#define MATH_H

#include <math.h>

#define HALF 0.5f
#define PI 3.1415926535897932384626433832795f

class Vector
{
public:
	void Add (const Vector& vec);
	void Sub (const Vector& vec);
	void Scale (float Sx, float Sy);
	float DotProduct (const Vector& vec) const;
	float GetLength (void) const;
	void Normalize (void);	

	friend float GetDistancePointPoint (const Vector& vec1, const Vector& vec2);
	friend float GetDistancePointLine (const Vector& vec1, const Vector& lineStart, const Vector& lineEnd);
	friend bool IsIntersecting (const Vector& vec1, float obj1Sx, float obj1Sy, const Vector& vec2, float obj2Sx, float obj2Sy);

	friend float DegreeToRadian(float degrees);
	friend float RadianToDegree(float radians);

public:
	//Public Data
	float m_x;
	float m_y;
};

#endif /*MATH_H*/