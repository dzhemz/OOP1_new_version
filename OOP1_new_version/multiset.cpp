#include <cstdio>
#include <cstdlib>
#include <string.h>
#include "multiset.h"



// создание коллеции
multiset* newMultiset() {
	// выделяем память
	multiset* newMultiset = (multiset*)malloc(sizeof(multiset));
	// параметры устанавливаем как у пустого множества
	if (newMultiset) {
		newMultiset->first = NULL;
		newMultiset->length = 0;
		// возращаем коллекцию
		return newMultiset;
	}
	else exit(0);
}


// создание узла для коллекции
multisetNode* createMultisetNode(int index, multisetNode* next, multisetNode* prev, char* str) {
	// выделяем память
	multisetNode* new_node = (multisetNode*)malloc(sizeof(multisetNode));
	if (new_node) {
		// устнавливаем значения полей
		// индекс узла
		new_node->index = index;
		// следующий узел
		new_node->next = next;
		// предыдущий узел
		new_node->prev = prev;
		// значение элемента
		new_node->str = str;
		return new_node;
	}
	else exit(0);
}

// Удаление узла из коллекции по идексу
void deleteNode(multiset* currentMultiset, multisetNode* nodefordeletion, int index) {
	// искользуя функцию getNode() получим узел по индексу
	// если узел не был передан изначально
	multisetNode* currentNode;
	if (nodefordeletion == NULL) currentNode = getNode(currentMultiset, index);
	else currentNode = nodefordeletion;
	
	// если узел не найден - бездействуем
	if (currentNode != NULL) {

		// если узел крайний в коллекции
		if (currentNode->next == NULL && currentNode->prev != NULL) {
			// тогда у предыдущего узла изменяем параметр next на NULL
			currentNode->prev->next = NULL;
			// производим пересчёт индексов узла в коллекции
			recountIndexes(currentMultiset);
		}

		// иначе если узел является первым в коллекции
		else if (currentNode->next != NULL && currentNode->prev == NULL) {
			// тогда у следующего узла изменяем параметр prev на NULL
			currentNode->next->prev = NULL;
			// изменяем ссылку в коллекции на следующий элемент
			currentMultiset->first = currentNode->next;
			// производим пересчёт индексов узла в коллекции
			recountIndexes(currentMultiset);
		}
		// если элемент не является не начальным или конечным
		else if (currentNode->next != NULL && currentNode->prev != NULL) {
			// изменяем ссылки у соседних узлов
			currentNode->next->prev = currentNode->prev;
			currentNode->prev->next = currentNode->next;
			// производим пересчёт индексов узла в коллекции
			recountIndexes(currentMultiset);

		}
		// если в коллекции был один узел
		else {
			currentMultiset->first = NULL;
		}

		// очищаем узел из памяти
		free(currentNode->str);
		free(currentNode);
		// изменяем параметр длины у текущего множества
		currentMultiset->length--;
	}
}


void recountIndexes(multiset* currentMultiset) {
	// функция, которая переприсвает текущий действительный индекс каждому узлу
	multisetNode* currentNode = currentMultiset->first;
	// эта переменная хранит текущий индекс элемента
	int index = 0;
	// далее цикл при помощи функции итерации реализует работу функции
	while (currentNode->next != NULL) {
		currentNode->index = index;
		index++;
		currentNode = iterator(currentMultiset, currentNode);
	}
}

// функция очистки коллекции 
void clear(multiset* currentMultiset) {
	// удаляет на каждой итерации элемент с индексом равным 0 в коллекции
	// пока они не закончатся
	multisetNode* currentNode = getNode(currentMultiset, 0);
	while (currentMultiset->first != NULL) {
		deleteNode(currentMultiset, NULL, 0);
	}
}


// функция удаления коллекции
void deleteMultiset(multiset* currentMultiset) {
	// очищаем коллекцию
	clear(currentMultiset);
	// освобождаем её
	free(currentMultiset);
}


// получение индекса элемента в коллекции
int indexOf(multiset* currentMultiset, char* s) {
	// получаем первый узел
	multisetNode* currentNode = currentMultiset->first;
	// запрашиваем адреса других узлов, пока не будет найден соответствующий элемент
	while (currentNode != NULL) {
		// если элемент найден
		if (strcmp(currentNode->str, s) == 0) return currentNode->index;
		currentNode = iterator(currentMultiset, currentNode);
	}
	// если такого элемента не существует в множестве
	return -1;
}


// метод для получения узла по идексу коллекции 
multisetNode* getNode(multiset* currentMultiset, int index) {
	// начиная с первого узла, функция вызывает итератор,
	// сравнивает индекс каждого узла
	// с заданным индексом,
	// пока не найдёт искомый узел
	if (index < 0 || index >= currentMultiset->length || currentMultiset->length == 0) {
		return NULL;
	}
	multisetNode* currentNode = currentMultiset->first;
	while (currentNode->index != index) {
		currentNode = iterator(currentMultiset, currentNode);
		// в случае если не существует узла с таким индексом
		// функция на выход выдаст NULL
		if (currentNode == NULL) return NULL;
	}
	return currentNode;
}


// вставка в коллекцию значения по определённому индексу
void insertValue(multiset* currentMultiset, char* s, int index) {
	// если переданный индекс уже занят каким-то узлом
	if (index < currentMultiset->length && index >= 0 && currentMultiset->length > 0) {
		// получаем указатель на узел стоящий по индексу
		multisetNode* nextNode = getNode(currentMultiset, index);
		if (nextNode != NULL) {
			// создаём узел с ссылкой на предшествующий узел
			multisetNode* new_node = createMultisetNode(index, nextNode, nextNode->prev, s);
			if (nextNode->prev != NULL) {
				nextNode->prev->next = new_node;
			}
			nextNode->prev = new_node;


			// увеличиваем длину множества
			currentMultiset->length++;
			// переуказываем индексы для множества
			if (index == 0) {
				currentMultiset->first = new_node;
			}

			recountIndexes(currentMultiset);
		}
	}
	// если переданный индекс равен длине множества, то добавляем элемент в конец с помощью функции append 
	else if (index == currentMultiset->length) {
		append(currentMultiset, s);
	}
}


// извлечение элемента из множества
char* popElement(multiset* currentMultiset, int index) {
	char* result = NULL;
	// если элемент с таким множеством существует в коллекции
	if (index < currentMultiset->length || index >= 0) {
		// получаем узел
		multisetNode* currentNode = getNode(currentMultiset, index);
		if (currentNode != NULL) {
			// извелекаем значение из этого узла
			result = currentNode->str;
			currentNode->str = NULL;
			// удаляем узел
			deleteNode(currentMultiset, currentNode, NULL);
		}
	}
	return result;
}


// функция добавления элемента в множество
// добавляет таким образом, чтобы множество было упорядоченным
void append(multiset* currentMultiset, char* s) {
	multisetNode* currentNode = currentMultiset->first;
	while (currentNode != NULL && strcmp(currentNode->str, s) < 0) {
		currentNode = iterator(currentMultiset, currentNode);
	}
	if (currentNode != NULL && strcmp(currentNode->str, s) >= 0) {
		insertValue(currentMultiset, s, currentNode->index);
	}
	else if (currentNode == NULL) {
		currentNode = createMultisetNode(0, NULL, getNode(currentMultiset, currentMultiset->length - 1), s);
		if (currentMultiset->length == 0) {
			currentMultiset->length++;
			currentMultiset->first = currentNode;
		}
		else {
			getNode(currentMultiset, currentMultiset->length - 1)->next = currentNode;
			recountIndexes(currentMultiset);
			currentMultiset->length++;
		}
	}
}

// функия итератора возращает следующий элемент в коллекции, если он существует
// если же он не существует, то возращает NULL
multisetNode* iterator(multiset* currentMultiset, multisetNode* currentNode) {
	if (currentNode == NULL) currentNode = currentMultiset->first;
	if (currentNode->next != NULL) return currentNode->next;
	return NULL;
}


// функция счёта количества определённого элемента 
int count(multiset* currentMultiset, char* s) {
	int result = 0;
	// получаем первый узел множества
	multisetNode* currentNode = currentMultiset->first;
	// просматриваем коллекцию и сравниваем каждую строку с заданной
	while (currentNode != NULL) {
		if (strcmp(s, currentNode->str) == 0) result++;
		currentNode = iterator(currentMultiset, currentNode);
	}
	return result;
}


// функция возращающая результат вычитания первого множества из второго
multiset* substraction(multiset* firstMultiset, multiset* secondMultiset) {
	// создаём экземпляр нового мультимножества
	multiset* result = newMultiset();
	// просматриваем первую коллекцию
	multisetNode* currentNode = firstMultiset->first;
	// разница между количествами элемента в первой и второй коллекции
	int difference;
	// если количество какого-либо элемента в первом множестве больше чем во втором, тогда добавляем
	// этот элемент в множество, причём количество этого элемента равно вышеуказанной разности 
	while (currentNode != NULL) {
		difference = count(firstMultiset, currentNode->str) - count(secondMultiset, currentNode->str);
		if (indexOf(result, currentNode->str) == -1 && difference > 0) {
			for (int i = 0; i < difference; i++) {
				append(result, currentNode->str);
			}
		}
		// c помощью итератора получаем следующий элемент
		currentNode = iterator(firstMultiset, currentNode);
	}

	recountIndexes(result);
	return result;
}

// функция объединения множеств
multiset* unification(multiset* firstMultiset, multiset* secondMultiset) {
	// запишем итогов 
	multiset* result = newMultiset();
	// разность первого и второго множества
	multiset* first_part = substraction(firstMultiset, secondMultiset);
	// разность второго и первого множества
	multiset* second_part = substraction(secondMultiset, firstMultiset);
	// пересечение множеств
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


// функция пересечения двух множеств
multiset* interscation(multiset* firstMultiset, multiset* secondMultiset) {
	// создаём два указателя на множества
	// control указывает на множество, у которого наибольшая длина
	// такое множество считаем контрольным и по его элементам проходим
	multiset* controlMultiset;
	// множество, которое получится в результате пересечения
	multiset* result = newMultiset();

	// значение равное минимальному количеству элемента, который содержится в множествах
	int minimum;

	// переменные используемые для сравнения количества определённого элемента в множестве
	int first_count;
	int second_count;

	// выбираем контрольное множество
	if (firstMultiset->length <= secondMultiset->length) controlMultiset = firstMultiset;
	else controlMultiset = secondMultiset;
	

	// берём первый элемент контрольного множества
	multisetNode* currentNode = controlMultiset->first;

	while (currentNode != NULL) {
		// если элемент не содержится в коллекции
		if (indexOf(result, currentNode->str) == -1) {
			// просчитываем сколько раз элемент встречается в коллекциях
			first_count = count(firstMultiset, currentNode->str);
			second_count = count(secondMultiset, currentNode->str);
			// сравниваем значения переменных для выбора наименьшего
			if (first_count <= second_count)  minimum = first_count;
			else minimum = second_count;

			// добавляем элемент минимальное количество раз
			for (int i = 0; i < minimum; i++) {
				append(result, currentNode->str);
			}
		}
		// итератором вызываем следующий узел
		currentNode = iterator(controlMultiset, currentNode);
	}
	return result;
}

// функция считывания строки 
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



// сохранение множества в файл
void saveMultiset(multiset* currentMultiset, char* filename) {
	// открываем файл
	FILE *file_for_save;
	errno_t err = fopen_s(&file_for_save, filename, "w");
	// если он существует
	if (err == 0) {
		// просматриваем все узлы
		multisetNode* currentNode = currentMultiset->first;
		while (currentNode) {
			// записываем в файл данные хранящиеся в узле 
			fprintf(file_for_save, "%s", currentNode->str);
			fprintf(file_for_save, "%s", "\n");
			currentNode = iterator(currentMultiset, currentNode);
		}
		fclose(file_for_save);
	}
}

// чтение множества из файла
// filename - название файла
// last Symbol - символ разделитель
multiset* readMultiset(char* filename, char lastSymbol) {
	// мультимножество на выход
	multiset* result = newMultiset();
	// переменная счёта количества индексов, которые необходимо выделить под строку
	int count = 1;
	// очередная строка
	char* content = (char *)malloc(sizeof(char));
	if (content == NULL) exit(0);
	// очередной символ из файла
	char currentSymbol;
	// указатель на файл
	FILE* file_for_read;
	errno_t err  = fopen_s(&file_for_read, filename, "r");
	// если файл доступен для чтения
	if (err == 0) {
		while (!feof(file_for_read)) {
			// считываем каждый символ, пока не будет символа конца файла
			currentSymbol = fgetc(file_for_read);
			// если символ равен символу разделителю
			if (currentSymbol == lastSymbol) {
				// запрашиваем память для расширенной строки
				content = (char*)realloc(content, count * sizeof(char));

				// вставляем нулевой символ
				content[count] = '/0';
				// добавляем строку в мультимножество
				// добавляем строку в мультимножество
				// добавляем строку в мультимножество
				// добавляем строку в мультимножество
				append(result, content);
				// запрашиваем её вновь
				content = (char*)malloc(sizeof(char));
				count = 1;

			}
			
			else {
				// запрашиваем память для расширенной строки
				content = (char*)realloc(content, count * sizeof(char));
				if (content == NULL) exit(0);

				// вставляем символ
				content[count - 1] = currentSymbol;
				// увеличиваем значение количества символов в строке на 1
				count++;
				
			}
		}
		fclose(file_for_read);
	}
	return result;
}

// функция, которая выводит содержимое колекции в консоль
void printContent(multiset* currentMultiset) {
	multisetNode* node = currentMultiset->first;

	while (node != NULL) {
		if (node->str != NULL) printf("%s", node->str);
		printf("%s", "\n");
		node = iterator(currentMultiset, node);
	}
}
