#include "../include/cnf.hpp"

void printModel(int res) {
    if (res == 1) {
        printf("\033[31mUNSAT: No model!\n\n[");
        for (int i = 1; i <= numOfVars; i++) {
            int value = 0;
            if (vars[i].val == FREE) value = 0;
            if (vars[i].val == TRUE) value = i;
            if (vars[i].val == FALSE) value = -i;

            printf("%i", value);
            (i < numOfVars) ? printf(", ", value) : printf("]\033[0m\n");
            if (i % 20 == 0) printf("\n");
        }
        for (int i = 1; i <= numOfClauses; i++) {
            bool sat = false;
            // std::cout << "Clause "<< i << " active no " << clauses[i].active;

            for (int literal : clauses[i].literals) {
                if (evaluateLiteral(literal)) sat = true;
            }
            if (!sat) {
                // printf("Error at %i ", i);
                std::cout << "Error at " << i << "\n";
                break;
            }
            if (i == numOfClauses) printf("\n\033[32mMODEL VERIFIED!\033[0m\n");
        }

    } else {
        std::cout << "\033[1;32mSAT!";
        printf(" Model:\n\n[");
        for (int i = 1; i <= numOfVars; i++) {
            int value = 0;
            if (vars[i].val == FREE) value = -i;
            if (vars[i].val == TRUE) value = i;
            if (vars[i].val == FALSE) value = -i;

            printf("%i", value);
            (i < numOfVars) ? printf(", ", value) : printf("]\033[0m\n");
            if (i % 20 == 0) printf("\n");
        }
    }
}
bool evaluateLiteral(int literal) {
    return vars[std::abs(literal)].val == FREE || !(vars[std::abs(literal)].val ^ (literal > 0));
}