#include <iostream>

#define NO_DEBUG
#ifdef DEBUG
#define println(str) std::cout << str << std::endl
#else
#define println(str)
#endif