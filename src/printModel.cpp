#include "../include/cnf.hpp"

void printModel(int res) {
    if (res == 1) {
        printf("\033[31mUNSAT: No model!\n\n[");
        for (int i = 1; i <= numOfVars; i++) {
            int value;
            if (vars[i].val == FREE) value = 0;
            if (vars[i].val == TRUE) value = i;
            if (vars[i].val == FALSE) value = -i;

            printf("%i", value);
            (i < numOfVars) ? printf(", ", value) : printf("]\033[0m\n");
            if (i % 20 == 0) printf("\n");
        }
    } else {
        std::cout << "\033[1;32mSAT!";
        printf(" Model:\n\n[");
        for (int i = 1; i <= numOfVars; i++) {
            int value;
            if (vars[i].val == FREE) value = -i;
            if (vars[i].val == TRUE) value = i;
            if (vars[i].val == FALSE) value = -i;

            printf("%i", value);
            (i < numOfVars) ? printf(", ", value) : printf("]\033[0m\n");
            if (i % 20 == 0) printf("\n");
        }
    }
}