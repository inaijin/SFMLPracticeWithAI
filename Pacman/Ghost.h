#ifndef GHOST_H
#define GHOST_H

#include "GhostAI.h"
#include "Pacman.h"
#include "GameObject.h"

class Blinky;

class Ghost : public GameObject {
public:
    Ghost(std::vector<float> dimensions, std::vector<float> initPosition, sf::Color color);
    void update(const Pacman& pacman, const Blinky* blinky, std::vector<std::vector<Tile>>* map);

protected:
    std::unique_ptr<GhostAI> ai;
    virtual std::string createAIState(const Pacman& pacman) const;
    virtual double calculateReward(const sf::Vector2f& old_position, const Pacman& pacman, const Blinky* blinky) = 0;
    float distance(const sf::Vector2f& p1, const sf::Vector2f& p2);

};

#endif // GHOST_H