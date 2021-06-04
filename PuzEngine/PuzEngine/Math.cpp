/******************************************************************************/
/*!
\file   Math.cpp
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
#include "Math.h"
/******************************************************************************/
/*!
Change degree in terms of radian.

\param degrees
What you want to change

\return float
Result
*/
/******************************************************************************/
float DegreeToRadian(float degrees)
{
	return (PI / 180.f) * degrees;
}
/******************************************************************************/
/*!
Change radian in terms of degree.

\param radians
What you want to change

\return float
Result
*/
/******************************************************************************/
float RadianToDegree(float radians)
{
	return (180.f / PI) * radians;
}
/******************************************************************************/
/*!
Add member vector with given vector.

\param vec
Given vector you want to add with.
*/
/******************************************************************************/
void Vector::Add (const Vector& vec)
{
	this->m_x += vec.m_x;
	this->m_y += vec.m_y;
}
/******************************************************************************/
/*!
Subtract member vector with given vector.

\param vec
Given vector you want to subtract with.
*/
/******************************************************************************/
void Vector::Sub (const Vector& vec)
{
	this->m_x -= vec.m_x;
	this->m_y -= vec.m_y;
}
/******************************************************************************/
/*!
Scale vector with given multiplier.

\param Sx
X component multiplier

\param Sy
Y component multiplier
*/
/******************************************************************************/
void Vector::Scale (float Sx, float Sy)
{
	this->m_x *= Sx;
	this->m_y *= Sy;
}
/******************************************************************************/
/*!
Do dot product with given vector

\param vec
Given vector you want to calculate dot product

\return float
Result
*/
/******************************************************************************/
float Vector::DotProduct (const Vector& vec) const
{
	return ((this->m_x * vec.m_x) + (this->m_y * vec.m_y));
}
/******************************************************************************/
/*!
Get magnitude of member vector

\return float
Magnitude of member vector
*/
/******************************************************************************/
float Vector::GetLength (void) const
{
	return sqrt(m_x*m_x + m_y*m_y);
}
/******************************************************************************/
/*!
Make member vector as unit vector
*/
/******************************************************************************/
void Vector::Normalize (void)
{
	float length = GetLength();

	this->m_x /= length;
}
/******************************************************************************/
/*!
Get distance between two vectors.

\param vec1
First vector

\param vec2
Second vector

\return float
Distance between two vectors.
*/
/******************************************************************************/
float GetDistancePointPoint (const Vector& vec1, const Vector& vec2)
{
	float dx = vec1.m_x - vec2.m_x;
	float dy = vec1.m_y - vec2.m_y;

	return sqrt(dx*dx + dy*dy);
}
/******************************************************************************/
/*!
Get distance between point and line.

\param point
Given point vector

\param lineStart
Given start vector of line

\param lineEnd
Given end vector of line

\return float
Distance between point and line.
*/
/******************************************************************************/
float GetDistancePointLine (const Vector& point, const Vector& lineStart, const Vector& lineEnd)
{
	Vector v;
	v.m_x = lineEnd.m_x - lineStart.m_x;
	v.m_y = lineEnd.m_y - lineStart.m_y;

	Vector w;
	w.m_x = point.m_x - lineStart.m_x;
	w.m_y = point.m_y - lineStart.m_y;

	float c1 = w.DotProduct(v);
	float c2 = v.DotProduct(v);

	if(c1 <= 0)
		return GetDistancePointPoint(point, lineStart);

	if(c2 <= c1)
		return GetDistancePointPoint(point, lineEnd);

	float b = c1/c2;

	Vector perpendicular;
	perpendicular.m_x = lineStart.m_x + b*v.m_x;
	perpendicular.m_y = lineStart.m_y + b*v.m_y;

	return GetDistancePointPoint(point, perpendicular);
}
/******************************************************************************/
/*!
Returns true if two rectangle objects are intersecting

\param vec1
Vector of first object

\param obj1Sx
X scale of first object

\param obj1Sy
Y scale of first object

\param vec2
Vector of second object

\param obj2Sx
X scale of second object

\param obj2Sy
Y scale of second object

\return bool
True if two rectangle objects are intersecting
otherwise false
*/
/******************************************************************************/
bool IsIntersecting (const Vector& vec1, float obj1Sx, float obj1Sy, const Vector& vec2, float obj2Sx, float obj2Sy)
{
	float dx = vec1.m_x - vec2.m_x;
	float dy = vec1.m_y - vec2.m_y;

	float sizeX = (obj1Sx + obj2Sx) * HALF;
	float sizeY = (obj1Sy + obj2Sy) * HALF;

	if(dx*dx > sizeX*sizeX)
		return false;

	else if(dy*dy > sizeY*sizeY)
		return false;

	else
		return true;
}