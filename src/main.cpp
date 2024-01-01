#include <unistd.h>

#include <chrono>
#include <iostream>

#include "../include/cnf.hpp"

int numOfVars;
int numOfClauses;
int numOfUnassigned;
std::vector<Clause> cnf;
std::vector<Variable> vars;
std::set<int> satClauses;
std::queue<int> unitQueue;
std::stack<int> assig;
int curVar = 1;
int curProp;

Heuristics heuristic = INC;

int main(int argc, char* argv[]) {
    std::ofstream outputFile("output.txt");  // Open a file stream for writing

    if (outputFile.is_open()) {
        // Redirecting std::cout to write to the file
        std::streambuf* coutBuffer = std::cout.rdbuf();
        std::cout.rdbuf(outputFile.rdbuf());
    }
    // measure CPU time...
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    std::string filename = "inputs/unsat/" + std::string(argv[1]) + ".cnf";

    if (argc > 2) heuristic = Heuristics(atoi(argv[2]));

    parseDIMACS(filename);

    pthread_t thread;

    if (pthread_create(&thread, NULL, dpll, NULL)) {
        std::cerr << "Error: Unable to create thread." << std::endl;
        return -1;
    }

    // Wait for the child thread to finish
    void* res;
    pthread_join(thread, &res);

    printModel((intptr_t)res);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

    std::cout << "\nCPU time used: " << duration.count() << " seconds\n" << std::endl;

    return 0;
}
