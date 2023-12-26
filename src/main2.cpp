#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

#include "../include/cnf2.hpp"

int numOfVars;
int numOfClauses;
std::vector<Clause> cnf;
std::vector<Variable> variables;
std::queue<int> unitQueue;
State state;
int CurVar = 1;

void parseDIMACS(const std::string &filename) {
  std::ifstream file(filename);
  std::string line;

  if (file.is_open()) {
    // parse head of DIMACS
    std::getline(file, line);

    // skip comment lines
    while (line[0] == 'c') {
      // The line below shows the skipped comments.
      // std::cout << "Comment: " << line << std::endl;
      std::getline(file, line);
    }

    std::istringstream iss(line);
    std::string token;
    std::vector<std::string> tokens;

    while (iss >> token) {
      tokens.push_back(token);
    }
    numOfVars = std::stoi(tokens[2]);
    numOfClauses = std::stoi(tokens[3]);
    std::cout << "Number of Variables: " << numOfVars << std::endl;
    std::cout << "Number of Clauses: " << numOfClauses << std::endl;

    // parse rest
    variables.resize(numOfVars + 1); // vars in DIMACS are 1-indexed
    for (int i = 0; i < numOfVars + 1; i++) {
      Variable v;
      variables[i] = v;
    }
    Clause dummy;
    cnf.push_back(dummy); // push dummy clause on cnf[0] to ensure 1-index. 
    int count = 1; // what clause are we processing?
    while (std::getline(file, line)) { // Fill pos and neg_occ for clauses
      std::istringstream iss(line);
      Clause clause;
      int literal;
      while (iss >> literal && literal != 0) {
        (literal > 0) ? variables[std::abs(literal)].pos_occ.push_back(count)
                      : variables[std::abs(literal)].neg_occ.push_back(count);
        clause.literals.push_back(literal);
      }
        cnf.push_back(clause);
      }
      count++;
    file.close();
  } else {
    printf("Unable to open file");
  }
}

int main(int argc, char *argv[]) {

  std::string filename =
      "DIMACS/test" + std::to_string(std::stoi(argv[1])) + ".cnf";

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

  for (int i = 1; i < numOfClauses + 1; ++i) {
    // std::cout << i << " pos clause: ";
    // // for (const auto &literal : variables[i].pos_occ) {
    // //   std::cout << literal << " ";
    // // }
    // // std::cout << std::endl;
    std::cout << i << "th Clause: " << cnf[i].w1 << " " << cnf[i].w2 << "\n";
  }

  dpll();
  checkAllClauses();
  return 0;
}
