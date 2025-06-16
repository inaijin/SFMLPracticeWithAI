#ifndef GHOST_H
#define GHOST_H

#include "GameObject.h"

class Ghost : public GameObject {
public:
    Ghost(std::vector<float> dimensions, std::vector<float> initPosition, sf::Color color);
    void update(std::vector<std::vector<Tile>>* map) override;
    void virtual move();

private:

};

#endif // GHOST_H