#ifndef PACMAN_H
#define PACMAN_H

#include "Tile.h"
#include "Ghost.h"
class Ghost;
#include "GameObject.h"
#include "GhostAI.h"

class Pacman : public GameObject {
public:
    Pacman(std::vector<float> dimensions, std::vector<float> initPosition);
    void updatePacman(const std::vector<Ghost*>& ghosts, std::vector<std::vector<Tile>>* map);
    bool isPowerUpActive() const { return powerUpActive; }
    void handleColitionWithGhosts(std::vector<Ghost*>* ghosts);
    bool handlePelletAndPowerUpCollisions(std::vector<std::vector<Tile>>* map);
    void setTrainingMode(bool is_training);
    std::unique_ptr<GhostAI>* getAI() { return &ai; }
    void reset() override;

private:
    bool powerUpActive = false;
    std::unique_ptr<GhostAI> ai;
    bool is_training = false;

    sf::Clock powerUpClock;
    sf::Time powerUpDuration;

    void handleInput();
    void handleColitionWithPowerUp(std::vector<std::vector<Tile>>* map);

    void updateAI(const std::vector<Ghost*>& ghosts, std::vector<std::vector<Tile>>* map);
    std::string createAIState(const std::vector<Ghost*>& ghosts, const std::vector<std::vector<Tile>>& map) const;
    double calculateReward(const sf::Vector2f& old_position, const std::vector<Ghost*>& ghosts, bool ate_power_up, bool ate_ghost, bool died) const;
    sf::Vector2f findClosestPellet(const std::vector<std::vector<Tile>>& map) const;
};

#endif // PACMAN_H