#ifndef UsineSort_h
#define UsineSort_h

#include "sort/Sort.h"

class Sort;
class UsineSort
{

public:
    static Sort* fabriqueSort(string const& nom);
    static vector<string> liste();
};
#endif // UsineSort
