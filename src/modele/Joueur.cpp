#include "Joueur.h"



Joueur::Joueur()
{
	this->abilite = 1;
	this->gainInitialMana = 1;
	this->manaMaximum = 1;
	this->manaActuel = 1;
	this->nom = "Joueur";
}

Joueur::Joueur(int gainInit, int manaMax, int abiliteInit, string  nom)
{
	this->abilite = abiliteInit;
	this->gainInitialMana = gainInit;
	this->manaMaximum = manaMax;
	this->manaActuel = manaMax;
	this->nom = nom;
}

Action Joueur::effectuerAction(Partie & partie)
{
    int numSort, x, y;
    Action retour;
    Sort* sort;
    Plateau* plateau = partie.getPlateau();
	//TODO a remplir quand j'aurais les sorts


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
        cout << sort[i]->description() << endl << endl;
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

void Joueur::notifierCreation() const
{
        string final = NOUVEAU_JOUEUR;
        final += SEPARATEUR_ELEMENT;
        final += this->nom;
        final += SEPARATEUR_ELEMENT;
        final += this->manaMaximum;
        final += SEPARATEUR_ELEMENT;
        final += this->gainInitialMana;
        final += SEPARATEUR_ELEMENT;
        final += this->abilite;
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
