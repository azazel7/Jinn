#include "Joueur.h"



Joueur::Joueur()
{
    this->abilite = 1;
    this->gainInitialMana = 1;
    this->manaMaximum = 1;
    this->manaActuel = 1;
    this->nom = "Joueur";
    this->socket = 1; //La sortie standard
    this->equipe = NULL;
}

Joueur::Joueur(int gainInit, int manaMax, int abiliteInit, string  nom)
{
    this->abilite = abiliteInit;
    this->gainInitialMana = gainInit;
    this->manaMaximum = manaMax;
    this->manaActuel = manaMax;
    this->nom = nom;
    this->socket = 1; //La sortie standard
}

Action Joueur::effectuerAction(Partie & partie)
{
    int numSort, x, y;
    Action retour;
    Sort* sort;
    Plateau* plateau = partie.getPlateau();


    //Afficher les cases
    for(x = 0; x < plateau->getLargeur(); x++)
    {
        for(y = 0; y < plateau->getHauteur(); y++)
        {
            Case* courante = plateau->getCase(x, y);
            if(courante != NULL)
            {
                cout << *courante << endl;
            }
        }
    }
    //Afficher les sorts
    for(int i = 0; i < listeSort.size(); i++)
    {
        cout << listeSort[i]->getNom() << " (" << i << ")" << endl;
    }

    //Choisir sort
    cout << "Entrez le numero du sort : ";
    cin >> numSort;
    sort = UsineSort::fabriqueSort(listeSort[numSort]->getNom());
    sort->setProprietaire(this);
    retour.setSort(sort);
    //Choisir case origine
    cout << "X origine : ";
    cin >> x;

    cout << "Y origine : ";
    cin >> y;
    retour.setOrigine(plateau->getCase(x, y));

    //Choisir case cible
    cout << "X cible : ";
    cin >> x;

    cout << "Y cible : ";
    cin >> y;
    retour.ajouterCible(plateau->getCase(x, y));

    return retour;
}

void Joueur::diminuerMana(int quantite)
{
    if(quantite < 0)
    {
        return;
    }
    this->manaActuel -= quantite;
    if(this->manaActuel <= 0)
    {
        this->manaActuel = 0;
        this->manaMaximum = 0;//On l'emp^eche de regagner du mana, donc il reste bien mort
    }
}

void Joueur::augmenterMana(int quantite)
{
    if(quantite < 0)
    {
        return;
    }
    this->manaActuel += quantite;
    if(this->manaActuel > this->manaMaximum)
    {
        this->manaActuel = this->manaMaximum; //On plafonne
    }
}

bool Joueur::estMort() const
{
    if(manaActuel <= 0)
    {
        return true;
    }
    return false;
}

void Joueur::genererStatistique()
{
    this->abilite = rand()%10;
    this->gainInitialMana = rand()%10;
    this->manaMaximum = 100 + rand()%10;
    this->manaActuel = this->manaMaximum;
}

string Joueur::saisieNom()
{
    string retour;
    cout << "Choix nom : ";
    cin >> retour;
    return retour;
}

string Joueur::saisieEquipe(std::vector< Equipe* > & equipe)
{
    string retour;
    for(int i = 0; i < equipe.size(); i++)
    {
        cout << "Equipe : " << equipe[i]->getNom() << endl;
    }
    cout << "Choix equipe : ";
    cin >> retour;
    return retour;
}

string Joueur::saisieSort(vector<Sort* > const& sort)
{
    int choix;
    for(int i = 0; i < sort.size(); i++)
    {
        cout << sort[i]->getNom() <<  "(" << i << ") :" << endl;
        cout << sort[i]->getDescription() << endl << endl;
    }
    cout << "choix numero sort : ";
    cin >> choix;
    return sort[choix]->getNom();
}


string Joueur::getNom() const
{
    return nom;
}

void Joueur::setNom(string nom)
{
    this->nom = nom;
}

void Joueur::ajouterSort(Sort* sort)
{
    sort->setProprietaire(this);
    listeSort.push_back(sort);
}

int Joueur::getManaActuel() const
{
    return this->manaActuel;
}

int Joueur::getManaMaximum() const
{
    return this->manaMaximum;
}

int Joueur::getGainInitialMana() const
{
    return this->gainInitialMana;
}

bool Joueur::possedeSort(Sort* sort)
{
    if(sort != NULL)
    {
        return this->possedeSort(sort->getNom());
    }
    return false;
}

bool Joueur::possedeSort(string nomsort)
{
    for(int i = 0; i < listeSort.size(); i++)
    {
        if(listeSort[i]->getNom() == nomsort)
        {
            return true;
        }
    }
    return false;
}
ostream& operator<<( ostream &flux, Joueur const& pos)
{
    string mort = "vivant";
    if(pos.estMort())
    {
        mort = "mort";
    }
    flux << "[" << pos.getNom() << "," << pos.getManaActuel() << "/" << pos.getManaMaximum() << "," << mort << "]";
    return flux;
}

int Joueur::getSocket() const
{
    return this->socket;
}

void Joueur::setSocket(int socket)
{
    this->socket = socket;
}

void Joueur::setEquipe(Equipe* newEquipe)
{
    this->equipe = newEquipe;
}

void Joueur::notifierCreation() const
{
    string final = NOUVEAU_JOUEUR;
    final += SEPARATEUR_ELEMENT;
    final += this->nom;
    final += SEPARATEUR_ELEMENT;
    final += to_string(this->manaMaximum);
    final += SEPARATEUR_ELEMENT;
    final += to_string(this->gainInitialMana);
    final += SEPARATEUR_ELEMENT;
    final += to_string(this->abilite);
    final += SEPARATEUR_ELEMENT;
    final += this->nom;

    for(int i = 0; i < this->listeSort.size(); i++)
    {
        final += SEPARATEUR_ELEMENT;
        final += listeSort[i]->getNom();
    }
    final += SEPARATEUR_ELEMENT;
    send(this->socket, final.c_str(), final.size(), 0);
}

void Joueur::notifierActionSort(string information) const
{

}

void Joueur::notifierPartie(Partie & partie) const
{
    //TODO, il va falloir notifier les changements ....
    //Un joueur n'est informer que de ce qu'il peut voir ou sentir ~~
    //Pour une case: Deffense initial, proprio
    //Pour une case en sa possession, informer des sorts dessus en excluant les siens ? (Au début, pas de case, donc tout va bien)
    //La position de tout ses sorts et leurs durée restante (Au début, pas de sort, donc pas de soucis)
    //De la liste des joueurs avec leurs équipe
    //Pour chaque joueur de son equipe: le mana actuel et le mana maximum
    vector<Joueur* > listeJoueur;
    vector<Case* > listeCase;
    list<pair<int, Sort*> > listeSortCase;
    string final = "";
    //On récupére la liste des joueurs
    listeJoueur = partie.getJoueur();
    //On récupére la liste des cases
    listeCase = partie.getPlateau()->getListeCase();
    //On informe sur chaque joueur
    for(int i = 0; i < listeJoueur.size(); i ++)
    {
        final += this->creerChaineNotificationJoueur(*(listeJoueur[i]));
    }
    //On informe sur chaque case
    for(int i = 0; i < listeCase.size(); i++)
    {
        final += this->creerChaineNotificationCase(*(listeCase[i]));
        //On récupére la liste des sorts de la case
        listeSortCase = listeCase[i]->getListSort();
        //On informe sur les sorts s'ils appartiennent au joueur courent
        for(list<pair<int, Sort*> >::iterator iterator = listeSortCase.begin(); iterator != listeSortCase.end(); iterator++)
        {
            if(iterator->second->getProprietaire() != NULL && iterator->second->getProprietaire()->getNom() == this->nom)
            {
                   final += this->creerChaineNotificationSort(*(iterator->second), iterator->first, listeCase[i]->getPosition());
            }
        }
    }

    send(this->socket, final.c_str(), final.size(), 0);
}

void Joueur::notifierDebutPartie() const
{
    string final = DEMARAGE_PARTIE;
    final += SEPARATEUR_ELEMENT;
    send(this->socket, final.c_str(), final.size(), 0);
}

void Joueur::notifierDebutTour(string nomJoueur) const
{
    string final = TOUR_DE;
    final += SEPARATEUR_ELEMENT;
    final += nomJoueur;
    final += SEPARATEUR_ELEMENT;
    send(this->socket, final.c_str(), final.size(), 0);
}
void Joueur::notifierFinTourPartie() const
{

}

void Joueur::notifierMort(string nomJoueur) const
{
    string final = MORT;
    final += SEPARATEUR_ELEMENT;
    final += nomJoueur;
    final += SEPARATEUR_ELEMENT;
    send(this->socket, final.c_str(), final.size(), 0);
}

void Joueur::notifierPropriaitaireCase(string nomJoueur, bool type, int x, int y)
{
    string final = CHANGEMENT_CASE_PROPRIAITAIRE;
    final += SEPARATEUR_ELEMENT;
    final += nomJoueur;
    final += SEPARATEUR_ELEMENT;
    if(type == true)
    {
        final += "GAIN";
    }
    else
    {
        final += "PERTE";
    }
    final += SEPARATEUR_ELEMENT;
    final += to_string(x);
    final += SEPARATEUR_ELEMENT;
    final += to_string(y);
    final += SEPARATEUR_ELEMENT;

    send(this->socket, final.c_str(), final.size(), 0);

}
void Joueur::notifierFinPartie(string nomEquipeGagnante) const
{
    string final = FIN_PARTIE;
    final += SEPARATEUR_ELEMENT;
    final += nomEquipeGagnante;
    final += SEPARATEUR_ELEMENT;
    send(this->socket, final.c_str(), final.size(), 0);
}

void Joueur::notifierSuppressionJoueur(string nomJoueur) const
{
    string final = QUITTER_PARTIE;
    final += SEPARATEUR_ELEMENT;
    final += nomJoueur;
    final += SEPARATEUR_ELEMENT;
    send(this->socket, final.c_str(), final.size(), 0);
}

Equipe* Joueur::getEquipe()
{
    return this->equipe;
}

string Joueur::getNomEquipe() const
{
    if(this->equipe != NULL)
    {
        return this->equipe->getNom();
    }
    return "";
}
void Joueur::notifierSort(Sort const& sort, int duree, Position* position) const
{
    string final = this->creerChaineNotificationSort(sort, duree, position);
    send(this->socket, final.c_str(), final.size(), 0);
}

string Joueur::creerChaineNotificationSort(Sort const& sort, int duree, Position* position) const
{
    string retour = INFORMATION_SORT;
    retour += SEPARATEUR_ELEMENT;
    retour += sort.getNom();
    retour += SEPARATEUR_ELEMENT;
    retour += to_string(sort.getId());
    retour += SEPARATEUR_ELEMENT;
    if(sort.getProprietaire() != NULL)
    {
        retour += sort.getProprietaire()->getNom();
    }
    retour += SEPARATEUR_ELEMENT;
    retour += to_string(duree);
    retour += SEPARATEUR_ELEMENT;
    retour += to_string(position->getX());
    retour += SEPARATEUR_ELEMENT;
    retour += to_string(position->getY());
    retour += SEPARATEUR_ELEMENT;
    return retour;
}

string Joueur::creerChaineNotificationJoueur(Joueur const& joueur) const
{
    string retour = INFORMATION_JOUEUR;
    retour += SEPARATEUR_ELEMENT;
    retour += joueur.getNom();
    retour += SEPARATEUR_ELEMENT;
    retour += joueur.getNomEquipe();
    retour += SEPARATEUR_ELEMENT;
    if(joueur.getNomEquipe() == this->getNomEquipe())
    {
        retour += to_string(joueur.getManaActuel());
        retour += SEPARATEUR_ELEMENT;
        retour += to_string(joueur.getManaMaximum());
        retour += SEPARATEUR_ELEMENT;
        retour += to_string(joueur.getGainInitialMana());
        retour += SEPARATEUR_ELEMENT;
    }
    else
    {
        retour += to_string(-1);
        retour += SEPARATEUR_ELEMENT;
        retour += to_string(-1);
        retour += SEPARATEUR_ELEMENT;
        retour += to_string(-1);
        retour += SEPARATEUR_ELEMENT;
    }
    return retour;
}

string Joueur::creerChaineNotificationCase(Case const& caseANotif) const
{
   string retour = INFORMATION_CASE;
   retour += SEPARATEUR_ELEMENT;
   retour += to_string(caseANotif.getPosition()->getX());
   retour += SEPARATEUR_ELEMENT;
   retour += to_string(caseANotif.getPosition()->getY());
   retour += SEPARATEUR_ELEMENT;
   retour += caseANotif.getNomProprietaire();
   retour += SEPARATEUR_ELEMENT;
   if(caseANotif.getNomProprietaire() == this->nom)
   {
        retour += to_string(caseANotif.getDefenseInitiale());
        retour += SEPARATEUR_ELEMENT;
        retour += to_string(caseANotif.getDefenseReel());
        retour += SEPARATEUR_ELEMENT;
        retour += to_string(caseANotif.getDefenseActuelle());
        retour += SEPARATEUR_ELEMENT;
        retour += to_string(caseANotif.getRegenerationDefense());
        retour += SEPARATEUR_ELEMENT;
        retour += to_string(caseANotif.getApportMana());
        retour += SEPARATEUR_ELEMENT;
        retour += to_string(caseANotif.getBonusOffensifInitial());
        retour += SEPARATEUR_ELEMENT;
        retour += to_string(caseANotif.getBonusOffensifActuel());
        retour += SEPARATEUR_ELEMENT;
   }
   else
   {
        retour += to_string(caseANotif.getDefenseInitiale());
        retour += SEPARATEUR_ELEMENT;
        retour += to_string(-1);
        retour += SEPARATEUR_ELEMENT;
        retour += to_string(-1);
        retour += SEPARATEUR_ELEMENT;
        retour += to_string(-1);
        retour += SEPARATEUR_ELEMENT;
        retour += to_string(-1);
        retour += SEPARATEUR_ELEMENT;
        retour += to_string(caseANotif.getBonusOffensifInitial());
        retour += SEPARATEUR_ELEMENT;
        retour += to_string(-1);
        retour += SEPARATEUR_ELEMENT;
   }
   return retour;
}

Joueur::~Joueur()
{
    for(int i = 0; i < this->listeSort.size(); i++)
    {
        delete this->listeSort[i];
    }
}
//TODO penser à comment notifier d'un sort de révélation
