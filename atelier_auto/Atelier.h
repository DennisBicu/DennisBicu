#include "Garaj.h"
class Atelier
{
    string status="inchis";
    vector<Garaj> garaje;
    vector<Angajat*> angajati;
    //list<Masina*> masini;
    queue<Masina*> waiting_q;
    queue<Masina*> left_out; ///pentru masini ce nu prind loc pana la umplerea garajelor
public:
    Atelier();
    Atelier(vector<Angajat*>a2);
    Atelier(const Atelier &);
    ~Atelier();

    void setStatus();
    string checkStatus();

    void setAngajati(vector<Angajat*> a2);
    vector<Angajat*> getAngajati();

    //void setMasini(list<Masina*> m2);
    //list<Masina*> getMasini();

    void addToWait_q(Masina*);
    void addToLeft_out(Masina *);
    Masina* delFromWait_q();
    void printWait_q();

    void creareGaraje();
    bool requestAngajat(Masina *m, int id2);
};
