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
        action = courant->effectuerAction(*this);
        //TODO verifier si l'action est valide
        plateau->appliquerAction(action);
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

void Partie::nouveauJoueur(Joueur & joueur)
{
    bool valid = false;
    string nom, equipe;
    //On récupére le nom
    while(valid == false)
    {
        valid = true;
        nom = joueur.saisieNom();
        //On verifie si le nom est dans une des equipe
        if(this->joueurExiste(nom) == true)
        {
            valid = false;
        }
    }
    joueur.setNom(nom);
    //On récupére l'equipe
    equipe = joueur.saisieEquipe(this->equipe);
    valid = false;
    //On cherche l'equipe correspondant au nom
    for(int i = 0; i < this->equipe.size(); i++)
    {
        if(this->equipe[i]->getNom() == equipe)
        {
            valid = true;
            this->equipe[i]->ajouterJoueur(&joueur);
        }
    }
    //sinon, on la créer
    if(valid == false)
    {
        Equipe* nouvelleEquipe = new Equipe(equipe);
        nouvelleEquipe->ajouterJoueur(&joueur);//on ajoute le joueur
        this->equipe.push_back(nouvelleEquipe);
    }


    //selection des sorts
    //TODO faire en sorte que le nombre de sort soi variable
    //TODO Peut-être faire en sorte que la liste des sorts soi stocké
    vector<Sort*> listeSort = this->listeSort();
    Sort* sort;
    string nomSort;
    bool eliteChoisi = false;
    for(int i = 0; i < nombreSortParJoueur; i++)
    {
        nomSort = joueur.saisieSort(listeSort);
        sort = UsineSort::fabriqueSort(nomSort);
        if(sort->getElite() == true && eliteChoisi == true)
        {
            i--;
            //TODO notifier le joueur d'une erreur
            continue;
        }
        if(sort->getElite() == true)
        {
            eliteChoisi = true;
        }
        joueur.ajouterSort(sort);
        //TODO Un joueur peut maitriser plusieurs fois le même sort
        //TODO génrer le cas des élites
    }

    joueur.genererStatistique();
    //TODO notifier le joueur de ses stats
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
            return NULL;
        }
        if(this->nombreSortParJoueur != listeSort.size())
        {
            return NULL;
        }

        joueur = new Joueur();
        joueur->setNom(nom);

        for(int i = 0; i < nombreSortParJoueur; i++)
        {
                sort = UsineSort::fabriqueSort(listeSort[i]);
                if(sort = NULL)
                {
                        delete joueur;
                        return NULL;
                }
                if(sort->getElite() == true && dejaElite == true)
                {
                        delete joueur;
                        return NULL;
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
