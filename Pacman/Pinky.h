#ifndef PINKY_H
#define PINKY_H

#include "Ghost.h"

class Pinky : public Ghost {
public:
    Pinky(std::vector<float> dimensions, std::vector<float> initPosition, sf::Color color);

private:
    double calculateReward(const sf::Vector2f& old_position, const Pacman& pacman, const Blinky* blinky) override;
};

#endif // PINKY_H