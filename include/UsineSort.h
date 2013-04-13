#ifndef UsineSort_h
#define UsineSort_h

#include "Sort.h"
#include "sort/SceauControle.h"
#include "sort/BouleDeFeu.h"
#include "sort/RuneDeProtection.h"


class UsineSort
{

public:
    static Sort* fabriqueSort(string const& nom);
    static vector<string> liste();
};
#endif // UsineSort
