#pragma once
#include "Angajat.h"

class Director: public Angajat
{
public:
    Director()
    {
        ID=id_count++;
        coeficient=2;
    }
    Director(string nume2, string prenume2, Data data_n2, Data data_a2);
    Director(Director &d);
    ~Director() {};

    string getType();
    float getSalariu();
    void afisare(ostream &out);
    void citire(istream &in);
    void set_angajat(string nume2, string prenume2, Data data_n2, Data data_a2);
    int ani_vechime();
};
