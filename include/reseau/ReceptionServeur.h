#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stropts.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <string.h>
#include "Partie.h"
#include "UsineSort.h"

#define SEPARATEUR_ELEMENT ";"
#define SEPARATEUR_SOUS_ELEMENT "#"
#define ACTION "action"
#define MESSAGE "message"
#define NOUVEAU_JOUEUR "joueur"
#define FIN_TOUR "fintour"
#define EQUIPE "equipe"
#define SORT "sort"

class ReceptionServeur
{
    public:
        ReceptionServeur(Partie* partie, string ip = "0.0.0.0", int port = 14790);
        bool initialiserServeur();
        void miseEnEcoute();

    private:
        void testerSelectionClient(fd_set& readfd);
        void testerSelectionServeur(fd_set& readfd);
        int maximunFileDescriptor();
        void traitementJoueur(char *commande, int socketClient);
        void traitementClient(char *commande, int socketClient);
        void traitementSort(int socketClient);
        void traitementEquipe(int socketClient);
        Partie *partie;
        int port;
        string ip;
        int socketServeur;
        map<int, Joueur*> listeClient;
};
