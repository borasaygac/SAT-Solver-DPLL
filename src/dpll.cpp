#include <string>
#include <vector>

#include "../include/cnf.hpp"

bool dpll(std::vector<Clause> &cnf, std::vector<Variable> &variables) {
  int count = 1;
  *variables[1].val = true;
  for (int i = 0; i < variables[1].pos_occ.size(); i++) {
    if (cnf[variables[1].pos_occ[i]].satLiteral != 0) {
      cnf[variables[1].pos_occ[i]].satLiteral = 1; // to be changed the var index
    }
  }
  for (int i = 0; i < variables[1].neg_occ.size(); i++) {
    if (cnf[variables[1].neg_occ[i]].satLiteral == 0) // check if clause fullfilled
      cnf[variables[1].neg_occ[i]].active--;
    if (cnf[variables[1].neg_occ[i]].active == 1) {
      // queue
    }
    if (cnf[variables[1].neg_occ[i]].active == 0) {
      // Backtracking and report conflict
    }
    return true;
  }
}
