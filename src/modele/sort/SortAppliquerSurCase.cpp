#include "sort/SortAppliquerSurCase.h"
#include "sort/actionApplique/AppliqueDegat.h"
#include "sort/actionApplique/AppliqueSortDuree.h"

std::map<string, SortAppliquerSurCaseFactory*>  SortAppliquerSurCaseFactory::liste;
SortAppliquerSurCaseRegister<AppliqueDegat> appliquerDegat("appliquerDegat");
SortAppliquerSurCaseRegister<AppliquerSortDuree> appliquerDuree("appliquerDuree");

SortAppliquerSurCase::~SortAppliquerSurCase(){}


std::map<string, SortAppliquerSurCaseFactory*> SortAppliquerSurCaseFactory::getListe()
{
    return SortAppliquerSurCaseFactory::liste;
}

SortAppliquerSurCaseFactory::SortAppliquerSurCaseFactory(string name)
{
    SortAppliquerSurCaseFactory::liste.insert(make_pair(name, this));
    cerr << "Register application(" << getListe().size() << "): " << name << endl;
}
