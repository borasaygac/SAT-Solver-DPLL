#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

#include "../include/cnf.hpp"

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
        variables[std::abs(clause.literals[clause.w2])].val == FREE;
        while (clause.w2 < clause.literals.size()) {
          if ((variables[std::abs(clause.literals[clause.w2])].val == TRUE &&
               clause.literals[clause.w2] > 0) ||
              (variables[std::abs(clause.literals[clause.w2])].val == FALSE &&
               clause.literals[clause.w2] < 0))
            break;
          if (variables[std::abs(clause.literals[clause.w2])].val == FREE) {
            clause.literals[clause.w2] > 0
                ? variables[std::abs(clause.literals[clause.w2])].val = TRUE
                : variables[std::abs(clause.literals[clause.w2])].val = FALSE;
            break;
          }
          clause.w2++;
        }
        while (clause.w1 < clause.literals.size()) {
          if (((variables[std::abs(clause.literals[clause.w1])].val == TRUE &&
                clause.literals[clause.w1] > 0) ||
               (variables[std::abs(clause.literals[clause.w1])].val == FALSE &&
                clause.literals[clause.w1] < 0)) &&
              clause.w1 != clause.w2)
            break;
          if (variables[std::abs(clause.literals[clause.w1])].val == FREE) {
            clause.literals[clause.w1] > 0
                ? variables[std::abs(clause.literals[clause.w1])].val = TRUE
                : variables[std::abs(clause.literals[clause.w1])].val = FALSE;
            break;
          }
          clause.w1++;
        }
        cnf.push_back(clause);
      }
      count++;
    }
    file.close();
  } else {
    printf("Unable to open file");
  }
}

bool checkAllClauses() {
  int count = 0;
  for (int i = 1; i <= numOfClauses; i++) {
    if (cnf[i].satLiteral != 0) {

      count++;
    }
  }
  if (count == numOfClauses) {
    std::cout << "All clauses satisfied!"
              << "\n";
    std::cout << "Model: ";

  } else {
    std::cout << " Not all clauses satisfied. Number of satisfied clauses is "
              << count << " != " << numOfClauses << "\n";
  }
  std::cout << "[";
  for (int i = 1; i < numOfVars; i++) {
    int val = variables[i].val == 0 ? -i : i;
    std::cout << val << ", ";
  }
  int val = variables[numOfVars].val == 0 ? -numOfVars : numOfVars;
  std::cout << val;
  std::cout << "]";
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
