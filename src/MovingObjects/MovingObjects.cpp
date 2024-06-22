#include "MovingObjects.h"

#include <iostream> //debugging

MovingObjects::MovingObjects(const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Vector2f& originOffset)
	: GameObject(texture, position, size, originOffset), m_direction(0, 0), m_speed(1), m_animation()
{
}

sf::Vector2i MovingObjects::getDirection()const
{
	return m_direction;
}

Animation& MovingObjects::getAnimation()
{
	return m_animation;
}

int MovingObjects::getSpeed() const
{
	return m_speed;
}

void MovingObjects::setDirection(const sf::Vector2i& direction)
{
	m_direction = direction;
}

void MovingObjects::move()
{	
	sf::Vector2f newPos;
	if(m_isPushedback){
		if(!(pushbackDuration - m_pushbackTimer.getElapsedTime() <= sf::Time(sf::seconds(0)))){
			newPos.x = getSprite().getPosition().x + (-m_collisionDirection.x * m_speed );
			newPos.y = getSprite().getPosition().y + (-m_collisionDirection.y * m_speed );
			setPosition(newPos);
			getSprite().setPosition(newPos);
		}
		else{
			m_isPushedback = false;
		}
		return;
	}
	newPos.x = getSprite().getPosition().x + m_direction.x * m_speed;
	newPos.y = getSprite().getPosition().y + m_direction.y * m_speed;
	setPosition(newPos);
	getSprite().setPosition(newPos);
}

void MovingObjects::updateSprite()
{
	getSprite().setTextureRect(m_animation.getuvRect());
	getSprite().setScale(0.8f, 0.8f);
}

void MovingObjects::setGraphics(const sf::Vector2u& animationPos, int imgCount, bool flip, bool singleTime, float switchTime)
{
	m_animation.setAnimation(animationPos, imgCount, flip, singleTime, switchTime);
}

void MovingObjects::setSpeed(int speed)
{
	m_speed = speed;
}

void MovingObjects::undoMove()
{
	getSprite().setPosition(getPreviousPosition());
	setPosition(getPreviousPosition());
}

void MovingObjects::pushBack(const sf::Vector2i& direction)
{	
	m_collisionDirection = direction;
	m_isPushedback = true;
	m_pushbackTimer.restart();
}

bool MovingObjects::isAttacking() const
{
	return m_attacking;
}

void MovingObjects::setHp(int hp){
	m_hp = hp;
}

int MovingObjects::getHp()const{
	return m_hp;
}

bool MovingObjects::isPushedBack()const{
	return m_isPushedback;
}

std::unique_ptr<MovingObjects> MovingObjects::getAttack(){
	return nullptr;
}