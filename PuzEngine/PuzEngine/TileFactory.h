/******************************************************************************/
/*!
\file   TileFactory.h
\author Taehoon Kwon
\par    email: kth2242\@gmail.com
\par    class: GAM200S14KR
\par    Team name : Puz
\par    Project name : Detect Dog
\brief  
This file contains entity list
and functions that manage entity list.
And some helper function that can load level data from ini file.

\copyright 
All content © 2014 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef TILE_FACTORY_H
#define TILE_FACTORY_H

#include <string>
#include <map>
#include "Component.h"
#include "TileEntity.h"
#include "TileCreator.h"
#include "Tile.h"

class TileFactory
{
public:
	typedef std::map<const std::string, TileCreator*> CreatorMap;
	typedef CreatorMap::iterator CreatorMapItor;
	typedef std::map<const std::string, TileEntity*> EntityMap;
	typedef EntityMap::iterator EntityMapItor;
	
private:
	CreatorMap creators;   // Map that contains component types in string and creator
	EntityMap entityList;  // Map that contains section name and tile entity
	TileEntity* tileEntity[NUM_OF_TILE]; // Dynamically allocated entity list that would be saved into entity list

public:
	TileFactory(void);
	~TileFactory(void);

	void registerCreator(void);
	void ReleaseFactory(void);
	Component* Create(const std::string type);

	void LoadEntity (const char* fileName);
	void addEntity(const std::string id, TileEntity* entity);
	
	void TileInit(void);

	EntityMap GetEntityList(void);

/* Helper functions */
private:
	typedef std::pair<std::string, std::string>        StringPair;
	typedef std::map<std::string, std::string>         KeyValMap;
	typedef KeyValMap::iterator                        KeyValMapItor;
	typedef std::map<std::string, KeyValMap>           SectionMap;
	typedef SectionMap::iterator                       SectionMapItor;

	void DoSectionName(std::string& line, size_t& begin, size_t& end);
	void DoKeyValue(std::string& line, size_t& begin, size_t& end);
	void SeparateKeyValueFromLine(StringPair& sPair, const std::string& line, size_t& begin, size_t& end) const;
	void RemoveLeadingSpaces(std::string& line, size_t& begin, size_t& end) const;
    void RemoveTrailingSpaces(std::string& line, size_t& begin, size_t& end) const;

	SectionMap m_sections;     // Map stores all the data
	KeyValMap* m_currSection;  // Dynamically allocated map
	std::string m_sectionName; // String stores section name
	SectionMapItor m_sectionItor;
	KeyValMapItor m_currSectionItor;
};

#endif /* TILE_FACTORY_H */