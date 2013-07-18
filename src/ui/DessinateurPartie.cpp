#include "ui/DessinateurPartie.h"

DessinateurPartie::DessinateurPartie(PartieClient* partie, ReceptionClient* recepteur)
{
    this->partie = partie;
    this->recepteur = recepteur;
    this->positionCourante = Position::fabriquePosition(0,0);
}

void DessinateurPartie::dessinerPartie()
{
    int hauteur, largeur, l_colonne;
    getmaxyx(stdscr, hauteur, largeur);
    l_colonne = largeur/4;
    erase();
    this->dessinerJoueurs(hauteur, largeur);
    this->dessinerMessage(hauteur, largeur);
    this->dessinerPlateau(hauteur, largeur);
    this->dessinerCaseCourante(hauteur, largeur);
}
void DessinateurPartie::dessinerJoueurs(int hauteur, int largeur)
{
    int h_win = hauteur;
    int l_win = largeur/5;
    int i = 1;
    Joueur* joueur = NULL;
    WINDOW * win = subwin(stdscr, h_win, l_win, 0, 0);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    map<string, Joueur*> listeJoueur = this->partie->getListeJoueur();

    for(map<string, Joueur*>::iterator it = listeJoueur.begin(); it != listeJoueur.end(); it++)
    {
        joueur = it->second;
        if(joueur != NULL)
        {
            if(joueur == this->partie->getJoueurCourant())
            {
                    wattron(win, COLOR_PAIR(2));
            }
            wmove(win, i, 1); //1 pour éviter d'empiéter sur la bordure
            wprintw(win, "Nom : %s   Equipe : %s", it->first.c_str(), joueur->getNomEquipe().c_str());
            wmove(win, i + 1, 1); //1 pour éviter d'empiéter sur la bordure
            wprintw(win, "Mana : %d/%d  Gain : %d", joueur->getManaActuel(), joueur->getManaMaximum(), joueur->getGainInitialMana());
            if(joueur == this->partie->getJoueurCourant())
            {
                wmove(win, i + 2, 1); //1 pour éviter d'empiéter sur la bordure
                wprintw(win, "** Tour **");
            }
            if(joueur == this->partie->getJoueurCourant())
            {
                    wattroff(win, COLOR_PAIR(2));
            }
            i += 4; //lignes d'écriture et une pour l'espace
        }
    }
    //TODO faire la limite d'affichage s'il y a trop de joueur
    //TODO faire une case d'information du joueur pour lister ses sorts
    wrefresh(win);
}

void DessinateurPartie::dessinerMessage(int hauteur, int largeur)
{
    int h_win = hauteur/5;
    int l_win = ((4*largeur)/5);
    int i = 1;
    WINDOW * win = subwin(stdscr, h_win, l_win, (4*hauteur)/5, largeur/5);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(win);
    list<pair<string, string> > listeMessage = this->partie->getListeMessage();
    for(list<pair<string, string> >::iterator it = listeMessage.begin(); it != listeMessage.end(); it++)
    {
        wmove(win, i, 1); //1 pour éviter d'empiéter sur la bordure
        wprintw(win, "%s | %s", it->first.c_str(), it->second.c_str());
        if(i > 5)
        {
            break;
        }
        i++;
    }
    wmove(win, i, 1); //1 pour éviter d'empiéter sur la bordure
    wprintw(win, "%s : %s", this->partie->getJoueurClient().c_str(), this->message.c_str());
    wrefresh(win);
    //TODO un message en fonction du nombre de ligne
}

void DessinateurPartie::effectuerAction(int n)
{
    try
    {
        string nomSort = this->partie->getJoueurCourant()->getListeSort()[n]->getNom();
        this->recepteur->envoyerCommandeAction(nomSort, NULL, this->positionCourante);
    }
    catch(exception e)
    {
        GestionnaireLogger::ecrirMessage(TypeMessage::WARN, "Pas sort pour cette touche");
    }
}

void DessinateurPartie::dessinerPlateau(int hauteur, int largeur)
{
    int h_win = (4*hauteur)/5;
    int l_win = ((3*largeur)/5);
    int h_case = 1;
    int l_case = 2;
    int l_vision_case = l_win/l_case;
    int h_vision_case = h_win/h_case;
    //TODO recadrer pour contenir la case
    int x_origine = 0;
    int y_origine = 0;
    int i = 1;
    WINDOW * win = subwin(stdscr, h_win, l_win, 0, largeur/5);
    for(int x = x_origine; x < x_origine + l_vision_case; x++)
    {
        for(int y = y_origine; y < y_origine + h_vision_case; y++)
        {
            if(this->partie->getCase(Position::fabriquePosition(x, y)) != NULL)
            {
                wmove(win, y*h_case, x*l_case); //1 pour éviter d'empiéter sur la bordure
                if(this->positionCourante == Position::fabriquePosition(x, y))
                {
                    wattron(win, COLOR_PAIR(1));
                }
                wprintw(win, "[]");
                if(this->positionCourante == Position::fabriquePosition(x, y))
                {
                    wattroff(win, COLOR_PAIR(1));
                }
            }
        }
    }
    wrefresh(win);
}

void DessinateurPartie::dessinerCaseCourante(int hauteur, int largeur)
{
    int h_win = (4*hauteur)/5;
    int l_win = largeur/5;
    WINDOW * win = subwin(stdscr, h_win, l_win, 0, (4*largeur)/5);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    Case* caseCourante = this->partie->getCase(this->positionCourante);
    if(caseCourante != NULL)
    {
        int i = 1;
        wmove(win, i++, 1); //1 pour éviter d'empiéter sur la bordure
        wprintw(win, "[%d;%d]", this->positionCourante->getX(), this->positionCourante->getY());
        wmove(win, i++, 1); //1 pour éviter d'empiéter sur la bordure
        wprintw(win, "Def Init : %d", caseCourante->getDefenseInitiale());
        wmove(win, i++, 1); //1 pour éviter d'empiéter sur la bordure
        wprintw(win, "Defense : %d/%d", caseCourante->getDefenseActuelle(), caseCourante->getDefenseReel());
        wmove(win, i++, 1); //1 pour éviter d'empiéter sur la bordure
        wprintw(win, "Apport Mana : %d", caseCourante->getApportMana());
        wmove(win, i++, 1); //1 pour éviter d'empiéter sur la bordure
        wprintw(win, "Regeneration : %d", caseCourante->getRegenerationDefense());
        wmove(win, i++, 1); //1 pour éviter d'empiéter sur la bordure
        wprintw(win, "Proprietaire : %s", caseCourante->getNomProprietaire().c_str());
        wmove(win, i++, 1); //1 pour éviter d'empiéter sur la bordure
        wprintw(win, "  --- Sort ---  ");
        list<pair<int, Sort*> > listeSort = caseCourante->getListSort();
        for(list<pair<int, Sort*> >::iterator it = listeSort.begin(); it != listeSort.end(); it++)
         {
            wmove(win, i++, 1); //1 pour éviter d'empiéter sur la bordure
            wprintw(win, "%s (%d)", it->second->getNom().c_str(), it->first);
        }
    }
    wrefresh(win);
}

void DessinateurPartie::saisie()
{
    int touche = 0;
    while(true)
    {
        touche = getch();
        switch(touche)
        {
            case KEY_BACKSPACE:
                this->message = this->message.substr(0, this->message.size() - 1);
            break;
            case KEY_UP:
                if(this->positionCourante->getY() > 0)
                {
                    this->positionCourante = Position::fabriquePosition(this->positionCourante->getX(), this->positionCourante->getY() -1);
                }
            break;
            case KEY_DOWN:
                    this->positionCourante = Position::fabriquePosition(this->positionCourante->getX(), this->positionCourante->getY() +1);
            break;
            case KEY_LEFT:
                if(this->positionCourante->getX() > 0)
                {
                    this->positionCourante = Position::fabriquePosition(this->positionCourante->getX() -1, this->positionCourante->getY());
                }
            break;
            case KEY_RIGHT:
                    this->positionCourante = Position::fabriquePosition(this->positionCourante->getX() +1, this->positionCourante->getY());
            break;
            case '\n':
                this->recepteur->envoyerCommandeMessage(this->message);
            break;
            case 27:
                this->recepteur->envoyerCommandeQuitter();
                return;
            break;
            default:
                this->message += touche;
            break;
        }
        this->dessinerPartie();
    }
}
