#include "OctorokProjectile.h"

#include <iostream> //debugging

bool OctorokProjectile::m_registerit = Factory::registerit("OctorokProjectile",
    [](const sf::Vector2f& position) -> std::unique_ptr<GameObject> {
        return std::make_unique<OctorokProjectile>(*Resources::getResource().getTexture(TEXTURE::Enemies), position);
    });

OctorokProjectile::OctorokProjectile(const sf::Texture& Texture, const sf::Vector2f& position)
    : Projectile(Texture, position, sf::Vector2f(8,8), sf::Vector2f(8/2,8/2))
{
    setGraphics({ 265, 143 }, 1);
	updateSprite();
    setDirection(DIRECTIONS::Down);
}

void OctorokProjectile::update(const sf::Time& deltaTime)
{
    move();
}

void OctorokProjectile::handleCollision()
{
}
