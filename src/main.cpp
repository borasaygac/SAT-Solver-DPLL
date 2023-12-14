#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../include/cnf.hpp"

int numOfVars;
int numOfClauses;
std::vector<Clause> cnf;
std::vector<Variable> variables;

void parseDIMACS(const std::string &filename) {
  std::ifstream file(filename);
  std::string line;

  if (file.is_open()) {
    // parse head of DIMACS
    std::getline(file, line);
    std::istringstream iss(line);
    std::string token;
    std::vector<std::string> tokens;
    while (iss >> token) {
      tokens.push_back(token);
    }
    numOfVars = std::stoi(tokens[2]);
    numOfClauses = std::stoi(tokens[3]);

    // parse rest
    variables.resize(numOfVars + 1); // vars in DIMACS are 1-indexed
    for (int i = 0; i < numOfVars + 1; i++) {
      Variable v;
      variables[i] = v;
    }
    Clause dummy;
    cnf.push_back(dummy);
    int count = 1; // what clause are we processing?
    while (std::getline(file, line)) {
      std::istringstream iss(line);
      Clause clause;
      int literal;
      while (iss >> literal && literal != 0) {
        (literal > 0) ? variables[std::abs(literal)].pos_occ.push_back(count)
                      : variables[std::abs(literal)].neg_occ.push_back(count);
        clause.literals.push_back(literal);
      }
      if (!clause.literals.empty()) {
        clause.active = clause.literals.size();
        cnf.push_back(clause);
      }
      count++;
    }
    file.close();
  } else {
    printf("Unable to open file");
  }
}

int main(int argc, char *argv[]) {

  std::string filename = "DIMACS/test" + std::to_string(std::stoi(argv[1])) + ".cnf";

  

  parseDIMACS(filename);
  std::cout << "Params: vars " << numOfVars << " and clauses " << numOfClauses
            << "\n";
  for (const auto &clause : cnf) {
    std::cout << "Clause: ";
    for (const auto &literal : clause.literals) {
      std::cout << literal << " ";
    }
    std::cout << std::endl;
  }

  for (int i = 0; i < numOfVars + 1; ++i) {
    std::cout << i << " pos clause: ";
    for (const auto &literal : variables[i].pos_occ) {
      std::cout << literal << " ";
    }
    std::cout << std::endl;
  }

  dpll(cnf, variables);
  std::cout << *(variables[1].val);
  return 0;
}
