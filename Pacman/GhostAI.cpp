#include <vector>
#include <algorithm>

#include "GhostAI.h"

GhostAI::GhostAI(double alpha, double gamma, double epsilon)
    : alpha(alpha), gamma(gamma), epsilon(epsilon),
      random_engine(std::random_device{}()),
      uniform_dist(0.0, 1.0) {}

std::vector<double>& GhostAI::getQValues(const std::string& state) {
    if (q_table.find(state) == q_table.end()) {
        q_table[state] = {0.0, 0.0, 0.0, 0.0};
    }
    return q_table.at(state);
}

Action GhostAI::chooseAction(const std::string& state) {
    std::vector<double>& q_values = getQValues(state);

    // Epsilon-Greedy logic:
    // 1. With probability epsilon, we explore by choosing a random action.
    // 2. Otherwise, we exploit by choosing the action with the highest Q-value.

    if (uniform_dist(random_engine) < epsilon) {
        // --- EXPLORE: Choose a random action ---
        int random_action_index = std::uniform_int_distribution<>(0, 3)(random_engine);
        return static_cast<Action>(random_action_index);
    } else {
        // --- EXPLOIT: Choose the best-known action ---
        auto max_it = std::max_element(q_values.begin(), q_values.end());
        int best_action_index = std::distance(q_values.begin(), max_it);
        return static_cast<Action>(best_action_index);
    }
}

void GhostAI::updateQValue(const std::string& state, Action action, double reward, const std::string& next_state) {
    double old_q_value = getQValues(state)[static_cast<int>(action)];
    std::vector<double>& next_q_values = getQValues(next_state);
    double max_next_q = *std::max_element(next_q_values.begin(), next_q_values.end());
    double new_q_value = old_q_value + alpha * (reward + gamma * max_next_q - old_q_value);
    getQValues(state)[static_cast<int>(action)] = new_q_value;
}
