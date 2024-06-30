#pragma once

#include "State.h"
#include "MainMenu.h"
#include "GameRunningState.h"
#include "Board.h"

#include "BadFileName.h"
#include "BadFileFormat.h"

class LoadGameState : public State
{
public:
	LoadGameState(sf::RenderWindow*);

	virtual void update(const sf::Time&) override;
	virtual void render(sf::RenderTarget* = nullptr) override;
	virtual std::unique_ptr<State> handleInput(const GAME_STATE&) override;
	virtual void buttonPressed(sf::RenderWindow&, const sf::Event&) override;

	void errorFileMsg(sf::RenderWindow* window, std::string msg);

	void updateLink();
	void updateLevel();

	//void loadGame();

private:
	void setMap();
	void loadGame(sf::RenderWindow* window);
	std::vector<Board> m_boardLevels;
	sf::View m_view;
	std::vector<std::unique_ptr<Enemy>> m_enemyObjects;
	std::vector<std::unique_ptr<Inanimate>> m_inanimateObjects;

	// about Link
	std::unique_ptr<Link> m_link;
	sf::Vector2f m_linkPosition;
	int m_linkLife;
	std::vector<int> m_weaponIds;

	// about the level
	int m_level;
	std::vector<std::pair<sf::Vector2f, EnemyType>> m_enemiesPositions;
	std::vector<sf::Vector2f> m_boulderPositions;

	// for exeptions
	bool m_isGameLoad = false;
	bool m_isLoadFail = false;
};
