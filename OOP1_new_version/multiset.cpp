#include <cstdio>
#include <cstdlib>
#include <string.h>
#include "multiset.h"



// �������� ��������
multiset* newMultiset() {
	// �������� ������
	multiset* newMultiset = (multiset*)malloc(sizeof(multiset));
	// ��������� ������������� ��� � ������� ���������
	if (newMultiset) {
		newMultiset->first = NULL;
		newMultiset->length = 0;
		// ��������� ���������
		return newMultiset;
	}
	else exit(0);
}


// �������� ���� ��� ���������
multisetNode* createMultisetNode(int index, multisetNode* next, multisetNode* prev, char* str) {
	// �������� ������
	multisetNode* new_node = (multisetNode*)malloc(sizeof(multisetNode));
	if (new_node) {
		// ������������ �������� �����
		// ������ ����
		new_node->index = index;
		// ��������� ����
		new_node->next = next;
		// ���������� ����
		new_node->prev = prev;
		// �������� ��������
		new_node->str = str;
		return new_node;
	}
	else exit(0);
}

// �������� ���� �� ��������� �� ������
void deleteNode(multiset* currentMultiset, multisetNode* nodefordeletion, int index) {
	// ��������� ������� getNode() ������� ���� �� �������
	// ���� ���� �� ��� ������� ����������
	multisetNode* currentNode;
	if (nodefordeletion == NULL) currentNode = getNode(currentMultiset, index);
	else currentNode = nodefordeletion;
	
	// ���� ���� �� ������ - ������������
	if (currentNode != NULL) {

		// ���� ���� ������� � ���������
		if (currentNode->next == NULL && currentNode->prev != NULL) {
			// ����� � ����������� ���� �������� �������� next �� NULL
			currentNode->prev->next = NULL;
			// ���������� �������� �������� ���� � ���������
			recountIndexes(currentMultiset);
		}

		// ����� ���� ���� �������� ������ � ���������
		else if (currentNode->next != NULL && currentNode->prev == NULL) {
			// ����� � ���������� ���� �������� �������� prev �� NULL
			currentNode->next->prev = NULL;
			// �������� ������ � ��������� �� ��������� �������
			currentMultiset->first = currentNode->next;
			// ���������� �������� �������� ���� � ���������
			recountIndexes(currentMultiset);
		}
		// ���� ������� �� �������� �� ��������� ��� ��������
		else if (currentNode->next != NULL && currentNode->prev != NULL) {
			// �������� ������ � �������� �����
			currentNode->next->prev = currentNode->prev;
			currentNode->prev->next = currentNode->next;
			// ���������� �������� �������� ���� � ���������
			recountIndexes(currentMultiset);

		}
		// ���� � ��������� ��� ���� ����
		else {
			currentMultiset->first = NULL;
		}

		// ������� ���� �� ������
		free(currentNode->str);
		free(currentNode);
		// �������� �������� ����� � �������� ���������
		currentMultiset->length--;
	}
}


void recountIndexes(multiset* currentMultiset) {
	// �������, ������� ������������ ������� �������������� ������ ������� ����
	multisetNode* currentNode = currentMultiset->first;
	// ��� ���������� ������ ������� ������ ��������
	int index = 0;
	// ����� ���� ��� ������ ������� �������� ��������� ������ �������
	while (currentNode->next != NULL) {
		currentNode->index = index;
		index++;
		currentNode = iterator(currentMultiset, currentNode);
	}
}

// ������� ������� ��������� 
void clear(multiset* currentMultiset) {
	// ������� �� ������ �������� ������� � �������� ������ 0 � ���������
	// ���� ��� �� ����������
	multisetNode* currentNode = getNode(currentMultiset, 0);
	while (currentMultiset->first != NULL) {
		deleteNode(currentMultiset, NULL, 0);
	}
}


// ������� �������� ���������
void deleteMultiset(multiset* currentMultiset) {
	// ������� ���������
	clear(currentMultiset);
	// ����������� �
	free(currentMultiset);
}


// ��������� ������� �������� � ���������
int indexOf(multiset* currentMultiset, char* s) {
	// �������� ������ ����
	multisetNode* currentNode = currentMultiset->first;
	// ����������� ������ ������ �����, ���� �� ����� ������ ��������������� �������
	while (currentNode != NULL) {
		// ���� ������� ������
		if (strcmp(currentNode->str, s) == 0) return currentNode->index;
		currentNode = iterator(currentMultiset, currentNode);
	}
	// ���� ������ �������� �� ���������� � ���������
	return -1;
}


// ����� ��� ��������� ���� �� ������ ��������� 
multisetNode* getNode(multiset* currentMultiset, int index) {
	// ������� � ������� ����, ������� �������� ��������,
	// ���������� ������ ������� ����
	// � �������� ��������,
	// ���� �� ����� ������� ����
	if (index < 0 || index >= currentMultiset->length) {
		return NULL;
	}
	multisetNode* currentNode = currentMultiset->first;
	while (currentNode->index != index) {
		currentNode = iterator(currentMultiset, currentNode);
		// � ������ ���� �� ���������� ���� � ����� ��������
		// ������� �� ����� ������ NULL
		if (currentNode == NULL) return NULL;
	}
	return currentNode;
}


// ������� � ��������� �������� �� ������������ �������
void insertValue(multiset* currentMultiset, char* s, int index) {
	// ���� ���������� ������ ��� ����� �����-�� �����
	if (index < currentMultiset->length && index >= 0 && currentMultiset->length > 0) {
		// �������� ��������� �� ���� ������� �� �������
		multisetNode* nextNode = getNode(currentMultiset, index);
		if (nextNode != NULL) {
			// ������ ���� � ������� �� �������������� ����
			multisetNode* new_node = createMultisetNode(index, nextNode, nextNode->prev, s);
			if (nextNode->prev != NULL) {
				nextNode->prev->next = new_node;
			}
			nextNode->prev = new_node;


			// ����������� ����� ���������
			currentMultiset->length++;
			// ������������� ������� ��� ���������
			if (index == 0) {
				currentMultiset->first = new_node;
			}

			recountIndexes(currentMultiset);
		}
	}
	// ���� ���������� ������ ����� ����� ���������, �� ��������� ������� � ����� � ������� ������� append 
	else if (index == currentMultiset->length) {
		append(currentMultiset, s);
	}
}


// ���������� �������� �� ���������
char* popElement(multiset* currentMultiset, int index) {
	char* result = NULL;
	// ���� ������� � ����� ���������� ���������� � ���������
	if (index < currentMultiset->length || index >= 0) {
		// �������� ����
		multisetNode* currentNode = getNode(currentMultiset, index);
		if (currentNode != NULL) {
			// ���������� �������� �� ����� ����
			result = currentNode->str;
			currentNode->str = NULL;
			// ������� ����
			deleteNode(currentMultiset, currentNode, NULL);
		}
	}
	return result;
}


// ������� ���������� �������� � ����� ���������
void append(multiset* currentMultiset, char* s) {
	if (currentMultiset->length > 0) {
		// ����������� ��������� �� ������� ������� � ���������
		multisetNode* currentNode = getNode(currentMultiset, currentMultiset->length - 1);
		// ������ ����� ����
		multisetNode* new_node = createMultisetNode(currentMultiset->length, NULL, currentNode, s);
		// ������������� ����� ���������
		currentNode->next = new_node;
		// ����������� �������� ����� ��������� �� �������
	}
	else {
		// ������ ������ ���� � ��������� ��� � ���������
		multisetNode* new_node = createMultisetNode(currentMultiset->length, NULL, NULL, s);
		currentMultiset->first = new_node;
	}
	currentMultiset->length++;
}

// ������ ��������� ��������� ��������� ������� � ���������, ���� �� ����������
// ���� �� �� �� ����������, �� ��������� NULL
multisetNode* iterator(multiset* currentMultiset, multisetNode* currentNode) {
	if (currentNode == NULL) currentNode = currentMultiset->first;
	if (currentNode->next != NULL) return currentNode->next;
	return NULL;
}


// ������� ����� ���������� ������������ �������� 
int count(multiset* currentMultiset, char* s) {
	int result = 0;
	// �������� ������ ���� ���������
	multisetNode* currentNode = currentMultiset->first;
	// ������������� ��������� � ���������� ������ ������ � ��������
	while (currentNode != NULL) {
		if (strcmp(s, currentNode->str) == 0) result++;
		currentNode = iterator(currentMultiset, currentNode);
	}
	return result;
}


// ������� ����������� ��������� ��������� ������� ��������� �� �������
multiset* substraction(multiset* firstMultiset, multiset* secondMultiset) {
	// ������ ��������� ������ ���������������
	multiset* result = newMultiset();
	// ������������� ������ ���������
	multisetNode* currentNode = firstMultiset->first;
	// ������� ����� ������������ �������� � ������ � ������ ���������
	int difference;
	// ���� ���������� ������-���� �������� � ������ ��������� ������ ��� �� ������, ����� ���������
	// ���� ������� � ���������, ������ ���������� ����� �������� ����� ������������� �������� 
	while (currentNode != NULL) {
		difference = count(firstMultiset, currentNode->str) - count(secondMultiset, currentNode->str);
		if (indexOf(result, currentNode->str) == -1 && difference > 0) {
			for (int i = 0; i < difference; i++) {
				append(result, currentNode->str);
			}
		}
		// c ������� ��������� �������� ��������� �������
		currentNode = iterator(firstMultiset, currentNode);
	}

	recountIndexes(result);
	return result;
}

// ������� ����������� ��������
multiset* unification(multiset* firstMultiset, multiset* secondMultiset) {
	// ������� ������ 
	multiset* result = newMultiset();
	// �������� ������� � ������� ���������
	multiset* first_part = substraction(firstMultiset, secondMultiset);
	// �������� ������� � ������� ���������
	multiset* second_part = substraction(secondMultiset, firstMultiset);
	// ����������� ��������
	multiset* third_part = interscation(firstMultiset, secondMultiset);
	
	multisetNode* currentNode = first_part->first;
	while (currentNode != NULL) {
		append(result, currentNode->str);
		currentNode = iterator(first_part, currentNode);
	}

	currentNode = second_part->first;
	while (currentNode != NULL) {
		append(result, currentNode->str);
		currentNode = iterator(second_part, currentNode);
		
	}

	currentNode = third_part->first;
	while (currentNode != NULL) {
		append(result, currentNode->str);
		currentNode = iterator(third_part, currentNode);
	
	}
	return result;
}


// ������� ����������� ���� ��������
multiset* interscation(multiset* firstMultiset, multiset* secondMultiset) {
	// ������ ��� ��������� �� ���������
	// control ��������� �� ���������, � �������� ���������� �����
	// ����� ��������� ������� ����������� � �� ��� ��������� ��������
	multiset* controlMultiset;
	// ���������, ������� ��������� � ���������� �����������
	multiset* result = newMultiset();

	// �������� ������ ������������ ���������� ��������, ������� ���������� � ����������
	int minimum;

	// ���������� ������������ ��� ��������� ���������� ������������ �������� � ���������
	int first_count;
	int second_count;

	// �������� ����������� ���������
	if (firstMultiset->length <= secondMultiset->length) controlMultiset = firstMultiset;
	else controlMultiset = secondMultiset;
	

	// ���� ������ ������� ������������ ���������
	multisetNode* currentNode = controlMultiset->first;

	while (currentNode != NULL) {
		// ���� ������� �� ���������� � ���������
		if (indexOf(result, currentNode->str) == -1) {
			// ������������ ������� ��� ������� ����������� � ����������
			first_count = count(firstMultiset, currentNode->str);
			second_count = count(secondMultiset, currentNode->str);
			// ���������� �������� ���������� ��� ������ �����������
			if (first_count <= second_count)  minimum = first_count;
			else minimum = second_count;

			// ��������� ������� ����������� ���������� ���
			for (int i = 0; i < minimum; i++) {
				append(result, currentNode->str);
			}
		}
		// ���������� �������� ��������� ����
		currentNode = iterator(controlMultiset, currentNode);
	}
	return result;
}

// ������� ���������� ������ 
char* get_string() {
	int len = 1;
	char* s = (char*)malloc(sizeof(char));
	
	if (s == NULL) exit(0);
	char c = getchar();

	while (c != '\n') {
		s[len - 1] = c;
		len++;
		s = (char*)realloc(s, len * sizeof(char));
	
		if (s == NULL) exit(0);
	
		c = getchar();
	}
	s[len - 1] = '\0';
	return s;
}



// ���������� ��������� � ����
void saveMultiset(multiset* currentMultiset, char* filename) {
	// ��������� ����
	FILE *file_for_save;
	errno_t err = fopen_s(&file_for_save, filename, "w");
	// ���� �� ����������
	if (err == 0) {
		// ������������� ��� ����
		multisetNode* currentNode = currentMultiset->first;
		while (currentNode) {
			// ���������� � ���� ������ ���������� � ���� 
			fprintf(file_for_save, "%s", currentNode->str);
			fprintf(file_for_save, "%s", "/n");
			currentNode = iterator(currentMultiset, currentNode);
		}
		fclose(file_for_save);
	}
}

// ������ ��������� �� �����
// filename - �������� �����
// last Symbol - ������ �����������
multiset* readMultiset(char* filename, char lastSymbol) {
	// ��������������� �� �����
	multiset* result = newMultiset();
	// ���������� ����� ���������� ��������, ������� ���������� �������� ��� ������
	int count = 1;
	// ��������� ������
	char* content = (char *)malloc(sizeof(char) * 5);
	if (content == NULL) exit(0);
	// ��������� ������ �� �����
	char currentSymbol;
	// ��������� �� ����
	FILE* file_for_read;
	errno_t err  = fopen_s(&file_for_read, filename, "r");
	// ���� ���� �������� ��� ������
	if (err == 0) {
		// ��������� ������ ������, ���� �� ����� ������� ����� �����
		currentSymbol = fgetc(file_for_read);
		while (currentSymbol != '/0') {
			// ���� ������ ����� ������� �����������
			if (currentSymbol == lastSymbol) {
				// ����������� ������ ��� ����������� ������
				content = (char*)realloc(content, count * sizeof(char));

				// ��������� ������� ������
				content[count] = '/0';
				// ��������� ������ � ���������������
				append(result, content);
				// ����������� � �����
				content = (char*)malloc(sizeof(char) * 5);

			}
			
			else {
				if (count > 5) {
					// ����������� ������ ��� ����������� ������
					content = (char*)realloc(content, count * sizeof(char));
					// ��������� ������
					content[count - 1] = currentSymbol;
					// ����������� �������� ���������� �������� � ������ �� 1
					count++;
				}
				else {
					// ��������� ������
					content[count - 1] = currentSymbol;
					// ����������� �������� ���������� �������� � ������ �� 1
					count++;
				}
			}
		}
	}
}

// �������, ������� ������� ���������� �������� � �������
void printContent(multiset* currentMultiset) {
	multisetNode* node = currentMultiset->first;

	while (node != NULL) {
		if (node->str != NULL) printf("%s", node->str);
		printf("%s", "\n");
		node = iterator(currentMultiset, node);
	}
}