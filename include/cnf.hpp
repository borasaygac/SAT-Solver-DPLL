#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>


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
    std::vector<int> pos_watched;  // All clauses where var appears as pos watched literal
    std::vector<int> neg_watched;  // All clauses where var appears as neg watched literal
    bool forced;
    int pos_occ;  // number of clauses var appears as pos literal
    int neg_occ;  // number of clauses var appears as neg literal
    void setValue(Assig _assig) {
        val = _assig;
        _assig != FREE ? numOfUnassigned-- : numOfUnassigned++;
    }
    Assig getValue() {
      return val;
    }
};

struct Clause {
    std::vector<int> literals;
    int w1 = 0;
    int w2 = 1;
    int satLiteral = 0;
};

extern Heuristics heuristic;

// the currently processed variable
extern int curVar;

// list of clauses (1-indexed)
extern std::vector<Clause> cnf;

// list of variables (1-indexed)
extern std::vector<Variable> variables;

// queue storing unit literals
extern std::queue<int> unitQueue;

// stack of variables with assigned values
extern std::stack<int> assig;

void parseDIMACS(std::string filename);

bool dpll();

bool printModel();

// evaluates the literal under its current assignment
bool evaluateLiteral(int literal);

void chooseLiteral();

// updates the clauses after a new assignment is made
void updateCNF(int literal);

void unitPropagate();
#endif