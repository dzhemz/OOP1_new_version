struct multisetNode {
    int index;
    multisetNode* next;
    multisetNode* prev;
    char* str;

};

struct multiset {
    multisetNode* first;
    int length;
};


multisetNode* createMultisetNode(int index, multisetNode* next, multisetNode* prev, char* str);

void deleteNode(multiset* currentMultiset, multisetNode* nodefordeletion, int index);

void recountIndexes(multiset* currentMultiset);

void clear(multiset* currentMultiset);

void deleteMultiset(multiset* currentMultiset);

int indexOf(multiset* currentMultiset, char* s);

multisetNode* getNode(multiset* currentMultiset, int index);

void insertValue(multiset* currentMultiset, char* s, int index);

char* popElement(multiset* currentMultiset, int index);

void append(multiset* currentMultiset, char* s);

multisetNode* iterator(multiset* currentMultiset, multisetNode* currentNode);

multiset* substraction(multiset* firstMultiset, multiset* secondMultiset);

int count(multiset* currentMultiset, char* s);

multiset* interscation(multiset* firstMultiset, multiset* secondMultiset);

multiset* unification(multiset* firstMultiset, multiset* secondMultiset);

char* get_string();

void saveMultiset(multiset* currentMultiset, char* filename);

multiset* readMultiset(char* filename, char lastSymbol);

multiset* newMultiset();

void printContent(multiset* currentMultiset);