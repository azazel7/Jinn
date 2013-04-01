#ifndef Serveur_h
#define Serveur_h

#include <iostream>
using namespace std;

class Partie;

class Serveur {

 public:

    Serveur(int port, string ip);

    virtual void demarrageServeur();

 public:
    int port;
    string ip;

 public:

    /**
     * @element-type Partie
     */
    Partie *myPartie;
};

#endif // Serveur_h
