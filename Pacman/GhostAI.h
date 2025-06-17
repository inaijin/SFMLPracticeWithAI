#ifndef GHOSTAI_H
#define GHOSTAI_H

#include <map>
#include <vector>
#include <string>
#include <random>

enum class Action {
    Up,
    Down,
    Left,
    Right,
    None
};

class GhostAI {
public:
    GhostAI(double alpha, double gamma, double epsilon);

    Action chooseAction(const std::string& state);

    void updateQValue(const std::string& state, Action action, double reward, const std::string& next_state);

private:
    // Example: "state_key" -> {Q_up, Q_down, Q_left, Q_right}
    std::map<std::string, std::vector<double>> q_table;

    double alpha;   // Learning Rate: How much we accept the new Q-value.
    double gamma;   // Discount Factor: Importance of future rewards.
    double epsilon; // Exploration Rate: Probability of choosing a random action vs. the best one.

    // --- Utility for random number generation (for exploration) ---
    std::mt19937 random_engine;
    std::uniform_real_distribution<> uniform_dist;

    std::vector<double>& getQValues(const std::string& state);
};

#endif // GHOSTAI_H