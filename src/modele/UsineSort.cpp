#include "UsineSort.h"
#include "sort/actionApplique/AppliqueDegat.h"
#include "sort/actionApplique/AppliqueControle.h"
#include "sort/actionApplique/AppliqueBaseProtection.h"
#include "sort/actionApplique/AppliqueRevelationCase.h"
#include "sort/actionApplique/AppliqueSortDuree.h"
#include "sort/actionApplique/AppliqueSoin.h"
#include "sort/actionApplique/AppliqueConditionDefense.h"
#include "sort/actionApplique/AppliqueConditionComparaisonMana.h"
#include "sort/actionApplique/AppliqueConsommerMana.h"
#include "sort/actionApplique/AppliqueSoinAstral.h"
#include "sort/actionApplique/AppliqueBrulureMana.h"
#include "sort/actionApplique/AppliqueVolDeMana.h"
#include "sort/actionApplique/AppliqueVolDefense.h"
#include "sort/actionApplique/AppliqueConditionPresenceSort.h"

#include "sort/actionChronique/chroniqueDegat.h"
#include "sort/actionChronique/chroniqueDegatCumulatif.h"
#include "sort/actionChronique/chroniqueSoin.h"
#include "sort/actionChronique/chroniqueSoinCondVie.h"

Sort* UsineSort::fabriqueSort(string const& nom)
{
    Sort* retour = NULL;
    if(nom == "Sceau de Controle")
    {
        retour = new Sort("Sceau de Controle", 1, false, 5, 100, 1, 0, 0, 0, 0, 0, NEUTRE);
        retour->ajouterApplication(new AppliqueControle());
        retour->setDescription("Sort permettant de prendre le controle d'une case");
    }
    else if(nom == "Boule de Feu")
    {
        retour = new Sort("Boule de Feu", 5, false, 5, 100, 1, 0, 0, 0, 0, 0, FEU);
        retour->ajouterApplication(new AppliqueDegat(50));
        retour->setDescription("Lance une boule de feu infligeant 50 degats");
    }
    else if(nom == "Rune de Protection")
    {
        retour = new Sort("Rune de Protection", 5, false, 5, 100, 1, 0, 3, 0, 0, 0, NEUTRE);
        retour->ajouterApplication(new AppliquerSortDuree());
        retour->ajouterApplication(new AppliqueBaseProtection(40));
        retour->setDescription("Augmente la defense maximal d'une case de 1 pendant 3 tours");
    }
    else if(nom == "Sceau de Vision")
    {
        retour = new Sort("Sceau de Vision", 1, false, 5, 100, 1, 0, 0, 0, 0, 0, NEUTRE);
        retour->ajouterApplication(new AppliqueRevelationCase());
        retour->setDescription("Sort permettant de visualiser une case");
    }
    else if(nom == "Spirale de Feu")
    {
        retour = new Sort("Spirale de Feu", 7, false, 5, 90, 1, 0, 5, 0, 0, 0, FEU);
        retour->ajouterActionChronique(new ChroniqueDegat(8));
        retour->ajouterApplication(new AppliquerSortDuree());
        retour->setDescription("Piege la case dans une spirale de feu infligeant 8 points de degats par tour");
    }
    else if(nom == "Esprit Patient")
    {
        retour = new Sort("Esprit Patient", 10, false, 5, 90, 1, 0, 2, 0, 0, 0, LUMIERE);
        retour->ajouterApplication(new AppliquerSortDuree());
        retour->ajouterApplication(new AppliqueSoin(120, false, true));
        retour->setDescription("A la fin de la duree du sort, Esprit Patient redonne 120 point de defense a la case");
    }
    else if(nom == "Chaleur de Savane")
    {
        retour = new Sort("Chaleur de Savane", 20, true, 5, 90, 1, 0, 5, 0, 0, 0, FEU);
        retour->ajouterApplication(new AppliquerSortDuree());
        retour->ajouterActionChronique(new ChroniqueDegatCumulatif(8, 8));
        retour->setDescription("Sort durant 5 tours et infligeant a la case 8 point de degat par tour d'activation");
    }
    else if(nom == "Esprit Gardien")
    {
        retour = new Sort("Esprit Gardien", 7, false, 5, 90, 1, 0, 10, 0, 0, 0, TERRE);
        retour->ajouterApplication(new AppliquerSortDuree());
        retour->ajouterActionChronique(new ChroniqueSoinCondVie(30, 50, true));
        retour->setDescription("Pendant 10 tours, si la case cible a moins de 50% de sa defense, le sort lui redonne 30 point de vie");
    }
    else if(nom == "Frappe Sournoise")
    {
        retour = new Sort("Frappe Sournoise", 6, false, 5, 90, 1, 0, 0, 0, 0, 0, TENEBRE);
        AppliqueConditionDefense* cond = new AppliqueConditionDefense(90, true, true, false);
        cond->ajouterApplication(new AppliqueDegat(70));
        retour->ajouterApplication(new AppliqueDegat(30));
        retour->ajouterApplication(cond);
        retour->setDescription("Inflige 30 points de degat. Si la cible a plus de 90% de sa vie, inflige 70 points de degat supplementaire");
    }
    else if(nom == "Choc Spirituel")
    {
        retour = new Sort("Choc Spirituel", 10, true, 5, 90, 1, 0, 0, 0, 0, 0, AIR);
        AppliqueConditionComparaisonMana* cond = new AppliqueConditionComparaisonMana(0, false, true, false);
        cond->ajouterApplication(new AppliqueDegat(120));
        retour->ajouterApplication(new AppliqueDegat(120));
        retour->ajouterApplication(cond);
        retour->setDescription("Inflige 120 points de degat. Si vous avez plus de mana que le proprietaire, Choc Sprirituel inflige 120 points de degat supplementaire");
    }
    else if(nom == "Soin Astral")
    {
        retour = new Sort("Soin Astral", 0, true, 5, 90, 1, 0, 0, 0, 0, 0, LUMIERE);
        retour->ajouterApplication(new AppliqueConsommerMana(25, true, true, false));
        retour->ajouterApplication(new AppliqueSoinAstral(7, true, false));
        retour->setDescription("Vous perder 25% de votre mana et la case cible gagne en defense sept fois ce que vous avez perdu en mana");
    }
    else if(nom == "Regard Vampirique")
    {
        retour = new Sort("Regard Vampirique", 7, false, 5, 90, 1, 0, 0, 0, 0, 0, TENEBRE);
        retour->ajouterApplication(new AppliqueDegat(40));
        retour->ajouterApplication(new AppliqueBrulureMana(5, false, true, false, false, false));
        retour->setDescription("Vous infligez 40 point de degat a la cible et son proprietaire perd 5 point de mana");
    }
    else if(nom == "Festin")
     {
        retour = new Sort("Festin", 6, false, 5, 90, 1, 0, 0, 0, 0, 0, TENEBRE);
        retour->ajouterApplication(new AppliqueVolDefense(40, false, true, false, false));
        retour->setDescription("Transfert 40 point de defense de la cible vers la case d'origine");
    }
    else if(nom == "Morsure Hivernale")
     {
        retour = new Sort("Morsure Hivernale", 17, false, 5, 90, 1, 0, 7, 0, 0, 0, EAU);
        retour->ajouterApplication(new AppliquerSortDuree());
        retour->ajouterApplication(new AppliqueBaseProtection(-50));
        retour->ajouterApplication(new AppliqueDegat(40));
        retour->setDescription("Sort infligeant 40 point de degat et diminuant pendant 7 tours de 50 la defense maximale de la cible");
    }
    else if(nom == "Eclaire de Zeus")
    {
        retour = new Sort("Eclaire de Zeus", 8, false, 7, 90, 1, 0, 0, 0, 0, 0, AIR);
        AppliqueConditionPresenceSort* cond = new AppliqueConditionPresenceSort("Morsure Hivernale", false, true, false);
        cond->ajouterApplication(new AppliqueDegat(70));
        retour->ajouterApplication(cond);
        retour->ajouterApplication(new AppliqueDegat(30));
        retour->setDescription("Inflige 30 point de degats. Si la cible est possede le sort Morsure Hivernale, Eclaire de Zeus inflige 70 points de degat supplementaires");

    }
    //TODO Sort qui supprime un sort sur la case d'origine et inflige des degats
    //TODO Sort de liaison des cases. SI l'une tombe à 0, l'autre aussi
    //TODO Soin de groupe
    return retour;
}

std::vector<string> UsineSort::liste()
{
    vector<string> retour;
    retour.push_back("Sceau de Controle");
    retour.push_back("Boule de Feu");
    retour.push_back("Rune de Protection");
    retour.push_back("Sceau de Vision");
    retour.push_back("Spirale de Feu");
    retour.push_back("Esprit Patient");
    retour.push_back("Chaleur de Savane");
    retour.push_back("Esprit Gardien");
    retour.push_back("Frappe Sournoise");
    retour.push_back("Choc Spirituel");
    retour.push_back("Soin Astral");
    retour.push_back("Regard Vampirique");
    retour.push_back("Festin");
    retour.push_back("Morsure Hivernale");
    retour.push_back("Eclaire de Zeus");
    return retour;
}

Sort* UsineSort::fabriqueSort(Sort* sortModele)
{
    Sort* sort = UsineSort::fabriqueSort(sortModele->getNom());
    sort->setProprietaire(sortModele->getProprietaire());
    sort->setOrigine(sortModele->getOrigine());
    sort->setId(sortModele->getId());
    return sort;
}
