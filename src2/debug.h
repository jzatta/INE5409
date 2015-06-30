#include <iostream>

#define NO_DEBUG
#ifdef DEBUG
#define printlndbg(str) std::cout << str << std::endl
#else
#define printlndbg(str)
#endif

/*
                printlndbg("II debug:" << occ->word << "@" << occ->occurrencesCount << ":");
                for (int k = 0; k < occ->occurrencesCount; k++) {
                std::cout << occ->occurrences[k] << ", ";
                }
                std::cout << std::endl;
                */