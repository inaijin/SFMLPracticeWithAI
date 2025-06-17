#ifndef CLYDE_H
#define CLYDE_H

#include "Ghost.h"

class Clyde : public Ghost {
public:
    Clyde(std::vector<float> dimensions, std::vector<float> initPosition, sf::Color color);

private:
    double calculateReward(const sf::Vector2f& old_position, const Pacman& pacman, const Blinky* blinky) override;
    const sf::Vector2f scatter_target = {30.f, 1100.f}; // A corner to run to
};

#endif // CLYDE_H