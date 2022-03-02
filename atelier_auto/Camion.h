#pragma once
#include "Masina.h"
class Camion: public Masina{
    int tonaj;
public:
    Camion();
    Camion(long int, int, bool, int);
    Camion(const Camion &);
    ~Camion();

    string getType();
    int getID();
    long int getKm();
    int get_an_fabr();
    bool getDiesel();
     int getTimp();

    void set_masina(long int,int,char,int);
    void afisare(ostream &out);
    void setTimp();

    int val_polita();
    float val_polita_discount();
};
