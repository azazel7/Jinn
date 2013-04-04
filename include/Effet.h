#ifndef Effet_h
#define Effet_h


class Effet {

 public:

    Effet(int type, int valeur);

    int getType();
    int getValeur();

 private:
    int typeEffet;
    int valeurEffet;

};

#endif // Effet_h
