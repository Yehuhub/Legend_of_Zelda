#pragma once

#include <SFML/GRAPHICS.hpp>
#include "Utilities.h"
#include "SoundResource.h"

class State
{
public:
	State(sf::RenderWindow*);
	virtual ~State() = default;

	virtual void update(const sf::Time&) = 0;
	virtual void render(sf::RenderTarget* = nullptr) = 0;
	virtual std::unique_ptr<State> handleInput(const GAME_STATE&) = 0;
	virtual void buttonPressed(sf::RenderWindow&, const sf::Event&) = 0;

	void updateState(GAME_STATE gameState);

	void startGame();
	void exitGame();
	void openSettings();
	void backToMenu();
	void backToGame();

	sf::RenderWindow* getWindow() const;
	static GAME_STATE getGameState();


private:
	sf::RenderWindow* m_window;

	static GAME_STATE m_gameState;
};