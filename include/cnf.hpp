#include <string>
#include <unordered_map>
#include <vector>

int numOfVars;
int numOfClauses;

struct Variable {
  bool *val = nullptr;
  std::vector<int> pos;
  std::vector<int> neg;
  bool forced;
};

struct Clause {
  int satLiteral;
  std::vector<int> literals;
  int active;
};

std::vector<Clause> cnf;
std::vector<Variable> variables;

bool dpll(std::vector<std::vector<int>> cnf,
          std::unordered_map<int, bool> &assignment);
