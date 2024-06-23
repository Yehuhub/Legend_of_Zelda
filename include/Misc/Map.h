#pragma once
#include <iostream> // debug

#include <SFML/Graphics.hpp>
#include "Utilities.h"
#include "Resources.h"
#include "Factory.h"
#include <memory>
#include <fstream>
#include <sstream>
#include <map>

#include "Enemy.h"
#include "StaticObjects.h"
//#include "BadFileName.h"

class Link;

class Map
{
public:
	Map();
	~Map() = default;

	void setDict(std::map<int, std::string>&);

	void setMap();
	void initVector(Cell);
	std::vector<std::unique_ptr<MovingObjects>>& getEnemyObjects(Link* link);
	std::vector<std::unique_ptr<StaticObjects>>& getStaticObjects();

	std::map<int, std::string> getDict() const;

private:
	std::map<int, std::string> m_dict;
	std::vector<std::unique_ptr<MovingObjects>> m_enemyObjects;
	std::vector<std::unique_ptr<StaticObjects>> m_staticObjects;

	std::vector<std::pair<std::string,Cell>> m_map;
};