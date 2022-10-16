#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readLine(char*** strArray) {
    int wordLength = 0, newWord = 1, c, numOfStrings = 0;
    char** inputs = calloc(1, sizeof(char*));
    *strArray = calloc(1, sizeof(char*));

    while((c = getchar()) != '\n' && c != EOF) {
        if (c != ' ') {
            if (newWord) { 
                wordLength = 0; 
                numOfStrings++;
                newWord = 0; // now not a new word
                // increase the memory allocation
                char** temp = realloc(inputs, (numOfStrings) * sizeof(char*)); 
                inputs = temp;
                // allocate new memory for new string
                inputs[numOfStrings - 1] = (char*) calloc(2, sizeof(char));
            } else { // increase memory allocation for current string
                inputs[numOfStrings - 1] = (char*) realloc(inputs[numOfStrings - 1], (wordLength + 2) * sizeof(char));
            }
            //set char of current string and set end to null terminator
            inputs[numOfStrings - 1][wordLength] = c;
            inputs[numOfStrings - 1][wordLength + 1] = '\0';
            wordLength++;
        } else if (wordLength > 0) newWord = 1;
    }

    // set the array given to the read input
    *strArray = realloc(*strArray, (numOfStrings) * sizeof(char*));
    *strArray = inputs;
    // return number of strings read successfully
    return numOfStrings;
}

int setWithNoRepeats(char*** set, int size) {
    char** items = calloc(1, sizeof(char*)); // set to build with no repeats
    int numOfItems = 0, valid;
    for (int i = 0; i < size; i++) {
        valid = 1; // assume not repeated
        for (int j = 0; j < i; j++) {
            if (!strcmp((*set)[i], (*set)[j])) valid = 0; // if it matches an element it is invalid
        }
        if (valid) {
            numOfItems++;
            // allocate memory for new element and set new element in list 
            char** temp = realloc(items, (numOfItems) * sizeof(char*));
            items = temp;
            items[numOfItems - 1] = (char*) calloc(strlen((*set)[i]), sizeof(char));
            items[numOfItems - 1] = (*set)[i];
        }
    }
    // set the set to the new list with no items
    *set = realloc(*set, (numOfItems) * sizeof(char*));
    *set = items;
    return numOfItems;
}

void printPowerSet(char** set, int size, int index, char* current) { 
    // string for next recursion (including indexed element)
    char* nextStr = malloc(sizeof(current) + sizeof(set[index]) + 2); // memory for current, indexed element, space and \0
    strcpy(nextStr, current); // set next string to current
    if (index == size) { // if fully built set then start to break it down
        printf("{%s }\n", current); // print given string
        return; // end as to not recurse and begin backtracking
    }
    strcat(strcat(nextStr,  " "),  set[index]); // add indexed element to nextStr
    printPowerSet(set, size, index + 1, nextStr); // include element at next index
    printPowerSet(set, size, index + 1, current); // doesn't include element at next index
    return;
}

int main() {
    char **set = malloc(sizeof(char*));
    int setSize = 0;

    printf("Input your set with elements seperated by spaces\n");
    setSize = readLine(&set); // reads set input to input
    setSize = setWithNoRepeats(&set, setSize);
    printPowerSet(set, setSize, 0, ""); // recursive powerset algorithm initially with no items

    for (int i = 0; i < setSize; i++) free(set[i]); // free memory used for the elements
    free(set); // free memory used for the set
    return 1;
}