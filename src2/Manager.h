#ifndef MANAGER_H
#define MANAGER_H

class PrimaryKey;
class InvertedIndex;

class Manager {
private:
    char **indexFiles;
    int noFiles;
    PrimaryKey *primaryKey;
    InvertedIndex *invertedIndex;
    
    void sortInput(char **input);
    int getFileSize(char *path);
public:
    Manager(int _noFiles, char **_indexFiles);
    
    int manage(void);
    
    int buildStructure(void);
};

#endif
