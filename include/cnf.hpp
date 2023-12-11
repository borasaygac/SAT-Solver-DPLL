#include <string>
#include <unordered_map>
#include <vector>
#ifndef MYHEADER_HPP
#define MYHEADER_HPP
extern int numOfVars;    // n = num of vars
extern int numOfClauses; //

struct Variable {
  bool *val;
  std::vector<int> pos_occ;
  std::vector<int> neg_occ;
  bool forced;
  // int bd; // branching depth
};

struct Clause {
  int satLiteral;
  std::vector<int> literals;
  int active;
};

extern std::vector<Clause> cnf;         // F = List of clauses
extern std::vector<Variable> variables; // V = list of vars

bool dpll(std::vector<Clause> &cnf, std::vector<Variable> &variables);
#endif