#pragma once
#include "Angajat.h"
class Asistent: public Angajat
{
public:
    Asistent()
    {
        ID=id_count++;
        coeficient=1;
    }
    Asistent(string nume2, string prenume2, Data data_n2, Data data_a2);
    Asistent(Asistent &d);
    ~Asistent() {};

    string getType();
    float getSalariu();
    void afisare(ostream &out);
    void citire(istream &in);
    void set_angajat(string nume2, string prenume2, Data data_n2, Data data_a2);
    int ani_vechime();
};
