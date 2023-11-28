#include <vector>
#include <unordered_map>

std::vector<std::vector<int>> cnf;

bool dpll(std::vector<std::vector<int>> cnf, std::unordered_map<int, bool>& assignment);
