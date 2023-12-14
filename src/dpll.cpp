#include <string>
#include <vector>

#include "../include/cnf.hpp"
#include <iostream>
#include <queue>

bool dpll(std::vector<Clause> &cnf, std::vector<Variable> &variables) {
  // While loop
  std::queue<int> q;
  int varSize = variables.size();
  int curVal;
  if (q.empty()) {
    curVal = 1;
  } else {
    curVal = q.front();
    q.pop();
  }

  while (variables[curVal].val != nullptr) {

    *(variables[curVal].val) = true;
    std::cout << "Current Var Val:" << *variables[curVal].val << '\n';

    // for positive occurances

    for (int i = 0, size = variables[curVal].pos_occ.size(); i < size; i++) {
      if (cnf[variables[curVal].pos_occ[i]].satLiteral == 0) {
        cnf[variables[curVal].pos_occ[i]].satLiteral = curVal;
        std::cout << "Clause " << variables[curVal].pos_occ[i]
                  << " satisfied by " << curVal << '\n';
      }
    }

    // for negative occurances

    for (int i = 0, size = variables[curVal].neg_occ.size(); i < size; i++) {
      std::cout << "in for loop 1" << '\n';
      // decrement active literals
      cnf[variables[curVal].neg_occ[i]].active--;
      std::cout << "active lit. no decremented to "
                << cnf[variables[curVal].neg_occ[i]].active << '\n';
      // if active lit. == 1
      if (cnf[variables[curVal].neg_occ[i]].active == 1) {
        std::cout << "active lit. == 1 " << '\n';
        // find unique free lit

        int clauseWidth = cnf[variables[curVal].neg_occ[i]].literals.size();
        for (int j = 0; j < clauseWidth; j++) {
          std::cout << "in for loop 2" << '\n';
          int varToCheck = cnf[variables[curVal].neg_occ[i]].literals[j];
          if (variables[varToCheck].val == nullptr) {
            // enqueue a
            std::cout << "in the for loop 3" << '\n';
            std::cout << "var to be added= "
                      << cnf[variables[curVal].neg_occ[i]].literals[j] << '\n';
            q.push(cnf[variables[curVal].neg_occ[i]].literals[j]);
            std::cout << "queue front= " << q.front() << '\n';
          }
        }
      }

      // if active lit. == 0
      if (cnf[variables[curVal].neg_occ[i]].active == 1) {
        // report conflict
      }
    }
    std::cout << "queue size= " << q.size() << '\n';
    curVal++;
  }
  return true;
}
