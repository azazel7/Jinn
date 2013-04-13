#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "Partie.h"

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
        Partie *partie;
        int port;
        string ip;
        int socketServeur;
        map<int, Joueur*> listeClient;
};
