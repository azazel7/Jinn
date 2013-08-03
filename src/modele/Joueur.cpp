#include "Joueur.h"

Joueur::Joueur()
{
    this->abilite = TypeSort::LUMIERE;
    this->gainInitialMana = 1;
    this->manaMaximum = 1;
    this->manaActuel = 1;
    this->nom = "Joueur";
    this->socket = 1; //La sortie standard
    this->equipe = NULL;
}

Joueur::Joueur(int gainInit, int manaMax, int niveauAbilite, string  nom, TypeSort abilite)
{
    this->niveauAbilite = niveauAbilite;
    this->abilite = abilite;
    this->gainInitialMana = gainInit;
    this->manaMaximum = manaMax;
    this->manaActuel = manaMax;
    this->nom = nom;
    this->socket = 1; //La sortie standard
    this->equipe = NULL;
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
    this->abilite = (TypeSort)(rand()%7);
    this->niveauAbilite = (rand()%10)+1;
    this->gainInitialMana = rand()%10;
    this->manaMaximum = 100 + rand()%10;
    this->manaActuel = this->manaMaximum;
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
    if(sort != NULL)
    {
        sort->setProprietaire(this);
        listeSort.push_back(sort);
    }
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

TypeSort Joueur::getAbilite() const
{
    return this->abilite;
}

void Joueur::setAbilite(TypeSort value)
{
        this->abilite = value;
}

int Joueur::getNiveauAbilite() const
{
    return this->niveauAbilite;
}

void Joueur::setNiveauAbilite(int value)
{
    this->niveauAbilite = value;
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

void Joueur::setManaActuel(int valeur)
{
    this->manaActuel = valeur;
    if(this->manaActuel > this->manaMaximum)
    {
        this->manaActuel = this->manaMaximum;
    }
    else if(this->manaActuel < 0)
    {
        this->manaActuel = 0;
    }
}

void Joueur::setManaMaximum(int valeur)
{
    this->manaMaximum = valeur;
    if(this->manaMaximum < 0)
    {
        this->manaMaximum = 0;
    }
    //On applique les controlles sur manaActuel
    this->setManaActuel(this->manaActuel);
}

void Joueur::setGainMana(int valeur)
{
    this->gainInitialMana = valeur;
}

void Joueur::setEquipe(Equipe* newEquipe)
{
    this->equipe = newEquipe;
}

void Joueur::ajouterSort(string const& nom)
{
    if(this->possedeSort(nom) == false)
    {
        Sort* sort = UsineSort::fabriqueSort(nom);
        if(sort != NULL)
        {
            sort->setProprietaire(this);
            this->listeSort.push_back(sort);
        }
    }
}

void Joueur::retirerSort(string const& nom)
{
    for(vector<Sort*>::iterator it = this->listeSort.begin(); it != this->listeSort.end(); it++)
    {
        if((*it)->getNom() == nom)
        {
            it = this->listeSort.erase(it);
            break;
        }
    }
}

vector<Sort* > Joueur::getListeSort()
{
    return this->listeSort;
}

void Joueur::notifierCreation() const
{
    string final = NOUVEAU_JOUEUR;
    final += SEPARATEUR_ELEMENT;
    final += this->nom;
    final += SEPARATEUR_ELEMENT;
    final += this->getNomEquipe();
    final += SEPARATEUR_ELEMENT;
    final += to_string(this->manaActuel);
    final += SEPARATEUR_ELEMENT;
    final += to_string(this->manaMaximum);
    final += SEPARATEUR_ELEMENT;
    final += to_string(this->gainInitialMana);
    final += SEPARATEUR_ELEMENT;
    final += to_string((int) this->abilite);
    final += SEPARATEUR_ELEMENT;
    final += to_string(this->niveauAbilite);

    for(int i = 0; i < this->listeSort.size(); i++)
    {
        final += SEPARATEUR_ELEMENT;
        final += listeSort[i]->getNom();
    }
    final += SEPARATEUR_ELEMENT;
    final += SEPARATEUR_COMMANDE;
    send(this->socket, final.c_str(), final.size(), 0);
}

void Joueur::notifierActionSort(string information) const
{

}

void Joueur::notifierPartie(Partie & partie) const
{
    //Un joueur n'est informer que de ce qu'il peut voir ou sentir ~~
    //Pour une case: Deffense initial, proprio
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
                Sort* sor = iterator->second;
                final += this->creerChaineNotificationSort(*sor, iterator->first, listeCase[i]->getPosition());
            }
        }
    }

    send(this->socket, final.c_str(), final.size(), 0);
}

void Joueur::notifierDebutPartie() const
{
    string final = DEMARAGE_PARTIE;
    final += SEPARATEUR_ELEMENT;
    final += SEPARATEUR_COMMANDE;
    send(this->socket, final.c_str(), final.size(), 0);
}

void Joueur::notifierDebutTour(string nomJoueur) const
{
    string final = TOUR_DE;
    final += SEPARATEUR_ELEMENT;
    final += nomJoueur;
    final += SEPARATEUR_ELEMENT;
    final += SEPARATEUR_COMMANDE;
    send(this->socket, final.c_str(), final.size(), 0);
}
void Joueur::notifierFinTourPartie() const
{
    string final = FIN_TOUR_PARTIE;
    final += SEPARATEUR_ELEMENT;
    final += SEPARATEUR_COMMANDE;
    send(this->socket, final.c_str(), final.size(), 0);
}

void Joueur::notifierMort(string nomJoueur) const
{
    string final = MORT;
    final += SEPARATEUR_ELEMENT;
    final += nomJoueur;
    final += SEPARATEUR_ELEMENT;
    final += SEPARATEUR_COMMANDE;
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
    final += SEPARATEUR_COMMANDE;

    send(this->socket, final.c_str(), final.size(), 0);

}
void Joueur::notifierFinPartie(string nomEquipeGagnante) const
{
    string final = FIN_PARTIE;
    final += SEPARATEUR_ELEMENT;
    final += nomEquipeGagnante;
    final += SEPARATEUR_ELEMENT;
    final += SEPARATEUR_COMMANDE;
    send(this->socket, final.c_str(), final.size(), 0);
}

void Joueur::notifierSuppressionJoueur(string nomJoueur) const
{
    string final = QUITTER_PARTIE;
    final += SEPARATEUR_ELEMENT;
    final += nomJoueur;
    final += SEPARATEUR_ELEMENT;
    final += SEPARATEUR_COMMANDE;
    send(this->socket, final.c_str(), final.size(), 0);
}

Equipe* Joueur::getEquipe()
{
    return this->equipe;
}

string Joueur::getNomEquipe() const
{
    if(equipe != NULL)
    {
        return equipe->getNom();
    }
    return "";
}
void Joueur::notifierSort(Sort const& sort, int duree, Position* position) const
{
    string final = this->creerChaineNotificationSort(sort, duree, position);
    send(this->socket, final.c_str(), final.size(), 0);
}

void Joueur::notifierCase(Case const& caseANotif, bool compteProprietaire = true) const
{
    string final = this->creerChaineNotificationCase(caseANotif, compteProprietaire);
    send(this->socket, final.c_str(), final.size(), 0);
}

void Joueur::notifierJoueur(Joueur const& joueur, bool compteEquipe) const
{
    string final = this->creerChaineNotificationJoueur(joueur, compteEquipe);
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
    retour += SEPARATEUR_COMMANDE;
    return retour;
}

string Joueur::creerChaineNotificationJoueur(Joueur const& joueur, bool compteEquipe) const
{
    string equipe = joueur.getNomEquipe();
    string retour = INFORMATION_JOUEUR;
    retour += SEPARATEUR_ELEMENT;
    retour += joueur.getNom();
    retour += SEPARATEUR_ELEMENT;
    if(equipe == "")
    {
        equipe = CHAMPS_VIDE;
    }
    retour += equipe;
    retour += SEPARATEUR_ELEMENT;
    if(joueur.getNomEquipe() == this->getNomEquipe() || compteEquipe == false)
    {
        retour += to_string(joueur.getManaActuel());
        retour += SEPARATEUR_ELEMENT;
        retour += to_string(joueur.getManaMaximum());
        retour += SEPARATEUR_ELEMENT;
        retour += to_string(joueur.getGainInitialMana());
        retour += SEPARATEUR_ELEMENT;
        retour += to_string(joueur.getAbilite());
        retour += SEPARATEUR_ELEMENT;
        retour += to_string(joueur.getNiveauAbilite());
        retour += SEPARATEUR_ELEMENT;
    }
    else
    {
        for(int i = 0; i < 5; i++)
        {
            retour += to_string(-1);
            retour += SEPARATEUR_ELEMENT;
        }
    }
    retour += SEPARATEUR_COMMANDE;
    return retour;
}

string Joueur::creerChaineNotificationCase(Case const& caseANotif, bool compteProprietaire) const
{
    string proprio = caseANotif.getNomProprietaire();
    if(proprio == "")
    {
        proprio = CHAMPS_VIDE;
    }
    string retour = INFORMATION_CASE;
    retour += SEPARATEUR_ELEMENT;
    retour += to_string(caseANotif.getPosition()->getX());
    retour += SEPARATEUR_ELEMENT;
    retour += to_string(caseANotif.getPosition()->getY());
    retour += SEPARATEUR_ELEMENT;
    retour += proprio;
    retour += SEPARATEUR_ELEMENT;
    if(caseANotif.getNomProprietaire() == this->nom || compteProprietaire == false)
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
    retour += SEPARATEUR_COMMANDE;
    return retour;
}

void Joueur::notifierResultatSort(string const& nom, Position const& cible, bool reussite)
{
    string final = REUSSITE_SORT;
    final += SEPARATEUR_ELEMENT;
    final += nom;
    final += SEPARATEUR_ELEMENT;
    final += to_string(cible.getX());
    final += SEPARATEUR_ELEMENT;
    final += to_string(cible.getY());
    final += SEPARATEUR_ELEMENT;
    if(reussite == true)
    {
        final += "TRUE";
    }
    else
    {
        final += "FALSE";
    }
    final += SEPARATEUR_ELEMENT;
    final += SEPARATEUR_COMMANDE;
    send(this->socket, final.c_str(), final.size(), 0);
}

Joueur::~Joueur()
{
    for(int i = 0; i < this->listeSort.size(); i++)
    {
        delete this->listeSort[i];
    }
}
