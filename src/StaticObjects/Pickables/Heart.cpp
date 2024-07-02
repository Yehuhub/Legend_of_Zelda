#include "Heart.h"

bool Heart::m_registerit = Factory<StaticObjects>::instance()->registerit("Heart",
	[](const sf::Vector2f& position) -> std::unique_ptr<StaticObjects>
	{
		return std::make_unique<Heart>(*Resources::getResource().getTexture(TEXTURE::PickableItems), position);
	});

Heart::Heart(const sf::Texture& texture, const sf::Vector2f& position)
	: Pickable(texture, position, sf::Vector2f(tileSize * 0.8f / 2.f, tileSize * 0.8f), sf::Vector2f(0, 0))
{
	getSprite().setTextureRect(sf::IntRect(SPRITE_POSITIONS::HeartItem, { 7, 7 }));
}