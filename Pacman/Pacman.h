#ifndef PACMAN_H
#define PACMAN_H

#include "Tile.h"
#include "GameObject.h"

class Pacman : public GameObject {
public:
    Pacman(std::vector<float> dimensions, std::vector<float> initPosition);
    void update(std::vector<std::vector<Tile>>* map) override;
    bool isPowerUpActive() const { return powerUpActive; }

private:
    bool powerUpActive = false;
    sf::Clock powerUpClock;
    sf::Time powerUpDuration;

    void handleInput();
    void handleColitionWithPowerUp(std::vector<std::vector<Tile>>* map);
};

#endif // PACMAN_H