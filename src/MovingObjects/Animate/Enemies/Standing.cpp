#include "Standing.h"

void Standing::move(Input& direction, Enemy& enemy, sf::Clock* directionChangeClock)
{
	if (directionChangeClock->getElapsedTime().asSeconds() >= 1.0f) // Change direction every 2 seconds
	{
		direction = STANDING;
		std::cout << "standing\n";
		directionChangeClock->restart();
	}
}
