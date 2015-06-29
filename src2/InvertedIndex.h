#ifndef INVERTEDINDEX_H
#define INVERTEDINDEX_H

struct InvertedIndexData {
    char word[50];
    int occurrences[5642];
    int occurrencesCount;
};

class InvertedIndex {
private:
    FILE *invertedIndex;
    
    bool isProhibited(char *word);
    bool isSeparator(char c);
public:
    InvertedIndex();
    
    void add(struct Manpage *page, int id);
    
    InvertedIndexData *search(char *word);
};

#endif
