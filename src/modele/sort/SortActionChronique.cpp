#include "sort/SortActionChronique.h"
#include "sort/actionChronique/chroniqueDegat.h"

std::map<string, SortActionChroniqueFactory*>  SortActionChroniqueFactory::liste;

SortActionChroniqueRegister<ChroniqueDegat> chroniquedegat("chroniqueDegat");

SortActionChronique::~SortActionChronique(){}


std::map<string, SortActionChroniqueFactory*> SortActionChroniqueFactory::getListe()
{
    return SortActionChroniqueFactory::liste;
}

SortActionChroniqueFactory::SortActionChroniqueFactory(string name)
{
    SortActionChroniqueFactory::liste.insert(make_pair(name, this));
    cerr << "Register chronique (" << getListe().size() << "): " << name << endl;
}
