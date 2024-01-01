#include <stdio.h>

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
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

struct Variable {
   private:
    Assig val = FREE;

   public:
    std::set<int> pos_watched;  // All clauses where var appears as pos watched literal
    std::set<int> neg_watched;  // All clauses where var appears as neg watched literal
    bool forced = false;
    int pos_occ;  // number of clauses var appears as pos literal
    int neg_occ;  // number of clauses var appears as neg literal
    bool enqueued = false;
    void setValue(Assig _assig) {
        // int assertedLit = unitProp ? curProp : curVar;
        if (_assig != FREE && val == FREE)
            numOfUnassigned--;
        else {
            if (_assig == FREE) numOfUnassigned++;

            // else
            //     vars[assertedLit].forced = true;
        }
        val = _assig;
        // printf("num of unassigned: %i \n", numOfUnassigned);

        // vars[assertedLit].enqueued = false;
        // vars[assertedLit].forced = true;
        // assig.push(assertedLit);
        // updateWatchedLiterals(assertedLit);
    }
    Assig getValue() { return val; }
};

struct Clause {
    std::vector<int> literals;
    int w1 = 0;
    int w2 = 1;
    bool sat = false;
};

extern Heuristics heuristic;

// the currently processed variable
extern int curVar;

// the currently processed unit literal
extern int curProp;

// list of clauses (1-indexed)
extern std::vector<Clause> cnf;

// list of variables (1-indexed)
extern std::vector<Variable> vars;

// queue storing unit literals
extern std::queue<int> unitQueue;

// stack of variables with assigned values
extern std::stack<int> assig;

void parseDIMACS(std::string filename);

void* dpll(void* arg);

void unitPropagate();

// chooses literals according to the used heuristic
void chooseLiteral();

// updates the watched literals after a new assignment is made
void updateWatchedLiterals(int literal);

// handles conficts and signals UNSAT
void backtrack();

// evaluates the literal under its current assignment
bool evaluateLiteral(int literal);

void printModel(int res);
#endif