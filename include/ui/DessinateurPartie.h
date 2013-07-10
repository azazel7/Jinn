#ifndef DessinateurPartie_h
#define DessinateurPartie_h

#include "PartieClient.h"

class DessinateurPartie
{
    public:
        DessinateurPartie(PartieClient* partie);
        void dessinerPartie();

    private:
        PartieClient* partie;

};
#endif
