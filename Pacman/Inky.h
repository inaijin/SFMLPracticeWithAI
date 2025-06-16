#ifndef INKY_H
#define INKY_H

#include "Ghost.h"
#include "GameObject.h"

class Inky : public Ghost {
public:
    Inky(std::vector<float> dimensions, std::vector<float> initPosition, sf::Color color);
    void update(std::vector<std::vector<Tile>>* map) override;
    void move() override;

private:

};

#endif // INKY_H