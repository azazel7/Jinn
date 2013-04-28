#include "Partie.h"




Partie::Partie(string nom, int nombrePlace, int nombreSortParJoueur)
{
    this->nom = nom;
    this->nombreDePlace = nombrePlace;
    this->enCours = false;
    this->nombreSortParJoueur = nombreSortParJoueur;
    this->joueurCourant = NULL;
}


/** 
     *  Demarre la partie.
     */
void Partie::demarrerPartie()
{
    int equipeCourante = 0;
    Joueur* courant = NULL;
    Action action;
    enCours = true;
    while(enCours == true)
    {
        courant = equipe[equipeCourante]->choisirJoueur();
        do
        {
            action = courant->effectuerAction(*this);
        }while(1);

        if(finPartie() == true)
        {
            enCours = false;
        }
        //effectuer action chronique de chaques sort
        plateau->effectuerActionChronique();
        //regenerer la defense des cases
        plateau->regenererDefenseCase();
        //regenerer le mana des joueurs
        this->regenererManaJoueur();
        plateau->regenererManaPourJoueur();
        //On retire les sorts qui expire
        plateau->retirerSortDeDureeEcoulee();
        equipeCourante = (equipeCourante+1)%equipe.size();
    }
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
                    nom = proprietaire->getNom();
                    if(equipe.joueurExiste(nom) == true)
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


/** 
     *  Initialise la partie, les different joueurs, les differentes equipes et le terrain
     */
void Partie::initialiser()
{
    plateau = new Plateau();
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
bool Partie::finPartie()
{
    for(int i = 0; i < equipe.size(); i++)
    {
        if(verifierVictoire(*(equipe[i])) == true)
        {
            return true;
            //TODO notifier les équipes
        }
    }
    return false;
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
    int nombreJoueur = 0;
    for(int i = 0; i < equipe.size(); i++)
    {
        nombreJoueur += equipe[i]->nombreDeJoueur();
    }
    return nombreJoueur;
}

bool Partie::joueurExiste(string nom)
{
    for (int i = 0; i < this->equipe.size(); i++)
    {
        if (this->equipe[i]->joueurExiste(nom))
        {
            return true;
        }
    }
}

bool Partie::prete()
{
    if(this->nombreDePlace != this->nombreDeJoueur())
    {
        return false;
    }
}


void Partie::regenererManaJoueur()
{
    for(int i = 0; i < equipe.size(); i++)
    {
        equipe[i]->regenererManaJoueur();
    }
}

bool Partie::estJoueurCourrant(Joueur* joueur)
{

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
    cout << this->nombreSortParJoueur << endl;
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
        equipe->ajouterJoueur(joueur);
    }
    else
    {
        equipe = new Equipe(nomEquipe);
        equipe->ajouterJoueur(joueur);
        this->equipe.push_back(equipe);
    }
    joueur->genererStatistique();
    return joueur;
}

int Partie::getNombreDePlace()
{
    return this->nombreDePlace;
}


void Partie::effectuerAction(Action* action, Joueur* joueur)
{
    vector<Case*> cible;
    //TODO verifier si l'action est valide
    if(action->getSort() != NULL && action->getCible().size() != 0)
    {
        //Si ce n'est pas au joueur courant on retire
        if(joueur != this->joueurCourant)
        {
            //TODO eventuellement lancer exception
            return;
        }
        if(action->getSort()->getProprietaire() != joueur)
        {
            //TODO eventuellement lancer exception
            return;
        }
        if(action->getOrigine()->getProprietaire() != joueur)
        {
            //TODO eventuellement lancer exception
            return;
        }
        //Verifier que le joueur posséde le sort
        if(joueur->possedeSort(action->getSort()) == false)
        {
            return;
        }
        //Verification des distances
        cible = action->getCible();
        for(int i = 0; i < action->getCible().size(); i++)
        {
            if(Position::distance(* (action->getOrigine()->getPosition()), *(cible[i]->getPosition())) > action->getSort()->getPorteeMax())
            {
                return;
            }
        }
        plateau->appliquerAction(*action);
        if(joueur->estMort())
        {
            //TODO notifier de la mort du joueur (tous les joueurs doivent l'être) car le joueur s'écroule dans d'atroce souffrance
            //Le joueur est retiré du plateau, ses sorts supprimés et ses cases libérées, mais il appartient toujours à l'équipe et n'est pas delete
            //Il est juste retiré du plateau
            plateau->retirerJoueur(joueur);
        }
    }
    else
    {
        if(action->getOrigine() == NULL && action->getSort() == NULL && action->getCible().size() == 0)
        {
            //TODO choisir un nouveau joueur
        }
    }
}

void Partie::retirerJoueur(Joueur* joueur)
{
    //retirer un joueur: retirer de ses cases, retirer ses sorts, retirer de l'equipe,
    for(int i = 0; i < equipe.size(); i++)
    {
        equipe[i]->retirerJoueur(joueur);
    }
    plateau->retirerJoueur(joueur);
    delete joueur;
}

vector<Equipe* > Partie::getEquipe()
{
    return equipe;
}
