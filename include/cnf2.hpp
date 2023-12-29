#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

#ifndef MYHEADER_HPP
#define MYHEADER_HPP
extern int numOfVars;     // n = num of vars
extern int numOfClauses;  //

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
    std::vector<int> watched_occ;
    // int bd; // branching depth
};

struct Clause {
    int satLiteral = 0;
    std::vector<int> literals;
    int active;
    int *w1 = nullptr;  // to not initialize without an address
    int *w2 = nullptr;
};

// Queue where unit clauses found in DPLL will be added to.
extern std::queue<int> unitQueue;

// Default indexing value for DPLL if queue is empty
extern int CurVar;

// List of clauses (1-indexed)
extern std::vector<Clause> cnf;

// List of variables (1-indexed)
extern std::vector<Variable> variables;
// Stack of variables with assigned values
extern std::stack<int> assig;

bool dpll(int curVar = CurVar);

bool checkAllClauses();

void parseDIMACS2(const std::string &filename);

void unitProp();
#endif