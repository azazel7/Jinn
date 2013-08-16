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
    Case* origine = action.getOrigine();
    Joueur* proprietaire = sort->getProprietaire();
    std::vector<Case*> cible;
    int dissipation, nouveauTaux, distance;
    //Le sort modifie ses attributs selon la case où il est lancé
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
        if(Sort::comparaisonType(proprietaire->getAbilite(), sort->getTypeSort()) == true)
        {
            nouveauTaux = nouveauTaux + proprietaire->getNiveauAbilite();
        }
        if(proprietaire->estMort())
        {
            throw invalid_argument("Le joueur est mort");
        }
        else
        {
            //tester réussite
            if (Sort::testerReussite(nouveauTaux))
            {
                sort->getProprietaire()->notifierResultatSort(sort->getNom(), *(cible[i]->getPosition()), true);
<<<<<<< HEAD
=======
                //TODO faire la liaison avec les types de sort
>>>>>>> 57e33e27a76faf8679788d9d5c4eeb8df3c4153f
                sort->appliquerSortSurCase(*(cible[i]));
            }
            else
            {
                sort->getProprietaire()->notifierResultatSort(sort->getNom(), *(cible[i]->getPosition()), false);
            }
        }
        proprietaire->notifierCase(*(cible[i]));
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
        delete listeCase[i]; //On supprime toutes les allocations de case
    }
    listeCase.clear();//On vide la liste des cases
}

void Plateau::initialiserPlateau()
{
    Case* courante;
    for(int x = 0; x < largeur; x++)
    {
        for(int y = 0; y < hauteur; y++)
        {
            courante = new Case(500, 1, 0, 0, 1, 100, 0, Position::fabriquePosition(x, y));
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
    for_each(this->listeCase.begin(), this->listeCase.end(), FoncteurSortEcoule());
}

void Plateau::regenererDefenseCase()
{
    for_each(this->listeCase.begin(), this->listeCase.end(), FoncteurRegenererCase());
}

void Plateau::regenererManaPourJoueur()
{
    for_each(this->listeCase.begin(), this->listeCase.end(), FoncteurRegenererManaJoueurCase());
}

void Plateau::effectuerActionChronique()
{
    for_each(this->listeCase.begin(), this->listeCase.end(), FoncteurActionChronique());
}

void Plateau::retirerJoueur(Joueur* joueur)
{
    for_each(this->listeCase.begin(), this->listeCase.end(), FoncteurRetirerJoueur(joueur));
}

vector<Case*> Plateau::getListeCase()
{
    return this->listeCase;
}
void FoncteurRegenererCase::operator()(Case* square) const
{
    square->modifierDefense(square->getRegenerationDefense());
}

void FoncteurSortEcoule::operator()(Case* square) const
{
    square->retirerSortEcoule();
}

void FoncteurRegenererManaJoueurCase::operator()(Case* square) const
{
    int apport;
    Joueur* proprietaire;
    apport = square->getApportMana();
    proprietaire = square->getProprietaire();
    if(proprietaire != NULL)
    {
        proprietaire->augmenterMana(apport);
    }
}
FoncteurRetirerJoueur::FoncteurRetirerJoueur(Joueur* joueur)
{
    this->joueur = joueur;
}

void FoncteurRetirerJoueur::operator()(Case* square) const
{
    square->retirerJoueur(this->joueur);
}

void FoncteurActionChronique::operator()(Case* square) const
{
    square->effectuerActionChroniqueDesSorts();
}
