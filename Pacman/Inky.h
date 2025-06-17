#ifndef INKY_H
#define INKY_H

#include "Ghost.h"

class Inky : public Ghost {
public:
    Inky(std::vector<float> dimensions, std::vector<float> initPosition, sf::Color color);

private:
    double calculateReward(const sf::Vector2f& old_position, const Pacman& pacman, const Blinky* blinky) override;
};

#endif // INKY_H