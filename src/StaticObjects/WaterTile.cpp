#include "WaterTile.h"

bool WaterTile::m_registerit = Factory::registerit("WaterTile",
	[](const sf::Vector2f& position) -> std::unique_ptr<GameObject> { return std::make_unique<WaterTile>(*Resources::getResource().getTexture(TEXTURE::MapObjects), position); });

WaterTile::WaterTile(const sf::Texture& texture, const sf::Vector2f& position)
	: InDestructible(texture, position, sf::Vector2f(16,16), sf::Vector2f(tileSize/2, tileSize/2))
{
	getSprite().setColor(sf::Color::Transparent);
	getSprite().scale(0.7f, 0.7f);
}

void WaterTile::handleCollision()
{
}
