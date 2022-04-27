#ifndef DEBUG_H
#define DEBUG_H
#include <iostream>
#define ShowMessages	0

#if ShowMessages
#define MSG(X) std::cout << X << std::endl
#else
#define MSG(X)

#endif
#endif

