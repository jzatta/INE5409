#include <iostream>

#define DEBUG
#ifdef DEBUG
#define println(str) std::cout << str << std::endl
#else
#define println(str)
#endif