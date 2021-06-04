/******************************************************************************/
/*!
\file   TileFactory.cpp
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
#include "TileFactory.h"
#include "Debug.h"
#include <fstream>
#include <iostream>

/******************************************************************************/
/*!
Default constructor that initialize data used for load ini files.
*/
/******************************************************************************/
TileFactory::TileFactory(void) : m_currSection(0)
{
	//registerCreator();
}
/******************************************************************************/
/*!
Default destructor that call release all the data that managed by factory.
*/
/******************************************************************************/
TileFactory::~TileFactory(void)
{
	ReleaseFactory();
}
/******************************************************************************/
/*!
Clear all the data that managed by factory.
*/
/******************************************************************************/
void TileFactory::ReleaseFactory(void)
{
	/* Clear data that is registered */
	for(CreatorMapItor it = creators.begin();
		it != creators.end();
		++it)
	{
		delete it->second;
		it->second = 0;
	}

	/* Clear entity */
	for(int i = 0; i < NUM_OF_TILE; ++i)
	{
		if(tileEntity[i] != 0)
		{
			delete tileEntity[i];
			tileEntity[i] = 0;
		}
	}

	/* Clear entity list */
	entityList.clear();

	/* Clear all the strings */
	m_sections.clear();
	m_currSection = 0;
}
/******************************************************************************/
/*!
Returns components that is created by factory.

\param type
Type of components that would be added into entity.
(Key component of creator map that already registered.)

\return Component*
Pointer to Component class that would be created by factory.
(Decided by parameter)
*/
/******************************************************************************/
Component* TileFactory::Create(const std::string type)
{
	CreatorMapItor it;

	it = creators.find(type);

	/* if type is not registered */
	if (it == creators.end())
		return 0;
	else
		/* Call Creator and Creator returns component */
		return it->second->Create();
}
/******************************************************************************/
/*!
Register all the creator that would be called by factory.
*/
/******************************************************************************/
void TileFactory::registerCreator(void)
{
	creators["Collision Type"] = new CollisionCreator();
	creators["Graphic Type"] = new GraphicCreator();
}
/******************************************************************************/
/*!
Load level files from ini file and store entity data.

\param fileName
File name of ini file.
If wrong file name is catched then would be asserted.
*/
/******************************************************************************/
void TileFactory::LoadEntity (const char* fileName)
{
	std::ifstream IniFile(fileName);
    std::string line;
	
    /* if it is fail to open file */
	if(!IniFile.is_open())
	{
		DEBUG_PRINT("\n%s can't be opened", fileName);
		DEBUG_ASSERT(IniFile.is_open(), "File can't be opened");
	}
	
    else
    {
		while(std::getline(IniFile, line))
		{
			/*if there is comment or nothing then skip the line*/
			if(line == "" || line[0] == ';')
				continue;

			/*Variable for storing begin and end of line*/
	        size_t begin = 0;
	        size_t end = line.size() -1;

			/*if line contains section*/
            if(line[0] == '[')
                DoSectionName(line, begin, end);
            else
                DoKeyValue(line, begin, end);
		}

		/*Store into SectionMap with sectionName and KeyValMap*/
        m_sections.insert(std::make_pair(m_sectionName, *m_currSection));

        /*Delete memory*/
        delete m_currSection;

		int i = 0;  // Variable for counter

		for(m_sectionItor = m_sections.begin();
			m_sectionItor != m_sections.end();
			++m_sectionItor)
		{
			/* Dynamically create tile entity */
			tileEntity[i] = new TileEntity;

			for(m_currSectionItor = m_sectionItor->second.begin();
				m_currSectionItor != m_sectionItor->second.end();
				++m_currSectionItor)
			{
				/* Dynamically create component */
				Component* cmp = this->Create(m_currSectionItor->first);

				/* Add components into dynamically created tile entity */
				tileEntity[i]->addComponent(m_currSectionItor->first, tileEntity[i]->GetElement(cmp, m_currSectionItor->second));
			}
			/* Add entity into entity list */
			addEntity(m_sectionItor->first, tileEntity[i]);

			++i;
		}
	}

	IniFile.close();
}
/******************************************************************************/
/*!
Insert entity to entity list

\param id
String that is section name.
(Key component of entity list)

\param entity
Tile entity that would be created by factory
(Value Component of entity list)
*/
/******************************************************************************/
void TileFactory::addEntity(const std::string id, TileEntity* entity)
{
	entityList.insert(std::make_pair(id, entity));
}
/******************************************************************************/
/*!
Returns list of entity.
*/
/******************************************************************************/
TileFactory::EntityMap TileFactory::GetEntityList(void)
{
	return entityList;
}
/******************************************************************************/
/*!
To separate key and value from the line

\param sPair 
A string pair for storing a pair of key and value.

\param line 
A const string that is a line containing pair and key.

\param begin 
A unsigned int that indicates begin position of the line.

\param end
A unsigned int that indicates end position of the line.
*/
/******************************************************************************/
void TileFactory::SeparateKeyValueFromLine(StringPair& sPair, const std::string& line, size_t& begin, size_t& end) const
{
    /*Variable for loop counter (Where value begins in the line)*/
    size_t valueBegin = 0;

    /*Set my key (Before = operator)*/
    for(size_t i = begin; i <= end; ++i)
    {
        if(line[i] == '=')
        {
            /*value begins after = operator*/
            valueBegin = i+1;
            break;
        }
        /*Set my key into first part of string pair*/
        sPair.first.push_back(line[i]);
    }
    /*Variable for storing begin and end of key section*/
    size_t keyBegin = 0;
    size_t keyEnd = sPair.first.size() -1;

    /*Remove space in the key section*/
    RemoveLeadingSpaces(sPair.first, keyBegin, keyEnd);
    RemoveTrailingSpaces(sPair.first, keyBegin, keyEnd);

    /*Set my value (After = operator)*/
    for(size_t i = valueBegin; i <= end; ++i)
    {
        /*Comment Check*/
        if(line[i] == ';')
            break;
        /*Set my value into second part of string pair*/
        sPair.second.push_back(line[i]);
    }
    /*Variable for storing begin and end of value section*/
    valueBegin = 0;
    size_t valueEnd = sPair.second.size() -1;

    /*Remove space in the value section*/
    RemoveLeadingSpaces(sPair.second, valueBegin, valueEnd);
    RemoveTrailingSpaces(sPair.second, valueBegin, valueEnd);   
}
/******************************************************************************/
/*!
To set my section name

\param line 
A string reference that is a line contains section.

\param begin 
A unsigned int that indicates begin position of the line.

\param end
A unsigned int that indicates end position of the line.
*/
/******************************************************************************/
void TileFactory::DoSectionName(std::string& line, size_t& begin, size_t& end)
{
    /*Variable for storing section name temporarily*/
    std::string temp;

    /*Store string between [] brackets into temporary string*/
    for(size_t i = begin+1; i <= end-1; ++i)
    {
        temp.push_back(line[i]);
    }

    /*Variable for storing begin and end of section*/
    size_t tempBegin = 0;
    size_t tempEnd = temp.size() -1;

    /*Remove the space*/
    RemoveLeadingSpaces(temp, tempBegin, tempEnd);
    RemoveTrailingSpaces(temp, tempBegin, tempEnd);

    /*if key and value of map is already allocated*/
    if(m_currSection != 0)
    {
        /*Store into SectionMap with sectionName and KeyValMap*/
        m_sections.insert(std::make_pair(m_sectionName, *m_currSection));

        /*Delete memory*/
        delete m_currSection;
    }

    /*Allocate memory for key and value*/
    m_currSection = new KeyValMap;

    /*Set my section name*/
    m_sectionName = temp;
}
/******************************************************************************/
/*!
To set my key and value

\param line 
A string reference that is a line contains key and value.

\param begin 
A unsigned int that indicates begin position of the line.

\param end
A unsigned int that indicates end position of the line. 
*/
/******************************************************************************/
void TileFactory::DoKeyValue(std::string& line, size_t& begin, size_t& end)
{
    StringPair temp; /*A variable for storing key and value temporarily*/

    /*Store my key and value into temp variable*/
    SeparateKeyValueFromLine(temp, line, begin, end);

    /*Store into KeyValMap*/
    m_currSection->insert(temp);
}
/******************************************************************************/
/*!
To remove leading spaces from the line

\param line 
A string reference that is a line that may contain leading spaces.

\param begin 
A unsigned int that indicates begin position of the line.

\param end
A unsigned int that indicates end position of the line.
*/
/******************************************************************************/
void TileFactory::RemoveLeadingSpaces(std::string& line, size_t& begin, size_t& end) const
{
    int leadingSpace = 0; /*A variable for counter*/

    /*Count how long leading space is*/
    for(size_t i = begin; i <= end; ++i)
    {
        if(line[i] != ' ')
            break;

        ++leadingSpace;
    }

    /*A variable for storing line, the space of which is removed*/
    std::string temp;

    /*Store string without leading spaces in temporary string*/
    for(size_t i = leadingSpace; i <= end; ++i)
        temp.push_back(line[i]);

    /*Clear original string and change with removed string*/
    line.clear();
    line.swap(temp);

    /*Set new end position*/
    end = line.size() -1;
}
/******************************************************************************/
/*!
To remove trailing spaces from the line

\param line 
A const string that is a line that may contain trailing spaces.

\param begin 
A unsigned int that indicates begin position of the line.

\param end
A unsigned int that indicates end position of the line. 
*/
/******************************************************************************/
void TileFactory::RemoveTrailingSpaces(std::string& line, size_t& begin, size_t& end) const
{
    int trailingSpace = 0; /*A variable for counter*/

    /*Count how long trailing space is*/
    for(size_t i = end; i >= begin; --i)
    {
        if(line[i] != ' ')
            break;

        ++trailingSpace;
    }

    /*A variable for storing line, the space of which is removed*/
    std::string temp;
    
    /*Variable for storing begin of space*/
    size_t spaceBegin = end - trailingSpace;

    /*Store string without trailing spaces in temporary string*/
    for(size_t i = begin; i <= spaceBegin; ++i)
        temp.push_back(line[i]);

    /*Clear original string and change with removed string*/
    line.clear();
    line.swap(temp);

    /*Set new end position*/
    end = line.size() -1;
}
/******************************************************************************/
/*!
Initialize all the tile entity in the entity list.
*/
/******************************************************************************/
void TileFactory::TileInit(void)
{
	for(EntityMapItor itor = entityList.begin();
		itor != entityList.end();
		++itor)
	{
		/* Call TileEntity Init function */
		itor->second->Init(itor->first);
	}
}