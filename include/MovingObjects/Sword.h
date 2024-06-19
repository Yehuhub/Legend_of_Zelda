#pragma once

#include "MovingObjects.h"


class Sword : public MovingObjects{
public:
    Sword(const sf::Texture&, const sf::Vector2f&);

    virtual void update(const sf::Time& deltaTime)override;
    virtual void handleCollision() override;
    void activate(const sf::Vector2f& position, const sf::Vector2i& direction);
    void deActivate();
    bool getActive()const;
    void setActive(bool active);
    const sf::Vector2u& getAnimationTexturePosition(Input) override { return sf::Vector2u(0, 0); };


private:
    bool m_active;
    static bool m_registerit;
};