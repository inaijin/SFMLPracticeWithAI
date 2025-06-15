#ifndef BLINKY_H
#define BLINKY_H

#include "Ghost.h"
#include "GameObject.h"

class Blinky : public Ghost {
public:
    Blinky(std::vector<float> dimensions, std::vector<float> initPosition, sf::Color color);
    void update(std::vector<std::vector<Tile>> map) override;
    void move() override;

private:

};

#endif // BLINKY_H