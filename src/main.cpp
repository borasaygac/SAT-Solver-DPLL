#include <unistd.h>

#include <chrono>
#include <iostream>

#include "../include/cnf.hpp"
#include "../include/fileNames.hpp"

int numOfVars;
int numOfClauses;
int numOfUnassigned;
std::vector<Clause> clauses;
std::vector<Variable> vars;
std::set<int> satClauses;
std::queue<int> unitQueue;
std::stack<int> assig;
std::queue<int> pureLitQueue;
int curVar = 1;
int numOfSatClauses = 0;
int curProp;
bool backtrackFlag = 0;
int minWidth = 10000;
std::queue<int> minClauses;
Heuristics heuristic = INC;
void (*heuristicPointers[5])() = {chooseINC, chooseDLIS, chooseDLCS, chooseJW, chooseMOM};
void (*chooseLiteral)() = chooseINC;
void (*update)(int assertedVar) = updateDef;
void (*updateBacktrack)(int unassignedVar) = updateBacktrackDef;
int dc = 0;
int clc = 0;
int btc = 0;
int numOfMinClauses = 0;
int lastValidWidth = 0;
std::queue<int> lastValidMinimalClauses;
int mcc = 0;
std::queue<int> toPropagate;
bool finished = false;

int main(int argc, char* argv[]) {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    std::string path = argv[1];

    if (argc > 2) heuristic = Heuristics(std::stoi(argv[2]));

    std::string index;
    for (int i = 1; i < path.length(); i++) {
        index += path[i];
    }

    std::string fileName;

    std::string heurAsStrings[] = {"INC", "DLIS", "DLCS", "JW", "MOM"};

    std::string heuristicToString = heurAsStrings[heuristic];

    if (path[0] == 't') fileName = "test/" + fileNamesTest[std::stoi(index)];

    if (path[0] == 'c') fileName = "comp/" + fileNamesComp[std::stoi(index)];

    printf("\nRunning \033[34m%s \033[38;5;208m%s\033[0m\n\n", fileName.c_str(), heuristicToString.c_str());

    chooseLiteral = heuristicPointers[heuristic];

    // if heuristic is MOM, assign the corresponding update methods
    if (heuristic == MOM) {
        update = updateMOM;
        updateBacktrack = updateBacktrackMOM;
    }

    parseDIMACS(fileName);

    preprocess();

    pthread_t thread;

    void* res = (void*)-1;

    std::chrono::steady_clock::time_point startDPLL = std::chrono::steady_clock::now();
    // start dpll
    if (pthread_create(&thread, NULL, dpll, NULL)) {
        std::cerr << "Error: Unable to create thread."
                  << "\n";
        std::cout.flush();
        return -1;
    }
    // set the timeout, 10 min = 600 sec by default
    auto timeout = std::chrono::seconds(30);
    std::chrono::steady_clock::time_point endDPLL = startDPLL + timeout;

    while (std::chrono::steady_clock::now() < endDPLL) {
        sleep(1);
        if (finished) break;
    }
    if (!finished) {
        printf("TIMEOUT of %i SECONDS REACHED!\n", timeout);
        pthread_cancel(thread);
    } else {  // wait for dpll to finish
        pthread_join(thread, &res);

        printModel((intptr_t)res);
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

    if ((intptr_t)res == 0) verifyModel();

    printf("\nCPU time used: %.6f seconds\n\nChoose: %i, Backtrack: %i\n", duration.count(), dc, btc);

    printf("\n-------------------------------------\n\n", duration.count());

    std::cout.flush();

    return 0;
}