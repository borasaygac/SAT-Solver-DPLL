#include <string>
#include <unordered_map>
#include <vector>
#include <queue>
#include <stack>
#ifndef MYHEADER_HPP
#define MYHEADER_HPP
extern int numOfVars;    // n = num of vars
extern int numOfClauses; //

enum Values {
  FALSE,
  TRUE,
  FREE,
};

struct Variable {
  Values val = Values::FREE;
  std::vector<int> pos_occ;
  std::vector<int> neg_occ;
  bool forced;
  // int bd; // branching depth
};

struct Clause {
  int satLiteral = 0;
  std::vector<int> literals;
  int active;
};

// Queue where unit clauses found in DPLL will be added to.
extern std::queue<int> unitQueue;

// Default indexing value for DPLL if queue is empty
extern int CurVar;

enum class State {
    DEFAULT,
    BACKTRACK,
};

extern State state;

// List of clauses (1-indexed)
extern std::vector<Clause> cnf;

// List of variables (1-indexed)
extern std::vector<Variable> variables;
// Stack of variables with assigned values
extern std::stack<int> assig;

bool dpll(int curVar = CurVar);

void unitProp();
#endif