#include "Link.h"

#include <iostream> //debugging

bool Link::m_registerit = Factory::registerit("Link",
    [](const sf::Vector2f& position) -> std::unique_ptr<GameObject> {
        return std::make_unique<Link>(*Resources::getResource().getTexture(TEXTURE::Link), position);
    });

Link::Link(const sf::Texture& texture, const sf::Vector2f& position)
	: MovingObjects(texture, position), m_state(std::make_unique<LinkStandingState>()), m_sword(nullptr)
{
    setGraphics(ANIMATIONS_POSITIONS::LinkDown, 2);
    updateSprite();
}


// void Link::attack(const sf::Time& deltaTime){

//     // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
//     //     if (!m_attacking) {
//     //         m_attacking = true;
//     //         //attack to left
//     //         if (m_direction.x == -1) {
//     //             m_animation.setAnimation(ANIMATIONS_POSITIONS::LinkAttackLeft, 2, false, true);
//     //         }
//     //         //attack to right
//     //         else if (m_direction.x == 1) {
//     //             m_animation.setAnimation(ANIMATIONS_POSITIONS::LinkAttackRight, 2, false, true);
//     //         }
//     //         //attack down
//     //         else if (m_direction.x == 0 && m_direction.y == 1) {
//     //             m_animation.setAnimation(ANIMATIONS_POSITIONS::LinkAttackDown, 3, false, true);
//     //         }
//     //         //attack up
//     //         else if (m_direction.x == 0 && m_direction.y == -1) {
//     //             m_animation.setAnimation(ANIMATIONS_POSITIONS::LinkAttackUp, 3, false, true);
//     //         }

//     //         // Need to also create a sword object 
//     //     }
//     // }

//     // if (m_attacking) {
//     //     m_animation.update(deltaTime);

//     //     if (m_animation.isDone()) {
//     //         m_attacking = false;

//     //         // Reset animation after attack is done
//     //         if (m_direction.x == 1) {
//     //             m_animation.setAnimation(ANIMATIONS_POSITIONS::LinkRight, 2);
//     //         } else if (m_direction.x == -1) {
//     //             m_animation.setAnimation(ANIMATIONS_POSITIONS::LinkLeft, 2);
//     //         } else if (m_direction == sf::Vector2i(0, -1)) {
//     //             m_animation.setAnimation(ANIMATIONS_POSITIONS::LinkUp, 2);
//     //         } else if (m_direction == sf::Vector2i(0, 1)) {
//     //             m_animation.setAnimation(ANIMATIONS_POSITIONS::LinkDown, 2);
//     //         }
//     //     }
//     // }
//     // updateSprite(m_animation.getuvRect());
// }

void Link::handleCollision()
{

}

void Link::update(const sf::Time& deltaTime){

    bool up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    bool down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    bool space = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
    
    Input input;
    if(space){
        input = PRESS_SPACE;
    }
    else if(down && right){
        input = PRESS_DOWN_RIGHT;
    }
    else if(down && left){
        input = PRESS_DOWN_LEFT;
    }
    else if(up && right){
        input = PRESS_UP_RIGHT;
    }
    else if(up && left){
        input = PRESS_UP_LEFT;
    }
    else if(up){
        input = PRESS_UP;
    }
    else if(down){
        input = PRESS_DOWN;
    }
    else if(right){
        input = PRESS_RIGHT;
    }
    else if(left){
        input = PRESS_LEFT;
    }
    else{
        input = NONE;
    }
    
    std::unique_ptr<LinkState> state = m_state->handleInput(input);

    if(state){
        m_state = std::move(state);
        m_state->enter(*this);

    }   
    if(!dynamic_cast<LinkStandingState*>(m_state.get())){
        updateGraphics(deltaTime);
    }
    updateSprite();

}

void Link::insertSword(Sword* sword){
    m_sword = sword;
}

void Link::swipeSword(){
    if(m_sword){
        m_sword->activate(getSprite().getPosition(), getDirection());
    }
}
void Link::stopSwordSwipe(){
    if(m_sword){
        m_sword->deActivate();
    }
}
