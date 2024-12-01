#ifdef DEBUG
#include <iostream>
auto & debug = std::cerr;
#else
class debuging
{
    public:
    template <class T>
    debuging & operator<< (T elem)
    {
        return *this;
    }
};

debuging debug;
#endif
