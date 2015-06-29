
#include <stdio.h>
#include <iostream>
#include <malloc.h>
#include <string.h>
#include <sys/stat.h>
#include "PrimaryKey.h"
#include "InvertedIndex.h"
#include "NoAVL.hpp"
#include "debug.h"


PrimaryKey::PrimaryKey(InvertedIndex *_invertedIndex) {
    printlndbg("Building Primary");
    root = NULL;
    invertedIndex = _invertedIndex;
    manPages = NULL;
}

void PrimaryKey::add(char *manName) {
    printlndbg("Add Element: " << manName);
    if (root == NULL) {
        root = new NoAVL<char *>(manName);
        return;
    }
    root = root->inserir(manName, root);
}

void PrimaryKey::save() {
    char **file, **cteFile, path[256];
    int nElements, i, manSize;
    struct Manpage *man = (struct Manpage *)malloc(sizeof(struct Manpage));
    if (man == NULL) {
        throw "Error allocate temp manPage structure";
    }
    FILE *manFile;
    printlndbg("Save PrimaryKey");
    nElements = root->getNElements();
    cteFile = file = root->encode();
    printlndbg("getNElements: " << nElements);
    manPages = fopen("manpages.dat","w");
    if (manPages == NULL) {
        throw "Error opening manpage file";
    }
    for (i = 0; i < nElements; i++) {
        if (*file == NULL) {
            printlndbg("write empty");
            memset(man, 0, sizeof(struct Manpage));
            fwrite(man, sizeof(struct Manpage), 1, manPages);
        } else {
            printlndbg("write file: " << *file);
            strcpy(man->name, *file);
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
        file++;
    }
    fflush(manPages);
    fclose(manPages);
    delete root;
    free(cteFile);
    free(man);
    root = NULL;
}

struct Manpage *PrimaryKey::readById(int id) {
    struct Manpage *ret = (struct Manpage *)malloc(sizeof(struct Manpage));
    if (ret == NULL) {
        throw "Error allocate tempRead structure";
    }
    manPages = fopen("manpages.dat","w");
    if (manPages == NULL) {
        throw "Error opening manpage file";
    }
    fseek(manPages, sizeof(struct Manpage) * id, SEEK_SET);
    fread(ret, sizeof(struct Manpage), 1, manPages);
    if (feof(manPages) || ferror(manPages)) {
        free(ret);
        ret = NULL;
    }
    fclose(manPages);
    return ret;
}

struct Manpage *PrimaryKey::readByName(const char *name) {
    int i, element = 0;
    struct Manpage *ret = (struct Manpage *)malloc(sizeof(struct Manpage));
    if (ret == NULL) {
        throw "Error allocate tempRead structure";
    }
    manPages = fopen("manpages.dat","r");
    if (manPages == NULL) {
        throw "Error opening manpage file";
    }
    while (true) {
        fseek(manPages, sizeof(struct Manpage) * element, SEEK_SET);
        fread(ret, sizeof(struct Manpage), 1, manPages);
        if (feof(manPages) || ferror(manPages)) {
            fclose(manPages);
            free(ret);
            return NULL;
        }
        i = strcmp(name, ret->name);
        if (i == 0) {
            fclose(manPages);
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