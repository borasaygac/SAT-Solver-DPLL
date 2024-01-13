#include <stdio.h>

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#ifndef MYHEADER_HPP
#define MYHEADER_HPP

extern int numOfVars;
extern int numOfClauses;
// num of not yet assigned variables;
// return true if equal to 0.
extern int numOfUnassigned;

enum Heuristics { INC, DLIS, DLCS, MOM, JW };

enum Assig {
    FALSE,
    TRUE,
    FREE,
};

enum Polarity { NEG, POS, MIX, UNSET };

struct Variable {
    Assig val = FREE;

    std::set<int> static_pos_occ;  // All clauses where var appears as pos watched literal
    std::set<int> static_neg_occ;  // All clauses where var appears as neg watched literal

    std::set<int> pos_occ;  // All clauses where var appears as pos watched literal
    std::set<int> neg_occ;  // All clauses where var appears as neg watched literal

    bool forced = false;
    bool enqueued = false;
    bool prioPureLit = false;
};

struct Clause {
    std::vector<int> literals;
    int active;
    int sat = 0;
};

extern Heuristics heuristic;

// the currently processed variable
extern int curVar;

extern int numOfSatClauses;

// the currently processed unit literal
extern int curProp;

// flag to determine whether to backtrack or not
extern int backtrackFlag;

// int for minimal clause width
extern int minimalWidth;

extern std::set<int> minimalClauses;

// list of clauses (1-indexed)
extern std::vector<Clause> cnf;

// list of variables (1-indexed)
extern std::vector<Variable> vars;

// set of unsatisfied clauses
extern std::set<int> satClauses;

extern std::queue<int> pureLitQueue; 

// queue storing unit literals
extern std::queue<int> unitQueue;

// stack of variables with assigned values
extern std::stack<int> assig;

extern std::priority_queue<int> heap;

void parseDIMACS(std::string filename);

void* dpll(void* arg);

void pureLiteralElimination();

void unitPropagate();

// chooses literals according to the used heuristic
void chooseLiteral();

void chooseINC();

void chooseDLIS();

void chooseDLCS();

/*-------------------------------------------------------------------------*/
void chooseMOM();

void chooseJW();

// updates the watched literals after a new assignment is made
void updateCNF(int assertedVar);

void updateBacktrack(int unassignedVar);

// handles conficts and signals UNSAT
void backtrack();

// evaluates the literal under its current assignment
bool evaluateLiteral(int literal);

void printModel(int res);

void verifyModel();

#endif