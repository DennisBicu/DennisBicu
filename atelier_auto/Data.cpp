#include "Data.h"
int Data::zi_azi=ltm->tm_mday;
int Data::luna_azi=ltm->tm_mon+1;
int Data::an_azi=ltm->tm_year+1900;

bool Data::check_viitor()
{
    if(this->an<an_azi)
    {
        return false;
    }
    else if(this->an==an_azi && this->luna==luna_azi && this->zi<=zi_azi)
    {
        return false;
    }
    else
    {
        return true;
    }
}
Data::Data(int x, int y, int z)
{
    if(z<an_azi)
    {
        zi=x;
        luna=y;
        an=z;
    }
    else if(z==an_azi && y==luna_azi && x<=zi_azi)
    {
        zi=x;
        luna=y;
        an=z;
    }
    else
    {
        cout<<"Data nu poate fi din viitor, data de astazi este:"<<zi_azi<<"/"<<luna_azi<<"/"<<an_azi;
        cout<<endl<<"Selectati noi valori pentru zi, luna, an:"<<endl;
        cout<<"Zi: ";
        cin>>x;
        cout<<"Luna: ";
        cin>>y;
        cout<<"An: ";
        cin>>z;
        zi=x;
        luna=y;
        an=z;
    }
}
Data::Data(Data &x)
{
    zi=x.zi;
    luna=x.luna;
    an=x.an;
}

Data& Data::operator=(Data &x)
{
    if(x.an<an_azi)
    {
        zi=x.zi;
        luna=x.luna;
        an=x.an;
        return *this;
    }
    else if(x.an==an_azi && x.luna==luna_azi && x.zi<=zi_azi)
    {
        zi=x.zi;
        luna=x.luna;
        an=x.an;
        return *this;
    }
    else
    {
        int x2,y,z;
        cout<<"Data nu poate fi din viitor, data de astazi este:"<<zi_azi<<"/"<<luna_azi<<"/"<<an_azi;
        cout<<endl<<"Selectati noi valori pentru zi, luna, an:"<<endl;
        cout<<"Zi: ";
        cin>>x2;
        cout<<"Luna: ";
        cin>>y;
        cout<<"An: ";
        cin>>z;
        x.set_data(x2,y,z);
        zi=x.zi;
        luna=x.luna;
        an=x.an;
        return *this;
    }
}
int Data::getZi()
{
    return zi;
}
int Data::getLuna()
{
    return luna;
}
int Data::getAn()
{
    return an;
}
void Data::afisare_data(ostream &out)
{
    out<<zi<<"/"<<luna<<"/"<<an<<endl;
}
void Data::set_data(int x, int y, int z)
{
    if(z<an_azi)
    {
        zi=x;
        luna=y;
        an=z;
    }
    else if(z==an_azi && y==luna_azi && x<=zi_azi)
    {
        zi=x;
        luna=y;
        an=z;
    }
    else
    {
        cout<<"Data nu poate fi din viitor, data de astazi este:"<<zi_azi<<"/"<<luna_azi<<"/"<<an_azi;
        cout<<endl<<"Selectati noi valori pentru zi, luna, an:"<<endl;
        cout<<"Zi: ";
        cin>>x;
        cout<<"Luna: ";
        cin>>y;
        cout<<"An: ";
        cin>>z;
        zi=x;
        luna=y;
        an=z;
    }
}
Data Data::getAzi()
{
    Data aux;
    aux.set_data(zi_azi,luna_azi,an_azi);
    return aux;
}
bool Data::check_18(Data data_a2)
{
    if(data_a2.getAn()-this->getAn()>18)
    {
        return true;
    }
    else if(data_a2.getAn()-this->getAn()==18)
    {
        if(data_a2.getLuna()>this->getLuna())
        {
            return true;
        }
        else if(data_a2.getLuna()==this->getLuna())
        {
            if(data_a2.getZi()>=this->getZi())
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}
