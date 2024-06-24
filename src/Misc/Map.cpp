#include "Map.h"
#include "Link.h"
#include "BowItem.h"
#include "SwordItem.h"


Map::Map()
{
	setDict(m_dict);
}

std::map<int, std::string> Map::getDict() const
{
	return m_dict;
}

void Map::setDict(std::map<int ,std::string>& dict)
{
	dict.emplace(264 ,"Wall");
	dict.emplace(265, "Wall");
	dict.emplace(267, "Wall");
	dict.emplace(268, "Wall");
	dict.emplace(269, "Wall" );
	dict.emplace(270, "Wall" );
	dict.emplace(274, "Wall" );
	dict.emplace(275, "Wall" );
	dict.emplace(288, "Wall" );
	dict.emplace(290, "Wall" );
	dict.emplace(291, "Wall" );
	dict.emplace(292, "Wall" );
	dict.emplace(293, "Wall" );
	dict.emplace(312, "Wall" );
	dict.emplace(313, "Wall" );
	dict.emplace(339, "Wall" );
	dict.emplace(340, "Wall" );
	dict.emplace(253, "Flowers" );
	dict.emplace(229, "Flowers" );
	dict.emplace(152, "Wall" );
	dict.emplace(153, "Wall" );
	dict.emplace(154, "Wall" );
	dict.emplace(162, "Wall" );
	dict.emplace(176, "Wall" );
	dict.emplace(177, "Wall" );
	dict.emplace(200, "Wall" );
	dict.emplace(201, "Wall" );
	dict.emplace(130, "Wall" );
	dict.emplace(131, "Wall" );
	dict.emplace(155, "Wall" );
	dict.emplace(225, "Wall" );
	dict.emplace(249, "Wall" );
	dict.emplace(49, "Wall" );
	dict.emplace(60, "Wall" );
	dict.emplace(61, "Wall" );
	dict.emplace(62, "Wall" );
	dict.emplace(9, "Wall" );
	dict.emplace(10, "Wall" );
	dict.emplace(11, "Wall" );
	dict.emplace(33, "Wall" );
	dict.emplace(34, "Wall" );
	dict.emplace(35, "Wall" );
	dict.emplace(48, "Wall" );
	dict.emplace(476, "WaterTile" );
	dict.emplace(477, "WaterTile" );
	dict.emplace(478, "WaterTile" );
	dict.emplace(479, "WaterTile" );
	dict.emplace(-1610612467, "Wall" );
	dict.emplace(1610613065, "Wall" );
	dict.emplace(1610613006, "Wall" );
	dict.emplace(1610613010, "Wall" );
	dict.emplace(1610613001, "Wall" );
	dict.emplace(1610613003, "Wall" );
	dict.emplace(-1610612468, "Wall" );
	dict.emplace(-1073741536, "Wall" );
	dict.emplace(-1073741511, "Wall" );
	dict.emplace(-1610612461, "Wall" );
	dict.emplace(-1610612462, "Wall" );
	dict.emplace(1610612787, "Door");
	dict.emplace(51, "Door");
}

void Map::setMap(const std::string& mapName)
{
	std::string gameMap = mapName;
	std::cout << "map name: " << gameMap << std::endl;
	try
	{
		auto map = std::ifstream(gameMap);
		if (!map)
		{
			throw BadFileName();
		}

		m_enemyObjects.clear();
		m_staticObjects.clear();

		std::string line;
		// Read the file line by line
		int currentRow = 0;
		while (std::getline(map, line)) {
			std::istringstream lineStream(line);
			std::string cell;
			int currentCol = 0;

			// Parse each line into comma-separated values
			while (std::getline(lineStream, cell, ',')) {
				// Convert the cell to an integer
				int value = std::stoi(cell);
				Cell c = { value, currentRow, currentCol };
				if (c.value != -1)
				{
					initVector(c);
				}
				currentCol++;
			}
			currentRow++;
		}

		// Close the file
		map.close();
	}
	catch (const BadFileName& e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "An error occurred: " << e.what() << std::endl;
	}
}

void Map::initVector(Cell cell)
{
	// texture of daungeon path
	if (cell.value <= -1610612618 && cell.value >= -1610612666 || cell.value == 1610613065 || cell.value == 1610613107 || cell.value == -1073741688)
	{
		return;
	}
	
	auto it = m_dict.find(cell.value);
	if (it != m_dict.end())
	{
		if (it->second == "Door")
		{
			if (auto p = Factory<Door>::instance()->create(it->second, { static_cast<float>(tileSize) * cell.col, static_cast<float>(tileSize) * cell.row }))
			{
				if (cell.value == 51)
				{
					p->setLevelToDoor(Level::FIRST_DUNGEON);
					p->setLinkOutPosition({ 22, 105 });
					m_doors.emplace_back(std::move(p));
				}
				if (cell.value == 1610612787)
				{
					p->setLevelToDoor(Level::MAIN);
					p->setLinkOutPosition({ 168, 149 });
					m_doors.emplace_back(std::move(p));
				}
			}
			return;
		}
		if (auto p = Factory<StaticObjects>::instance()->create(it->second, {static_cast<float>(tileSize) * cell.col, static_cast<float>(tileSize) * cell.row}))
		{
			m_staticObjects.emplace_back(std::move(p));
		}
	}

}

std::vector<std::unique_ptr<Enemy>>& Map::getEnemyObjects(Link* link)
{
	//tmp create
	if (auto p = Factory<Octorok>::instance()->create("Octorok", { 70.f, 150.f }))
	{
		m_enemyObjects.emplace_back(std::move(p));
	}
	 if (auto p1 = Factory<PigWarrior>::instance()->create("PigWarrior", { 32.f, 150.f }))
	 {
	 	p1->registerAsLinkObserver(link);
	 	m_enemyObjects.emplace_back(std::move(p1));
	 }
	return m_enemyObjects;
}

std::vector<std::unique_ptr<StaticObjects>>& Map::getStaticObjects()
{
	if(auto p = Factory<BowItem>::instance()->create("BowItem", {25,25})){
		m_staticObjects.emplace_back(std::move(p));
	}

	if(auto p = Factory<SwordItem>::instance()->create("SwordItem", {25,45})){
		m_staticObjects.emplace_back(std::move(p));
	}
	return m_staticObjects;
}

std::vector<std::unique_ptr<Door>>& Map::getDoors()
{
	return m_doors;
}
