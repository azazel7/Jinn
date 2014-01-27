#include "sort/SortAppliquerSurCase.h"

SortAppliquerSurCase::~SortAppliquerSurCase(){}

std::map<string, SortAppliquerSurCaseFactory*>  SortAppliquerSurCaseFactory::liste;

std::map<string, SortAppliquerSurCaseFactory*> SortAppliquerSurCaseFactory::getListe()
{
    return SortAppliquerSurCaseFactory::liste;
}

SortAppliquerSurCaseFactory::SortAppliquerSurCaseFactory(string name)
{
    getListe().insert(make_pair(name, this));
}
