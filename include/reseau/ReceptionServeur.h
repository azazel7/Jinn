#include <Partie.h>

class ReceptionServeur
{
    public:
        ReceptionServeur(Partie* partie, string ip = "0.0.0.0", int port = 14790);
        void miseEnEcoute();

    private:
        Partie *partie;
        int port;
        string ip;
};
