#pragma once
#include "Data.h"
#include <string>
#include <list>
class Angajat
{
protected:
    int ID;
    static int id_count;
    string nume;
    string prenume;
    Data data_nastere;
    Data data_angajare;
    float coeficient;
public:
//    Angajat()
//    {
//        ID=id_count++;
//    }
//    Angajat(string nume2, string prenume2, Data data_n2, Data data_a2, int coef)
    virtual ~Angajat()=0;
    virtual string getType()=0;
    virtual float getSalariu()=0;
    virtual void afisare(ostream &out)=0;
    virtual void citire(istream &in)=0;
    virtual void set_angajat(string nume2, string prenume2, Data data_n2, Data data_a2)=0;
    virtual int ani_vechime()=0;
    int getID();
    string getNume();
    string getPrenume();
    Data getData_n();
    Data getData_a();
};
