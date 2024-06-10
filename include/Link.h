#pragma once

#include "MovingObjects.h"
#include "Animation.h"

class Link : public MovingObjects
{
public:
	Link(const sf::Texture&, const sf::Vector2f&);

	virtual void move(const sf::Time&) override;
	virtual void attack(const sf::Time&)override;
	virtual void handleCollision() override;

	void undoMove();
	bool isAttacking() const;

private:
	Animation m_animation;
	sf::Vector2i m_direction;
};