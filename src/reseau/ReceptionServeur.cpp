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
    }
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
                //On supprime l'entrée
                it = listeClient.erase(it);
            }
            else if(octetLus != octetRecus) //Curieuse affaire
            {
                //TODO Bizarre bizarre
            }

            //TODO traitement d'un client
            if(it->second == NULL)
            {
                //TODO Traitement d'un joueur potentiel
                cout << "Potentiel client" << endl;
                this->traitementClient(data, it->first);
            }
            else
            {
                //TODO Traitement d'un joueur
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
    }
    else if(strcmp(action, ACTION) == 0)
    {
        //Le joueur veut effectuer une action (nom du sort, origine, cible, cible , ...)
        //verifier si c'est à ce joueur de jouer ...
    }
    else if(strcmp(action, FIN_TOUR) == 0)
    {
        //Le joueur declare son tour finis
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
    cout << action << endl;
    if(strcmp(action, NOUVEAU_JOUEUR) == 0)
    {
        //Le joueur veut s'inscrire (nom, equipe, liste de sort(nom, pour l'usine)
        traitementJoueur(NULL, socketClient);
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

void ReceptionServeur::traitementNouveauJoueur(char* data, int socketClient)
{
        char *nom, *equipe, *sort;
        Joueur* joueur = NULL;
        vector<string> listeSortDemande(this->partie->getNombreSortParJoueur());

        nom = strtok(NULL, SEPARATEUR_ELEMENT);
        equipe = strtok(NULL, SEPARATEUR_ELEMENT);
        if(nom == NULL || equipe == NULL)
        {
                //TODO envoyer erreur
        }
        for(int i = 0; i < this->partie->getNombreSortParJoueur(); i++)
        {
                sort = strtok(NULL, SEPARATEUR_ELEMENT);
                if(sort == NULL)
                {
                        //TODO envoyer erreur
                        return;
                }
                listeSortDemande[i] = sort;
        }
        joueur = this->partie->ajouterJoueur(nom, equipe, listeSortDemande);
        if(joueur == NULL)
        {
            //TODO envoyer une erreur
        }
        //TODO, renvoyer le joueur
}
