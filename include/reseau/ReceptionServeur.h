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

//Relatif au jeu
#define PERTE_CASE "pertecase"
#define INFORMATION_PARTIE "informationpartie"

class Partie;

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
        map<int, Joueur*> listeClient;
};

#endif // ReceptionServeur_h
