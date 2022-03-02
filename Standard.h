#pragma once
#include "Masina.h"
class Standard: public Masina
{
    string transmisie; //automat/manual
public:
    Standard();
    Standard(long int,int,bool,string);
    Standard(const Standard &);
    ~Standard() {};

    string getType();
    int getID();
    long int getKm();
    int get_an_fabr();
    bool getDiesel();
     int getTimp();

    void set_masina(long int,int,char,string);
    void afisare(ostream &out);
    void citire(istream &in);
    void setTimp();

    int val_polita();
    float val_polita_discount();
};
