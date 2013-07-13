#ifndef ReceptionClient_h
#define ReceptionClient_h

#include <sys/select.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include "PartieClient.h"
#include "reseau/constanteReseau.h"

using namespace std;


class ReceptionClient
{
public:
    ReceptionClient(PartieClient* partie, string ip, int port);
    bool initialiserClient();
    bool miseEnEcoute();
    void envoyerCommandeSort();
    void envoyerCommandeEquipe();
    void envoyerCommandeNouveauJoueur(string const& nomJoueur, string const& nomEquipe, list<string> &listeSort);


private:
    void testerSelection(fd_set readfd);
    void traitementCommande(char* commande);
    void traitementInfoCase();
    void traitementInfoJoueur();
    void traitementInfoSort();
    void traitementTourDe();
    void traitementSort();
    void traitementEquipe();
    int port;
    string ip;
    int socketClient;
    bool eteindre;
    PartieClient *partie;
};

#endif
