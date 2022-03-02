#include "Standard.h"
Standard::Standard()
{
    //id_counter++;
}
Standard::Standard(long int km2, int an2, bool d2, string t2):Masina(km2,an2,d2)
{
    transmisie=t2;
}
Standard::Standard(const Standard &s):Masina(s.km,s.an_fabr,s.diesel)
{
    transmisie=s.transmisie;
}
string Standard::getType()
{
    return "Standard";
}
int Standard::getID()
{
    return id;
}
long int Standard::getKm()
{
    return km;
}
int Standard::get_an_fabr()
{
    return an_fabr;
}
bool Standard::getDiesel()
{
    return diesel;
}
int Standard::getTimp()
{
    return timp;
}
void Standard::setTimp()
{
    timp=rand()%10+1;
}
void Standard::set_masina(long int km2, int an2, char q, string t2)
{
    if(q=='Y')
        diesel=true;
    if(q=='N')
        diesel=false;
    km=km2;
    an_fabr=an2;
    transmisie=t2;
}
int Standard::val_polita()
{
    int vechime=2021-an_fabr;
    if(diesel==true && km>=200000)
    {
        return vechime*100+500+500;
    }
    if(diesel==true && km<200000)
        return vechime*100+500;
    if(diesel==false && km>=200000)
        return vechime*100+500;
    return vechime*100;
}
float Standard::val_polita_discount()
{
    int vechime=2021-an_fabr;
    float aux;
    if(diesel==true && km>=200000)
    {
        aux=(float)(vechime*100+500+500);
        return aux-0.05*aux;
    }
    if(diesel==true && km<200000)
    {
        aux=(float)(vechime*100+500);
        return aux-0.05*aux;
    }
    if(diesel==false && km>=200000)
    {
        aux=(float)(vechime*100+500);
        return aux-0.05*aux;
    }
    aux=(float)(vechime*100);
    return aux-0.05*aux;
}
void Standard::afisare(ostream &out)
{
    out<<getID()<<" - "<<this->getType()<<" - "<<km<<"km"<<" - "<<an_fabr<<"(fabricatie) - ";
    if(diesel) out<<"Diesel - ";
    else out<<"Benzina - ";
    out<<transmisie<<"(transmisie) "<<timp<<"(ETA)\n";
//    out<<getID()<<" "<<this->getType()<<" "<<km<<" "<<an_fabr<<" ";
//    if(diesel) out<<true<<" ";
//    else out<<false<<" ";
//    out<<transmisie<<"(tra "<<endl;

}
