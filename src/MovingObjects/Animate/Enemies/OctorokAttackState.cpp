#include "OctorokAttackState.h"

OctorokAttackState::OctorokAttackState() : m_attackDuration(sf::seconds(0.3f)), m_isAnimationSet(false) {}

std::unique_ptr<OctorokState> OctorokAttackState::handleInput(Input input)
{
    if (m_attackDuration.asSeconds() - m_attackTimer.getElapsedTime().asSeconds() <= 0)
    {
        return std::make_unique<OctorokStandingState>();
    }
    return nullptr;
}

void OctorokAttackState::enter(Octorok& octorok)
{
	m_attackTimer.restart();
    octorok.attack();
}