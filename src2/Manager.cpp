
#include <iostream>
#include <malloc.h>
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
    char input[128];
    buildStructure();
    while (true) {
        std::cout << "\n\n\n\n\nComands:\ncommand:'command'\nword:'wordsearch'\n2word:'firstword','secondword'\nexit\n" << std::endl;
        scanf("%s", input);
        if (!strncmp(input, "exit", 4)) {
            break;
        }
        else if (!strncmp(input, "command:", 8)) {
            struct Manpage *man = primaryKey->readByName(&input[8]);
            if (man != NULL) {
                std::cout << man->name << std::endl;
                std::cout << man->content << std::endl;
                free(man);
            } else {
                std::cout << "Manpage not founded" << std::endl;
            }
        }
        else if (!strncmp(input, "word:", 5)) {
            int *occ = invertedIndex->search(&input[5]);
            int i;
            if (*occ > 0) {
//                 printlndbg("manage: " << occ->occurrencesCount);
                for (i = 1; i <= *occ; i++) {
                    std::cout << primaryKey->readById(occ[i])->name << std::endl;
                }
            } else {
                std::cout << "Manpages not founded" << std::endl;
            }
            free(occ);
        }
        else if (!strncmp(input, "2word:", 6)) {
            
        }
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