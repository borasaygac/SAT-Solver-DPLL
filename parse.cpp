#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

struct Clause {
    std::vector<int> literals;
};

struct CNFFormula {
    std::vector<Clause> clauses;
};

CNFFormula parseDIMACS(const std::string& filename) {
    std::ifstream file(filename);
    CNFFormula formula;
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == 'c' || line[0] == 'p') {
                continue; // Skip comments and problem specification lines
            } else {
                std::istringstream iss(line);
                Clause clause;
                int literal;
                while (iss >> literal && literal != 0) {
                    clause.literals.push_back(literal);
                }
                if (!clause.literals.empty()) {
                    formula.clauses.push_back(clause);
                }
            }
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }

    return formula;
}

int main() {
    // Replace "your_file_path.dimacs" with your DIMACS file path
    CNFFormula parsedFormula = parseDIMACS("DIMACS/test1.cnf");

    // Access parsed data
    for (const auto& clause : parsedFormula.clauses) {
        std::cout << "Clause: ";
        for (const auto& literal : clause.literals) {
            std::cout << literal << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
