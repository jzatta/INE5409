
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
    int wordsCount = 0, i, j;
    char ch;
    char wordsFouded[3000][50];
    bool notInArchive[3000];
    struct InvertedIndexData *occ;
    ptr = page->content;
    ch = *ptr++;
    // read content of manpage
    printlndbg("II: " << page->name << "@" << id);
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
                        break;
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
        notInArchive[i] = true;
    }
    invertedIndex = fopen("index.dat","r+");
    if (invertedIndex == NULL) {
        throw "Error opening InvertedIndex file";
    }
    occ = (struct InvertedIndexData *)malloc(sizeof(struct InvertedIndexData));
    // search occurrence in file, if has add link to file
    for (j = 0; ; j++) {
        fseek(invertedIndex, sizeof(struct InvertedIndexData) * j, SEEK_SET);
        fread(occ, sizeof(struct InvertedIndexData), 1, invertedIndex);
        if (feof(invertedIndex)) {
            break;
        }
        for (i = 0; i < wordsCount; i++) {
            if (!strcmp(occ->word, wordsFouded[i])) {
                notInArchive[i] = false;
                printlndbg("II update: " << occ->word << " : " << occ->occurrencesCount);
                occ->occurrences[occ->occurrencesCount] = id;
                occ->occurrencesCount += 1;
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
        if (notInArchive[i]) {
            strcpy(occ->word, wordsFouded[i]);
            occ->occurrences[0] = id;
            occ->occurrencesCount = 1;
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

InvertedIndexData *InvertedIndex::search(char *word) {
    InvertedIndexData *occ;
    int j = 0;
    invertedIndex = fopen("index.dat","r");
    if (invertedIndex == NULL) {
        throw "Error opening InvertedIndex file";
    }
    occ = (struct InvertedIndexData *)malloc(sizeof(struct InvertedIndexData));
    // search occurrence in file, if has add link to file
    while (true) {
        fseek(invertedIndex, sizeof(struct InvertedIndexData) * j++, SEEK_SET);
        fread(occ, sizeof(struct InvertedIndexData), 1, invertedIndex);
        if (feof(invertedIndex)) {
            free(occ);
            occ = NULL;
            break;
        }
        if (!strcmp(occ->word, word)) {
            break;
        }
    }
    fclose(invertedIndex);
    return occ;
}
