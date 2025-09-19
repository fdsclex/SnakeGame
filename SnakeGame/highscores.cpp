#include "highscores.h"
#include <fstream>
#include <algorithm>

void saveScore(int score, const std::string& filename) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) file << score << std::endl;
}

std::vector<int> loadScores(const std::string& filename) {
    std::vector<int> scores;
    std::ifstream file(filename);
    int score;
    while (file >> score) scores.push_back(score);
    if (scores.size() > 5) scores.resize(5);
    std::sort(scores.rbegin(), scores.rend());
    return scores;
}