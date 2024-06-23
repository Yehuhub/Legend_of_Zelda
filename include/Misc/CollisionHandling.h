#pragma once

#include "GameObject.h"

#include <typeinfo>
#include <map>
#include <string>
#include <typeindex>

#include "Link.h"
#include "Wall.h"
#include "Pot.h"
#include "WaterTile.h"
#include "Octorok.h"
#include "PigWarrior.h"
#include "Sword.h"
#include "Shield.h"
#include "Projectile.h"
#include "Boulder.h"
#include "LinkArrow.h"

struct UnknownCollision : public std::runtime_error
{
    UnknownCollision(GameObject& a, GameObject& b)
        : std::runtime_error(std::string("Unknown collision of ") + typeid(a).name() + " and " + typeid(b).name())
    {
    }
};

void processCollision(GameObject&, GameObject&);

sf::Vector2i getCollisionDirection(GameObject&, GameObject&);