#include "ui/DessinateurPartie.h"

DessinateurPartie::DessinateurPartie(PartieClient* partie, ReceptionClient* recepteur)
{
    this->partie = partie;
    this->recepteur = recepteur;
    this->positionCourante = Position::fabriquePosition(0,0);
    this->indexPanneau = IndexDessinateurPartie::index_plateau;
    this->origineSort = NULL;
}

void DessinateurPartie::dessinerPartie()
{
    this->mut.lock();
    int hauteur, largeur, l_colonne;
    getmaxyx(stdscr, hauteur, largeur);
    l_colonne = largeur/4;
    erase();
    this->dessinerJoueurs(hauteur, largeur);
    this->dessinerMessage(hauteur, largeur);
    this->dessinerPlateau(hauteur, largeur);
    this->dessinerCaseCourante(hauteur, largeur);
    this->dessinerListeSortJoueur(hauteur, largeur);
    this->dessinerNotification(hauteur, largeur);
    this->mut.unlock();
}
void DessinateurPartie::dessinerJoueurs(int hauteur, int largeur)
{
    int h_win = (4*hauteur)/5;
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
    wmove(win, i, 1); //1 pour éviter d'empiéter sur la bordure
    if(this->indexPanneau == IndexDessinateurPartie::index_message)
    {
        wattron(win, COLOR_PAIR(2));
    }
    wprintw(win, "%s : %s", this->partie->getJoueurClient().c_str(), this->message.c_str());
    if(this->indexPanneau == IndexDessinateurPartie::index_message)
    {
        wattroff(win, COLOR_PAIR(2));
    }
    i++;
    for(list<pair<string, string> >::iterator it = listeMessage.begin(); it != listeMessage.end(); it++)
    {
        wmove(win, i, 1); //1 pour éviter d'empiéter sur la bordure
        wprintw(win, "%s | %s", it->first.c_str(), it->second.c_str());
        if(i >= h_win - 2) //-2 pour la bordure
        {
            break;
        }
        i++;
    }
    wrefresh(win);
    //TODO en fonction du nombre de ligne et de la taille des messages
}

void DessinateurPartie::effectuerAction(int n)
{
    try
    {
        Sort* sort = this->partie->getJoueur(this->partie->getJoueurClient())->getListeSort()[n];
        if(sort != NULL)
        {
            string nomSort = sort->getNom();
            if(this->listeCible.size() > 0)
            {
                this->recepteur->envoyerCommandeAction(nomSort, this->origineSort, this->listeCible);
            }
            else
            {
                this->listeCible.push_front(this->positionCourante);
                this->recepteur->envoyerCommandeAction(nomSort, this->origineSort, this->listeCible);
                this->listeCible.pop_front();
            }
        }
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
    Position* position = NULL;
    WINDOW * win = subwin(stdscr, h_win, l_win, 0, largeur/5);
    for(int x = x_origine; x < x_origine + l_vision_case; x++)
    {
        for(int y = y_origine; y < y_origine + h_vision_case; y++)
        {
            position = Position::fabriquePosition(x, y);
            if(this->partie->getCase(position) != NULL)
            {
                wmove(win, y*h_case, x*l_case); //1 pour éviter d'empiéter sur la bordure
                this->modifierCouleurPlateau(position, true, win);
                wprintw(win, "[]");
                this->modifierCouleurPlateau(position, false, win);
            }
        }
    }
    wrefresh(win);
}

void DessinateurPartie::dessinerCaseCourante(int hauteur, int largeur)
{
    int h_win = (2*hauteur)/5;
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

void DessinateurPartie::dessinerListeSortJoueur(int hauteur, int largeur)
{
    int h_win = (2*hauteur)/5;
    int l_win = largeur/5;
    int i = 1;
    WINDOW * win = subwin(stdscr, h_win, l_win, (2*hauteur)/5, (4*largeur)/5);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    Joueur* joueur = this->partie->getJoueur(this->partie->getJoueurClient());
    if(joueur == NULL)
    {
        return;
    }
    vector<Sort*> listeSort = joueur->getListeSort();
    for(vector<Sort*>::iterator it = listeSort.begin(); it != listeSort.end(); it++)
    {
        wmove(win, i, 1); //1 pour éviter d'empiéter sur la bordure
        wprintw(win, "F%d : %s", i + 1, (*it)->getNom().c_str());
        if(i >= 16 || i >= h_win - 2)
        {
            break;
        }
        i++;
    }
}

void DessinateurPartie::dessinerNotification(int hauteur, int largeur)
{
    int h_win = hauteur/5;
    int l_win = largeur/5;
    int i = 1;
    WINDOW * win = subwin(stdscr, h_win, l_win, (4*hauteur)/5, 0);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    list<string> listeNotification = this->partie->getListeNotification();
    for(list<string>::iterator it = listeNotification.begin(); it != listeNotification.end(); it++)
    {
        wmove(win, i, 1); //1 pour éviter d'empiéter sur la bordure
        wprintw(win, "%s", it->c_str());
        i++;
        if(i > h_win -2)
        {
            break;
        }
    }
}

void DessinateurPartie::saisie()
{
    int touche = 0;
    while(this->partie->getEquipeGagnante() == "")
    {
        touche = getch();
        switch(touche)
        {
        case '\t':
            this->tournerIndexPanneaux();
            break;
        case 27: //touche echap
            this->recepteur->envoyerCommandeQuitter();
            return;
            break;
        case KEY_F(1):
            GestionnaireLogger::ecrirMessage(INFO, "F1 enfoncée -> demande d'aide");
            //TODO faire un menu d'aide
            break;
        default:
            this->traitementToucheParPanneaux(touche);
            break;
        }
        this->dessinerPartie();
    }
}

void DessinateurPartie::traitementToucheParPanneaux(int touche)
{
    switch(this->indexPanneau)
    {
    case IndexDessinateurPartie::index_message:
        this->traitementToucheMessage(touche);
        break;
    case IndexDessinateurPartie::index_plateau:
        this->traitementTouchePlateau(touche);
        break;
    }
}

void DessinateurPartie::tournerIndexPanneaux()
{
    if(this->indexPanneau == IndexDessinateurPartie::index_plateau)
    {
        this->indexPanneau = IndexDessinateurPartie::index_message;
    }
    else if(this->indexPanneau == IndexDessinateurPartie::index_message)
    {
        this->indexPanneau = IndexDessinateurPartie::index_plateau;
    }
}

void DessinateurPartie::traitementTouchePlateau(int touche)
{
    Position* position;
    switch(touche)
    {
    case KEY_UP:
        if(this->positionCourante->getY() > 0)
        {
            position = Position::fabriquePosition(this->positionCourante->getX(), this->positionCourante->getY() -1);
            if(this->partie->getCase(position) != NULL)
            {
                this->positionCourante = position;
            }
        }
        break;
    case KEY_DOWN:
        position = Position::fabriquePosition(this->positionCourante->getX(), this->positionCourante->getY() +1);
        if(this->partie->getCase(position) != NULL)
        {
            this->positionCourante = position;
        }
        break;
    case KEY_LEFT:
        if(this->positionCourante->getX() > 0)
        {
            position = Position::fabriquePosition(this->positionCourante->getX() -1, this->positionCourante->getY());
            if(this->partie->getCase(position) != NULL)
            {
                this->positionCourante = position;
            }
        }
        break;
    case KEY_RIGHT:
        position = Position::fabriquePosition(this->positionCourante->getX() +1, this->positionCourante->getY());
        if(this->partie->getCase(position) != NULL)
        {
            this->positionCourante = position;
        }
        break;
    case ' ':
        this->ajouterCible(this->positionCourante);
        break;
    case '+':
        if(this->positionCourante == this->origineSort)
        {
            this->origineSort = NULL;
        }
        else
        {
            this->origineSort = this->positionCourante;
        }
        break;
    case 't':
        this->recepteur->envoyerCommandeFinTour();
        break;
    default:
        for(int i = 2; i < 16; i++)
        {
            if(touche == KEY_F(i))
            {
                this->effectuerAction(i - 2);
                break;
            }
        }
        break;
    }
}

void DessinateurPartie::traitementToucheMessage(int touche)
{
    switch(touche)
    {
    case '\n':
        this->recepteur->envoyerCommandeMessage(this->message);
        this->message = "";
        break;
    case KEY_BACKSPACE:
        this->message = this->message.substr(0, this->message.size() - 1);
        break;
    default:
        if(touche >= 32 && touche <= 126)
        {
            this->message += touche;
        }
        break;
    }
}

void DessinateurPartie::ajouterCible(Position* position)
{
    list<Position*>::iterator element = find(this->listeCible.begin(), this->listeCible.end(), position);
    if(element == this->listeCible.end()) //il n'existe pas, on l'ajoute
    {
        this->listeCible.push_front(position);
    }
    else //Il existe, on le retire
    {
        this->listeCible.erase(element);
    }
}

void DessinateurPartie::modifierCouleurPlateau(Position* position, bool activer, WINDOW *win)
{
    if(position == this->positionCourante && this->indexPanneau == IndexDessinateurPartie::index_plateau)
    {
        if(activer == true)
        {
                    wattron(win, COLOR_PAIR(1));
        }
        else
        {
                    wattroff(win, COLOR_PAIR(1));
        }
        return;
    }
    if(position == this->origineSort)
    {
        if(activer == true)
        {
                    wattron(win, COLOR_PAIR(2));
        }
        else
        {
                    wattroff(win, COLOR_PAIR(2));
        }
    }
    list<Position*>::iterator element = find(this->listeCible.begin(), this->listeCible.end(), position);
    if(element != this->listeCible.end())
    {
        if(activer == true)
        {
                    wattron(win, COLOR_PAIR(3));
        }
        else
        {
                    wattroff(win, COLOR_PAIR(3));
        }
    }
}
