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
#include <map>
#include "Action.h"
#include "Partie.h"
#include "UsineSort.h"
#include "Case.h"
#include "reseau/serveur/Client.h"
#include "logger/GestionnaireLogger.h"
#include "logger/LoggerFileDescriptor.h"
#include "reseau/constanteReseau.h"
#include <boost/algorithm/string.hpp>

class Partie;
class Client;

class ReceptionServeur
{
public:
    ReceptionServeur(Partie* partie, string ip = "0.0.0.0", int port = 14790);
    bool initialiserServeur();
    void miseEnEcoute();
    void finirServeur();
    void fermerServeur();

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
    void traitementQuitter(int socketClient);
    Partie *partie;
    int port;
    string ip;
    int socketServeur;
    map<int, Client*> listeClient;
    bool eteindre;
};

#endif // ReceptionServeur_h
