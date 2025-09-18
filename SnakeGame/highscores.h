#pragma once
#include <vector>
#include <string>

void saveScore(int score, const std::string& filename);
std::vector<int> loadScores(const std::string& filename);