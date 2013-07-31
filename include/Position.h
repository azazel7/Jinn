#ifndef Position_h
#define Position_h

#include <map>
#include <iostream>
#include <cmath>

using namespace std;

/**
 * @brief The Position class
 */
class Position
{

public:
    /**
     * @brief fabriquePosition
     *  Permet d'obtenir un pointeur vers une position en fonction de ses coordonnée
     * @param x l'absice
     * @param y l'ordonnée
     * @return Un pointeur vers un objet position
     */
    static Position* fabriquePosition(int x, int y);
    /**
     * @brief codePosition
     *  Calcule le code d'une position en fonction de ses coordonnées
     * @param x l'abscice
     * @param y l'ordonnée
     * @return  le code de la position
     */
    static int codePosition(int x, int y);
    /**
     * @brief getPosition
     *   Permet d'obtenir une position par son code
     * @param code le code de la position
     * @return Un pointeur vers une position
     */
    static Position* getPosition(int code);
    /**
     * @brief getX
     * renvois l'abscice d'une position
     * @return l'absice de la position
     */
	int getX() const;
    /**
     * @brief getY
     * renvois l'ordonnée d'une position
     * @return l'ordonnée de la position
     */
    int getY() const;
    /**
     * @brief operator ==
     *  Operateur de comparaison
     * @param a La position à comparer
     * @return true si les deux positions sont égales
     */
    bool operator ==(Position const& a) const;
    /**
     * @brief distance
     * Calcule la distance entre deux positions
     * @param a Une position
     * @param b une autre position
     * @return une distance entière arrondi au supérieur
     */
    static int distance(Position const& a, Position const& b);
    /**
     * @brief libererPositions
     * Libére toutes les positions créées.
     */
    static void libererPositions();

private:
    /**
     * @brief Position
     *  Constructeur
     * @param x abscice
     * @param y ordonnée
     */
	Position(int x, int y);
	int x;
	int y;
	static map<int, Position*> listePosition;

};
/**
 * @brief operator <<
 * Surcharge de l'operateur de flux pour mieux afficher une position
 * @param flux
 *  Le flux dans lequel on ecrit
 * @param pos
 *  La position
 * @return Un flux
 */
ostream& operator<<( ostream &flux, Position const& pos);
#endif // Position_h
