
#include <stdio.h>
#include <iostream>
#include "InvertedIndex.h"
#include "debug.h"

char wordsSeparators[] = "!@#$%*()-, .;:?/\\|";
char wordsProhibited[][50] = {""};

InvertedIndex::InvertedIndex() {
    printlndbg("Building Inverted");
    invertedIndex = NULL;
}

void InvertedIndex::add(struct Manpage *page, int id) {
    invertedIndex = fopen("index.dat","w");
    if (invertedIndex == NULL) {
        throw "Error opening InvertedIndex file";
    }
    fclose(invertedIndex);
}

int *InvertedIndex::seach(char *word) {
    
}
