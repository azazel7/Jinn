#ifndef ReceptionServeur_h
#define ReceptionServeur_h
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stropts.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <string.h>
#include "Action.h"
#include "Partie.h"
#include "UsineSort.h"
#include "Case.h"
#include "reseau/Client.h"

//relatif au serveur
#define SEPARATEUR_ELEMENT ";"
#define SEPARATEUR_SOUS_ELEMENT "#"
#define ACTION "action"
#define MESSAGE "message"
#define NOUVEAU_JOUEUR "joueur"
#define FIN_TOUR "fintour"
#define EQUIPE "equipe"
#define SORT "sort"
#define ERREUR "erreur"
#define QUITTER "quitter"
//TODO ajouter traitement de quitter

//Relatif au jeu
#define CHANGEMENT_CASE_PROPRIAITAIRE "chgcasepropri"
#define INFORMATION_PARTIE "informationpartie"
#define TOUR_DE "tourde"
#define MORT "mort"
#define DEMARAGE_PARTIE "demaragepartie"
#define FIN_PARTIE "finpartie"
#define QUITTER_PARTIE "quitterpartie"

class Partie;
class Client;

class ReceptionServeur
{
    public:
        ReceptionServeur(Partie* partie, string ip = "0.0.0.0", int port = 14790);
        bool initialiserServeur();
        void miseEnEcoute();

    private:
        void remplirSelection(fd_set& readfd);
        void testerSelectionClient(fd_set& readfd);
        void testerSelectionServeur(fd_set& readfd);
        int maximunFileDescriptor();
        void traitementJoueur(char *commande, int socketClient);
        void traitementClient(char *commande, int socketClient);
        void traitementAction(char *commande, int socketClient);
        void traitementSort(int socketClient);
        void traitementEquipe(int socketClient);
        void traitementNouveauJoueur(int socketClient);
        void traitementMessage(char *commande, const string &nomJoueurParlant);
        Partie *partie;
        int port;
        string ip;
        int socketServeur;
        map<int, Client*> listeClient;
};

#endif // ReceptionServeur_h
