#pragma once

#include "LinkState.h"
#include "LinkAttackState.h"
#include "LinkStandingState.h"
#include "Link.h"

class LinkShieldMovingState: public LinkState
{
public:
    LinkShieldMovingState(Input);
    virtual std::unique_ptr<LinkState> handleInput(Input, bool)override;
    virtual void enter(Link&) override;

private:
    Input m_direction;    
};