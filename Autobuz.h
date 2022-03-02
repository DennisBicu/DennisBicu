#pragma once
#include "Masina.h"
class Autobuz: public Masina
{
    int nr_locuri;
public:
    Autobuz();
    Autobuz(long int, int, bool, int);
    Autobuz(const Autobuz &);
    ~Autobuz();

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
