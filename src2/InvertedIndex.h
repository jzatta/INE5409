#ifndef INVERTEDINDEX_H
#define INVERTEDINDEX_H

#define MAXOCCURRENCES 75
struct InvertedIndexData {
    char word[50];
    int occurrences[MAXOCCURRENCES];
    int occurrencesCount;
    char hasMore;
};

class InvertedIndex {
private:
    FILE *invertedIndex;
    
    bool isProhibited(char *word);
    bool isSeparator(char c);
public:
    InvertedIndex();
    
    void add(struct Manpage *page, int id);
    
    int *search(char *word);
};

#endif
