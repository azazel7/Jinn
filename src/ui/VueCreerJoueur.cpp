#include "ui/VueCreerJoueur.h"

VueCreerJoueur::VueCreerJoueur(PartieClient* partie, ReceptionClient *reception)
{
    this->partie = partie;
    this->receptionClient = reception;
    this->curseur = IndexCreerJoueur::curseur_liste_equipe;
    this->nomEquipe = "";
    this->nomJoueur = "";
    this->positionEquipe = 0;
    this->positionSort = 0;
}
void VueCreerJoueur::dessinerFenetre()
{
    int hauteur, largeur, l_colonne;
    getmaxyx(stdscr, hauteur, largeur);
    l_colonne = largeur/4;
    WINDOW * win = subwin(stdscr, hauteur, largeur, 0, 0);
//    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    for(int i = 0; i < this->partie->getListeEquipe().size(); i++)
    {
        const char* nom = this->partie->getListeEquipe()[i].c_str();
        if(this->positionEquipe == i && this->curseur == IndexCreerJoueur::curseur_liste_equipe)
        {
            wattron(win, COLOR_PAIR(1));
        }
        wmove(win, i, 0);
        wprintw(win, nom);
        if(this->positionEquipe == i && this->curseur == IndexCreerJoueur::curseur_liste_equipe)
        {
            wprintw(win, " *");
            wattroff(win, COLOR_PAIR(1));
        }
        else
        {
            wprintw(win, "  ");
        }
    }
    for(int i = 0; i < this->partie->getListeSortDispo().size(); i++)
    {
        const char* nom = this->partie->getListeSortDispo()[i]->getNom().c_str();
        if(this->positionSort == i && this->curseur == IndexCreerJoueur::curseur_liste_sort)
        {
            wattron(win, COLOR_PAIR(1));
        }
        wmove(win, i, l_colonne);
        wprintw(win, nom);
        if(this->positionSort == i && this->curseur == IndexCreerJoueur::curseur_liste_sort)
        {
            wprintw(win, " *");
            wattroff(win, COLOR_PAIR(1));
        }
        else
        {
            list<string>::iterator it = find(this->sortChoisie.begin(), this->sortChoisie.end(), this->partie->getListeSortDispo()[i]->getNom());
            if(it == this->sortChoisie.end())
            {
                wprintw(win, "  ");
            }
            else
            {
                wprintw(win, " +");
            }
        }
    }
    //Print description du sort
    wmove(win, 0, 2*l_colonne);
    //Description
    if(this->partie->getListeSortDispo().empty() == false)
    {
        wprintw(win, "%s", this->partie->getListeSortDispo()[this->positionSort]->getDescription().c_str());
    }
    //Print nom Joueur
    if(this->curseur == IndexCreerJoueur::curseur_nom_joueur)
    {
        wattron(win, COLOR_PAIR(1));
    }
    wmove(win, (hauteur/2), 2*l_colonne);
    wprintw(win, "Nom du joueur : %s", this->nomJoueur.c_str());
    if(this->curseur == IndexCreerJoueur::curseur_nom_joueur)
    {
        wattroff(win, COLOR_PAIR(1));
    }
    //Print nom equipe
    if(this->curseur == IndexCreerJoueur::curseur_nom_equipe)
    {
        wattron(win, COLOR_PAIR(1));
    }
    wmove(win, (hauteur/2) + 1, 2*l_colonne);
    wprintw(win, "Nom d'équipe : %s", this->nomEquipe.c_str());
    if(this->curseur == IndexCreerJoueur::curseur_nom_equipe)
    {
        wattroff(win, COLOR_PAIR(1));
    }

    wmove(win, (hauteur/2) + 3, 2*l_colonne);
    wprintw(win, " ↓↑ : Deplace le curseur sur les listes");
    wmove(win, (hauteur/2) + 4, 2*l_colonne);
    wprintw(win, " <- -> : Deplace le curseur entre les colonnes");
    wmove(win, (hauteur/2) + 5, 2*l_colonne);
    wprintw(win, " F2 : Quitte sans valider");
    wmove(win, (hauteur/2) + 6, 2*l_colonne);
    wprintw(win, " F3 : Valide les informations");
    wmove(win, (hauteur/2) + 7, 2*l_colonne);
    wprintw(win, " + : Ajouter un sort à la liste ou choisir une équipe");

    wrefresh(win);

}
void VueCreerJoueur::modifierPosition(int valeur)
{
    if(this->curseur == IndexCreerJoueur::curseur_liste_equipe)
    {
        this->positionEquipe += valeur;
        if(this->positionEquipe < 0)
        {
            this->positionEquipe = 0;
        }
        else if(this->positionEquipe >= this->partie->getListeEquipe().size())
        {
            this->positionEquipe = this->partie->getListeEquipe().size() - 1;
        }
    }
    else if(this->curseur == IndexCreerJoueur::curseur_liste_sort)
    {
        this->positionSort += valeur;
        if(this->positionSort < 0)
        {
            this->positionSort = 0;
        }
        else if(this->positionSort >= this->partie->getListeSortDispo().size())
        {
            this->positionSort = this->partie->getListeSortDispo().size() - 1;
        }
    }
}
void VueCreerJoueur::modifierCurseur(int valeur)
{
    this->curseur += valeur;
    if(this->curseur > IndexCreerJoueur::curseur_nom_equipe)
    {
        this->curseur = IndexCreerJoueur::curseur_nom_equipe;
    }
    else if(this->curseur < 0)
    {
        this->curseur = 0;
    }
}
void VueCreerJoueur::ajouterLettre(char lettre)
{
    if(this->curseur == IndexCreerJoueur::curseur_nom_joueur)
    {
        this->nomJoueur += lettre;
    }
    else if(this->curseur == IndexCreerJoueur::curseur_nom_equipe)
    {
        this->nomEquipe += lettre;
    }
}
void VueCreerJoueur::retirerLettre()
{
    if(this->curseur == IndexCreerJoueur::curseur_nom_joueur)
    {
        this->nomJoueur = this->nomJoueur.substr(0, this->nomJoueur.size() - 1);
    }
    else if(this->curseur == IndexCreerJoueur::curseur_nom_equipe)
    {
        this->nomEquipe = this->nomEquipe.substr(0, this->nomEquipe.size() - 1);
    }
}

void VueCreerJoueur::enterSort()
{
    list<string>::iterator it = find(this->sortChoisie.begin(), this->sortChoisie.end(), this->partie->getListeSortDispo()[this->positionSort]->getNom());
    if(it != this->sortChoisie.end())
    {
        this->sortChoisie.erase(it);
    }
    else
    {
        this->sortChoisie.push_front(this->partie->getListeSortDispo()[this->positionSort]->getNom());
    }
}
void VueCreerJoueur::enterEquipe()
{
    this->nomEquipe = this->partie->getListeEquipe()[this->positionEquipe];
}
void VueCreerJoueur::saisieInformation()
{
    int touche = 0;
    while(true)
    {
        touche = getch();
        switch(touche)
        {
            case KEY_BACKSPACE:
                this->retirerLettre();
            break;
            case KEY_UP:
                this->modifierPosition(-1);
            break;
            case KEY_DOWN:
                this->modifierPosition(1);
            break;
            case KEY_LEFT:
                this->modifierCurseur(-1);
            break;
            case KEY_RIGHT:
                this->modifierCurseur(1);
            break;
            case '+':
                if(this->curseur == IndexCreerJoueur::curseur_liste_equipe)
                {
                    enterEquipe();
                }
                else if(this->curseur == IndexCreerJoueur::curseur_liste_sort)
                {
                    enterSort();
                }
            break;
            case KEY_F(2):
                return;
            break;
            case KEY_F(3):
                //Valider et envoyer
            break;
            default:
                this->ajouterLettre(touche);
            break;
        }
        this->dessinerFenetre();
    }
}
