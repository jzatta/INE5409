
#include <stdio.h>
#include <iostream>
#include "InvertedIndex.h"

struct InvertedIndexData {
    char word[50];
    char dataCount;
    int dataLocal[50];
    char hasMore;
};

char wordsSeparators[] = "!@#$%*()-, .;:?/\\|";s
char wordsProhibited[][] = {""};

InvertedIndex::InvertedIndex() {
    invertedIndex = fopen("index.dat","rw");
    if (invertedIndex == NULL) {
        throw "Error opening InvertedIndex file";
    }
}

void InvertedIndex::add(struct Manpage *page, int id) {
    
}

int *InvertedIndex::seach(char *word) {
    
}
