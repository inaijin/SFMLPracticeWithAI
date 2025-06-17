#ifndef BLINKY_H
#define BLINKY_H

#include "Ghost.h"
#include "GameObject.h"

class Blinky : public Ghost {
public:
    Blinky(std::vector<float> dimensions, std::vector<float> initPosition, sf::Color color);

private:
    double calculateReward(const sf::Vector2f& old_position, const Pacman& pacman, const Blinky* blinky) override;
};

#endif // BLINKY_H