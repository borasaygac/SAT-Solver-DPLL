#include <string>
#include <vector>
#include <queue>

#include "../include/cnf.hpp"
#include <iostream>

bool backtrack() {
  while (variables[assig.top()].forced) { // until the last branching variable.
    int toUnassign = assig.top(); 
    variables[toUnassign].val = FREE;
    assig.pop();
    
  }

  if (assig.empty())
    return false; // UNSAT

  // clear unit queue

  while(!unitQueue.empty()) unitQueue.pop();

  // Most recent branching variable
  int b = assig.top();

  // Assign negated val

  variables[b].val = Assig(int(2 - std::pow(2.0, variables[b].val)));

  curVar = b;
  // UP
}