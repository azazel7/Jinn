#include "reseau/serveur/ReceptionServeur.h"

ReceptionServeur::ReceptionServeur(Partie* partie, string ip, int port)
{
    this->partie = partie;
    this->ip = ip;
    this->port = port;
    this->eteindre = false;
}

bool ReceptionServeur::initialiserServeur()
{
    struct sockaddr_in sin;
    //Creation d'une socket en TCP/IP usant d'un protocole libre
    GestionnaireLogger::ecrirMessage(TypeMessage::INFO, "Creation du socket");
    this->socketServeur = socket(AF_INET, SOCK_STREAM, 0);
    //On écoute sur le port fournis et sur toutes l'adresse ip fournis
    sin.sin_addr.s_addr = inet_addr(this->ip.c_str());
    sin.sin_family = AF_INET;
    sin.sin_port = htons(this->port);
    //On associe la socket au contexte d'adressage
    if(bind(this->socketServeur, (struct sockaddr*) &sin, sizeof(sin)) < 0)
    {
        GestionnaireLogger::ecrirMessage(TypeMessage::FATAL, "Erreur de bind");
        return false;
    }
    //On mes en ecoute la socket
    if(listen(this->socketServeur, 5) < 0)
    {
        GestionnaireLogger::ecrirMessage(TypeMessage::FATAL, "Erreur listen");
        return false;
    }
    GestionnaireLogger::ecrirMessage(TypeMessage::SUCCESS, "Initialisation du serveur terminée");
    return true;
}


void ReceptionServeur::miseEnEcoute()
{
    /* Création de l'ensemble de lecture */
    fd_set readfs;
    /* On vide l'ensemble de lecture et on lui ajoute
         la socket serveur */
    FD_ZERO(&readfs);
    FD_SET(this->socketServeur, &readfs);
    while(this->eteindre == false)
    {
        /* Si une erreur est survenue au niveau du select */
        FD_ZERO(&readfs);
        this->remplirSelection(readfs);
        GestionnaireLogger::ecrirMessage(TypeMessage::INFO, "Attente du select");
        if(select(this->maximunFileDescriptor() + 1, &readfs, NULL, NULL, NULL) < 0)
        {
            GestionnaireLogger::ecrirMessage(TypeMessage::FATAL, "Select erreur");
            exit(-1);
        }
        GestionnaireLogger::ecrirMessage(TypeMessage::INFO, "Données reçus par le select");
        //Priorité au client qui joue on avise ensuite pour les nouvelles connexions
        this->testerSelectionClient(readfs);
        this->testerSelectionServeur(readfs);
        if (this->partie->isEnCours() == false && this->partie->nombreDeJoueur() == this->partie->getNombreDePlace() && this->partie->getEquipe().size() >= 2 && this->partie->isFinis() == false)
        {
            this->partie->demarrerPartie();
        }
        else if(this->partie->isFinis())
        {
            this->finirServeur();
            return;
        }
    }
    FD_ZERO(&readfs);
}

void ReceptionServeur::remplirSelection(fd_set& readfd)
{
    for(map<int, Client*>::iterator it = listeClient.begin(); it != listeClient.end(); it++)
    {
        FD_SET(it->first, &readfd);
    }
    FD_SET(this->socketServeur, &readfd);
}
void ReceptionServeur::testerSelectionClient(fd_set& readfd)
{
    bool clientSupp = false;
    for(map<int, Client*>::iterator it = listeClient.begin(); it != listeClient.end(); ++it)
    {
        if(FD_ISSET(it->first, &readfd))
        {
            char *data = NULL;
            int octetRecus = 0;
            int octetLus = 0;
            //On calcule combien il y a d'octet à lire
            ioctl(it->first, FIONREAD, &octetRecus);

            //Deconnexion du client
            if(octetRecus == 0)
            {
                //On ferme la socket
                close(it->first);
                if(it->second != NULL)
                {
                    GestionnaireLogger::ecrirMessage(TypeMessage::INFO, "Destruction du joueur " + it->second->getJoueur()->getNom());
                    //Si c'était un joueur on le retire de la partie
                    this->partie->retirerJoueur(it->second->getJoueur());
                    delete it->second;
                    it->second = NULL;
                }
                close(it->first);
                //On supprime l'entrée
                it = listeClient.erase(it);
                GestionnaireLogger::ecrirMessage(TypeMessage::SUCCESS, "Destruction réussi");
                continue;
            }
            cout << "Octet reçus : " << octetRecus << endl;
            //On alloue en conséquence
            data = (char*)malloc(sizeof(char)*(octetRecus + 1));
            if(data == NULL)
            {
                GestionnaireLogger::ecrirMessage(TypeMessage::FATAL, "Erreur malloc");
                exit(-1);
            }
            //On lit les données
            octetLus = recv(it->first, data, octetRecus, 0);
            data[octetRecus] = 0;
            if( octetLus < 0)
            {
                GestionnaireLogger::ecrirMessage(TypeMessage::ERROR, "Erreur recv. Nombre d'octets négatif");
                free(data);
                continue;
            }
            else if(octetLus != octetRecus) //Curieuse affaire
            {
                GestionnaireLogger::ecrirMessage(TypeMessage::ERROR, "Nombre d'octet lu different du nombre d'octet reçu");
                free(data);
                continue;
            }
            string ligne = data;
            free(data);
            vector<string> listeCommande;
            boost::split(listeCommande, ligne, boost::is_any_of(SEPARATEUR_COMMANDE));
            for(int i = 0; i < listeCommande.size(); i++)
            {
                data = (char*)malloc((listeCommande[i].size() + 1) * sizeof(char));
                strncpy(data, listeCommande[i].c_str(), listeCommande[i].size());
                cout << listeCommande[i] << endl;

                if(it->second == NULL)
                {
                    GestionnaireLogger::ecrirMessage(TypeMessage::INFO, "Traitement client");
                    this->traitementClient(data, it->first, clientSupp);
                }
                else
                {
                    GestionnaireLogger::ecrirMessage(TypeMessage::INFO, "Traitement joueur");
                    this->traitementJoueur(data, it->first, clientSupp);
                }
                if(clientSupp == true)
                {
                    clientSupp = false;
                    //On repart au début
                    return;
                }
            }
        }
    }
}

void ReceptionServeur::testerSelectionServeur(fd_set& readfd)
{
    /* Ici comme c'est la socket du serveur cela signifie
           forcement qu'un client veut se connecter au serveur.
           Dans le cas d'une socket cliente c'est juste des
           données qui serons reçues ici*/
    if(FD_ISSET(this->socketServeur, &readfd))
    {
        int csock;
        struct sockaddr_in csin;
        int crecsize = sizeof csin;
        //On l'accept en tant que potentiel nouveau joueur
        csock = accept(this->socketServeur, (struct sockaddr *) &csin, (socklen_t*)&crecsize);
        listeClient[csock] = NULL;
        //On l'ajoute à la selection
        FD_SET(csock, &readfd);
        GestionnaireLogger::ecrirMessage(TypeMessage::INFO, "Nouvelle connexion sur le serveur");
        //TODO améliorer ce log  inet_ntoa(csin.sin_addr), htons(csin.sin_port)
    }
}

int ReceptionServeur::maximunFileDescriptor()
{
    int retour = this->socketServeur;
    for(map<int, Client*>::iterator it = listeClient.begin(); it != listeClient.end(); it++)
    {
        if(it->first > this->socketServeur)
        {
            retour = it->first;
        }
    }
    return retour;
}

void ReceptionServeur::traitementJoueur(char *commande, int socketClient, bool &clientSuppr)
{
    char *action = NULL;
    action = strtok (commande, SEPARATEUR_ELEMENT);
    if(action == NULL)
    {
        return;
    }
    if(strcmp(action, MESSAGE) == 0)
    {
        //Envoyer un message à tout le monde
        this->traitementMessage(commande, listeClient[socketClient]->getJoueur()->getNom());
    }
    else if(strcmp(action, ACTION) == 0)
    {
        this->traitementAction(action, socketClient);
    }
    else if(strcmp(action, FIN_TOUR) == 0)
    {
        //Le joueur declare son tour finis
        Action *coup = new Action();
        coup->setOrigine(NULL);
        coup->setSort(NULL);
        this->partie->effectuerAction(coup, this->listeClient[socketClient]->getJoueur());
        delete coup;
    }
    else if(strcmp(action, QUITTER_PARTIE) == 0)
    {
        this->partie->retirerJoueur(this->listeClient[socketClient]->getJoueur());
        delete this->listeClient[socketClient];
        this->listeClient[socketClient] = NULL;
    }
    else if(strcmp(action, QUITTER) == 0)
    {
        this->partie->retirerJoueur(this->listeClient[socketClient]->getJoueur());
        delete this->listeClient[socketClient];
        this->listeClient[socketClient] = NULL;
        this->listeClient.erase(socketClient);
        clientSuppr = true;
        traitementQuitter(socketClient);
    }
}

void ReceptionServeur::traitementClient(char *commande, int socketClient, bool & clientSuppr)
{
    char *action = NULL;
    action = strtok (commande, SEPARATEUR_ELEMENT);
    if(action == NULL)
    {
        return;
    }
    if(strcmp(action, NOUVEAU_JOUEUR) == 0)
    {
        //Le joueur veut s'inscrire (nom, equipe, liste de sort(nom, pour l'usine)
        this->traitementNouveauJoueur(socketClient);
    }
    else if(strcmp(action, EQUIPE) == 0)
    {
        //Envoyer la liste des equipes ("equipe", nom, nom, ...)
        traitementEquipe(socketClient);
    }
    else if(strcmp(action, SORT) == 0)
    {
        //Envoyer la liste des sorts ("sort", nom, description, nom, description, ....)
        traitementSort(socketClient);
    }
    else if(strcmp(action, INFORMATION_PARTIE) == 0)
    {
        this->traitementInformationPartie(socketClient);
    }
    else if(strcmp(action, QUITTER) == 0)
    {
        this->listeClient.erase(socketClient);
        clientSuppr = true;
        traitementQuitter(socketClient);
    }
}

void ReceptionServeur::traitementSort(int socketClient)
{
    vector<string> listeNomSort = UsineSort::liste();
    Sort* sort = NULL;
    string final = SORT;
    final += SEPARATEUR_ELEMENT;
    for(int i = 0; i < listeNomSort.size(); i++)
    {
        sort = UsineSort::fabriqueSort(listeNomSort[i]);
        final += sort->getNom();
        final += SEPARATEUR_ELEMENT;
        final += sort->getDescription();
        final += SEPARATEUR_ELEMENT;
        final += to_string(sort->getElite());
        final += SEPARATEUR_ELEMENT;
        final += to_string(sort->getCoupManaParCase());
        final += SEPARATEUR_ELEMENT;
        final += to_string(sort->getDuree());
        final += SEPARATEUR_ELEMENT;
        final += to_string(sort->getPorteeMax());
        final += SEPARATEUR_ELEMENT;
        final += to_string(sort->getnombreCibleMax());
        final += SEPARATEUR_ELEMENT;
        final += to_string(sort->getPourcentageReussite());
        final += SEPARATEUR_ELEMENT;
        delete sort;
    }
    final += SEPARATEUR_COMMANDE;
    send(socketClient, final.c_str(), final.size(), 0);
}

void ReceptionServeur::traitementEquipe(int socketClient)
{
    string final = EQUIPE;
    vector<string> listeEquipe = this->partie->listeEquipe();
    for(int i = 0; i < listeEquipe.size(); i++)
    {
        final += SEPARATEUR_ELEMENT + listeEquipe[i];
    }
    final += SEPARATEUR_ELEMENT;
    final += SEPARATEUR_COMMANDE;
    send(socketClient, final.c_str(), final.size(), 0);
}

void ReceptionServeur::traitementNouveauJoueur(int socketClient)
{
    char *nom, *equipe, *sort;
    Joueur* joueur = NULL;
    vector<string> listeSortDemande(this->partie->getNombreSortParJoueur());
    string final;

    if(this->partie->getNombreDePlace() > this->partie->getNombreSortParJoueur())
    {
        final = ERREUR;
        final += SEPARATEUR_ELEMENT;
        final += "la partie est pleine";
        send(socketClient, final.c_str(), final.size(), 0);
        return;
    }

    nom = strtok(NULL, SEPARATEUR_ELEMENT);
    equipe = strtok(NULL, SEPARATEUR_ELEMENT);
    if(nom == NULL || equipe == NULL || strcmp(nom, CHAMPS_VIDE) == 0 || strcmp(equipe, CHAMPS_VIDE) == 0)
    {
        final = ERREUR;
        final += SEPARATEUR_ELEMENT;
        final += "nom de joueur ou d'equipe invalide";
        send(socketClient, final.c_str(), final.size(), 0);
        return;
    }
    for(int i = 0; i < this->partie->getNombreSortParJoueur(); i++)
    {
        sort = strtok(NULL, SEPARATEUR_ELEMENT);
        if(sort == NULL)
        {
            final = ERREUR;
            final += SEPARATEUR_ELEMENT;
            final += "nombre de sort non valide";
            final += SEPARATEUR_COMMANDE;
            send(socketClient, final.c_str(), final.size(), 0);
            return;
        }
        listeSortDemande[i] = sort;
    }
    try
    {
        joueur = this->partie->ajouterJoueur(nom, equipe, listeSortDemande);
    }
    catch(exception const& e)
    {
        final = ERREUR;
        final += SEPARATEUR_ELEMENT;
        final += e.what();
    final += SEPARATEUR_ELEMENT;
    final += SEPARATEUR_COMMANDE;
        send(socketClient, final.c_str(), final.size(), 0);
        return;
    }
    if(joueur == NULL)
    {
        final = ERREUR;
        final += SEPARATEUR_ELEMENT;
    final += SEPARATEUR_COMMANDE;
        send(socketClient, final.c_str(), final.size(), 0);
        return;
    }
    listeClient[socketClient] = new Client();
    listeClient[socketClient]->setJoueur(joueur);
    joueur->setSocket(socketClient);
    joueur->notifierCreation();
    joueur->notifierPartie(*partie);
}


void ReceptionServeur::traitementMessage(char *commande, string const& nomJoueurParlant)
{
    char* message = NULL;
    message = strtok(NULL, SEPARATEUR_ELEMENT);
    if(message == NULL)
    {
        return;
    }
    string final = MESSAGE;
    final += SEPARATEUR_ELEMENT;
    final += nomJoueurParlant;
    final += SEPARATEUR_ELEMENT;
    final += message;
    final += SEPARATEUR_ELEMENT;
    final += SEPARATEUR_COMMANDE;
    for(map<int, Client*>::iterator it = listeClient.begin(); it != listeClient.end(); it++)
    {
        if(it->second->getJoueur() != NULL)
        {
            send(it->first, final.c_str(), final.size(), 0);
        }
    }
}

void ReceptionServeur::traitementAction(char *commande, int socketClient)
{
    //Le joueur veut effectuer une action (nom du sort, origine, cible, cible , ...)
    //verifier si c'est à ce joueur de jouer ...
    char* nomSort = NULL, *origineX = NULL, *origineY = NULL, *tmp = NULL;
    int x = -1, y = -1, xCible = -1, yCible = -1, nombreCible = 0;
    Sort* sortAction = NULL;
    Action* action = NULL;
    Case *origine = NULL, *cibleTmp = NULL;
    vector<char*> listeCible;
    if(this->partie->estJoueurCourrant(listeClient[socketClient]->getJoueur()) == false)
    {
        GestionnaireLogger::ecrirMessage(TypeMessage::WARN, "N'est pas le joueur courant");
        return;
    }
    nomSort = strtok(NULL, SEPARATEUR_ELEMENT);
    origineX = strtok(NULL, SEPARATEUR_ELEMENT);
    origineY = strtok(NULL, SEPARATEUR_ELEMENT);
    if(nomSort == NULL || origineX == NULL || origineY == NULL)
    {
        GestionnaireLogger::ecrirMessage(TypeMessage::WARN, "Nom sort, X ou Y sont possiblement NULL");
        return;
    }
    x = atoi(origineX);
    y = atoi(origineY);
    if(x >= 0 && y >= 0)
    {
        origine = this->partie->getPlateau()->getCase(x, y);
    }
    sortAction = UsineSort::fabriqueSort(nomSort);
    if(sortAction == NULL)
    {
        GestionnaireLogger::ecrirMessage(TypeMessage::WARN, "Le sort requis n'existe pas");
        return;
    }
    if(listeClient[socketClient]->getJoueur()->possedeSort(nomSort) == false)
    {
        GestionnaireLogger::ecrirMessage(TypeMessage::WARN, "Le joueur n'a pas ce sort");
        return;
    }
    //Il y a deux coordonnées (x et y)
    for(int i = 0; i < sortAction->getnombreCibleMax()*2; i++)
    {
        tmp = strtok(NULL, SEPARATEUR_ELEMENT);
        if(tmp == NULL)
        {
            break;
        }
        nombreCible ++;
        listeCible.push_back(tmp);
    }
    //Pas de coordonnées valide. car une position n'a qu'un x ou qu'un y
    if((nombreCible%2) != 0)
    {
        GestionnaireLogger::ecrirMessage(TypeMessage::INFO, "Le nombre de coordonnée n'est pas valide");
        return;
    }
    action = new Action();
    nombreCible = nombreCible/2;
    sortAction->setProprietaire(listeClient[socketClient]->getJoueur());
    action->setSort(sortAction);
    action->setOrigine(origine);
    for(int i = 0; i < nombreCible; i++)
    {
        xCible = yCible = -1;
        xCible = atoi(listeCible[i*2]);
        yCible = atoi(listeCible[(i*2)+1]);
        if(xCible == -1 || yCible == -1)
        {
            GestionnaireLogger::ecrirMessage(TypeMessage::INFO, "Coordonnées invalides");
            return;
        }
        cibleTmp = this->partie->getPlateau()->getCase(xCible, yCible);
        if(cibleTmp == NULL)
        {
            GestionnaireLogger::ecrirMessage(TypeMessage::INFO, "Pas de case cible");
            return;
        }
        if(action->possedeCible(cibleTmp) == true)
        {
            GestionnaireLogger::ecrirMessage(TypeMessage::INFO, "Cible déjà visée");
            return;
        }
        action->ajouterCible(cibleTmp);
    }
    try
    {
        this->partie->effectuerAction(action, listeClient[socketClient]->getJoueur());
    }
    catch(invalid_argument e)
    {
        GestionnaireLogger::ecrirMessage(TypeMessage::INFO, e.what());
    }

    delete action;
    delete sortAction;
}

void ReceptionServeur::traitementQuitter(int socketClient)
{
    close(socketClient);
}

void ReceptionServeur::fermerServeur()
{
    close(this->socketServeur);
}

void ReceptionServeur::finirServeur()
{
    GestionnaireLogger::ecrirMessage(TypeMessage::INFO, "Destruction de la partie");
    delete this->partie;
    this->partie = NULL;
    GestionnaireLogger::ecrirMessage(TypeMessage::INFO, "Destruction des clients");
    for(map<int, Client*>::iterator it = listeClient.begin(); it != listeClient.end(); it++)
    {
        if(it->second != NULL)
        {
            it->second->setPartie(NULL);
            it->second->setJoueur(NULL);
            //Destuction du client
            delete it->second;
            it->second = NULL;
        }
        //Fermeture du descripteur de fichier
        close(it->first);
    }
    this->listeClient.clear();
    this->eteindre = true;
    GestionnaireLogger::ecrirMessage(TypeMessage::INFO, "Fin du serveur");
}

void ReceptionServeur::traitementInformationPartie(int socketClient)
{
    string final = INFORMATION_PARTIE;
    final += SEPARATEUR_ELEMENT;
    final += to_string(this->partie->getNombreDePlace());
    final += SEPARATEUR_ELEMENT;
    final += to_string(this->partie->nombreDeJoueur());
    final += SEPARATEUR_ELEMENT;
    final += to_string(this->partie->getNombreSortParJoueur());
    final += SEPARATEUR_ELEMENT;
    final += SEPARATEUR_COMMANDE;
    send(socketClient, final.c_str(), final.size(), 0);
}
