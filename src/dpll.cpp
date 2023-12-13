#include <string>
#include <vector>

#include "../include/cnf.hpp"
#include <iostream>
#include <queue>

bool dpll(std::vector<Clause> &cnf, std::vector<Variable> &variables) {
  // While loop
  int count = 1;
  std::queue<int> q;
  while(count != numOfVars){
    if(*(variables[count].val) == true || *(variables[count].val) == false){
      continue;
    }
    *(variables[count].val) = true;
    
    //positive occurances
    for (int i = 0, size = variables[count].pos_occ.size(); i < size; i++) {
      if (cnf[variables[count].pos_occ[i]].satLiteral != 0) {
        cnf[variables[count].pos_occ[i]].satLiteral = count;
      }
    }

    // for every unsatisfied clause C in neg_occ 
    for (int i = 0, size = variables[count].neg_occ.size(); i < size; i++) {
      // decrement active
      cnf[variables[count].neg_occ[i]].active--;
    
      // if act == 1 -> find free unique lit. a in C  
      if (cnf[variables[count].neg_occ[i]].active == 1) {
        for (int vars: cnf[variables[count].neg_occ[i]].literals){
          if(vars == 0){
            q.push(vars);
          } 
        }
      }

      // Backtracking and report conflict
      if (cnf[variables[count].neg_occ[i]].active == 0) {
      }
    }
    count++;
  }
  std::cout << "P";
  return true;
}
