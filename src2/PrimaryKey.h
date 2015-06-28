#ifndef PRIMARYKEY_H
#define PRIMARYKEY_H

struct PrimaryKeyNode {
    char *name;
    int pos;
}

struct Manpage{
    char name[50];
    char content[139715];
};

class InvertedIndex;

class PrimaryKey {
private:
    Tree<struct PrimaryKeyNode> *root;
    FILE *manpages;
    InvertedIndex *invertedIndex;
    
    getFileSize(char *path);
public:
    PrimaryKey(InvertedIndex *invertedIndex);
    
    void add(char *manName);
    
    void save(void);
    
    struct Manpage *read(int id);
    struct Manpage *read(char *name);
};

#endif
