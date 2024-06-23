#include "PatrolMovement.h"
#include "PigWarrior.h"

void PatrolMovement::move(Input& direction, Enemy& enemy, sf::Clock* directionChangeClock)
{
    bool up = false;
    bool down = false;
    bool right = false;
    bool left = false;
    if (directionChangeClock->getElapsedTime().asSeconds() >= 1.0f) // Change direction every 2 seconds
    {
        int randomMovment = rand() % 4;

        std::cout << "randomMovment: " << randomMovment << std::endl;

        switch (randomMovment)
        {
        case 0:
            up = true;
            m_direction = PRESS_UP;
            break;
        case 1:
            down = true;
            m_direction = PRESS_DOWN;
            break;
        case 2:
            right = true;
            m_direction = PRESS_RIGHT;
            break;
        case 3:
            left = true;
            m_direction = PRESS_LEFT;
            break;
        default:
            m_direction = STANDING;
            break;
        }
        directionChangeClock->restart();
        direction = m_direction;
    }

    sf::Vector2i currentDirection = enemy.getDirection();
    if (m_direction == PRESS_RIGHT) {
        if (currentDirection != DIRECTIONS::Right) {

            enemy.setGraphics(enemy.getAnimationTexturePosition(PRESS_RIGHT), 2);
            enemy.setDirection(DIRECTIONS::Right);
        }
    }
    else if (m_direction == PRESS_LEFT) {
        if (currentDirection != DIRECTIONS::Left) {
            enemy.setGraphics(enemy.getAnimationTexturePosition(PRESS_LEFT), 2);
            enemy.setDirection(DIRECTIONS::Left);
        }
    }
    else if (m_direction == PRESS_UP) {
        if (currentDirection != DIRECTIONS::Up) {
            enemy.setGraphics(enemy.getAnimationTexturePosition(PRESS_UP), 2);
            enemy.setDirection(DIRECTIONS::Up);
        }
    }
    else if (m_direction == PRESS_DOWN) {
        if (currentDirection != DIRECTIONS::Down) {
            enemy.setGraphics(enemy.getAnimationTexturePosition(PRESS_DOWN), 2);
            enemy.setDirection(DIRECTIONS::Down);
        }
    }
    enemy.move();
}
