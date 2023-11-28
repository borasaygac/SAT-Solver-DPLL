#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

#include "../include/cnf.hpp"

std::vector<std::vector<int>> parseDIMACS(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::vector<int>> f;
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            if (line[0] == 'c' || line[0] == 'p') {
                continue; // Skip comments and problem specification lines
            } else {
                std::istringstream iss(line);
                std::vector<int> clause;
                int literal;
                while (iss >> literal && literal != 0) {
                    clause.push_back(literal);
                }
                if (!clause.empty()) {
                    f.push_back(clause);
                }
            }
        }
        file.close();
    } else {
       printf("Unable to open file");
    }

    return f;
}

int main(int argc, char* argv[]) {

    std::string filename = "DIMACS/test" + std::to_string(std::stoi(argv[1])) + ".cnf";

    cnf = parseDIMACS(filename);
    
    for (const auto& clause : cnf) {
        std::cout << "Clause: ";
        for (const auto& literal : clause) {
            std::cout << literal << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
