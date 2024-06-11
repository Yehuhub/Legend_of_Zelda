#pragma once

#include <SFML/Graphics.hpp>
#include "Utilities.h"
#include "Resources.h"
#include "StartButton.h"
#include "ExitButton.h"
#include "SettingsButton.h"
#include "HelpButton.h"
#include "LoadButton.h"

#include "State.h"

class NewGameState;

using Option = std::pair<std::string, std::unique_ptr<Button>>;

class MainMenu : public State
{
public:
	MainMenu(sf::RenderWindow*);

	void drawMainMenu(sf::RenderWindow&);
	void buttonPressed(sf::RenderWindow&, const sf::Event::MouseButtonEvent&);
	void overButton(sf::RenderWindow&);
	void startGame();
	void exitGame();


	virtual void update(const sf::Time&) override;
	virtual void render(sf::RenderTarget* = nullptr) override;
	virtual std::unique_ptr<State> handleInput(GAME_STATE) override;

private:
	void add(const std::string&, std::unique_ptr<Button>);

	sf::RectangleShape m_menuBackground;
	std::vector<Option> m_options;
};