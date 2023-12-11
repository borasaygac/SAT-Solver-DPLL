#include <string>
#include <vector>

#include "../include/cnf.hpp"
#include <iostream>

bool dpll(std::vector<Clause> &cnf, std::vector<Variable> &variables) {
  // While loop
  int count = 1;
  *(variables[1].val) = true;

  for (int i = 0; i < variables[count].pos_occ.size(); i++) {
    if (cnf[variables[count].pos_occ[i]].satLiteral != 0) {
      cnf[variables[count].pos_occ[i]].satLiteral = 1;
    }
  }

  for (int i = 0; i < variables[count].neg_occ.size(); i++) {
    // check if clause fullfilled
    if (cnf[variables[count].neg_occ[i]].satLiteral == 0) {
      cnf[variables[count].neg_occ[i]].active--;
    }

    // queue
    if (cnf[variables[count].neg_occ[i]].active == 1) {
    }
    // Backtracking and report conflict
    if (cnf[variables[count].neg_occ[i]].active == 0) {
    }
  }
  std::cout << "P";
  return true;
}
