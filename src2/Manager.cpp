
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Manager.h"
#include "PrimaryKey.h"
#include "InvertedIndex.h"
#include "debug.h"


Manager::Manager(int _noFiles, char **_indexFiles) {
    printlndbg("Building Manager");
    indexFiles = _indexFiles;
    noFiles = _noFiles;
    invertedIndex = new InvertedIndex();
    primaryKey = new PrimaryKey(invertedIndex);
}

int Manager::manage() {
    char input[50];
    buildStructure();
    std::cout << "Comandos:" << std::endl;
    while (true) {
        scanf("%s", input);
        if (!strcmp(input, "exit")) {
            break;
        }
        // implementar tratamentos dos comandos
        struct Manpage *a = primaryKey->readByName("acos.3m");
        if (a == NULL) {
            printlndbg("404");
        }
        printlndbg(a->name << ":" << a->content);
    }
}
    
int Manager::buildStructure() {
    int fileNo, i;
    for (fileNo = 0; fileNo < noFiles; fileNo++) {
        for (i = 0; indexFiles[fileNo][i]; i++) {
            if (indexFiles[fileNo][i] == '/') {
                indexFiles[fileNo] = &indexFiles[fileNo][i+1];
                i = -1; // because of +1 from for loop
                // remove abspath
            }
        }
        indexFiles[fileNo][i - 4] = '\0'; // remove ".txt"
        primaryKey->add(indexFiles[fileNo]);
    }
    primaryKey->save();
}

int main (int argc, char **argv) {
    int ret = -6;
    if (argc < 2) {
        std::cout << "Insira os arquivos" << std::endl;
        return -2;
    }
    Manager *man = new Manager(argc - 1, &argv[1]);
    if (man == NULL)
        std::cout << "Erro ao alocar gerenciador" << std::endl;
    try {
        ret = man->manage();
    } catch (char const *exception) {
        std::cout << "Exception: " << exception << std::endl;
    }
    printlndbg("Done");
    delete man;
    return ret;
}