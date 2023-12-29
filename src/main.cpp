#include "../include/cnf.hpp"
#include <chrono>
int numOfVars;
int numOfClauses;
int numOfUnassigned;
std::vector<Clause> cnf;
std::vector<Variable> variables;
std::queue<int> unitQueue;
int curVar = 1;
Heuristics heuristic = INC;

int main(int argc, char* argv[]) {
    
    // measure CPU time...
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    std::string filename = "DIMACS/test" + std::to_string(std::stoi(argv[1])) + ".cnf";

    if (argc > 2) heuristic = Heuristics(atoi(argv[2]));

    parseDIMACS(filename);
    // std::cout << "Params: vars " << numOfVars << " and clauses " << numOfClauses << "\n";
    // for (const auto& clause : cnf) {
    //     std::cout << "Clause: ";
    //     for (const auto& literal : clause.literals) {
    //         std::cout << literal << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // for (int i = 1; i < numOfClauses + 1; ++i) {
    //     // std::cout << i << " pos clause: ";
    //     // // for (const auto &literal : variables[i].pos_occ) {
    //     // //   std::cout << literal << " ";
    //     // // }
    //     // // std::cout << std::endl;
    //     // std::cout << i << "th Clause: " << cnf[i].w1 << " " << cnf[i].w2 << "\n";
    // }

    dpll();
    printModel();

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

    std::cout << "\nCPU time used: " << duration.count() << " seconds" << std::endl;

    return 0;
}
