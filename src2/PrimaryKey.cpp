
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
    primaryKey = NULL;
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
    int nElements, i, manPos, manSize;
    struct Manpage *man = (struct Manpage *)malloc(sizeof(struct Manpage));
    if (man == NULL) {
        throw "Error allocate temp manPage structure";
    }
    struct PrimaryKeyData *key = (struct PrimaryKeyData *)malloc(sizeof(struct PrimaryKeyData));
    if (key == NULL) {
        throw "Error allocate temp PK structure";
    }
    FILE *manFile;
    printlndbg("Save PrimaryKey");
    nElements = root->getNElements();
    cteFile = file = root->encode();
    printlndbg("getNElements: " << nElements);
    manPages = fopen("manpages.dat","w");
    if (manPages == NULL) {
        throw "Error opening manpages file";
    }
    primaryKey = fopen("primary.dat","w");
    if (primaryKey == NULL) {
        throw "Error opening PrimaryTree file";
    }
    manPos = 0;
    for (i = 0; i < nElements; i++) {
        if (*file != NULL) {
            printlndbg("write file: " << *file << "@" << manPos);
            strcpy(man->name, *file);
            strcpy(key->name, *file);
            key->pos = manPos++;
            sprintf(path, "%s.txt", man->name);
            manSize = getFileSize(path);
            manFile = fopen(path,"r");
            if (manFile == NULL) {
                throw "Error opening a manpage";
            }
            fread(man->content, 1, manSize, manFile);
            man->content[manSize - 1] = '\0';
            invertedIndex->add(man, key->pos);
            fwrite(man, sizeof(struct Manpage), 1, manPages);
            fwrite(key, sizeof(struct PrimaryKeyData), 1, primaryKey);
            fclose(manFile);
        } else {
            printlndbg("write empty");
            memset(key, 0, sizeof(struct PrimaryKeyData));
            fwrite(key, sizeof(struct PrimaryKeyData), 1, primaryKey);
        }
        file++;
    }
    fflush(manPages);
    fclose(manPages);
    fflush(primaryKey);
    fclose(primaryKey);
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
    manPages = fopen("manpages.dat","r");
    if (manPages == NULL) {
        throw "Error opening manpages file";
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
    struct PrimaryKeyData *key = (struct PrimaryKeyData *)malloc(sizeof(struct PrimaryKeyData));
    if (key == NULL) {
        throw "Error allocate temp PK structure";
    }
    primaryKey = fopen("primary.dat","r");
    if (primaryKey == NULL) {
        throw "Error opening PrimaryTree file";
    }
    while (true) {
        fseek(primaryKey, sizeof(struct PrimaryKeyData) * element, SEEK_SET);
        fread(key, sizeof(struct PrimaryKeyData), 1, primaryKey);
        printlndbg("key: " << key->name << "->" << key->pos << "@" << element);
        if (feof(primaryKey) || ferror(primaryKey)) {
            fclose(primaryKey);
            free(key);
            return NULL;
        }
        i = strcmp(name, key->name);
        if (i == 0) {
            struct Manpage *ret = (struct Manpage *)malloc(sizeof(struct Manpage));
            if (ret == NULL) {
                throw "Error allocate tempRead structure";
            }
            manPages = fopen("manpages.dat","r");
            if (manPages == NULL) {
                throw "Error opening manpages file";
            }
            fseek(manPages, sizeof(struct Manpage) * key->pos, SEEK_SET);
            fread(ret, sizeof(struct Manpage), 1, manPages);
            fclose(manPages);
            fclose(primaryKey);
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