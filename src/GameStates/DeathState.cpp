#include "DeathState.h"

DeathState::DeathState(sf::RenderWindow* window, sf::Vector2f position, sf::View view)
	:State(window), m_whiteBackground(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y))),
	m_linkDeathSprite(), m_amountOfSpins(0)
{
	getWindow()->setView(view);
	m_linkDeathSprite.setTexture(*Resources::getResource().getTexture(TEXTURE::Link));
	m_linkDeathSprite.setPosition(position);
	m_animation.setAnimation(sf::Vector2u(188, 42), 4, true, 0.2f);
	m_linkDeathSprite.setTextureRect(m_animation.getuvRect());
	m_linkDeathSprite.setScale(1, 1);
}

void DeathState::update(const sf::Time& deltaTime)
{
	if (m_animation.isDone() && m_amountOfSpins < 3)
	{
		
		m_animation.setAnimation(sf::Vector2u(188, 42), 4, true, 0.2f);
		m_amountOfSpins++;
	}

	m_animation.update(deltaTime);
	m_linkDeathSprite.setTextureRect(m_animation.getuvRect());
	m_linkDeathSprite.setScale(1, 1);

	if (m_amountOfSpins >= 3)
	{
		updateState(GAME_STATE::GAME_OVER);
	}
}

void DeathState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = getWindow();
	}
	target->draw(m_whiteBackground);
	target->draw(m_linkDeathSprite);
}

std::unique_ptr<State> DeathState::handleInput(const GAME_STATE& gameState)
{
	switch (gameState)
	{
		case GAME_OVER:
			return std::make_unique<GameOverState>(getWindow());
	}
	return nullptr;
}

void DeathState::buttonPressed(sf::RenderWindow&, const sf::Event&) {}