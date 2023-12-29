#include <stdio.h>

#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

#include "../include/cnf.hpp"

void parseDIMACS(std::string filename) {
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
        numOfUnassigned = numOfVars;
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