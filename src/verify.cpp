#include "../include/cnf.hpp"

void verifyModel() {
    for (int i = 1; i <= numOfClauses; i++) {
        bool sat = false;
        //std::cout << "Clause "<< i << " active no " << cnf[i].active;

        for (int literal : cnf[i].literals) {
            if (evaluateLiteral(literal)) sat = true;
        }
        if (!sat) {
            //printf("Error at %i ", i);
            std::cout<< "Error at " << i << "\n";
            break;
        }
        //if (i == numOfClauses) printf("MODEL VERIFIED!\n");
    }
}