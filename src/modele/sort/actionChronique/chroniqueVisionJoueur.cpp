#include "sort/actionChronique/chroniqueVisionJoueur.h"

void ChroniqueVisionJoueur::effectuerActionChronique(Case &cible, Sort *sortExecutant)
{
    Joueur* proprio = cible.getProprietaire();
    if(proprio == NULL)
    {
        return;
    }
    sortExecutant->getProprietaire()->notifierJoueur(*proprio, false);
}
