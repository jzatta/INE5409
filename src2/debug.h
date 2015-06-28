#include <iostream>

#define NO_DEBUG
#ifdef DEBUG
#define printlndbg(str) std::cout << str << std::endl
#else
#define printlndbg(str)
#endif