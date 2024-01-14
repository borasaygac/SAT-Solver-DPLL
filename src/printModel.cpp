#include "../include/cnf.hpp"

void printModel(int res) {
    if (res == 1) {
        printf("\033[31mUNSAT: No model!\n\n[");
    } else {
        std::cout << "\033[1;32mSAT!";
        printf(" Model:\n\n[");
    }

    for (int i = 1; i < numOfVars; i++) {
        int value;
        if (vars[i].val == FREE) value = 0;
        if (vars[i].val == TRUE) value = i;
        if (vars[i].val == FALSE) value = -i;

        printf("%i, ", value);
        if (i % 20 == 0) printf("\n");
    }
    int value;
    if (vars[numOfVars].val == FREE) value = 0;
    if (vars[numOfVars].val == TRUE) value = numOfVars;
    if (vars[numOfVars].val == FALSE) value = -numOfVars;
    printf("%i", value);
    printf("]\033[0m\n");
    //printf("backtr: %i, choose: %i", btc, numOfMinClauses);

}