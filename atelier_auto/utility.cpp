#include "utility.h"
vector<Angajat*> creare_lista_angajati()
{
    vector<Angajat*> a2;
    Angajat **a=new Angajat*[3];
    a[0]=new Director;
    Data d3(26,3,1970);
    Data d4(1,1,2000);
    a[0]->set_angajat("Enescu","Dragos",d3,d4);

    Data d1(25,6,2016);
    Data d2(9,7,1997);
    a[1]=new Mecanic("Bicu","Dennis",d2,d1);

    Data d5(14,8,2015);
    Data d6(9,7,1995);
    a[2]=new Asistent("Popescu","Marian",d6,d5);
    a2.push_back(a[0]);
    a2.push_back(a[1]);
    a2.push_back(a[2]);
//    cout<<"Cati angajati doriti sa introduceti?"<<endl;
//    int n;
//    cin>>n;
//    for(int i=0;i<n;i++)
//    {
//        a2=adauga_angajat(a2);
//    }
    return a2;
}

vector<Angajat*> adauga_angajat(vector<Angajat*>a2)
{
    Angajat **a=new Angajat*;
    cout<<"Ce fel de angajat doriti sa adaugati? (Director/Mecanic/Asistent)"<<endl;
    string tip;
    do
    {
        cin>>tip;
        if(tip!="Director" && tip!="Mecanic" && tip!="Asistent")
        {
            cout<<"Alegeti dintre: Director/Mecanic/Asistent. Reincercati."<<endl;
        }
    }
    while(tip!="Director" && tip!="Mecanic" && tip!="Asistent");
    if(tip=="Director")
    {
        *a=new Director;
        (*a)->citire(cin);
        a2.push_back((*a));
    }
    if(tip=="Mecanic")
    {
        *a=new Mecanic;
        (*a)->citire(cin);
        a2.push_back((*a));
    }
    if(tip=="Asistent")
    {
        *a=new Asistent;
        (*a)->citire(cin);
        a2.push_back((*a));
    }
    return a2;
}
vector<Angajat*> sterge_angajat(int id, vector<Angajat*> a2)
{

    int i=id-1;
    a2.erase(a2.begin()+i);
    return a2;
}
vector<Angajat*> edit_angajat(int id, vector<Angajat*> a2)
{
    ///Se considera ca vrem sa schimbam doar datele angajatului, nu si functia ocupata in atelier
    cout<<"Angajat de editat: "<<id;
    cout<<"\nNoile date:\n";
    for(auto it=a2.begin(); it!=a2.end(); it++)
    {
        if((*it)->getID()==id)
        {
            (*it)->citire(cin);
        }
    }
    return a2;
}
void afisare_angajati(ostream &out, vector<Angajat*> a2)
{
    auto it=a2.begin();
    for(; it!=a2.end(); it++)
    {
        (*it)->afisare(out);
    }
//    cout<<flush;
//    system("CLS");
}

void afis_salariu_id(int id, vector<Angajat*> a2)
{
    cout<<endl<<"Salariul angajatului cu id "<<id<<" este: "<<endl;
    auto it=a2.begin();
    for(; it!=a2.end(); it++)
    {
        if((*it)->getID()==id )
            cout<<(*it)->getSalariu();
    }
//    cout<<flush;
//    system("CLS");
}
void operatii_angajati()
{
    vector<Angajat*> angajati;
    angajati=creare_lista_angajati();
    afisare_angajati(cout,angajati);
    afis_salariu_id(2,angajati);
    angajati=sterge_angajat(1, angajati);
    angajati=edit_angajat(3,angajati);
    afisare_angajati(cout,angajati);
}
void creare_file_masini(list<Masina*>aux)
{
    ofstream file("masini.txt");

        for(auto it=aux.begin();it!=aux.end();it++)
        {
            (*it)->afisare(file);
        }
        file.close();
    }
list<Masina*> creare_lista_masini()
{
    Masina **m=new Masina*[20];
    for(int i=1;i<=20;i++)
    {
        if(i<6)
        {
            if(i%2==0) m[i-1]=new Standard((rand()%100000+1)*10,rand()%23+1998,1,"automat");
            else  m[i-1]=new Standard((rand()%100000+1)*10,rand()%23+1998,0,"manual");
        }
        if(i>=6 && i<12)
        {
            if(i%2==0)
            {
                m[i-1]=new Camion(((rand()%1000000+1)*10)+600000,rand()%30+1996,0,rand()%20+11);
            }
            else m[i-1]=new Autobuz(((rand()%1000000+1)*10)+100000,rand()%30+1996,1,rand()%40+11);
        }
        if(i>=12 && i<16)
        {
            if(i%2==0) m[i-1]=new Standard((rand()%100000+1)*10,rand()%23+1998,1,"manual");
            else  m[i-1]=new Standard((rand()%100000+1)*10,rand()%23+1998,0,"automat");
        }
        if(i>=16)
        {
            if(i%2==0 && i%3!=0) m[i-1]=new Standard((rand()%100000+1)*10,rand()%23+1998,1,"manual");
            if(i%2==1) m[i-1]=new Autobuz(((rand()%1000000+1)*10)+100000,rand()%30+1996,0,rand()%40+11);
            if(i==18) m[i-1]=new Camion(((rand()%1000000+1)*10)+600000,rand()%30+1996,1,rand()%20+11);
        }
        }
       list<Masina*>aux;
       for(int i=0;i<20;i++)
        {
            aux.push_back(m[i]);
        }
        return aux;
}
