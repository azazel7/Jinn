#include "Equipe.h"

Equipe::Equipe(string nom)
{
    this->nom = nom;
    this->indexJoueurCourrant = 0;
    this->nombreJoueur = 0;
}

string Equipe::getNom()
{
    return this->nom;
}

void Equipe::setNom(string nom)
{
    this->nom = nom;
}

int  Equipe::getNombreJoueur()
{
    return this->nombreJoueur;
}

void  Equipe::setNombreJoueur(int nombre)
{
    if(nombre >= 0)
    {
        this->nombreJoueur = nombre;
    }
}

int  Equipe::getIndexCourrant()
{
    return this->indexJoueurCourrant;
}

void  Equipe::setIndexCourrant(int newIndex)
{
    if(newIndex >= 0)
    {
        this->indexJoueurCourrant = newIndex;
    }
}

void Equipe::tournerIndex()
{
        this->indexJoueurCourrant = (this->indexJoueurCourrant + 1)% this->nombreJoueur;
}
