#include "Asistent.h"
Asistent::Asistent(string nume2, string prenume2, Data data_n2, Data data_a2)
{
    ID=id_count++;
    coeficient=1;
    if((nume2.length()>0 && nume2.length()<=30) && (prenume2.length()>0 && prenume2.length()<=30))
    {
        if(data_n2.check_18(data_a2))
        {
            nume=nume2;
            prenume=prenume2;
            data_nastere=data_n2;
            data_angajare=data_a2;
        }
        else
        {
            cout<<"Persoana nu are 18 ani la momentul angajarii";
            exit(1);
        }
    }
    else
    {
        cout<<"Numele si prenumele sunt prea lungi sau sunt NULL";
        exit(1);
    }
}
Asistent::Asistent(Asistent &d)
{
    ID=id_count++;
    coeficient=1;
    nume=d.nume;
    prenume=d.prenume;
    data_nastere=d.data_nastere;
    data_angajare=d.data_angajare;
}

string Asistent::getType()
{
    return "Asistent";
}

float Asistent::getSalariu()
{
    float ani=(float)this->ani_vechime();
    return ani*coeficient*1000;
}
int Asistent::ani_vechime()
{
    return (data_angajare.getAzi()).getAn()-data_angajare.getAn();
}
void Asistent::afisare(ostream &out)
{
    out<<"ID: "<<ID<<endl;
    out<<"Angajat: "<<this->getType()<<endl;
    out<<"Nume si prenume: "<<nume<<" "<<prenume<<endl;
    out<<"Data nasterii: ";
    data_nastere.afisare_data(out);
    out<<"Data angajarii: ";
    data_angajare.afisare_data(out);
    out<<"Ani vechime: "<<this->ani_vechime()<<endl;
    out<<"Salariu: "<<this->getSalariu()<<endl;

}
void Asistent::citire(istream &in)
{
    cout<<"Nume: ";
    string lastName;
    do
    {
        in>>lastName;
        if(lastName.length()>=30 || lastName[0]=='\0')
        {
            cout<<"Numele este prea lung sau nul. Reincercati:";
        }
    }
    while (lastName.length()>=30 || lastName[0]=='\0' );
    cout<<"Prenume: ";
    string firstName;
    do
    {
        in>>firstName;
        if(firstName.length()>=30 || firstName.length()==0)
        {
            cout<<"Prenumele este prea lung sau nul. Reincercati:";
        }
    }
    while (firstName.length()>=30);
    cout<<"Data nasterii si a angajarii: "<<endl;

    int day,month,year,day2,month2,year2;
    Data aux_nastere, aux_angajare;
    do
    {
        cout<<"Zi / Luna / An (nastere):"<<endl;
        in>>day;
        in>>month;
        in>>year;
        aux_nastere.set_data(day,month,year);
        cout<<"Zi / Luna / An (angajare):"<<endl;
        in>>day2;
        in>>month2;
        in>>year2;
        aux_angajare.set_data(day2,month2,year2);
        if(!aux_nastere.check_18(aux_angajare))
        {
            cout<<"Angajatul nu are 18 ani impliniti in momentul angajarii. Reincercati alte date."<<endl;
        }
    }
    while(!aux_nastere.check_18(aux_angajare));
    this->set_angajat(lastName,firstName,aux_nastere,aux_angajare);
}
void Asistent::set_angajat(string nume2, string prenume2, Data data_n2, Data data_a2)
{
    if((nume2.length()>0 && nume2.length()<=30) && (prenume2.length()>0 && prenume2.length()<=30))
    {
        if(data_n2.check_18(data_a2))
        {
            nume=nume2;
            prenume=prenume2;
            data_nastere=data_n2;
            data_angajare=data_a2;
        }
        else
        {
            cout<<"Persoana nu are 18 ani la momentul angajarii";
            exit(1);
        }
    }
    else
    {
        cout<<"Numele si prenumele sunt prea lungi sau sunt NULL";
        exit(1);
    }
}

