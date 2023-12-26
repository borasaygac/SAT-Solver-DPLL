#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

#include "../include/cnf2.hpp"

void parseDIMACS2(const std::string &filename) {
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
    int count = 1;        // what clause are we processing?
    while (std::getline(file, line)) { // Fill pos and neg_occ for clauses
      std::istringstream iss(line);
      Clause clause;
      int literal;
      while (iss >> literal && literal != 0) {
        (literal > 0) ? variables[std::abs(literal)].pos_occ.push_back(count)
                      : variables[std::abs(literal)].neg_occ.push_back(count);
        clause.literals.push_back(literal);
        }
        clause.w1 = &clause.literals[0]; // Assign the first and second watcher to the first and second literal in clause.
        clause.w2 = &clause.literals[1];
        cnf.push_back(clause);
      }
    count++;
    file.close();
  } else {
    printf("Unable to open file");
  }
}