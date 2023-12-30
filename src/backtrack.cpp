#include <string>
#include <vector>
#include <queue>
#include <cmath>

#include "../include/cnf.hpp"
#include <iostream>

bool backtrack() {
  while (variables[assig.top()].forced) { // until the last branching variable.
    int toUnassign = assig.top(); 
    variables[toUnassign].setValue(FREE);
    assig.pop();
    printf("backtrack intro");
  }

  if (assig.empty())
    return false; // UNSAT

  // clear unit queue

  while(!unitQueue.empty()) unitQueue.pop();

  // Most recent branching variable
  int b = assig.top();

  // Assign negated val
  variables[b].forced = true;
  variables[b].setValue(FREE);
  variables[b].setValue(Assig(int(2 - std::pow(2.0, variables[b].getValue()))));

  curVar = b;
  // UP

  return true;
}