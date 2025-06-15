#ifndef CLYDE_H
#define CLYDE_H

#include "Ghost.h"
#include "GameObject.h"

class Clyde : public Ghost {
public:
    Clyde(std::vector<float> dimensions, std::vector<float> initPosition, sf::Color color);
    void update(std::vector<std::vector<Tile>> map) override;
    void move() override;

private:

};

#endif // CLYDE_H