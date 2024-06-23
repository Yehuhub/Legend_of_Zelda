#include "Boulder.h"

bool Boulder::m_registerit = Factory<MovingObjects>::instance()->registerit("Boulder",
	[](const sf::Vector2f& position) -> std::unique_ptr<MovingObjects>
	{
		return std::make_unique<Boulder>(*Resources::getResource().getTexture(TEXTURE::Enemies), position);
	});

Boulder::Boulder(const sf::Texture& texture, const sf::Vector2f& pos)
	: Inanimate(texture, pos, sf::Vector2f(tileSize / 1.3f, tileSize / 1.3f), sf::Vector2f(tileSize / 2.5f, tileSize / 2.5f))
{
	setPosition(pos);
	setGraphics({190, 170}, 1);
	getSprite().setTextureRect(getAnimation().getuvRect());
}

void Boulder::update(const sf::Time& deltaTime)
{
	setSpeed(1.f);
}