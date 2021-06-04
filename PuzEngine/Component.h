/******************************************************************************/
/*!
\file   Component.h
\author Taehoon Kwon
\par    email: kth2242\@gmail.com
\par    class: GAM200S14KR
\par    Team name : Puz
\par    Project name : Detect Dog
\brief  
The base class of Components that would be created by factory.

\copyright 
All content © 2014 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

class Component
{
public:
	virtual void Init(const std::string sectionName, const std::string value) = 0;
};

#endif /* COMPONENT_H */