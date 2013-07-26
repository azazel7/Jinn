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
#include "ui/DessinateurPartie.h"

using namespace std;

class DessinateurPartie;

class ReceptionClient
{
public:
    ReceptionClient(PartieClient* partie, string ip, int port);
    bool initialiserClient();
    bool miseEnEcoute();
    void envoyerCommandeSort();
    void envoyerCommandeEquipe();
    void envoyerCommandeNouveauJoueur(string const& nomJoueur, string const& nomEquipe, list<string> &listeSort);
    void envoyerCommandeMessage(string const& message);
    void envoyerCommandeAction(string const& sort, Position* origine, list<Position*> cible);
    void envoyerCommandeQuitter();
    void envoyerCommandeFinTour();
    void envoyerCommandeInformationPartie();

    DessinateurPartie* getDessinateur();
    void setDessinateur(DessinateurPartie* nouveauDessinateur);

private:
    bool testerSelection(fd_set readfd);
    void traitementCommande(char* commande);
    void traitementInfoCase();
    string traitementInfoJoueur();
    void traitementInfoSort();
    void traitementTourDe();
    void traitementSort();
    void traitementEquipe();
    void traitementNouveauJoueur();
    void traitementInfoPartie();
    void traitementMessage();
    void traitementFinTourPartie();
    void traitementMortJoueur();
    void traitementQuitterPartie();
    void traitementFinPartie();
    void traitementReussiteSort();
    int port;
    string ip;
    int socketClient;
    bool eteindre;
    PartieClient *partie;
    DessinateurPartie* dessinateur;
};

#endif
