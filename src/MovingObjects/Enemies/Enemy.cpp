#include "Enemy.h"

Enemy::Enemy(const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Vector2f& originOffset)
	: MovingObjects(texture, position, size, originOffset)
{
}

