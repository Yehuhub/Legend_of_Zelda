#include "Sword.h"
#include <iostream>//debugging

Sword::Sword(const sf::Texture& texture, const sf::Vector2f& position)
    : MovingObjects(texture, position), m_active(false){}
    
void Sword::activate(const sf::Vector2f& position, const sf::Vector2i& direction){
    m_active = true;
    //set sword position
    getSprite().setPosition(position);
    setDirection(direction);

    //make sprite visible
    sf::Color color = getSprite().getColor();
    color.a = 255;
    getSprite().setColor(color);

    sf::Vector2f attackPos;
    //set sword position and animation according to direction and link position
    if(direction.x == 1){
        setGraphics(ANIMATIONS_POSITIONS::SwordRight, 2, false ,true, 0.10f);//true for singleTime
        attackPos.x = position.x + tileSize * 0.6f;
        attackPos.y = position.y;
        getSprite().setPosition(attackPos);
    }
    else if(direction.x == -1){
        setGraphics(ANIMATIONS_POSITIONS::SwordLeft, 2, false ,true, 0.10f);//true for singleTime
        attackPos.x = position.x - tileSize* 0.6f;
        attackPos.y = position.y;
        getSprite().setPosition(attackPos);
    }
    else if(direction == DIRECTIONS::Up){
        setGraphics(ANIMATIONS_POSITIONS::SwordUp, 3, false ,true, 0.10f);//true for singleTime
        attackPos.x = position.x ;
        attackPos.y = position.y - tileSize* 0.6f;
        getSprite().setPosition(attackPos);
    }
    else if(direction == DIRECTIONS::Down){
        setGraphics(ANIMATIONS_POSITIONS::SwordDown, 3, false ,true, 0.10f);//true for singleTime
        attackPos.x = position.x ;
        attackPos.y = position.y + tileSize* 0.6f;
        getSprite().setPosition(attackPos);
    }

}

void Sword::deActivate(){
    m_active = false;

    //make sprite invisible
    sf::Color color = getSprite().getColor();
    color.a = 0;
    getSprite().setColor(color);
}

bool Sword::getActive()const{
    return m_active;
}

void Sword::update(const sf::Time& deltaTime){
    if(m_active){
        updateGraphics(deltaTime);
        updateSprite();
    }
}
void Sword::handleCollision(){

}