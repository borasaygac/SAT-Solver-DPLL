#include <string>
#include <vector>

#include "../include/cnf.hpp"

bool dpll(std::vector<Clause>& cnf, std::vector<Variable>& variables) {
  // While loop
  int count = 1;
  *variables[count].val = true;
  for (int i = 0; i < variables[count].pos_occ.size(); i++) {
    if (cnf[variables[count].pos_occ[i]].satLiteral != 0) {
      cnf[variables[count].pos_occ[i]].satLiteral = 1; // to be changed the var index
    }
  }
  for (int i = 0; i < variables[count].neg_occ.size(); i++) {
    if (cnf[variables[count].neg_occ[i]].satLiteral == 0) // check if clause fullfilled
      cnf[variables[count].neg_occ[i]].active--;
    if (cnf[variables[count].neg_occ[i]].active == 1) {
      // queue
    }
    if (cnf[variables[count].neg_occ[i]].active == 0) {
      // Backtracking and report conflict
    }
    return true;
  }
}
