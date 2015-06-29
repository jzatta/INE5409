#ifndef INVERTEDINDEX_H
#define INVERTEDINDEX_H

struct InvertedIndexData {
    char word[50];
    char dataCount;
    int dataLocal[50];
    char hasMore;
};

class InvertedIndex {
private:
    FILE *invertedIndex;
    
    bool isProhibited(char *word);
    char *getNext(char *);
public:
    InvertedIndex();
    
    void add(struct Manpage *page, int id);
    
    int *seach(char *word);
};

#endif
