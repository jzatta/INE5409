
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <iostream>
#include "InvertedIndex.h"
#include "PrimaryKey.h"
#include "debug.h"

char wordsProhibited[][50] = {""};

InvertedIndex::InvertedIndex() {
    printlndbg("Building Inverted");
    fclose(fopen("index.dat","w"));
    invertedIndex = NULL;
}

void InvertedIndex::add(struct Manpage *page, int id) {
    char *ptr, word[50];
    char path[] = "x.dat";
    int wordsCount = 0, i, j;
    char ch;
    char wordsFouded[3000][50];
    bool notIndexed[3000];
    struct InvertedIndexData *occ;
    ptr = page->content;
    ch = *ptr++;
    // read content of manpage
    printlndbg("II: " << page->name << "@" << id);
    printlndbg("II: " << page->content);
    for (i = 0; ch; ch = *ptr++) {
        if (ch >= 'A' && ch <= 'Z') {
            ch += 'a' - 'A';
        }
        word[i] = ch;
        if (isSeparator(ch)) {
            if (i < 3) {
                i = 0;
                continue;
            }
            word[i] = '\0';
            if (!isProhibited(word)) {
                // save word in a buffer, if not present yet
                for (i = 0; i < wordsCount; i++) {
                    if (!strcmp(wordsFouded[i], word)) {
                        break;
                    }
                }
                if (i == wordsCount) {
                    printlndbg("II:word: " << page->name << " : " << word << "@" << wordsCount);
                    strcpy(wordsFouded[wordsCount], word);
                    wordsCount++;
                    if (wordsCount >= 3000) {
                        throw "More than 3000 different words in file";
                    }
                }
            }
            i = 0;
            continue;
        }
        i++;
    }
    printlndbg("II:::: " << page->name << "@" << wordsCount);
    // initialize a buffer to write word wasnt in file
    for (i = 0; i < wordsCount; i++) {
        notIndexed[i] = true;
    }
    occ = (struct InvertedIndexData *)malloc(sizeof(struct InvertedIndexData));
    invertedIndex = fopen("index.dat","r+");
    if (invertedIndex == NULL) {
        throw "Error opening InvertedIndex file";
    }
    // search occurrence in file, if has add link to file
    for (j = 0; ; j++) {
        fseek(invertedIndex, sizeof(struct InvertedIndexData) * j, SEEK_SET);
        fread(occ, sizeof(struct InvertedIndexData), 1, invertedIndex);
        if (feof(invertedIndex)) {
            break;
        }
        for (i = 0; i < wordsCount; i++) {
            if (!strcmp(occ->word, wordsFouded[i])) {
                if (occ->hasMore) {
                    break;
                }
                notIndexed[i] = false;
                printlndbg("II update: " << occ->word << " : " << occ->occurrencesCount);
                if (occ->occurrencesCount >= MAXOCCURRENCES) {
                    occ->hasMore = true;
                    notIndexed[i] = true;
                } else {
                    occ->occurrences[occ->occurrencesCount] = id;
                    occ->occurrencesCount += 1;
                }
                fseek(invertedIndex, sizeof(struct InvertedIndexData) * j, SEEK_SET);
                fwrite(occ, sizeof(struct InvertedIndexData), 1, invertedIndex);
            }
        }
    }
    fclose(invertedIndex);
    invertedIndex = fopen("index.dat","a");
    if (invertedIndex == NULL) {
        throw "Error opening InvertedIndex file";
    }
    // if not, add first occurrence
    for (i = 0; i < wordsCount; i++) {
        if (notIndexed[i]) {
            strcpy(occ->word, wordsFouded[i]);
            occ->occurrences[0] = id;
            occ->occurrencesCount = 1;
            occ->hasMore;
            printlndbg("II append: " << occ->word << " : " << occ->occurrencesCount);
            fwrite(occ, sizeof(struct InvertedIndexData), 1, invertedIndex);
        }
    }
    free(occ);
    fclose(invertedIndex);
    return;
}

bool InvertedIndex::isSeparator(char c) {
    if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')) {
        return false;
    }
    return true;
}

bool InvertedIndex::isProhibited(char *word) {
    int i;
    return false;
    const int limit = sizeof(wordsProhibited) / 50;
    for (i = 0; i < limit; i++) {
        if (strcmp(word, wordsProhibited[i]) == 0) {
            return true;
        }
    }
    return false;
}

int *InvertedIndex::search(char *word) {
    int *occ, occCount;
    InvertedIndexData *index;
    int j = 0;
    invertedIndex = fopen("index.dat","r");
    if (invertedIndex == NULL) {
        throw "Error opening InvertedIndex file";
    }
    index = (struct InvertedIndexData *)malloc(sizeof(struct InvertedIndexData));
    occ = (int *)malloc(1);
    occCount = 0;
    // search occurrence in file, if has add link to file
    while (true) {
        fseek(invertedIndex, sizeof(struct InvertedIndexData) * j++, SEEK_SET);
        fread(index, sizeof(struct InvertedIndexData), 1, invertedIndex);
        if (feof(invertedIndex)) {
            break;
        }
        if (!strcmp(index->word, word)) {
            int basePtr = occCount;
            occCount += index->occurrencesCount;
            occ = (int *)realloc(occ, sizeof(int) * (occCount + 1));
            memcpy(&occ[basePtr + 1], index->occurrences, sizeof(int) * index->occurrencesCount);
            if (index->hasMore) {
                continue;
            } else {
                break;
            }
        }
    }
    occ[0] = occCount;
    free(index);
    fclose(invertedIndex);
    return occ;
}
