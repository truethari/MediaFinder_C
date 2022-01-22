#include <stdio.h>
#include <ctype.h>

void welcome() {
    int number;
    while (1) {
        printf("1. Run\n2. Exit\n\n");
        printf("> ");
        if (scanf("%d", &number) == 0) {
            fflush(stdin);
            printf("Wrong input!\n");
            continue;
        }

        if ((number <= 0) || (number > 2)) printf("Wrong input!\n");
        else break;
    }
    if (number == 1) {
        printf("Run..");
    }
}

void listDir() {
    
}

int main() {
   welcome();
   return 0;
}