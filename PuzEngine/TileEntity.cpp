/******************************************************************************/
/*!
\file   TileEntity.cpp
\author Taehoon Kwon
\par    email: kth2242\@gmail.com
\par    class: GAM200S14KR
\par    Team name : Puz
\par    Project name : Detect Dog
\brief  
This file contains component list of tile entity
and functions that manage entity.

\copyright 
All content © 2014 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "TileEntity.h"
#include "Physics.h"
#include "GraphicComponent.h"
/******************************************************************************/
/*!
Default destructor that clear all the components added into entity.
*/
/******************************************************************************/
TileEntity::~TileEntity(void)
{
	/* clear components */
	for(COMP_ITOR itor = components.begin();
		itor != components.end();
		++itor)
		delete itor->second.first;
}
/******************************************************************************/
/*!
Returns element that contains pair of a pointer to Component class and string.

\param cmp
A pointer to Component class.

\return value
Value that contains information about collision
(Value component of Ini file)
*/
/******************************************************************************/
TileEntity::ELEMENT TileEntity::GetElement(Component* cmp, const std::string value)
{
	return std::make_pair(cmp, value);
}
/******************************************************************************/
/*!
Insert component to entity

\param id
String that is type of component.
(Key component of components)

\param element
Pair of a pointer to Component class and string
that would be created by factory
(Value Component of components)
*/
/******************************************************************************/
void TileEntity::addComponent(const std::string id, ELEMENT element)
{
	components.insert(std::make_pair(id, element));
}
/******************************************************************************/
/*!
Returns component that is added into entity

\param id
A string that is type of component.

\return Component*
A pointer to Component class that already added into entity.
*/
/******************************************************************************/
Component* TileEntity::getComponent(const std::string id)
{
	COMP_ITOR result = components.find(id);

	/* if type is not same as already added one */
	if(result == components.end())
		return 0;
	else
		return result->second.first;
}
/******************************************************************************/
/*!
Initialize tile entity with added components.
*/
/******************************************************************************/
void TileEntity::Init(const std::string sectionName)
{
	COMP_ITOR itor = components.find("Collision Type");

	if(itor == components.end())
		return;
	else
		/* Call CollisionComponent Init function */
		static_cast<CollisionComponent*>(itor->second.first)->Init(sectionName, itor->second.second);

	itor = components.find("Graphic Type");

	if(itor == components.end())
		return;
	else
		/* Call GraphicComponent Init function */
		static_cast<GraphicComponent*>(itor->second.first)->Init(sectionName, itor->second.second);
}