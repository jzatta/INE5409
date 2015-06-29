#include <iostream>

#define DEBUG
#ifdef DEBUG
#define printlndbg(str) std::cerr << str << std::endl
#else
#define printlndbg(str)
#endif