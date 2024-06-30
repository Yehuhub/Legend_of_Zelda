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

#include "StaticObjects.h"
#include "PigWarrior.h"
#include "Octorok.h"
#include "Door.h"
#include "Sign.h"
#include "BowItem.h"
#include "SwordItem.h"
#include "Link.h"
#include "Heart.h"

#include "BadFileName.h"

class Link;

class Map
{
public:
	Map();
	~Map() = default;

	void setDict(std::map<int, std::string>&);

	void setMap(const std::string&);
	void initVector(Cell);
	std::vector<std::unique_ptr<Enemy>>& getEnemyObjects(Link*);
	std::vector<std::unique_ptr<Inanimate>>& getInanimateObjects();
	std::vector<std::unique_ptr<StaticObjects>>& getStaticObjects(Link*);

	std::vector<std::unique_ptr<Door>>& getDoors();

	std::map<int, std::string> getDict() const;

private:
	std::map<int, std::string> m_dict;
	std::vector<std::unique_ptr<Enemy>> m_enemyObjects;
	std::vector<std::unique_ptr<Inanimate>> m_inanimateObjects;
	std::vector<std::unique_ptr<StaticObjects>> m_staticObjects;
	std::vector<std::unique_ptr<Door>> m_doors;

	std::vector<std::pair<std::string,Cell>> m_map;
};