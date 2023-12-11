#include <string>
#include <unordered_map>
#include <vector>

int numOfVars; // n = num of vars
int numOfClauses; //

struct Variable {
  bool *val = nullptr;
  std::vector<int> pos_occ;
  std::vector<int> neg_occ;
  bool forced;
  //int bd; // branching depth
};

struct Clause {
  int satLiteral;
  std::vector<int> literals;
  int active;
};

std::vector<Clause> cnf; // F = List of clauses
std::vector<Variable> variables; // V = list of vars

bool dpll(std::vector<Clause> &cnf, std::vector<Variable> &variables);
