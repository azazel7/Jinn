#include "Plateau.h"

Plateau::Plateau()
{
    largeur = hauteur = 2;
    this->initialiserPlateau();
}

Plateau::Plateau(int largeur, int hauteur)
{
    this->hauteur = hauteur;
    this->largeur = largeur;
    this->initialiserPlateau();
}

Case* Plateau::getCase(int x, int y)
{
    Position* position = Position::fabriquePosition(x, y);
    for(int i = 0; i < listeCase.size(); i++)
    {
        if( (*listeCase[i]->getPosition()) == (*position))
        {
            return listeCase[i];
        }
    }
    return NULL;
}

Case* Plateau::getCase(Position const& position)
{
    for(int i = 0; i < listeCase.size(); i++)
    {
        if( (*listeCase[i]->getPosition()) == position)
        {
            return listeCase[i];
        }
    }
    return NULL;
}

void Plateau::appliquerAction(Action action)
{
    Sort* sort = action.getSort();
    //    sort->modifierSuivantProprietaire();
    Case* origine = action.getOrigine();
    Joueur* proprietaire = sort->getProprietaire();
    std::vector<Case*> cible;
    int dissipation, nouveauTaux, distance;
    //Le sort modifie ses attributs selon la case où il est lancé
    if(origine != NULL)
    {
        //        sort->modifierSuivantOrigine(*origine);
    }
    cible = action.getCible();
    for(int i = 0; i < cible.size(); i++)
    {
        dissipation = cible[i]->getEffetDissipation();
        nouveauTaux = Sort::calculeNouveauTauxReussite(dissipation, sort->getPourcentageReussite());
        if(origine != NULL)
        {
            distance = Position::distance(*(origine->getPosition()), *(cible[i]->getPosition()));
        }
        else
        {
            distance = 1;
        }
        proprietaire->diminuerMana( distance * sort->getCoupManaParCase() );
        if(proprietaire->estMort())
        {
            return;
        }
        else
        {
            //tester réussite
            if (Sort::testerReussite(nouveauTaux))
            {
                sort->appliquerSortSurCase(*(cible[i]));
                sort->getProprietaire()->notifierResultatSort(sort->getNom(), *(cible[i]->getPosition()), true);
            }
            else
            {
                sort->getProprietaire()->notifierResultatSort(sort->getNom(), *(cible[i]->getPosition()), false);
            }
        }

    }
}

int Plateau::nombreCase()
{
    return hauteur*largeur;
}

int Plateau::nombreCaseControlable()
{
    return listeCase.size();
}

Plateau::~Plateau()
{
    for(int i = 0; i < listeCase.size(); i++)
    {
        delete listeCase[i]; //On supprime toutes les allocation de case
    }
    listeCase.clear();//On vide la liste des case
}

void Plateau::initialiserPlateau()
{
    Case* courante;
    for(int x = 0; x < largeur; x++)
    {
        for(int y = 0; y < hauteur; y++)
        {
            courante = new Case(5, 1, 0, 0, 1, 1, 0, Position::fabriquePosition(x, y));
            listeCase.push_back(courante);
        }
    }
}

int Plateau::getHauteur()
{
    return hauteur;
}

int Plateau::getLargeur()
{
    return largeur;
}

void Plateau::retirerSortDeDureeEcoulee()
{
    for(int i = 0; i < listeCase.size(); i++)
    {
        listeCase[i]->retirerSortEcoule();
    }
}

void Plateau::regenererDefenseCase()
{
    for(int i = 0; i < listeCase.size(); i++)
    {
        listeCase[i]->modifierDefense(listeCase[i]->getRegenerationDefense());
    }
}

void Plateau::regenererManaPourJoueur()
{
    int apport;
    Joueur* proprietaire;
    for(int i = 0; i < listeCase.size(); i++)
    {
        apport = listeCase[i]->getApportMana();
        proprietaire = listeCase[i]->getProprietaire();
        if(proprietaire != NULL)
        {
            proprietaire->augmenterMana(apport);
        }
    }
}

void Plateau::effectuerActionChronique()
{
    for(int i = 0; i < listeCase.size(); i++)
    {
        listeCase[i]->effectuerActionChroniqueDesSorts();
    }
}

void Plateau::retirerJoueur(Joueur* joueur)
{
    for(int i = 0; i < this->listeCase.size(); i++)
    {
        listeCase[i]->retirerJoueur(joueur);
    }
}

vector<Case*> Plateau::getListeCase()
{
    return this->listeCase;
}
