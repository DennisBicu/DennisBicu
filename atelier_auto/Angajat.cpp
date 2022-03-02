#include "Angajat.h"
int Angajat::id_count=1;
Angajat::~Angajat()
{
    ;
}
int Angajat::getID()
{
    return ID;
}
string Angajat::getNume()
{
    return nume;
}
string Angajat::getPrenume()
{
    return prenume;
}
Data Angajat::getData_n()
{
    return data_nastere;
}
Data Angajat::getData_a()
{
    return data_angajare;
}
