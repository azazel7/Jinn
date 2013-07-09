#include "reseau/client/ReceptionClient.h"

ReceptionClient::ReceptionClient(PartieClient* partie, string ip, int port = 14790)
{
    this->partie = partie;
    this->port = port;
    this->ip = ip;
    this->eteindre = false;
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
        }
        //Erreur
        else if(octetRecus < 0)
        {
            GestionnaireLogger::ecrirMessage(TypeMessage::ERROR, "Erreur de lecture du nombre d'octet par ioctl");
        }
        data = (char*)malloc(sizeof(char)*octetRecus);
        if(data == NULL)
        {
            GestionnaireLogger::ecrirMessage(TypeMessage::FATAL, "Erreur malloc");
            exit(-1);
        }

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
        this->traitementCommande(data);
        free(data);
    }

}

void ReceptionClient::traitementCommande(char* commande)
{
    char *action = NULL;
    action = strtok (commande, SEPARATEUR_ELEMENT);
    while(action != NULL)
    {
        if(strcmp(action, MESSAGE) == 0)
        {

        }
        else if(strcmp(action, INFORMATION_CASE) == 0)
        {
            traitementInfoCase();
        }
        else if(strcmp(action, INFORMATION_JOUEUR) == 0)
        {

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
        if(argument[i] == NULL)
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
        caseCible->setProprietaire(this->partie->getJoueur(argument[2]));
    }
}

void ReceptionClient::traitementInfoJoueur()
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
            return;
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
}

void ReceptionClient::traitementInfoSort()
{
    char* argument[6] = {NULL};
    Sort* sort = NULL;
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

    //TODO Comment ajouter un sort ? Créer une fonction d'accés au sort par sont id et sa position
}
