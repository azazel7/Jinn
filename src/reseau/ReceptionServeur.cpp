#include "reseau/ReceptionServeur.h"

ReceptionServeur::ReceptionServeur(Partie* partie, string ip, int port)
{
    this->partie = partie;
    this->ip = ip;
    this->port = port;
}

bool ReceptionServeur::initialiserServeur()
{
    struct sockaddr_in sin;
    //Creation d'une socket en TCP/IP usant d'un protocole libre
    this->socketServeur = socket(AF_INET, SOCK_STREAM, 0);
    //On écoute sur le port fournis et sur toutes l'adresse ip fournis
    sin.sin_addr.s_addr = inet_addr(this->ip.c_str());
    sin.sin_family = AF_INET;
    sin.sin_port = htons(this->port);
    //On associe la socket au contexte d'adressage
    if(bind(this->socketServeur, (struct sockaddr*) &sin, sizeof(sin)) < 0)
    {
        return false;
    }
    //On mes en ecoute la socket
    if(listen(this->socketServeur, 5) < 0)
    {
        return false;
    }
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
    while(true)
    {
        /* Si une erreur est survenue au niveau du select */
        FD_ZERO(&readfs);
        this->remplirSelection(readfs);
        cout << "Attente select " << this->socketServeur << endl;
        if(select(this->maximunFileDescriptor() + 1, &readfs, NULL, NULL, NULL) < 0)
        {
            perror("[-] select ReceptionServeur");
            exit(-1);
        }
        cout << "Fin select" << endl;
        //Priorité au client qui joue on avise ensuite pour les nouvelles connexions
        this->testerSelectionClient(readfs);
        this->testerSelectionServeur(readfs);
        if (this->partie->nombreDeJoueur() == this->partie->getNombreDePlace())
        {
            //TODO demarer la partie
        }
    }
}

void ReceptionServeur::remplirSelection(fd_set& readfd)
{
    for(map<int, Joueur*>::iterator it = listeClient.begin(); it != listeClient.end(); it++)
    {

        FD_SET(it->first, &readfd);
    }
        FD_SET(this->socketServeur, &readfd);
}
void ReceptionServeur::testerSelectionClient(fd_set& readfd)
{
    for(map<int, Joueur*>::iterator it = listeClient.begin(); it != listeClient.end(); it++)
    {
        if(FD_ISSET(it->first, &readfd))
        {
            char *data = NULL;
            int octetRecus = 0;
            int octetLus = 0;
            //On calcule combien il y a d'octet à lire
            ioctl(it->first, FIONREAD, &octetRecus);

            //On alloue en conséquence
            data = (char*)malloc(sizeof(char)*octetRecus);
            if(data == NULL)
            {
                perror("[-] malloc");
                exit(1);
            }
            //On lit les données
            octetLus = recv(it->first, data, octetRecus, 0);
            if( octetLus < 0)
            {
                perror("[-] recv");
                exit(1);
            }
            else if (octetLus == 0)//Deconnexion du client
            {
                //On retire la socket de la séléction
                FD_CLR(it->first, &readfd);
                //On ferme la socket
                close(it->first);
                if(it->second != NULL)
                {
                        //Si c'était un joueur on le retire de la partie
                        this->partie->retirerJoueur(it->second);
                }
                //On supprime l'entrée
                it = listeClient.erase(it);
            }
            else if(octetLus != octetRecus) //Curieuse affaire
            {
                continue;
            }

            if(it->second == NULL)
            {
                cout << "Potentiel client" << endl;
                this->traitementClient(data, it->first);
            }
            else
            {
                cout << "Joueur" << endl;
                this->traitementJoueur(data, it->first);
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
        cout << "Nouvelle connexion" << endl;
        int csock;
        struct sockaddr_in csin;
        int crecsize = sizeof csin;
        //On l'accept en tant que potentiel nouveau joueur
        csock = accept(this->socketServeur, (struct sockaddr *) &csin, (socklen_t*)&crecsize);
        listeClient[csock] = NULL;
        //On l'ajoute à la selection
        FD_SET(csock, &readfd);
    }
}

int ReceptionServeur::maximunFileDescriptor()
{
    int retour = this->socketServeur;
    for(map<int, Joueur*>::iterator it = listeClient.begin(); it != listeClient.end(); it++)
    {
        if(it->first > this->socketServeur)
        {
            retour = it->first;
        }
    }
    return retour;
}

void ReceptionServeur::traitementJoueur(char *commande, int socketClient)
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
        this->traitementMessage(commande, listeClient[socketClient]->getNom());
    }
    else if(strcmp(action, ACTION) == 0)
    {
        //Le joueur veut effectuer une action (nom du sort, origine, cible, cible , ...)
        //verifier si c'est à ce joueur de jouer ...
    }
    else if(strcmp(action, FIN_TOUR) == 0)
    {
        //Le joueur declare son tour finis
        Action *coup = new Action();
        coup->setOrigine(NULL);
        coup->setSort(NULL);
        this->partie->effectuerAction(coup, this->listeClient[socketClient]);
        delete coup;
    }
}

void ReceptionServeur::traitementClient(char *commande, int socketClient)
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
}

void ReceptionServeur::traitementSort(int socketClient)
{
    vector<string> listeNomSort = UsineSort::liste();
    Sort* sort = NULL;
    string final = SORT;
    for(int i = 0; i < listeNomSort.size(); i++)
    {
        sort = UsineSort::fabriqueSort(listeNomSort[i]);
        final += SEPARATEUR_ELEMENT + sort->getNom() + SEPARATEUR_SOUS_ELEMENT + sort->description();
        delete sort;
    }
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
    if(nom == NULL || equipe == NULL)
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
        send(socketClient, final.c_str(), final.size(), 0);
        return;
    }
    if(joueur == NULL)
    {
        final = ERREUR;
        final += SEPARATEUR_ELEMENT;
        send(socketClient, final.c_str(), final.size(), 0);
        return;
    }
    listeClient[socketClient] = joueur;
    joueur->setSocket(socketClient);
    joueur->notifierCreation();
    joueur->notifierPartie(*partie);
}


void ReceptionServeur::traitementMessage(char *commande, string const& nomJoueurParlant)
{
    cout << "un message" << endl;
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
    for(map<int, Joueur*>::iterator it = listeClient.begin(); it != listeClient.end(); it++)
    {
        if(it->second != NULL)
        {
                send(it->first, final.c_str(), final.size(), 0);
        }
    }
}
