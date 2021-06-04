/******************************************************************************/
/*!
\file   TileEntity.h
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
#ifndef TILE_ENTITY_H
#define TILE_ENTITY_H

#include <string>
#include <map>
#include "Component.h"

class TileEntity
{
private:
	typedef std::pair<Component*, const std::string> ELEMENT;
	typedef std::map<const std::string, ELEMENT> COMP_MAP;
	typedef COMP_MAP::iterator COMP_ITOR;

	COMP_MAP components;

public:
	~TileEntity(void);
	ELEMENT GetElement(Component* cmp, const std::string value);
	void addComponent(const std::string id, ELEMENT element);

	Component* getComponent(const std::string id);

	void Init(const std::string sectionName);
};

#endif /* TILE_ENTITY_H */