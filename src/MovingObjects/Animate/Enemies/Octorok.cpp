#include "Octorok.h"

#include <iostream> //debug

bool Octorok::m_registerit = Factory<Enemy>::instance()->registerit("Octorok",
    [](const sf::Vector2f& position) -> std::unique_ptr<Enemy>
    {
        return std::make_unique<Octorok>(*Resources::getResource().getTexture(TEXTURE::Enemies), position);
    });

Octorok::Octorok(const sf::Texture& texture, const sf::Vector2f& position)
	:Enemy(texture, position, sf::Vector2f(12,12),sf::Vector2f(12/2, 12/2)), 
     m_projectile(nullptr), m_currInput(PRESS_DOWN),
     m_moveStrategy(std::make_unique<PatrolMovement>()),
     m_attackStrategy(std::make_unique<Shoot>())
{
    setDirection(DIRECTIONS::Down);
	setGraphics(ANIMATIONS_POSITIONS::OctorokDown, 2);
	updateSprite();
    setHp(2);
}

void Octorok::update(const sf::Time& deltaTime)
{ 
    bool standing = false;
    bool attacking = false;
    auto directionChange = m_directionChangeClock.getElapsedTime().asSeconds();
    if (directionChange >= 1.0f) // Change direction every 1 seconds
    {
        setMoveStrategy(std::make_unique<PatrolMovement>());
        setAttackStrategy(std::make_unique<Shoot>());
        
        int randomMovment = rand() % 4;

        switch (randomMovment)
        {
        case 3:
            setMoveStrategy(std::make_unique<Standing>());
            PerformMove();
			std::cout << "Octorok is attacking" << std::endl;
            PerformAttack();
			break;            
        default:
            break;
        }
    }

    PerformMove();
    updateGraphics(deltaTime);
    updateSprite();

    if(getHp() <= 0)
    {
        destroy();
    }
}

void Octorok::attack()
{
	setAttacking(true);
}

sf::Vector2f Octorok::getLinkPos()
{
    return sf::Vector2f();
}

const sf::Vector2u& Octorok::getAnimationTexturePosition(Input side)
{
    switch (side)
    {
    case PRESS_UP:
        return ANIMATIONS_POSITIONS::OctorokUp;
    case PRESS_DOWN:
        return ANIMATIONS_POSITIONS::OctorokDown;
    case PRESS_LEFT:
        return ANIMATIONS_POSITIONS::OctorokLeft;
    case PRESS_RIGHT:
        return ANIMATIONS_POSITIONS::OctorokRight;
    }
}

void Octorok::setMoveStrategy(std::unique_ptr<MovementStrategy> move)
{
    m_moveStrategy = std::move(move);
}
void Octorok::PerformMove()
{
    m_moveStrategy->move(m_currInput, *this, &m_directionChangeClock);
}

void Octorok::setAttackStrategy(std::unique_ptr<AttackStrategy> attack)
{
    m_attackStrategy = std::move(attack);
}

void Octorok::PerformAttack()
{
    m_attackDuration = sf::seconds(0.3f);
    m_attackStrategy->attack(m_attackDuration, m_attackTimer, m_projectile, *this);
}

std::unique_ptr<Inanimate> Octorok::getAttack()
{
    setAttacking(false);
    return std::move(m_projectile);
}