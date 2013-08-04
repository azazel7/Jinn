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
    int hauteur, largeur;
    getmaxyx(stdscr, hauteur, largeur);
    erase();
    this->dessinerInfoPartie(hauteur, largeur);
    this->dessinerInfoSort(hauteur, largeur);
    this->dessinerSort(hauteur, largeur);
    this->dessinerInfoJoueur(hauteur, largeur);
    this->dessinerAide(hauteur, largeur);
    this->dessinerEquipe(hauteur, largeur);
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
            if(this->sortChoisie.size() == partie->getNombreSortParJoueur())
            {
                this->receptionClient->envoyerCommandeNouveauJoueur(this->nomJoueur, this->nomEquipe, this->sortChoisie);
                return;
            }
            break;
            default:
                this->ajouterLettre(touche);
            break;
        }
        this->dessinerFenetre();
    }
}

void VueCreerJoueur::dessinerInfoPartie(int hauteur, int largeur)
{
    int h_win = HAUTEUR_INFO_PARTIE;
    int l_win = largeur;
    if(hauteur < HAUTEUR_INFO_PARTIE)
    {
        return;
    }
    WINDOW * win = subwin(stdscr, h_win, l_win, 0, 0);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    wmove(win, 1, 1); //1 pour éviter d'empiéter sur la bordure
    wprintw(win, "Nombre de sorts : %d   Nombre de place : %d/%d", this->partie->getNombreSortParJoueur(), this->partie->getNombreJoueur(), this->partie->getNombrePlace());
    wrefresh(win);
}

void VueCreerJoueur::dessinerSort(int hauteur, int largeur)
{
    int h_win = hauteur - HAUTEUR_INFO_PARTIE;
    int l_win = largeur/3;
    int i = 1;
    string choisi = "";
    WINDOW * win = subwin(stdscr, h_win, l_win, HAUTEUR_INFO_PARTIE, largeur/3);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    vector<Sort*> listeSort = this->partie->getListeSortDispo();
    for(auto it = listeSort.begin(); it != listeSort.end(); it++)
    {
        choisi.clear();
        if(find(this->sortChoisie.begin(), this->sortChoisie.end(), (*it)->getNom()) != this->sortChoisie.end())
        {
            choisi = "+";
        }
        this->activerCouleurCurseur(win, IndexCreerJoueur::curseur_liste_sort, true, i-1);
        wmove(win, i, 1); //1 pour éviter d'empiéter sur la bordure
        wprintw(win, "%s %s", (*it)->getNom().c_str(), choisi.c_str());
        this->activerCouleurCurseur(win, IndexCreerJoueur::curseur_liste_sort, false, i-1);
        i++;
        if(i + 2 > h_win)
        {
            break;
        }
    }
    wrefresh(win);
}

void VueCreerJoueur::dessinerInfoSort(int hauteur, int largeur)
{
    int h_win = HAUTEUR_INFO_SORT;
    int l_win = largeur/3;
    int i = 1;
    WINDOW * win = subwin(stdscr, h_win, l_win, HAUTEUR_INFO_PARTIE + HAUTEUR_INFO_JOUEUR, (2*largeur)/3);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    Sort* courant = this->partie->getListeSortDispo()[this->positionSort];
    if(courant->getElite() == true)
    {
        wattron(win, COLOR_PAIR(2));
    }
    wmove(win, i, 1); //1 pour éviter d'empiéter sur la bordure
    wprintw(win, "%s", courant->getDescription().c_str());
    i++;
    wmove(win, i, 1); //1 pour éviter d'empiéter sur la bordure
    wprintw(win, "Mana : %d", courant->getCoupManaParCase());
    i++;
    wmove(win, i, 1); //1 pour éviter d'empiéter sur la bordure
    wprintw(win, "Portée : %d", courant->getPorteeMax());
    i++;
    wmove(win, i, 1); //1 pour éviter d'empiéter sur la bordure
    wprintw(win, "Nb cible : %d", courant->getnombreCibleMax());
    i++;
    if(courant->getElite() == true)
    {
        wattroff(win, COLOR_PAIR(2));
    }
}

void VueCreerJoueur::dessinerInfoJoueur(int hauteur, int largeur)
{
    int h_win = HAUTEUR_INFO_JOUEUR;
    int l_win = largeur/3;
    if(hauteur < HAUTEUR_INFO_JOUEUR)
    {
        return;
    }
    WINDOW * win = subwin(stdscr, h_win, l_win, HAUTEUR_INFO_PARTIE, (2*largeur)/3);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    this->activerCouleurCurseur(win, IndexCreerJoueur::curseur_nom_joueur, true);
    wmove(win, 1, 1); //1 pour éviter d'empiéter sur la bordure
    wprintw(win, "Nom : %s", this->nomJoueur.c_str());
    this->activerCouleurCurseur(win, IndexCreerJoueur::curseur_nom_joueur, false);
    this->activerCouleurCurseur(win, IndexCreerJoueur::curseur_nom_equipe, true);
    wmove(win, 2, 1); //1 pour éviter d'empiéter sur la bordure
    wprintw(win, "Nom Equipe : %s", this->nomEquipe.c_str());
    this->activerCouleurCurseur(win, IndexCreerJoueur::curseur_nom_equipe, false);
    wrefresh(win);
}

void VueCreerJoueur::dessinerEquipe(int hauteur, int largeur)
{
    int h_win = hauteur - HAUTEUR_INFO_PARTIE;
    int l_win = largeur/3;
    int i = 1;
    WINDOW * win = subwin(stdscr, h_win, l_win, HAUTEUR_INFO_PARTIE, 0);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    vector<string> listeEquipe = this->partie->getListeEquipe();
    for(auto it = listeEquipe.begin(); it != listeEquipe.end(); it++)
    {
        this->activerCouleurCurseur(win, IndexCreerJoueur::curseur_liste_equipe, true, i-1);
        wmove(win, i, 1); //1 pour éviter d'empiéter sur la bordure
        wprintw(win, "%s", it->c_str());
        this->activerCouleurCurseur(win, IndexCreerJoueur::curseur_liste_equipe, false, i-1);
        i++;
        if(i + 2 > h_win)
        {
            break;
        }
    }
    wrefresh(win);
}

void VueCreerJoueur::dessinerAide(int hauteur, int largeur)
{
    int h_win = hauteur - HAUTEUR_INFO_PARTIE - HAUTEUR_INFO_JOUEUR - HAUTEUR_INFO_SORT;
    int l_win = largeur/3;
    int i = 1;
    WINDOW * win = subwin(stdscr, h_win, l_win, HAUTEUR_INFO_PARTIE + HAUTEUR_INFO_JOUEUR + HAUTEUR_INFO_SORT, (2*largeur)/3);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    wmove(win,i++, 1);
    wprintw(win, " Flêche haut et bas : Deplace le curseur sur les listes");
    wmove(win, i++, 1);
    wprintw(win, " <- -> : Deplace le curseur entre les colonnes");
    wmove(win, i++, 1);
    wprintw(win, " F2 : Quitte sans valider");
    wmove(win, i++, 1);
    wprintw(win, " F3 : Valide les informations");
    wmove(win, i++, 1);
    wprintw(win, " + : Ajouter un sort à la liste ou choisir une équipe");
    wrefresh(win);
}

void VueCreerJoueur::activerCouleurCurseur(WINDOW* win, int index, bool activer, int position)
{
    if(index == this->curseur)
    {
        if(activer == true)
        {
            if((index == IndexCreerJoueur::curseur_liste_equipe && position == this->positionEquipe) || (index == IndexCreerJoueur::curseur_liste_sort && position == this->positionSort) || index == IndexCreerJoueur::curseur_nom_equipe || index == IndexCreerJoueur::curseur_nom_joueur)
            {
                wattron(win, COLOR_PAIR(1));
            }
        }
        else
        {
            if((index == IndexCreerJoueur::curseur_liste_equipe && position == this->positionEquipe) || (index == IndexCreerJoueur::curseur_liste_sort && position == this->positionSort) || index == IndexCreerJoueur::curseur_nom_equipe || index == IndexCreerJoueur::curseur_nom_joueur)
            {
                wattroff(win, COLOR_PAIR(1));
            }
        }
    }
}
