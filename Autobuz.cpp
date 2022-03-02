#include "Autobuz.h"
Autobuz::Autobuz()
{
    //id=id_counter++;
}
Autobuz::Autobuz(long int k, int a, bool d, int nr):Masina(k,a,d)
{
    nr_locuri=nr;
}
Autobuz::Autobuz(const Autobuz &a):Masina(a.km,a.an_fabr,a.diesel)
{
    nr_locuri=a.nr_locuri;
}
Autobuz::~Autobuz()
{
    ;
}
string Autobuz::getType()
{
    return "Autobuz";
}
int Autobuz::getID()
{
    return id;
}
long int Autobuz::getKm()
{
    return km;
}
int Autobuz::get_an_fabr()
{
    return an_fabr;
}
bool Autobuz::getDiesel()
{
    return diesel;
}
int Autobuz::getTimp()
{
    return timp;
}
void Autobuz::setTimp()
{
    timp=rand()%10+1;
}
void Autobuz::set_masina(long int km2, int an2, char d, int nr2)
{
    km=km2;
    an_fabr=an2;
    if(d=='Y') diesel=true;
    if(d=='N') diesel=false;
    nr_locuri=nr2;
}
int Autobuz::val_polita()
{
    int vechime=2021-an_fabr;
    if(diesel==true )
    {
        if(km>=200000)
            return vechime*200+1000+1000;
        if(km<100000)
            return vechime*200+1000;
        if(km>=100000 && km<200000)
            return vechime*200+1500;
    }
    else
    {
        if(km>=200000)
            return vechime*200+1000;
        if(km>=100000 && km<200000)
            return vechime*200+500;
    }
    return vechime*200;
}
float Autobuz::val_polita_discount()
{
    float aux;
    int vechime=2021-an_fabr;
    if(diesel==true )
    {
        if(km>=200000)
        {
            aux=(float)(vechime*200+1000+1000);
            return aux-0.1*aux;
        }
        if(km<100000)
        {
            aux=(float)(vechime*200+1000);
            return aux-0.1*aux;
        }
        if(km>=100000 && km<200000)
        {
            aux=(float)(vechime*200+1500);
            return aux-0.1*aux;
        }

    }
    else
    {
        if(km>=200000)
        {
            aux=(float)(vechime*200+1000);
            return aux-0.1*aux;
        }
        if(km>=100000 && km<200000)
        {
            aux=(float)(vechime*200+500);
            return aux-0.1*aux;
        }
    }
    aux=(float)vechime*200;
    return aux-0.1*aux;
}
void Autobuz::afisare(ostream &out)
{
    out<<getID()<<" - "<<this->getType()<<" - "<<km<<"km"<<" - "<<an_fabr<<"(fabricatie) - ";
    if(diesel) out<<"Diesel - ";
    else out<<"Benzina - ";
    out<<nr_locuri<<"(nr. locuri) "<<timp<<"(ETA)\n";
//    out<<getID()<<" "<<this->getType()<<" "<<km<<" "<<an_fabr<<" ";
//    if(diesel) out<<true<<" ";
//    else out<<false<<" ";
//    out<<nr_locuri<<" "<<endl;

}


