#include "Garaj.h"
Garaj::Garaj()
{
    id_angajat=0;
    //ang=NULL;
}
Garaj::Garaj(int id2, queue<Masina*> mas2)
{
    id_angajat=id2;
    qmasini=mas2;
}
Garaj::Garaj(const Garaj &g)
{
    id_angajat=g.id_angajat;
    qmasini=g.qmasini;
}
Garaj::~Garaj()
{
    ;
}
unsigned int Garaj::checkSize()
{
    return qmasini.size();
}
void Garaj::AddCar(Masina *m2)
{
    qmasini.push(m2);
}
void Garaj::deleteCar()
{
    qmasini.pop();
}
int Garaj::getID_angajat()
{
    return id_angajat;
}
void Garaj::setID_angajat(int id2)
{
    id_angajat=id2;
}
void Garaj::afisare_qgaraj()
{

    queue<Masina*>aux=qmasini;
    if(aux.size()>0){
    cout<<"Garajul "<<id_angajat<<" este:\n";
    while(aux.size()>0)
    {
        (aux.front())->afisare(cout);
        aux.pop();
    }
    cout<<endl;
    }
    else
    {
        cout<<"Garajul "<<id_angajat<<" este:\nLIBER\n\n";
    }
}
bool Garaj::checkRoom4Standard()
{
    int s=0;
    queue<Masina*>aux=qmasini;
    if(aux.size()>0){
    while(aux.size()>0)
    {
        if((aux.front())->getType()=="Standard") s++;
        aux.pop();
    }
    if (s==3) return false;
    else return true;
    }
    else
    {
        return true;
    }

}
bool Garaj::checkRoom4Bus()
{
     int s=0;
    queue<Masina*>aux=qmasini;
    if(aux.size()>0){
    while(aux.size()>0)
    {
        if((aux.front())->getType()=="Autobuz") s++;
        aux.pop();
    }
    if (s==1) return false;
    else return true;
    }
    else
    {
        return true;
    }

}
bool Garaj::checkRoom4Camion()
{
     int s=0;
    queue<Masina*>aux=qmasini;
    if(aux.size()>0){
    while(aux.size()>0)
    {
        if((aux.front())->getType()=="Camion") s++;
        aux.pop();
    }
    if (s==1) return false;
    else return true;
    }
    else
    {
        return true;
    }

}
bool Garaj::checkFULL()
{
    if(this->checkRoom4Standard()==false && this->checkRoom4Bus()==false && this->checkRoom4Camion()==false) return true;
    else return false;
}
queue<Masina*> Garaj::getMasiniGaraj()
{
    return qmasini;
}
void Garaj::deleteMasini()
{
    while(!qmasini.empty())
    {
        qmasini.pop();
    }
}
