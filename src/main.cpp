#include <unistd.h>

#include <chrono>
#include <iostream>

#include "../include/cnf.hpp"
#include "../include/fileNames.hpp"

int numOfVars;
int numOfClauses;
int numOfUnassigned;
std::vector<Clause> cnf;
std::vector<Variable> vars;
std::set<int> satClauses;
std::queue<int> unitQueue;
std::stack<int> assig;
std::queue<int> pureLitQueue;
int curVar = 1;
int numOfSatClauses = 0;
int curProp;
bool backtrackFlag = 0;
int minimalWidth = 10000;
std::set<int> minimalClauses;
Heuristics heuristic = INC;
void (*heuristicPointers[5])() = {chooseINC, chooseDLIS, chooseDLCS, chooseMOM, chooseJW};
void (*chooseLiteral)() = nullptr;

int main(int argc, char* argv[]) {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    std::string path = argv[1];

    if (argc > 2) heuristic = Heuristics(std::stoi(argv[2]));

    std::string index;
    for (int i = 1; i < path.length(); i++) {
        index += path[i];
    }

    std::string fileName;

    char* heurAsStrings[] = {"INC", "DLIS", "DLCS", "MOM", "JW"};

    std::string heuristicToString = heurAsStrings[heuristic];

    if (path[0] == 't') fileName = "test/" + fileNamesTest[std::stoi(index)];

    if (path[0] == 'c') fileName = "comp/" + fileNamesComp[std::stoi(index)];


    printf("\nRunning \033[34m%s \033[38;5;208m%s\033[0m\n\n", fileName.c_str(), heuristicToString.c_str());

    chooseLiteral = heuristicPointers[heuristic];

    parseDIMACS(fileName);

    preprocess();

    pthread_t thread;

    void* res;

    if (pthread_create(&thread, NULL, dpll, NULL)) {
        std::cerr << "Error: Unable to create thread."
                  << "\n";
        std::cout.flush();
        return -1;
    }

    // Wait for dpll to finish
    pthread_join(thread, &res);

    printModel((intptr_t)res);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    
    if ((intptr_t)res == 0) verifyModel();

    printf("\nCPU time used: %.6f seconds\033[0m\n\n", duration.count());

    std::cout.flush();

    return 0;
}
