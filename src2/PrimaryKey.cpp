
#include <stdio.h>
#include <iostream>
#include <sys/stat.h>
#include "PrimaryKey.h"
#include "InvertedIndex.h"
#include "debug.h"


PrimaryKey::PrimaryKey(InvertedIndex *_invertedIndex) {
    root = NULL;
    invertedIndex = _invertedIndex;
    manPages = fopen("manpages.dat","rw");
    if (manPages == NULL) {
        throw "Error opening manpage file";
    }
}

void PrimaryKey::add(char *manName) {
    if (root == NULL) {
        root = new TreeAVL(manName);
        return;
    }
    root->insert(manName);
}

void PrimaryKey::save() {
    char **file, path[256];
    int nElements, i, manSize;
    struct Manpage *man = (struct Manpage *)malloc(sizeof(struct Manpage));
    FILE *manFile;
    nElements = root->getNElements();
    file = root->encode();
    for (i = 0; i < nElements; i++) {
        strcpy(man->name, file[i]);
        sprintf(path, "%s.txt", man->name);
        manSize = getFileSize(path);
        manFile = fopen(path,"r");
        if (manFile == NULL) {
            throw "Error opening a manpage";
        }
        fread(man->content, 1, manSize, manFile);
        invertedIndex->add(man, i);
        fwrite(man, sizeof(struct Manpage), 1, manPages);
        fclose(manFile);
    }
    delete root;
    root = NULL;
}

struct Manpage *PrimaryKey::read(int id) {
    struct Manpage *ret = (struct Manpage *)malloc(sizeof(struct Manpage));
    fseek(manPages, sizeof(struct Manpage) * id, SEEK_SET);
    fread(ret, sizeof(struct Manpage), 1, manPages);
    return ret;
}

struct Manpage *PrimaryKey::read(char *name) {
    int i, element = 0;
    struct Manpage *ret = (struct Manpage *)malloc(sizeof(struct Manpage));
    while (true) {
        fseek(manPages, sizeof(struct Manpage) * element, SEEK_SET);
        fread(ret, sizeof(struct Manpage), 1, manPages);
        i = strcmp(name, ret->name);
        if (i == 0) {
            return ret;
        } else if (i < 0) {
            element = (element * 2) + 1;
        } else if (i > 0) {
            element = (element * 2) + 2;
        }
    }
}

int PrimaryKey::getFileSize(char *path) {
    struct stat st;
    if (stat(path, &st))
        throw "Error reading file size";
    return st.st_size;
}