#include <math.h>
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

    std::set<int> static_pos_occ;  // All clauses where var appears as pos literal
    std::set<int> static_neg_occ;  // All clauses where var appears as neg literal

    std::set<int> pos_occ;  // All clauses where var appears as pos literal
    std::set<int> neg_occ;  // All clauses where var appears as neg literal

    bool forced = false;
    bool enqueued = false;

    std::queue<int> localMinClauses;
    int localMinWidth;

    int posMOM = 0;
    int negMOM = 0;
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

extern int dc;

extern int btc;

extern int mcc;

extern int numOfMinClauses;

// flag to determine whether to backtrack or not
extern bool backtrackFlag;

// int for minimal clause width
extern int minWidth;

// list of clauses (1-indexed)
extern std::vector<Clause> clauses;

// list of variables (1-indexed)
extern std::vector<Variable> vars;

// set of unsatisfied clauses
extern std::set<int> satClauses;

extern std::queue<int> pureLitQueue;

// queue storing unit literals
extern std::queue<int> unitQueue;

// stack of variables with assigned values
extern std::stack<int> assig;

extern std::queue<int> minClauses;

void parseDIMACS(std::string filename);

// processes pure and unit literals before dpll starts
// sets architecture for chosen heuristic
void preprocess();

void* dpll(void* arg);

void pureLiteralElimination();

void propagate();

// chooses next branching var according to the selected heuristic
extern void (*chooseLiteral)();

extern void (*update)(int assertedVar);

extern void (*updateBacktrack)(int unassignedVar);

void chooseINC();

void chooseDLIS();

void chooseDLCS();

/*-------------------------------------------------------------------------*/
// auto customMOMComparator = [](int left, int right) {
//     return ((vars[left].posCount + vars[left].negCount)*pow(2,2) + (vars[left].negCount*vars[left].posCount)) <
//     ((vars[right].posCount + vars[right].negCount)*pow(2,2) + (vars[right].negCount*vars[right].posCount));  // TODO: add
//     comments
// };

// extern std::set<int, decltype(customMOMComparator)> maxHeap(customMOMComparator);

void chooseMOM();

void chooseJW();

// updates the CNF after a new assignment is made
void updateDef(int assertedVar);

// updates the CNF after succ unassignment in backtrack()
void updateBacktrackDef(int unassignedVar);

// handles conficts and signals UNSAT
void backtrack();

void updateMOM(int assertedVar);

void updateBacktrackMOM(int unassignedVar);

// evaluates the literal under its current assignment
bool evaluateLiteral(int literal);

void printModel(int res);

void verifyModel();

#endif