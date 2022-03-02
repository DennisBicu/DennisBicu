#include "Masina.h"
int Masina::id_counter=1;

Masina::~Masina()
{
    ;
}
Masina::Masina()
{
    id=id_counter++;
}
Masina::Masina(long int km2, int an2, bool d2)
{
    id=id_counter++;
    km=km2;
    an_fabr=an2;
    diesel=d2;
}
Masina::Masina(const Masina &m)
{
    id=id_counter++;
    km=m.km;
    an_fabr=m.an_fabr;
    diesel=m.diesel;
}
int Masina::getID()
{
    return id;
}
long int Masina::getKm()
{
    return km;
}
int Masina::get_an_fabr()
{
    return an_fabr;
}
bool Masina::getDiesel()
{
    return diesel;
}
int Masina::getTimp()
{
    return timp;
}
