#include "Sort.h"




void Sort::appliquerSortSurCase(Case &cible)
// don't delete the following line as it's needed to preserve source code of this autogenerated element
// section 10-103-10-84-37565dd:13daac254e2:-8000:0000000000000DFB begin
{
}
// section 10-103-10-84-37565dd:13daac254e2:-8000:0000000000000DFB end
// don't delete the previous line as it's needed to preserve source code of this autogenerated element

void Sort::modifierSuivantOrigine(Case const& origine)
// don't delete the following line as it's needed to preserve source code of this autogenerated element
// section 10-103-10-84-37565dd:13daac254e2:-8000:0000000000000DFE begin
{
}
// section 10-103-10-84-37565dd:13daac254e2:-8000:0000000000000DFE end
// don't delete the previous line as it's needed to preserve source code of this autogenerated element

void Sort::modifierSuivantProprietaire()
// don't delete the following line as it's needed to preserve source code of this autogenerated element
// section 10-103-10-84-37565dd:13daac254e2:-8000:0000000000000E02 begin
{
}
// section 10-103-10-84-37565dd:13daac254e2:-8000:0000000000000E02 end
// don't delete the previous line as it's needed to preserve source code of this autogenerated element

string Sort::description()
// don't delete the following line as it's needed to preserve source code of this autogenerated element
// section 10-103-10-84-37565dd:13daac254e2:-8000:0000000000000E0F begin
{
}
// section 10-103-10-84-37565dd:13daac254e2:-8000:0000000000000E0F end
// don't delete the previous line as it's needed to preserve source code of this autogenerated element

Sort::~Sort()
// don't delete the following line as it's needed to preserve source code of this autogenerated element
// section 10-103-10-63-43ade06e:13db6b35c7b:-8000:0000000000000E67 begin
{
}
// section 10-103-10-63-43ade06e:13db6b35c7b:-8000:0000000000000E67 end
// don't delete the previous line as it's needed to preserve source code of this autogenerated element

Sort::Sort(string nom, int coupMana, bool elite, int porteeMax, int reussite, int nbCible, int att, int duree, int znEffet, int dissip, int nbMaxSortDissip)
// don't delete the following line as it's needed to preserve source code of this autogenerated element
// section -64--88-1-13--239a61df:13dc1d51575:-8000:0000000000000F2A begin
{
}
// section -64--88-1-13--239a61df:13dc1d51575:-8000:0000000000000F2A end
// don't delete the previous line as it's needed to preserve source code of this autogenerated element

int Sort::calculeNouveauTauxReussite(int dissip, int ancienTaux)
{
	return 1;
}

int Sort::getPourcentageReussite()
{
	return pourcentageReussite;
}

bool Sort::testerReussite(int taux)
{
    int nb = rand()%100;
    if(nb <= taux)
    {
        return true;
    }
    return false;
}

Joueur* Sort::getProprietaire()
{
	return proprietaire;
}

int Sort::getCoupManaParCase()
{
	return coupManaParCase;
}

string Sort::getNom()
{
    return nom;
}
