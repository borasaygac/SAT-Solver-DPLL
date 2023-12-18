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

    // skip comment lines
    while (line[0] == 'c') {
      //The line below shows the skipped comments.
      //std::cout << "Comment: " << line << std::endl;
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

bool checkAllClauses(std::vector<Clause> &cnf) {
  int count = 0;
  for (Clause clause : cnf) {
    if (clause.satLiteral != 0) {
      count++;
    }
  }
  if (count == numOfClauses) {
    std::cout << "All clauses satisfied " << count << " = " << numOfClauses
              << "\n";
    return true;
  }
  std::cout << " Not all clauses satisfied. Number of satisfied clauses is "
            << count << " != " << numOfClauses << "\n";
  return false;
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

  for (int i = 0; i < numOfVars + 1; ++i) {
    std::cout << i << " pos clause: ";
    for (const auto &literal : variables[i].pos_occ) {
      std::cout << literal << " ";
    }
    std::cout << std::endl;
  }

  dpll(cnf, variables);
  std::cout << *(variables[1].val);
  checkAllClauses(cnf);
  return 0;
}
