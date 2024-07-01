#include "WizardBoss.h"
#include <cmath>

#include <iostream> // Debug

bool WizardBoss::m_registerit = Factory<Enemy>::instance()->registerit("WizardBoss",
    [](const sf::Vector2f& position) -> std::unique_ptr<Enemy>
    {
        return std::make_unique<WizardBoss>(*Resources::getResource().getTexture(TEXTURE::Boss), position);
    });

WizardBoss::WizardBoss(const sf::Texture& texture, const sf::Vector2f& position)
    :Enemy(texture, position, sf::Vector2f(12.f * 0.8f, 12.f * 0.8f), sf::Vector2f(-2, -2)),
     m_currInput(PRESS_RIGHT),
     m_moveStrategy(std::make_unique<SmartMovement>()), 
     m_attackStrategy(std::make_unique<Stab>()),
     m_weapon(nullptr), m_invincible(false)
{
    setDirection(DIRECTIONS::Down);
    setGraphics(ANIMATIONS_POSITIONS::BossDown, 2, true);
    updateSprite();
    setHp(10);
    
}

WizardBoss::~WizardBoss()
{
    if (m_link)
    {
        m_link->RemoveObserver(this);
    }
}

void WizardBoss::update(const sf::Time& deltaTime)
{
    Enemy::updateHitAnimation(deltaTime);
    Enemy::update(deltaTime);
    
    sf::Vector2f currentPosition = getSprite().getPosition();

    //setPhase
    if (!(getHp() % 4 == 0)) {


        setMoveStrategy(std::make_unique<SmartMovement>());
        setAttackStrategy(std::make_unique<Stab>());
        if (distance(currentPosition, m_linkPos) < 28.0f) {

            PerformAttack();
            m_weapon->setBool();
        }
    }
    else{
        auto p = dynamic_cast<PositionMovement*>(m_moveStrategy.get());
        auto s = dynamic_cast<Standing*>(m_moveStrategy.get());

        if(!p && !s){
            auto posmove = std::make_unique<PositionMovement>();
            posmove->setDestination(sf::Vector2f(251,124)); //NEED TO CHANGE THE DESTINATION WHEN WE HAVE A LEVEL
            setMoveStrategy(std::move(posmove));
            m_invincible = true;
            m_shootingPhase = true;
            m_shootingPhaseTimer.restart();
        }
        //5x5 pixels threshold from the desired position
        auto sh = dynamic_cast<Shoot*>(m_attackStrategy.get());
        if((getPosition().x< 256 && getPosition().x > 245) && (getPosition().y< 129 && getPosition().y > 119) && !sh){
            setAttackStrategy(std::make_unique<Shoot>());
            setMoveStrategy(std::make_unique<Standing>());
            setGraphics(ANIMATIONS_POSITIONS::BossDown,2);
            m_shootIntervalTimer.restart();
        }
        if(m_shootingPhaseTimer.getElapsedTime() >= shootingPhaseDuration){
            m_shootingPhase = true;
            m_invincible = false;
            setHp(getHp() - 1);
        }
        
    }
    if(m_shootingPhase && m_shootIntervalTimer.getElapsedTime() >= shootInterval){//add condition to shoot only after a specific time interval
        PerformAttack();
        m_weapon->setBool();
        m_shootIntervalTimer.restart();
    }

    PerformMove();
    updateGraphics(deltaTime);
    updateSprite();
    if (getHp() <= MIN_HEALTH)
    {
        destroy();
    }
	setSpeed(1.f);
}


const sf::Vector2u& WizardBoss::getAnimationTexturePosition(Input side)
{
    switch (side)
    {
    case PRESS_UP:
        return ANIMATIONS_POSITIONS::BossUp;
    case PRESS_DOWN:
        return ANIMATIONS_POSITIONS::BossDown;
    case PRESS_LEFT:
        return ANIMATIONS_POSITIONS::BossLeft;
    case PRESS_RIGHT:
        return ANIMATIONS_POSITIONS::BossRight;
    default:
        return ANIMATIONS_POSITIONS::BossDown; //will never get here
    }
}

sf::Vector2f WizardBoss::getLinkPos()
{
    return m_linkPos;
}

void WizardBoss::attack()
{
    setAttacking(true);
}

void WizardBoss::PerformMove()
{
    m_moveStrategy->move(m_currInput, *this, &m_directionChangeClock);
}

void WizardBoss::setAttackStrategy(std::unique_ptr<AttackStrategy> attack)
{
    m_attackStrategy = std::move(attack);
}

void WizardBoss::PerformAttack()
{
    m_attackDuration = sf::seconds(2.f);
    m_attackStrategy->attack(m_attackDuration, m_attackTimer, m_weapon, *this);

}

std::unique_ptr<Inanimate> WizardBoss::getAttack()
{
    setAttacking(false);
    if(m_weapon){
        return std::move(m_weapon);
    }
    else{
        return nullptr;
    }
}

bool WizardBoss::m_getInvincible()const{
    return m_invincible;
}

bool WizardBoss::isShootingPhase()const{
    return getHp() % 4 == 0;
}

void WizardBoss::setMoveStrategy(std::unique_ptr<MovementStrategy> move)
{
    m_moveStrategy = std::move(move);
}

float WizardBoss::distance(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    return std::sqrt(dx * dx + dy * dy);
}

EnemyType WizardBoss::getType()const{
    return WIZARDBOSS;
}

//----------observer functions----------
void WizardBoss::updateLinkPosition(const sf::Vector2f& position){
    m_linkPos = position;
}

void WizardBoss::removeLink()
{
    m_link = nullptr;
}

void WizardBoss::registerAsLinkObserver(Link* link){
    m_link = link;
    m_link->RegisterObserver(this);
}