#include "Camion.h"
Camion::Camion()
{
    //id=id_counter++;
}
Camion::Camion(long int k, int a, bool d, int t):Masina(k,a,d)
{
    tonaj=t;
}
Camion::Camion(const Camion &a):Masina(a.km,a.an_fabr,a.diesel)
{
    tonaj=a.tonaj;
}
Camion::~Camion()
{
    ;
}
string Camion::getType()
{
    return "Camion";
}
int Camion::getID()
{
    return id;
}
long int Camion::getKm()
{
    return km;
}
int Camion::get_an_fabr()
{
    return an_fabr;
}
bool Camion::getDiesel()
{
    return diesel;
}
int Camion::getTimp()
{
    return timp;
}
void Camion::setTimp()
{
    timp=rand()%10+1;
}
void Camion::set_masina(long int km2, int an2, char d, int t)
{
    km=km2;
    an_fabr=an2;
    if(d=='Y') diesel=true;
    if(d=='N') diesel=false;
    tonaj=t;
}
int Camion::val_polita()
{
    int vechime=2021-an_fabr;
    if(km>=800000) return vechime*300+700;
    else return vechime*300;
}
float Camion::val_polita_discount()
{
    float aux;
    int vechime=2021-an_fabr;

    if(km>=800000)
    {
         aux=(float)(vechime*300+700);
         return aux-0.15*aux;
    }
    else
    {
        aux=(float)vechime*300;
        return aux-0.15*aux;
    }
}

void Camion::afisare(ostream &out)
{
    out<<getID()<<" - "<<this->getType()<<" - "<<km<<"km"<<" - "<<an_fabr<<"(fabricatie) - ";
    if(diesel==true) out<<"Diesel - ";
    else out<<"Benzina - ";
    out<<tonaj<<"tone "<<timp<<"(ETA)\n";
//    out<<getID()<<" "<<this->getType()<<" "<<km<<" "<<an_fabr<<" ";
//    if(diesel) out<<true<<" ";
//    else out<<false<<" ";
//    out<<tonaj<<" "<<endl;

}


