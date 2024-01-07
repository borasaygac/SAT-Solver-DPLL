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

    std::string path = argv[1];

    std::string index;

    for (int i = 1; i < path.length(); i++) {
        index += path[i];
    }

    std::string fileName;

    if (path[0] == 't') fileName = "test/" + fileNamesTest[std::stoi(index)];

    if (path[0] == 'c') fileName = "comp/" + fileNamesComp[std::stoi(index)];

    printf("\nRunning %s\n\n", fileName.c_str());

    if (argc > 2) heuristic = Heuristics(std::stoi(argv[2]));

    parseDIMACS(fileName);

    for (int i = 1; i <= numOfVars; i++) {
        std::cout.flush();
        std::cout << "\n"
                  << "VAR: " << i << "\n"
                  << "FORCED: " << vars[i].enqueued << " " << vars[i].forced << "\n";
        std::cout << "POS_OCC: ";
        for (const auto& element : vars[i].static_pos_occ) {
            std::cout << element << " ";
        }

        std::cout << "\n";
        std::cout << "NEG_OCC: ";

        for (const auto& element : vars[i].static_neg_occ) {
            std::cout << element << " ";
        }
    }

    for (int i = 1; i <= numOfClauses; i++) {
        std::cout << "CLAUSE: " << i << " Active:" << cnf[i].active << std::endl;
    }

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

    printf("\nCPU time used: %.6f seconds\n\n", duration.count());
    // for (auto it = satClauses.begin(); it != satClauses.end(); ++it) {
    //     std::cout << *it << std::endl;  // Perform operations with each element
    // }
    if ((intptr_t)res == 0) verifyModel();

    // std::cout << "\nCPU time used: " << duration.count() << " seconds\n" << std::endl;

    return 0;
}
