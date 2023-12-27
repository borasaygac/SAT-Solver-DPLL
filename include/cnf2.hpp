#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

#ifndef MYHEADER_HPP
#define MYHEADER_HPP
extern int numOfVars;    // n = num of vars
extern int numOfClauses; //

enum Assign {
  FALSE,
  TRUE,
  FREE,
};

enum Polarity { NEG = -1, POS = 1, MIX = 0, UNDEF = 2 };

struct Variable {
  Assign val = FREE;
  std::vector<int> pos_occ;
  std::vector<int> neg_occ;
  bool forced;
  std::vector<int> watched_occ;
  Polarity polarity = UNDEF;
  // int bd; // branching depth
};

struct Clause {
  int satLiteral = 0;
  std::vector<int> literals;
  int active;
  int *w1 = nullptr; // to not initialize without an address
  int *w2 = nullptr;
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

// DPLL Algorithm Function Call
bool dpll(int curVar = CurVar);

// Check all Clauses for whether they are satisfied
bool checkAllClauses();

// Parse Dimacs function call
void parseDIMACS2(const std::string &filename);

void unitProp();
#endif