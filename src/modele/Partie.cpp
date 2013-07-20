#include "Partie.h"

Partie::Partie(string nom, int nombrePlace, int nombreSortParJoueur)
{
    this->nom = nom;
    this->nombreDePlace = nombrePlace;
    this->enCours = false;
    this->estFini = false;
    this->nombreSortParJoueur = nombreSortParJoueur;
    this->joueurCourant = NULL;
    this->indexEquipeCourante = 0;
    this->nombreDeJoueurAyantJoue = 0;
}


/** 
     *  Demarre la partie.
     */
void Partie::demarrerPartie()
{
    this->enCours = true;
    this->nombreDeJoueurAyantJoue = 0;
    //notifier joueur du démarrage de la partie
    for(int i = 0; i < this->joueur.size(); i++)
    {
        this->joueur[i]->notifierDebutPartie();
    }
    this->changerJoueur();
}


/** 
     *  Verifie la victoire d'une équipe
     */
bool Partie::verifierVictoire(Equipe & equipe)
{
    int nombreCaseControllee = 0;
    Case* courante;
    Joueur* proprietaire;
    string nom;
    //On parcoure toutes les cases
    for(int x = 0; x < plateau->getLargeur(); x++)
    {
        for(int y = 0; y < plateau->getHauteur(); y++)
        {
            courante = plateau->getCase(x, y);
            if(courante != NULL)
            {
                //On récupére son proprietaire
                proprietaire = courante->getProprietaire();
                if(proprietaire != NULL)
                {
                    if(proprietaire->getNomEquipe() == equipe.getNom())
                    {
                        nombreCaseControllee++;
                    }
                }
            }
        }
    }
    if(nombreCaseControllee == plateau->nombreCaseControlable())
    {
        return true;
    }
    return false;
}

void Partie::initialiser()
{
    plateau = new Plateau(3,3);
}

std::vector<Sort*> Partie::listeSort()
{
    vector<Sort*> retour;
    //On liste les sorts
    vector<string> listeNom = UsineSort::liste();
    for(int i = 0; i < listeNom.size(); i++)
    {
        retour.push_back(UsineSort::fabriqueSort(listeNom[i])); //On créer une liste de sort.
    }
    return retour;
}
bool Partie::finPartie(string & nomEquipeGagnante)
{
    if(this->equipe.size() == 1)
    {
        nomEquipeGagnante = equipe[0]->getNom();
        return true;
    }
    else if(this->equipe.size() <= 0)
    {
        //TODO que faire quand il n'y a plus d'équipe
    }
    for(int i = 0; i < equipe.size(); i++)
    {
        if(verifierVictoire(*(equipe[i])) == true)
        {
            nomEquipeGagnante = equipe[i]->getNom();
            return true;
        }
    }
    return false;
}

void Partie::finirPartie(string nomEquipeGagnante)
{
    GestionnaireLogger::ecrirMessage(TypeMessage::INFO, "Fin de la partie");
    this->estFini = true;
    this->enCours = false;
    for(int i = 0; i < this->joueur.size(); i++)
    {
        this->joueur[i]->notifierFinPartie(nomEquipeGagnante);
    }
}

bool Partie::isEnCours()
{
    return enCours;
}

void Partie::setEnCours(bool valeur)
{
    this->enCours = valeur;
}

Plateau* Partie::getPlateau()
{
    return plateau;
}

bool Partie::actionValide(Action & action)
{
    if(action.getOrigine()->getProprietaire() != action.getSort()->getProprietaire())
    {
        return false;
    }
    if(action.getSort()->getProprietaire()->estMort())
    {
        return false;
    }
    return true;
}

int Partie::nombreDeJoueur()
{
    return this->joueur.size();
}

bool Partie::joueurExiste(string nom)
{
    for(int i = 0; i < this->joueur.size(); i++)
    {
        if(this->joueur[i]->getNom() == nom)
        {
            return true;
        }
    }
}

bool Partie::prete()
{
    if(this->nombreDePlace != this->nombreDeJoueur() || this->equipe.size() < 2)
    {
        return false;
    }
    return true;
}


void Partie::regenererManaJoueur()
{
    for(int i = 0; i < this->joueur.size(); i++)
    {
        if(this->joueur[i]->estMort() == false)
        {
            this->joueur[i]->augmenterMana(joueur[i]->getGainInitialMana());
        }
    }
}

bool Partie::estJoueurCourrant(Joueur* joueur)
{
    if(joueur == this->joueurCourant)
    {
        return true;
    }
    return false;
}

vector<string> Partie::listeEquipe()
{
    vector<string> retour(this->equipe.size());
    for(int i = 0; i < this->equipe.size(); i++)
    {
        retour[i] = this->equipe[i]->getNom();
    }
    return retour;
}

int Partie::getNombreSortParJoueur()
{
    return this->nombreSortParJoueur;
}

Equipe* Partie::equipeExiste(string const& nom)
{
    for(int i = 0; i < this->equipe.size(); i++)
    {
        if(this->equipe[i]->getNom() == nom)
        {
            return this->equipe[i];
        }
    }
    return NULL;
}


Joueur* Partie::ajouterJoueur(string const& nom, string const& nomEquipe, vector<string> const& listeSort)
{
    Equipe* equipe = NULL;
    Joueur* joueur = NULL;
    Sort* sort = NULL;
    bool dejaElite = false;
    if(this->joueurExiste(nom) == true)
    {
        throw invalid_argument("Nom de joueur existant");
    }
    if(this->nombreSortParJoueur != listeSort.size())
    {
        throw invalid_argument("Nombre de sort invalide");
    }

    joueur = new Joueur();
    joueur->setNom(nom);

    for(int i = 0; i < nombreSortParJoueur; i++)
    {
        sort = UsineSort::fabriqueSort(listeSort[i]);
        if(sort == NULL)
        {
            delete joueur;
            throw invalid_argument("Sort inconnu");
        }
        if(sort->getElite() == true && dejaElite == true)
        {
            delete joueur;
            throw invalid_argument("Impossible d'avoir plus d'un sort elite");
        }
        if(sort->getElite() == true && dejaElite == false)
        {
            dejaElite = true;
        }
        joueur->ajouterSort(sort);
    }

    if((equipe = this->equipeExiste(nomEquipe)) != NULL)
    {
        joueur->setEquipe(equipe);
        equipe->setNombreJoueur(equipe->getNombreJoueur()+1);
    }
    else
    {
        equipe = new Equipe(nomEquipe);
        this->equipe.push_back(equipe);
        joueur->setEquipe(equipe);
        equipe->setNombreJoueur(equipe->getNombreJoueur()+1);
    }
    joueur->genererStatistique();
    this->joueur.push_back(joueur);
    return joueur;
}

int Partie::getNombreDePlace()
{
    return this->nombreDePlace;
}


void Partie::effectuerAction(Action* action, Joueur* joueur)
{
    vector<Case*> cible;
    string nomEquipeGagnante;
    GestionnaireLogger::ecrirMessage(TypeMessage::INFO, "Action effectuée");
    //Cas des sorts
    if(action->getSort() != NULL && action->getCible().size() != 0)
    {
        //Si ce n'est pas au joueur courant on retire
        if(joueur != this->joueurCourant)
        {
            throw invalid_argument("Pas le joueur courant");
            return;
        }
        if(action->getSort()->getProprietaire() != joueur)
        {
            throw invalid_argument("Le proprietaire du sort n'est pas le joueur");
            return;
        }
        if(action->getOrigine() != NULL && action->getOrigine()->getProprietaire() != joueur)
        {
            throw invalid_argument("La case d'origine n'appartient pas au joueur");
            return;
        }
        //Verifier que le joueur posséde le sort
        if(joueur->possedeSort(action->getSort()) == false)
        {
            throw invalid_argument("Le joueur ne posséde pas ce sort");
            return;
        }
        //Verification des distances
        cible = action->getCible();
        for(int i = 0; i < action->getCible().size(); i++)
        {
            if(action->getOrigine() != NULL)
            {
                if(Position::distance( *(action->getOrigine()->getPosition()), *(cible[i]->getPosition())) > action->getSort()->getPorteeMax())
                {
                    throw invalid_argument("Impossible de lancer le sort sur une telle distance");
                    return;
                }
            }
            else
            {
                //Tout du moins, cela vérifie si la cible est bien sur le bord, donc, si l'une de ses coordonné est sur le bord
                if(cible[i]->getPosition()->getX() != 0 && cible[i]->getPosition()->getX() != this->plateau->getLargeur() - 1 && cible[i]->getPosition()->getY() != 0 && cible[i]->getPosition()->getX() != this->plateau->getHauteur() - 1)
                {
                    throw invalid_argument("La cible est au centre, impossible de l'atteindre.");
                    return;
                }
            }
        }
        plateau->appliquerAction(*action);
        if(joueur->estMort())
        {
            //Le joueur est retiré du plateau, ses sorts supprimés et ses cases libérées, mais il appartient toujours à l'équipe et n'est pas delete
            //Il est juste retiré du plateau
            plateau->retirerJoueur(joueur);
            for(int i = 0; i < this->joueur.size(); i++)
            {
                this->joueur[i]->notifierMort(joueur->getNom());
            }
            GestionnaireLogger::ecrirMessage(TypeMessage::INFO, "Un joueur est mort");
        }
    }
    //Cas des autre action comme la fin de tour
    else
    {
        //Cela correspond au changement de joueur
        if(action->getOrigine() == NULL && action->getSort() == NULL && action->getCible().size() == 0 && this->estJoueurCourrant(joueur) == true)
        {
            this->changerJoueur();
        }
    }
    //On verifie si la partie s'est finie
    if(this->finPartie(nomEquipeGagnante) == true)
    {
        this->finirPartie(nomEquipeGagnante);
    }
    //Afficher les cases
    for(int x = 0; x < plateau->getLargeur(); x++)
    {
        for(int y = 0; y < plateau->getHauteur(); y++)
        {
            Case* courante = plateau->getCase(x, y);
            if(courante != NULL)
            {
                cout << *courante << endl;
            }
        }
    }
}

bool Partie::isFinis()
{
    return this->estFini;
}
void Partie::retirerJoueur(Joueur* joueur)
{

    //retirer un joueur: retirer de ses cases, retirer ses sorts, retirer de l'equipe,
    Equipe *equipeJoueur = joueur->getEquipe();
    plateau->retirerJoueur(joueur);
    for(vector<Joueur*>::iterator it = this->joueur.begin(); it != this->joueur.end(); it++)
    {
        if((*it) != NULL && it != this->joueur.end())
        {
            if((*it)->getNom() == joueur->getNom())
            {
                it = this->joueur.erase(it);
                break;
            }
        }
    }
    //On notifie de la suppression du joueur
    for(vector<Joueur*>::iterator it = this->joueur.begin(); it != this->joueur.end(); it++)
    {
        (*it)->notifierSuppressionJoueur(joueur->getNom());
    }
    //On le retire de l'équipe
    equipeJoueur->setNombreJoueur(equipeJoueur->getNombreJoueur() - 1);
    if(joueur == this->joueurCourant)
    {
        this->changerJoueur();
    }
    //Une équipe n'a plus de joueur
    if(equipeJoueur->getNombreJoueur() == 0)
    {
        string nomEquipeGagnante;
        //supprimer l'équipe
        for(vector<Equipe*>::iterator it = this->equipe.begin(); it != this->equipe.end(); it++)
        {
            if((*it)->getNom() == equipeJoueur->getNom())
            {
                it = this->equipe.erase(it);
                break;
            }
        }

        delete equipeJoueur;

        if(this->enCours == true)
        {
            if(this->finPartie(nomEquipeGagnante) == true)
            {
                this->finirPartie(nomEquipeGagnante);

            }
        }
    }
    //On tourne
    equipeJoueur->tournerIndex();
    delete joueur;

}

vector<Equipe* > Partie::getEquipe()
{
    return equipe;
}

void Partie::changerJoueur()
{
    indexEquipeCourante = (indexEquipeCourante + 1)%this->equipe.size();
    this->nombreDeJoueurAyantJoue ++;
    if(this->nombreDeJoueurAyantJoue >= this->nombreDeJoueur())
    {
        this->finTourPartie();
        this->nombreDeJoueurAyantJoue = 0;
    }
    for(int i = 0; i < this->joueur.size(); i++)
    {
        this->joueur[i]->notifierPartie((*this));
    }


    this->joueurCourant = choisirJoueur();
    if(this->joueurCourant != NULL)
    {
        for(int i = 0; i < this->joueur.size(); i++)
        {
            this->joueur[i]->notifierDebutTour(this->joueurCourant->getNom());
        }
    }
}

void Partie::finTourPartie()
{
    this->plateau->effectuerActionChronique();
    this->plateau->regenererDefenseCase();
    this->plateau->regenererManaPourJoueur();
    this->plateau->retirerSortDeDureeEcoulee();
    this->regenererManaJoueur();
}

Partie::~Partie()
{
    for(int i = 0; i < this->joueur.size(); i++)
    {
        delete this->joueur[i];
    }
    this->joueur.clear();
    for(int i = 0; i < this->equipe.size(); i++)
    {
        delete this->equipe[i];
    }
    this->equipe.clear();
    delete this->plateau;
}

vector<Joueur*> Partie::getJoueur()
{
    return this->joueur;
}

Joueur* Partie::choisirJoueur()
{
    int nb = -1;
    //Pour tous les joueurs
    for(int i = 0; i < this->joueur.size(); i++)
    {
        //Si c'est le meme nom d'équipe que celui de l'équipe courante
        if(this->joueur[i]->getNomEquipe() == this->equipe[this->indexEquipeCourante]->getNom())
        {
            //On incrémente le compteur
            nb += 1;
            //Si c'est le bon index
            if(nb == this->equipe[this->indexEquipeCourante]->getIndexCourrant())
            {
                //Retourne le joueur
                this->equipe[this->indexEquipeCourante]->tournerIndex();
                return this->joueur[i];
            }
        }
    }
    return NULL;
}
