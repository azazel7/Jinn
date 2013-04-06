#include "Joueur.h"
#include <cstdlib>



Joueur::Joueur()
// don't delete the following line as it's needed to preserve source code of this autogenerated element
// section -64--88-1-10-e7a04d0:13db7368584:-8000:0000000000000E76 begin
{
	this->abilite = 1;
	this->gainInitialMana = 1;
	this->manaMaximum = 1;
	this->manaActuel = 1;
	this->nom = "Joueur";
}
// section -64--88-1-10-e7a04d0:13db7368584:-8000:0000000000000E76 end
// don't delete the previous line as it's needed to preserve source code of this autogenerated element

Joueur::Joueur(int gainInit, int manaMax, int abiliteInit, string  nom)
// don't delete the following line as it's needed to preserve source code of this autogenerated element
// section -64--88-1-10-e7a04d0:13db7368584:-8000:0000000000000E71 begin
{
	this->abilite = abiliteInit;
	this->gainInitialMana = gainInit;
	this->manaMaximum = manaMax;
	this->manaActuel = manaMax;
	this->nom = nom;
}
// section -64--88-1-10-e7a04d0:13db7368584:-8000:0000000000000E71 end
// don't delete the previous line as it's needed to preserve source code of this autogenerated element

Action Joueur::effectuerAction(Partie & partie)
// don't delete the following line as it's needed to preserve source code of this autogenerated element
// section -64--88-1-11-15711965:13d9366bd46:-8000:0000000000000B2B begin
{
    Action retour;
    Sort* sort = UsineSort::fabriqueSort("Sceau de Controle");
    Plateau* plateau = partie.getPlateau();
	//TODO a remplir quand j'aurais les sorts
    sort->setProprietaire(this);
    retour.setSort(sort);
    retour.setOrigine(plateau->getCase(0, 0));
    retour.ajouterCible(plateau->getCase(1,1));

    return retour;
}
// section -64--88-1-11-15711965:13d9366bd46:-8000:0000000000000B2B end
// don't delete the previous line as it's needed to preserve source code of this autogenerated element

void Joueur::diminuerMana(int quantite)
{
	if(quantite < 0)
	{
		return;
	}
}

bool Joueur::estMort()
{
	if(manaActuel < 0)
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


string Joueur::getNom()
{
    return nom;
}
