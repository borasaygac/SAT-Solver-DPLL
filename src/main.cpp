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
int CurVar = 1;
Heuristics heuristic = INC;

void parseDIMACS(const std::string& filename) {
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
        variables.resize(numOfVars + 1);  // vars in DIMACS are 1-indexed
        for (int i = 0; i < numOfVars + 1; i++) {
            Variable v;
            variables[i] = v;
        }
        Clause dummy;
        cnf.push_back(dummy);  // push dummy clause on cnf[0] to ensure 1-index.
        int count = 1;         // what clause are we processing?
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            Clause clause;
            int literal;
            while (iss >> literal && literal != 0) {
                // not precise if the literal appears multiple times in the
                // clause (unlikely)
                (literal > 0) ? variables[std::abs(literal)].pos_occ++ : variables[std::abs(literal)].neg_occ++;

                clause.literals.push_back(literal);
            }

            if (!clause.literals.empty()) {
                // if unit clause, push to unit queue
                if (clause.literals.size() == 1) unitQueue.push(clause.literals[0]);

                // else link the init watched literals to their respective entry in variables
                else {
                    clause.literals[0] > 0 ? variables[std::abs(clause.literals[0])].pos_watched.push_back(count)
                                           : variables[std::abs(clause.literals[0])].neg_watched.push_back(count);

                    clause.literals[1] > 0 ? variables[std::abs(clause.literals[1])].pos_watched.push_back(count)
                                           : variables[std::abs(clause.literals[1])].neg_watched.push_back(count);
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

int main(int argc, char* argv[]) {
    std::string filename = "DIMACS/test" + std::to_string(std::stoi(argv[1])) + ".cnf";

    if (argc > 2) heuristic = Heuristics(atoi(argv[2]));

    parseDIMACS(filename);
    std::cout << "Params: vars " << numOfVars << " and clauses " << numOfClauses << "\n";
    for (const auto& clause : cnf) {
        std::cout << "Clause: ";
        for (const auto& literal : clause.literals) {
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
