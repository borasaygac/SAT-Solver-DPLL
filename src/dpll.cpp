#include <string>
#include <vector>

#include "../include/cnf.hpp"
#include <iostream>
#include <queue>

bool dpll(std::vector<Clause> &cnf, std::vector<Variable> &variables) {
  // While loop
  std::queue<int> q;
  int varSize = variables.size();
  int curVar;
  if (q.empty()) {
    curVar = 1;
  } else {
    curVar = q.front();
    q.pop();
  }

  while (variables[curVar].val != nullptr) {

    *(variables[curVar].val) = true;
    std::cout << "Current Var Val:" << *variables[curVar].val << '\n';

    // for positive occurances

    for (int i = 0, size = variables[curVar].pos_occ.size(); i < size; i++) {
      if (cnf[variables[curVar].pos_occ[i]].satLiteral == 0) {
        cnf[variables[curVar].pos_occ[i]].satLiteral = curVar;
        std::cout << "Clause " << variables[curVar].pos_occ[i]
                  << " satisfied by " << curVar << '\n';
      }
    }

    // for negative occurances

    for (int i = 0, size = variables[curVar].neg_occ.size(); i < size; i++) {
      std::cout << "in for loop 1" << '\n';
      // decrement active literals
      cnf[variables[curVar].neg_occ[i]].active--;
      std::cout << "active lit. no decremented to "
                << cnf[variables[curVar].neg_occ[i]].active << '\n';
      // if active lit. == 1
      if (cnf[variables[curVar].neg_occ[i]].active == 1) {
        std::cout << "active lit. == 1 " << '\n';
        // find unique free lit

        int clauseWidth = cnf[variables[curVar].neg_occ[i]].literals.size();
        for (int j = 0; j < clauseWidth; j++) {
          std::cout << "in for loop 2" << '\n';
          int varToCheck = cnf[variables[curVar].neg_occ[i]].literals[j];
          if (variables[varToCheck].val == nullptr) {
            // enqueue a
            std::cout << "in the for loop 3" << '\n';
            std::cout << "var to be added= "
                      << varToCheck << '\n';
            q.push(varToCheck);
            std::cout << "queue front= " << q.front() << '\n';
          }
        }
      }

      // if active lit. == 0
      if (cnf[variables[curVar].neg_occ[i]].active == 1) {
        // report conflict
      }
    }
    std::cout << "queue size= " << q.size() << '\n';
    curVar++;
  }
  return true;
}
