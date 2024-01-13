#include "../include/cnf.hpp"

void parseDIMACS(std::string filename) {
    std::ifstream file(filename);
    std::string line;

    if (file.is_open()) {
        // parse head of DIMACS
        std::getline(file, line);

        // skip comment lines and empty lines
        while (line[0] == 'c' || line.empty()) {
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
        // numOfUnassigned = numOfVars;
        std::cout << "Number of Variables: " << numOfVars << "\n";
        std::cout << "Number of Clauses: " << numOfClauses << "\n";
        std::cout << "Number of Clauses: " << numOfUnassigned << "\n";

        // parse rest
        vars.resize(numOfVars + 1);  // vars in DIMACS are 1-indexed
        for (int i = 0; i < numOfVars + 1; i++) {
            Variable v;
            vars[i] = v;
        }
        Clause dummy;
        dummy.literals = {};
        dummy.active = -1;
        cnf.push_back(dummy);  // push dummy clause on cnf[0] to ensure 1-index.
        int count = 1;         // what clause are we processing?
        Clause clause;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            if (line[0] == 0) {
                continue;
            }

            int literal;
            while (iss >> literal && literal != 0) {
                // not precise if the literal appears multiple times in the
                // clause (unlikely)
                clause.literals.push_back(literal);
                literal > 0 ? vars[std::abs(literal)].static_pos_occ.insert(count)
                            : vars[std::abs(literal)].static_neg_occ.insert(count);
                // std::cout << "Literal: " << literal << "\n";
            }

            if (literal == 0) {
                if (!clause.literals.empty()) {
                    // std::cout << "Literal: " << clause.literals[0] << "in if" << std::endl;
                    clause.active = clause.literals.size();
                    // if unit clause, push to unit queue
                    if (clause.literals.size() == 1) {
                        // std::cout << "Literal: " << clause.literals[0] << "in if22" << std::endl;
                        if (!vars[std::abs(clause.literals[0])].enqueued) {
                            unitQueue.push(clause.literals[0]);
                            // std::cout << "Pushing " << clause.literals[0] << " on unit queue" << "\n";
                            vars[std::abs(clause.literals[0])].enqueued = true;
                        }
                    }

                    // else also link the second watched literal to their respective entry in variables

                    cnf.push_back(clause);
                    // std::cout << "for clause " << count << ":";
                    for (int i = 0; i < clause.literals.size(); i++) {
                        // std::cout << " " << clause.literals[i];
                    }
                    // std::cout << "\n";

                    clause = {};
                    count++;
                }
            }
        }
        file.close();
    } else {
        printf("Unable to open file");
    }

    for (int i = 1; i <= numOfVars; i++) {
        vars[i].pos_occ = vars[i].static_pos_occ;
        vars[i].neg_occ = vars[i].static_neg_occ;
    }

    // Find pure lits and assign them to pure lit queue
    // TODO: Change the structure where you check only one occ list. Only one is enough.
    for (int i = 1; i <= numOfVars; i++) {
        if (vars[i].static_neg_occ.size() == 0 && vars[i].static_pos_occ.size() > 0) {
            vars[i].prioPureLit = true;
            // std::cout << "Var no: " << i << " is a pure lit"
            //   << "\n"
            //   << std::flush;
            vars[std::abs(i)].enqueued = true;
            pureLitQueue.push(i);
        }
        if (vars[i].static_pos_occ.size() == 0 && vars[i].static_neg_occ.size() > 0) {
            vars[i].prioPureLit = true;
            // std::cout << "Var no: " << i << " is a pure lit"
            //   << "\n"
            //   << std::flush;
            vars[std::abs(i)].enqueued = true;
            pureLitQueue.push(-i);
            // TODO FOR LATER: Fix the queue structure
        }
    }
}