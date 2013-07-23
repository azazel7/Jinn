#include "reseau/client/ReceptionClient.h"

ReceptionClient::ReceptionClient(PartieClient* partie, string ip, int port = 14790)
{
    this->partie = partie;
    this->port = port;
    this->ip = ip;
    this->eteindre = false;
    this->dessinateur = NULL;
}
bool ReceptionClient::initialiserClient()
{
    int nombreEssai = 0;
    this->socketClient = socket(AF_INET, SOCK_STREAM, 0);
    //    struct hostent *hostinfo = NULL;
    struct sockaddr_in sin = { 0 }; /* initialise la structure avec des 0 */
    //    const char *hostname = "www.developpez.com";

    //    hostinfo = gethostbyname(hostname); /* on récupère les informations de l'hôte auquel on veut se connecter */
    //    if (hostinfo == NULL) /* l'hôte n'existe pas */
    //    {
    //        fprintf (stderr, "Unknown host %s.\n", hostname);
    //        exit(EXIT_FAILURE);
    //    }

    //    sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr; /* l'adresse se trouve dans le champ h_addr de la structure hostinfo */
    sin.sin_addr.s_addr = inet_addr(this->ip.c_str());
    sin.sin_port = htons(this->port); /* on utilise htons pour le port */
    sin.sin_family = AF_INET;

    while(connect(this->socketClient,(struct sockaddr *) &sin, sizeof(struct sockaddr)) == -1)
    {
        GestionnaireLogger::ecrirMessage(TypeMessage::ERROR, "Impossible de se connecter");
        nombreEssai++;
        if(nombreEssai == 10)
        {
            GestionnaireLogger::ecrirMessage(TypeMessage::FATAL, "Impossible de se connecter après dix essais");
            return false;
        }
        sleep(2);
    }
    return true;
}
bool ReceptionClient::miseEnEcoute()
{
    /* Création de l'ensemble de lecture */
    fd_set readfs;
    /* On vide l'ensemble de lecture et on lui ajoute
         la socket serveur */
    while(this->eteindre == false)
    {
        /* Si une erreur est survenue au niveau du select */
        FD_ZERO(&readfs);
        FD_SET(this->socketClient, &readfs);
        GestionnaireLogger::ecrirMessage(TypeMessage::INFO, "Attente du select");
        if(select(this->socketClient + 1, &readfs, NULL, NULL, NULL) < 0)
        {
            GestionnaireLogger::ecrirMessage(TypeMessage::FATAL, "Select erreur");
            exit(-1);
        }
        GestionnaireLogger::ecrirMessage(TypeMessage::INFO, "Données reçus par le select");
        this->testerSelection(readfs);
    }
}

void ReceptionClient::testerSelection(fd_set readfd)
{
    char* data = NULL;
    int octetRecus = -1, octetLus = -1;
    if(FD_ISSET(this->socketClient, &readfd))
    {
        ioctl(this->socketClient, FIONREAD, &octetRecus);
        //Deconnexion du serveur
        if(octetRecus == 0)
        {
            GestionnaireLogger::ecrirMessage(TypeMessage::INFO, "Le serveur vous à deconnecté");
            exit(-1);
        }
        //Erreur
        else if(octetRecus < 0)
        {
            GestionnaireLogger::ecrirMessage(TypeMessage::ERROR, "Erreur de lecture du nombre d'octet par ioctl");
        }
        //On ajoute 1 car c'est une chaine et qu'il faut le 0 final
        data = (char*)malloc(sizeof(char)*(octetRecus + 1));
        if(data == NULL)
        {
            GestionnaireLogger::ecrirMessage(TypeMessage::FATAL, "Erreur malloc");
            exit(-1);
        }
        data[octetRecus] = 0;
        octetLus = recv(this->socketClient, data, octetRecus, 0);
        if( octetLus < 0)
        {
            GestionnaireLogger::ecrirMessage(TypeMessage::ERROR, "Erreur recv. Nombre d'octets négatif");
            free(data);
            return;
        }
        else if(octetLus != octetRecus) //Curieuse affaire
        {
            GestionnaireLogger::ecrirMessage(TypeMessage::ERROR, "Nombre d'octet lu different du nombre d'octet reçu");
            free(data);
            return;
        }
        GestionnaireLogger::ecrirMessage(TypeMessage::INFO, "Traitement des données en cour ...");
        string ligne = data;
        free(data);
        vector<string> listeCommande;
        boost::split(listeCommande, ligne, boost::is_any_of(SEPARATEUR_COMMANDE));
        for(int i = 0; i < listeCommande.size(); i++)
        {
            data = (char*)malloc((listeCommande[i].size() + 1) * sizeof(char));
            strncpy(data, listeCommande[i].c_str(), listeCommande[i].size());
            data[listeCommande[i].size()] = 0;
            GestionnaireLogger::ecrirMessage(INFO, data);
            this->traitementCommande(data);
            free(data);
        }
    }
}

void ReceptionClient::traitementCommande(char* commande)
{
    char *action = NULL;
    action = strtok (commande, SEPARATEUR_ELEMENT);
    if(action != NULL)
    {
        if(strcmp(action, MESSAGE) == 0)
        {
            traitementMessage();
        }
        else if(strcmp(action, INFORMATION_CASE) == 0)
        {
            traitementInfoCase();
        }
        else if(strcmp(action, INFORMATION_JOUEUR) == 0)
        {
            traitementInfoJoueur();
        }
        else if(strcmp(action, INFORMATION_SORT) == 0)
        {
            traitementInfoSort();
        }
        else if(strcmp(action, INFORMATION_PARTIE) == 0)
        {
             traitementInfoPartie();
        }
        else if(strcmp(action, TOUR_DE) == 0)
        {
            traitementTourDe();
        }
        else if(strcmp(action, FIN_TOUR_PARTIE) == 0)
        {
            traitementFinTourPartie();
        }
        else if(strcmp(action, MORT) == 0)
        {
            //Message, supprimer les sorts et le joueur
        }
        else if(strcmp(action, QUITTER_PARTIE) == 0)
        {
            traitementQuitterPartie();
        }
        else if(strcmp(action, DEMARAGE_PARTIE) == 0)
        {
        }
        else if(strcmp(action, FIN_PARTIE) == 0)
        {
            //Message
        }
        else if(strcmp(action, REUSSITE_SORT) == 0)
        {
            //Message
        }
        else if(strcmp(action, SORT) == 0)
        {
            traitementSort();
        }
        else if(strcmp(action, EQUIPE) == 0)
        {
            traitementEquipe();
        }
        else if(strcmp(action, NOUVEAU_JOUEUR) == 0)
        {
            traitementNouveauJoueur();
        }

        if(this->dessinateur != NULL)
        {
            //ecrit sur l'entrée standard pour forcé ncurse à sortir de son trou
            //ncurses gére mal les entrée-sortie en même temps
            write(0, "\x01", 1);
        }
    }

}

void ReceptionClient::traitementInfoCase()
{
    char* argument[10] = {NULL};
    Case* caseCible = NULL;
    int x = -1, y = -1, defReel = -1, defActuelle = -1, defInit = -1, regenDef = -1, apportMana = -1, bonusOffInit = -1, bonusOffActuel = -1;
    for(int i = 0; i < 10; i++)
    {
        argument[i] = strtok (NULL, SEPARATEUR_ELEMENT);
    }

    for(int i = 0; i < 10; i++)
    {
        if(argument[i] == NULL) // i != 2 car le second est le proprio qui peut être vide
        {
            //Info fausse
            return;
        }
    }
    x = atoi(argument[0]);
    y = atoi(argument[1]);
    if(x < 0 || y < 0)
    {
        //Fausse info
        return;
    }
    defInit = atoi(argument[3]);
    defReel = atoi(argument[4]);
    defActuelle = atoi(argument[5]);
    regenDef = atoi(argument[6]);
    apportMana = atoi(argument[7]);
    bonusOffInit = atoi(argument[8]);
    bonusOffActuel = atoi(argument[9]);
    caseCible = this->partie->getCase(Position::fabriquePosition(x, y));
    if(caseCible == NULL)
    {
        caseCible = new Case(defInit, bonusOffInit, -1, -1, apportMana, regenDef, -1, Position::fabriquePosition(x, y));
        caseCible->setDefenseReel(defReel);
        caseCible->setDefenseActuelle(defActuelle);
        caseCible->setBonusOffensifActuel(bonusOffActuel);
        caseCible->setProprietaire(this->partie->getJoueur(argument[2]));
        this->partie->ajouterCase(caseCible);
    }
    else
    {
        if(defReel != -1)
        {
            caseCible->setDefenseReel(defReel);
        }
        if(defActuelle != -1)
        {
            caseCible->setDefenseActuelle(defActuelle);
        }
        if(defInit != -1)
        {
            caseCible->setDefenseInitiale(defInit);
        }
        if(regenDef != -1)
        {
            caseCible->setRegenerationDefense(regenDef);
        }
        if(apportMana != -1)
        {
            caseCible->setApportMana(apportMana);
        }
        if(bonusOffActuel != -1)
        {
            caseCible->setBonusOffensifActuel(bonusOffActuel);
        }
        if(bonusOffInit != -1)
        {
            caseCible->setBonusOffensifInitial(bonusOffInit);
        }
        caseCible->setProprietaire(this->partie->getJoueur(argument[2]));
    }
}

string ReceptionClient::traitementInfoJoueur()
{
    char* argument[5] = {NULL};
    int manaActuel = -1, manaMax = -1, gainMana = -1;
    Joueur* joueur;
    for(int i = 0; i < 5; i++)
    {
        argument[i] = strtok (NULL, SEPARATEUR_ELEMENT);
    }

    for(int i = 0; i < 5; i++)
    {
        if(argument[i] == NULL)
        {
            //Info fausse
            return "";
        }
    }
    manaActuel = atoi(argument[2]);
    manaMax = atoi(argument[3]);
    gainMana = atoi(argument[4]);
    joueur = this->partie->getJoueur(argument[0]);
    if(joueur == NULL)
    {
        joueur = new Joueur(gainMana, manaMax, -1, argument[0]);
        joueur->setManaActuel(manaActuel);
        //TODO Setter l'equipe
        this->partie->ajouterJoueur(joueur);
    }
    else
    {
        if(manaMax != -1)
        {
            joueur->setManaMaximum(manaMax);
        }
        if(manaActuel != -1)
        {
            joueur->setManaActuel(manaActuel);
        }
        if(gainMana != -1)
        {
            joueur->setGainMana(gainMana);
        }
    }
    return joueur->getNom();
}

void ReceptionClient::traitementInfoSort()
{
    char* argument[6] = {NULL};
    Sort* sort = NULL;
    Case* caseCible = NULL;
    Joueur* proprietaire = NULL;
    int x = -1, y = -1, duree = -1;
    unsigned int id = 0;
    for(int i = 0; i < 6; i++)
    {
        argument[i] = strtok (NULL, SEPARATEUR_ELEMENT);
    }
    for(int i = 0; i < 6; i++)
    {
        if(argument[i] == NULL)
        {
            //Info fausse
            return;
        }
    }
    x = atoi(argument[4]);
    y = atoi(argument[5]);
    duree = atoi(argument[3]);
    id = atoi(argument[1]);

    sort = this->partie->getSort(Position::fabriquePosition(x, y), id);
    //Sort inexistant sur la case
    if(sort == NULL)
    {
        sort = UsineSort::fabriqueSort(argument[0]);
        //Pas de sort de ce nom
        if(sort == NULL)
        {
            return;
        }
        proprietaire = this->partie->getJoueur((argument[2]));
        //Pas de joueur de ce nom
        if(proprietaire == NULL)
        {
            return;
        }
        sort->setProprietaire(proprietaire);
        sort->setId(id);
        caseCible = this->partie->getCase(Position::fabriquePosition(x, y));
        //Pas de case à cette position
        if(caseCible != NULL)
        {
            caseCible->ajouterSort(sort, duree);
        }
    }
}

void ReceptionClient::traitementTourDe()
{
    GestionnaireLogger::ecrirMessage(INFO, "Tour de");
    char* nom = NULL;
    Joueur* joueur = NULL;
    nom = strtok (NULL, SEPARATEUR_ELEMENT);
    if(nom != NULL)
    {
        joueur = this->partie->getJoueur(nom);
    }
    this->partie->setJoueurCourant(joueur);
}

void ReceptionClient::traitementSort()
{
    vector<Sort*> listeSort;
    char* nomSort = NULL;
    Sort* courant = NULL;
    int compteur = 0;
    while( (nomSort = strtok (NULL, SEPARATEUR_ELEMENT)) != NULL)
    {
        if((compteur%8) == 0)
        {
            courant = UsineSort::fabriqueSort(nomSort);
            if(courant != NULL)
            {
                listeSort.push_back(courant);
            }
        }
    }
    this->partie->setListeSortDispo(listeSort);
}

void ReceptionClient::traitementEquipe()
{
    vector<string> listeEquipe;
    char* nom = NULL;
    while( (nom = strtok (NULL, SEPARATEUR_ELEMENT)) != NULL)
    {
        listeEquipe.push_back(nom);
    }
    this->partie->setListeEquipe(listeEquipe);
}

void ReceptionClient::traitementNouveauJoueur()
{
    string nom = traitementInfoJoueur();
    if(nom == "")
    {
        return;
    }
    this->partie->setJoueurClient(nom);
    char* nomSort = NULL;
    while((nomSort = strtok(NULL, SEPARATEUR_ELEMENT)) != NULL)
    {
        this->partie->ajouterSortJoueur(nom, nomSort);
        GestionnaireLogger::ecrirMessage(INFO, nomSort);
    }
}

void ReceptionClient::traitementInfoPartie()
{
    char* argument[3] = {NULL};
    int nombrePlace = -1, nombreJoueur = -1, nombreSortParJoueur = -1;
    for(int i = 0; i < 3; i++)
    {
        argument[i] = strtok(NULL, SEPARATEUR_ELEMENT);
        if(argument[i] == NULL)
        {
            return;
        }
    }
    nombrePlace = atoi(argument[0]);
    nombreJoueur = atoi(argument[1]);
    nombreSortParJoueur = atoi(argument[2]);
    if(nombreJoueur < 0 || nombrePlace < 0 || nombreSortParJoueur < 0)
    {
        return;
    }
    this->partie->setNombreJoueur(nombreJoueur);
    this->partie->setNombrePlace(nombrePlace);
    this->partie->setNombreSortParJoueur(nombreSortParJoueur);
}

void ReceptionClient::envoyerCommandeSort()
{
    string final = SORT;
    final += SEPARATEUR_ELEMENT;
    final += SEPARATEUR_COMMANDE;
    send(this->socketClient, final.c_str(), final.size(), 0);
}
void ReceptionClient::envoyerCommandeEquipe()
{
    string final = EQUIPE;
    final += SEPARATEUR_ELEMENT;
    final += SEPARATEUR_COMMANDE;
    send(this->socketClient, final.c_str(), final.size(), 0);
}

void ReceptionClient::envoyerCommandeNouveauJoueur(string const& nomJoueur, string const& nomEquipe, list<string> & listeSort)
{
    string final = NOUVEAU_JOUEUR;
    final += SEPARATEUR_ELEMENT;
    final += nomJoueur;
    final += SEPARATEUR_ELEMENT;
    final += nomEquipe;
    final += SEPARATEUR_ELEMENT;
    for(list<string>::iterator it = listeSort.begin(); it != listeSort.end(); it++)
    {
        final += (*it);
        final += SEPARATEUR_ELEMENT;
    }
    final += SEPARATEUR_COMMANDE;
    send(this->socketClient, final.c_str(), final.size(), 0);
}

void ReceptionClient::envoyerCommandeMessage(string const& message)
{
    string final = MESSAGE;
    final += SEPARATEUR_ELEMENT;
    final += message;
    final += SEPARATEUR_ELEMENT;
    final += SEPARATEUR_COMMANDE;
    send(this->socketClient, final.c_str(), final.size(), 0);
}

void ReceptionClient::envoyerCommandeAction(string const& sort, Position* origine, list<Position *> cible)
{
    string final = ACTION;
    final += SEPARATEUR_ELEMENT;
    final += sort;
    final += SEPARATEUR_ELEMENT;
    if(origine == NULL)
    {
        final += to_string(-1);
        final += SEPARATEUR_ELEMENT;
        final += to_string(-1);
        final += SEPARATEUR_ELEMENT;
    }
    else
    {
        final += to_string(origine->getX());
        final += SEPARATEUR_ELEMENT;
        final += to_string(origine->getY());
        final += SEPARATEUR_ELEMENT;
    }
    for(list<Position*>::iterator it = cible.begin(); it != cible.end(); it++)
    {
        final += to_string((*it)->getX());
        final += SEPARATEUR_ELEMENT;
        final += to_string((*it)->getY());
        final += SEPARATEUR_ELEMENT;
    }
    final += SEPARATEUR_COMMANDE;
    send(this->socketClient, final.c_str(), final.size(), 0);
}

void ReceptionClient::envoyerCommandeQuitter()
{
    string final = QUITTER;
    final += SEPARATEUR_ELEMENT;
    final += SEPARATEUR_COMMANDE;
    send(this->socketClient, final.c_str(), final.size(), 0);
}

void ReceptionClient::envoyerCommandeFinTour()
{
    string final = FIN_TOUR;
    final += SEPARATEUR_ELEMENT;
    final += SEPARATEUR_COMMANDE;
    send(this->socketClient, final.c_str(), final.size(), 0);
}

void ReceptionClient::envoyerCommandeInformationPartie()
{
    string final = INFORMATION_PARTIE;
    final += SEPARATEUR_ELEMENT;
    final += SEPARATEUR_COMMANDE;
    send(this->socketClient, final.c_str(), final.size(), 0);
}

void ReceptionClient::traitementMessage()
{
    char* auteur = strtok(NULL, SEPARATEUR_ELEMENT);
    char* message = strtok(NULL, SEPARATEUR_ELEMENT);
    if(auteur == NULL || message == NULL)
    {
        return;
    }
    this->partie->ajouterMessage(auteur, message);
}

DessinateurPartie* ReceptionClient::getDessinateur()
{
    return this->dessinateur;
}
void ReceptionClient::setDessinateur(DessinateurPartie* nouveauDessinateur)
{
    this->dessinateur = nouveauDessinateur;
}

void ReceptionClient::traitementFinTourPartie()
{
    map<int, Case*> listeCase = this->partie->getListeCase();
    for(map<int, Case*>::iterator it = listeCase.begin(); it != listeCase.end(); it++)
    {
        pair<int, Case*> cour = *it;
        Case* courante = cour.second;
        if(courante != NULL)
        {
            list<pair<int, Sort*> > listeSort = courante->getListSort();
            for(list<pair<int, Sort*> >::iterator ot = listeSort.begin(); ot != listeSort.end(); ot++)
            {
                ot->first--;
                if(ot->first <= 0)
                {
                    this->partie->retirerSortCase(courante->getPosition(), ot->second->getId());
                }
            }
        }
    }
}

void ReceptionClient::traitementMortJoueur()
{
    char* nom = strtok(NULL, SEPARATEUR_ELEMENT);
    if(nom == NULL)
    {
        return;
    }
    this->partie->retirerJoueur(nom);
}

void ReceptionClient::traitementQuitterPartie()
{
    char* nom = strtok(NULL, SEPARATEUR_ELEMENT);
    if(nom == NULL)
    {
        return;
    }
    this->partie->retirerJoueur(nom);
}
