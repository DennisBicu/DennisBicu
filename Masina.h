#pragma once
#include <iostream>
#include <string>
using namespace std;
class Masina
{
protected:
    int id;
    static int id_counter;
    long int km;
    int an_fabr;
    bool diesel;
    int timp=0;
public:
    virtual string getType()=0;
    virtual void afisare(ostream &out)=0;
    //virtual void citire(istream &in)=0;
    virtual int val_polita()=0;
    virtual float val_polita_discount()=0;
    //virtual void set_masina(long int,int,char)=0;
    virtual ~Masina()=0;
    virtual void setTimp()=0;

    Masina();
    Masina(long int, int, bool);
    Masina(const Masina &);

    int getID();
    long int getKm();
    int get_an_fabr();
    bool getDiesel();
    int getTimp();

};
