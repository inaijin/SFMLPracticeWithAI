#ifndef PINKY_H
#define PINKY_H

#include "Ghost.h"
#include "GameObject.h"

class Pinky : public Ghost {
public:
    Pinky(std::vector<float> dimensions, std::vector<float> initPosition, sf::Color color);
    void update(std::vector<std::vector<Tile>>* map) override;
    void move() override;

private:

};

#endif // PINKY_H