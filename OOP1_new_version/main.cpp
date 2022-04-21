#include <cstdio>
#include <cstdlib>
#include <string.h>
#include "multiset.h"


int main() {
    multiset* collection1 = newMultiset();
    multiset* collection2 = newMultiset();
    char* new_line;
    printf("%s", "Input a data of first multiset\n");
    for (int i = 0; i < 3; i++) {
        new_line = get_string();
        append(collection1, new_line);
    }
    insertValue(collection1, get_string(), 1);
    printContent(collection1);
}