#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

#ifndef MYHEADER_HPP
#define MYHEADER_HPP
extern int numOfVars;     // n = num of vars
extern int numOfClauses;  //

enum Heuristics { INC, DLIS, DLCS, MOM, JW };

enum Assig {
    FALSE,
    TRUE,
    FREE,
};

struct Variable {
    Assig val = FREE;
    std::vector<int> pos_watched;
    std::vector<int> neg_watched;
    bool forced;
    int pos_occ;
    int neg_occ;
};

struct Clause {
    std::vector<int> literals;
    int w1 = 0;
    int w2 = 1;
    int satLiteral = 0;
};

extern Heuristics heuristic;

// Default indexing value for DPLL if queue is empty
extern int CurVar;

// List of clauses (1-indexed)
extern std::vector<Clause> cnf;

// List of variables (1-indexed)
extern std::vector<Variable> variables;

// Queue where unit clauses found in DPLL will be added to.
extern std::queue<int> unitQueue;

// Stack of variables with assigned values
extern std::stack<int> assig;

// DPLL Algorithm Function Call
bool dpll(int curVar = CurVar);

// Check all Clauses for whether they are satisfied
bool checkAllClauses();

void unitProp();
#endif