#include "Angajat.h"
class Mecanic: public Angajat
{
public:
    Mecanic()
    {
        ID=id_count++;
        coeficient=1.5;
    }
    Mecanic(string nume2, string prenume2, Data data_n2, Data data_a2);
    Mecanic(Mecanic &d);
    ~Mecanic() {};

    string getType();
    float getSalariu();
    void afisare(ostream &out);
    void citire(istream &in);
    void set_angajat(string nume2, string prenume2, Data data_n2, Data data_a2);
    int ani_vechime();
};
