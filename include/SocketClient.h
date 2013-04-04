#ifndef SocketClient_h
#define SocketClient_h

#include <iostream>

using namespace std;

class SocketClient
{

public:

	SocketClient(string ip, int port);

	virtual void connexion();

	virtual string lireChaine(int finSequence, int timeout);

	virtual bool ecrireChaine(string chaine);

	virtual bool estConnecte();

public:
	int socket;
	int port;
	string ip;
};

#endif // Classe utiles_SocketClient_h
