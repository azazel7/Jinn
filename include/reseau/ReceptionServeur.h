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
#include "reseau/Client.h"
#include "logger/GestionnaireLogger.h"
#include "logger/LoggerFileDescriptor.h"

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
//TODO les action d'un joueur ne se passe plus sur la partie, mais sur sa partie
//Relatif au jeu
#define CHANGEMENT_CASE_PROPRIAITAIRE "chgcasepropri"
#define INFORMATION_PARTIE "informationpartie"
#define TOUR_DE "tourde"
#define MORT "mort"
#define DEMARAGE_PARTIE "demaragepartie"
#define FIN_PARTIE "finpartie"
#define QUITTER_PARTIE "quitterpartie"
#define INFORMATION_SORT "infosort"
#define INFORMATION_JOUEUR "infojoueur"
#define INFORMATION_CASE "infocase"

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
