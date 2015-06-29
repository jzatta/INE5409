#ifndef PRIMARYKEY_H
#define PRIMARYKEY_H

struct Manpage{
    char name[50];
    char content[139715];
};

struct PrimaryKeyData {
    char name[50];
    int pos;
};

template<typename T>
class NoAVL;
class InvertedIndex;

class PrimaryKey {
private:
    NoAVL<char *> *root;
    FILE *manPages, *primaryKey;
    InvertedIndex *invertedIndex;
    
    int getFileSize(char *path);
public:
    PrimaryKey(InvertedIndex *invertedIndex);
    
    void add(char *manName);
    
    void save(void);
    
    struct Manpage *readById(int id);
    struct Manpage *readByName(const char *name);
};

#endif
