#ifndef UsineSort_h
#define UsineSort_h

#include "Sort.h"
#include "sort/SceauControle.h"



class UsineSort
{

public:
    static Sort* fabriqueSort(string const& nom);
    static vector<string> liste();
};
#endif // UsineSort
