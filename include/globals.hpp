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

enum Heuristics { INC, DLIS, DLCS, JW, MOM };

enum Assig {
    FALSE,
    TRUE,
    FREE,
};

enum Polarity { NEG, POS, MIX };

struct Variable {
   private:
    Assig val = FREE;

   public:
    // std::set<int> pos_pol;  // = {1,2};  All clauses where var appears as pos watched literal
    //     std::set<int>
    //         neg_poll;  // = {3,4} All clauses where var appears as neg watched literal
    //             //    (1 2 -3) (1 -2 3 4) (-1 2 -4) (-1 3 -4)
    //             // clause x sat => x is in neg_poll => erase x from neg_poll
    //             // if neg_pol.empty() => pureLiter => set var to 1

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
    int sat = -1;
};

extern Heuristics heuristic;

// the currently processed variable
extern int curVar;

// the currently processed unit literal
extern int curProp;

// list of clauses (1-indexed)
extern std::vector<Clause> clauses;

// list of variables (1-indexed)
extern std::vector<Variable> vars;

// set of unsatisfied clauses
extern std::set<int> satClauses;

// queue storing unit literals
extern std::queue<int> unitQueue;

// stack of variables with assigned values
extern std::stack<int> assig;

#endif
