#include <iostream>

#define DEBUG
#ifdef DEBUG
#define printlndbg(str) std::cout << str << std::endl
#else
#define printlndbg(str)
#endif