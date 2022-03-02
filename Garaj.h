#pragma once
#include "Data.h"
#include "Director.h"
#include "Mecanic.h"
#include "Asistent.h"
#include "Standard.h"
#include "Autobuz.h"
#include "Camion.h"
#include <queue>
#include <vector>
class Garaj
{
   // Angajat *ang; ///la fiecare garaj lucreaza un angajat
    int id_angajat; //id-ul angajatului care lucreaza la acest garaj;
    queue<Masina*> qmasini; ///care ia in primire masini in coada
    //vector<Masina*> mas;
public:
    Garaj();
    Garaj(int id2, queue<Masina*>mas2);
    Garaj(const Garaj& );
    ~Garaj();

    //bool checkAngajat();
    unsigned int checkSize();
    bool checkRoom4Standard();
    bool checkRoom4Bus();
    bool checkRoom4Camion();
    bool checkFULL();
    void AddCar(Masina* m2);
    void deleteCar();
    void deleteMasini();
    queue<Masina*> getMasiniGaraj();
    //void setAngajat(Angajat* a2);
    int getID_angajat();
    void setID_angajat(int);
    void afisare_qgaraj();
};
