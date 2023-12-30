#include <unistd.h>

#include <chrono>
#include <iostream>

#include "../include/cnf.hpp"

int numOfVars;
int numOfClauses;
int numOfUnassigned;
std::vector<Clause> cnf;
std::vector<Variable> vars;
std::queue<int> unitQueue;
std::stack<int> assig;
int curVar = 1;
Heuristics heuristic = INC;

int main(int argc, char* argv[]) {
    // measure CPU time...
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    std::string filename = "DIMACS/test" + std::to_string(std::stoi(argv[1])) + ".cnf";

    if (argc > 2) heuristic = Heuristics(atoi(argv[2]));

    parseDIMACS(filename);


    dpll();
    printModel();

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

    std::cout << "\nCPU time used: " << duration.count() << " seconds" << std::endl;

    return 0;
}
