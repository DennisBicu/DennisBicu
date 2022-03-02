#include "Atelier.h"
Atelier::Atelier()
{
    garaje.resize(3); ///asumam faptul ca atelierul are 3 garaje;
}
Atelier::Atelier(vector<Angajat*>a2)
{
    garaje.resize(3);
    angajati=a2;
    if(angajati.size()>0)
        status="Deschis";
    //masini=m2;
}
Atelier::Atelier(const Atelier &a)
{
    status=a.status;
    angajati=a.angajati;
    garaje=a.garaje;
    waiting_q=a.waiting_q;
    left_out=a.left_out;
}
Atelier::~Atelier()
{
    ;
}

void Atelier::setStatus()
{
    if(angajati.size()>0)
        status="Deschis";
}
string Atelier::checkStatus()
{
    return status;
}
void Atelier::setAngajati(vector<Angajat*>a2)
{
    angajati=a2;
}
vector<Angajat*> Atelier::getAngajati()
{
    return angajati;
}
void Atelier::addToWait_q(Masina *m)
{
    waiting_q.push(m);
}
void Atelier::addToLeft_out(Masina *m)
{
    left_out.push(m);
}
Masina* Atelier::delFromWait_q()
{
    Masina* aux=waiting_q.front();
    waiting_q.pop();
    return aux;
}
void Atelier::printWait_q()
{
    queue<Masina*> aux=waiting_q;
    if(aux.size()>0)
    {
        cout<<"Masinile care se afla la coada in acest moment:\n";
        while(aux.size()>0)
        {
            (aux.front())->afisare(cout);
            aux.pop();
        }
        cout<<"\n----------------------------------------------------------------------------\n";
    }
    else
    {
        cout<<"Coada de asteptare este goala.\n";
    }
}
void Atelier::creareGaraje()
{
     cout<<"\nSa incepem distribuirea masinilor!\n";
    string tip_masina;
    auto ita=angajati.begin();
    char urm;
    int id;
    cout<<"\nGarajele disponibile sunt ale angajatilor (id, nume):\n";
    for(auto itg=garaje.begin(); itg!=garaje.end() && ita!=angajati.end() ; itg++, ita++)
    {
        itg->setID_angajat((*ita)->getID());
        cout<<itg->getID_angajat()<<" "<<(*ita)->getNume()<<" "<<(*ita)->getPrenume()<<endl;
    }
    cout<<"Doriti sa se aloce automat toate masinile in garaje? (daca nu, le veti aloca manual sau semi-automat) (y/n)\n";
    cin>>urm;
///SETARE MANUALA si SEMI-MANUALA masini:
    if(urm=='n')
    {
        while(waiting_q.size()>0)
        {
            cout<<"\nFiecare dintre ele are o capacitate de: 3 masini Standard, 1 Autobuz si 1 Camion.\n";
            cout<<"----------------------------------------------------------------------------\n";
            garaje[0].afisare_qgaraj();
            garaje[1].afisare_qgaraj();
            garaje[2].afisare_qgaraj();
            if(garaje[2].checkFULL() && garaje[1].checkFULL() && garaje[0].checkFULL())
            {
                cout<<"\nTOATE GARAJELE SUNT PLINE\n";
                cout<<"\nMasinile RAMASE in coada:\n";
                left_out=waiting_q;
                while(left_out.size()>0)
                {
                    left_out.front()->afisare(cout);
                    left_out.pop();
                }
                goto continuare1;
                break;
            }

            tip_masina=(waiting_q.front())->getType();
            cout<<"Masina '"<<(waiting_q.front())->getID()<<" "<<(waiting_q.front())->getType()<<"' doriti sa fiti alocat automat la un garaj al unui angajat, sau preferati sa alegeti?(1-automat, 2-alegere)\n";
            int x;
            cin>>x;
            if(x==2)
            {
                cout<<"Masina '"<<(waiting_q.front())->getID()<<" "<<(waiting_q.front())->getType()<<"' la ce garaj doriti sa intrati?(1/2/3): ";
                cin>>id;
                cout<<endl<<"----------------------------------------------------------------------------\n";

                switch (id)
                {
                case 1:
                {
                    if(tip_masina=="Standard")
                    {
                        if(garaje[0].checkRoom4Standard())
                        {
                            (waiting_q.front())->setTimp();
                            garaje[0].AddCar(waiting_q.front());
                            //garaje[0].afisare_qgaraj();
                            waiting_q.pop();
                            break;

                        }
                        else
                        {
                            cout<<"Exista deja 3 masini Standard la coada. Doriti sa plecati?(y/n)";
                            cin>>urm;
                            if(urm=='y')
                            {
                                waiting_q.pop();
                                break;
                            }
                            else{
                                    int poz=1;
                                    int n;
                                    cout<<"Vreti sa incercati la alt angajat liber sau sa asteptati eliberarea acestui garaj?(1/2)\n";
                                    cin>>n;
                                    if(n==1)
                                        break;
                                    else
                                    {
                                        poz=1;
                                        queue<Masina*> aux_masini=garaje[id-1].getMasiniGaraj();
                                        while(aux_masini.size()>0)
                                        {
                                            if(aux_masini.front()->getType()=="Standard")
                                            {
                                                break;
                                            }
                                            poz++;
                                            aux_masini.pop();
                                        }
                                        int sum=0,poz2=poz;
                                        cout<<"Pentru a elibera un loc pt. masina '"<<(waiting_q.front())->getID()<<" "<<(waiting_q.front())->getType()<<"' este nevoie sa asteptati timpul de: ";
                                        aux_masini=garaje[id-1].getMasiniGaraj();
                                        while(aux_masini.size()>0 && poz2!=0)
                                        {
                                            sum=sum+aux_masini.front()->getTimp();
                                            poz2--;
                                            aux_masini.pop();
                                        }
                                        char acord;
                                        cout<<sum<<"(unit. de timp). Sunteti de acord? (daca nu, masina va parasi coada) (y/n)\n";
                                        cin>>acord;
                                        if(acord=='n')
                                        {
                                            waiting_q.pop();
                                            break;
                                        }
                                        else
                                        {
                                            for(int i=sum; i>0; i--)
                                            {
                                                cout<<i<<"s...";
                                            }
                                            cout<<endl;
                                            while((garaje[id-1].getMasiniGaraj()).size()>0 && poz!=0)
                                            {
                                                garaje[id-1].deleteCar();
                                                poz--;
                                            }
                                            waiting_q.front()->setTimp();
                                            garaje[id-1].AddCar(waiting_q.front());
                                            waiting_q.pop();
                                            break;
                                        }
                                    }
                                }
                            }
                    }

                    else if(tip_masina=="Autobuz")
                    {
                        if(garaje[0].checkRoom4Bus())
                        {
                            (waiting_q.front())->setTimp();
                            garaje[0].AddCar(waiting_q.front());
                            waiting_q.pop();
                            break;
                        }
                        else
                        {

                            cout<<"Exista deja 1 masina Autobuz la coada. Doriti sa plecati?(y/n)\n";
                            cin>>urm;
                            if(urm=='y')
                            {
                                waiting_q.pop();
                                break;

                            }
                            else
                            {
                                int poz=1;
                                    int n;
                                    cout<<"Vreti sa incercati la alt angajat liber sau sa asteptati eliberarea acestui garaj?(1/2)\n";
                                    cin>>n;
                                    if(n==1)
                                        break;
                                    else
                                    {
                                        poz=1;
                                        queue<Masina*> aux_masini=garaje[id-1].getMasiniGaraj();
                                        while(aux_masini.size()>0)
                                        {
                                            if(aux_masini.front()->getType()=="Autobuz")
                                            {
                                                break;
                                            }
                                            poz++;
                                            aux_masini.pop();
                                        }
                                        int sum=0,poz2=poz;
                                        cout<<"Pentru a elibera un loc pt. masina '"<<(waiting_q.front())->getID()<<" "<<(waiting_q.front())->getType()<<"' este nevoie sa asteptati timpul de: ";
                                        aux_masini=garaje[id-1].getMasiniGaraj();
                                        while(aux_masini.size()>0 && poz2!=0)
                                        {
                                            sum=sum+aux_masini.front()->getTimp();
                                            poz2--;
                                            aux_masini.pop();
                                        }
                                        char acord;
                                        cout<<sum<<"(unit. de timp). Sunteti de acord? (daca nu, masina va parasi coada) (y/n)\n";
                                        cin>>acord;
                                        if(acord=='n')
                                        {
                                            waiting_q.pop();
                                            break;
                                        }
                                        else
                                        {
                                            for(int i=sum; i>0; i--)
                                            {
                                                cout<<i<<"s...";
                                            }
                                            cout<<endl;
                                            while((garaje[id-1].getMasiniGaraj()).size()>0 && poz!=0)
                                            {
                                                garaje[id-1].deleteCar();
                                                poz--;
                                            }
                                            waiting_q.front()->setTimp();
                                            garaje[id-1].AddCar(waiting_q.front());
                                            waiting_q.pop();
                                            break;
                                        }
                                    }
                            }
                        }
                    }
                    else if(tip_masina=="Camion")
                    {
                        if(garaje[0].checkRoom4Camion())
                        {
                            (waiting_q.front())->setTimp();
                            garaje[0].AddCar(waiting_q.front());
                            waiting_q.pop();
                            break;
                        }
                        else
                        {
                            cout<<"Exista deja 1 masina Camion la coada. Doriti sa plecati?(y/n)\n";
                            cin>>urm;
                            if(urm=='y')
                            {
                                waiting_q.pop();
                                break;
                            }
                            else
                            {
                                 int poz=1;
                                    int n;
                                    cout<<"Vreti sa incercati la alt angajat liber sau sa asteptati eliberarea acestui garaj?(1/2)\n";
                                    cin>>n;
                                    if(n==1)
                                        break;
                                    else
                                    {
                                        poz=1;
                                        queue<Masina*> aux_masini=garaje[id-1].getMasiniGaraj();
                                        while(aux_masini.size()>0)
                                        {
                                            if(aux_masini.front()->getType()=="Camion")
                                            {
                                                break;
                                            }
                                            poz++;
                                            aux_masini.pop();
                                        }
                                        int sum=0,poz2=poz;
                                        cout<<"Pentru a elibera un loc pt. masina '"<<(waiting_q.front())->getID()<<" "<<(waiting_q.front())->getType()<<"' este nevoie sa asteptati timpul de: ";
                                        aux_masini=garaje[id-1].getMasiniGaraj();
                                        while(aux_masini.size()>0 && poz2!=0)
                                        {
                                            sum=sum+aux_masini.front()->getTimp();
                                            poz2--;
                                            aux_masini.pop();
                                        }
                                        char acord;
                                        cout<<sum<<"(unit. de timp). Sunteti de acord? (daca nu, masina va parasi coada) (y/n)\n";
                                        cin>>acord;
                                        if(acord=='n')
                                        {
                                            waiting_q.pop();
                                            break;
                                        }
                                        else
                                        {
                                            for(int i=sum; i>0; i--)
                                            {
                                                cout<<i<<"s...";
                                            }
                                            cout<<endl;
                                            while((garaje[id-1].getMasiniGaraj()).size()>0 && poz!=0)
                                            {
                                                garaje[id-1].deleteCar();
                                                poz--;
                                            }
                                            waiting_q.front()->setTimp();
                                            garaje[id-1].AddCar(waiting_q.front());
                                            waiting_q.pop();
                                            break;
                                        }
                                    }
                            }
                        }
                    }
                }
                case 2:
                {
                    if(tip_masina=="Standard")
                    {
                        if(garaje[1].checkRoom4Standard())
                        {
                            (waiting_q.front())->setTimp();
                            garaje[1].AddCar(waiting_q.front());
                            //garaje[1].afisare_qgaraj();
                            waiting_q.pop();
                            break;

                        }
                        else
                        {
                            cout<<"Exista deja 3 masini Standard la coada. Doriti sa plecati?(y/n)\n";
                            cin>>urm;
                            if(urm=='y')
                            {
                                waiting_q.pop();
                                break;

                            }
                            else
                            {
                                int poz=1;
                                    int n;
                                    cout<<"Vreti sa incercati la alt angajat liber sau sa asteptati eliberarea acestui garaj?(1/2)\n";
                                    cin>>n;
                                    if(n==1)
                                        break;
                                    else
                                    {
                                        poz=1;
                                        queue<Masina*> aux_masini=garaje[id-1].getMasiniGaraj();
                                        while(aux_masini.size()>0)
                                        {
                                            if(aux_masini.front()->getType()=="Standard")
                                            {
                                                break;
                                            }
                                            poz++;
                                            aux_masini.pop();
                                        }
                                        int sum=0,poz2=poz;
                                        cout<<"Pentru a elibera un loc pt. masina '"<<(waiting_q.front())->getID()<<" "<<(waiting_q.front())->getType()<<"' este nevoie sa asteptati timpul de: ";
                                        aux_masini=garaje[id-1].getMasiniGaraj();
                                        while(aux_masini.size()>0 && poz2!=0)
                                        {
                                            sum=sum+aux_masini.front()->getTimp();
                                            poz2--;
                                            aux_masini.pop();
                                        }
                                        char acord;
                                        cout<<sum<<"(unit. de timp). Sunteti de acord? (daca nu, masina va parasi coada) (y/n)\n";
                                        cin>>acord;
                                        if(acord=='n')
                                        {
                                            waiting_q.pop();
                                            break;
                                        }
                                        else
                                        {
                                            for(int i=sum; i>0; i--)
                                            {
                                                cout<<i<<"s...";
                                            }
                                            cout<<endl;
                                            while((garaje[id-1].getMasiniGaraj()).size()>0 && poz!=0)
                                            {
                                                garaje[id-1].deleteCar();
                                                poz--;
                                            }
                                            waiting_q.front()->setTimp();
                                            garaje[id-1].AddCar(waiting_q.front());
                                            waiting_q.pop();
                                            break;
                                        }
                                    }
                            }
                        }
                    }
                    else if(tip_masina=="Autobuz")
                    {
                        if(garaje[1].checkRoom4Bus())
                        {
                            (waiting_q.front())->setTimp();
                            garaje[1].AddCar(waiting_q.front());
                            //garaje[1].afisare_qgaraj();
                            waiting_q.pop();
                            break;
                        }
                        else
                        {

                            cout<<"Exista deja 1 masina Autobuz la coada. Doriti sa plecati?(y/n)\n";
                            cin>>urm;
                            if(urm=='y')
                            {
                                waiting_q.pop();
                                break;

                            }
                            else
                            {
                                int poz=1;
                                    int n;
                                    cout<<"Vreti sa incercati la alt angajat liber sau sa asteptati eliberarea acestui garaj?(1/2)\n";
                                    cin>>n;
                                    if(n==1)
                                        break;
                                    else
                                    {
                                        poz=1;
                                        queue<Masina*> aux_masini=garaje[id-1].getMasiniGaraj();
                                        while(aux_masini.size()>0)
                                        {
                                            if(aux_masini.front()->getType()=="Autobuz")
                                            {
                                                break;
                                            }
                                            poz++;
                                            aux_masini.pop();
                                        }
                                        int sum=0,poz2=poz;
                                        cout<<"Pentru a elibera un loc pt. masina '"<<(waiting_q.front())->getID()<<" "<<(waiting_q.front())->getType()<<"' este nevoie sa asteptati timpul de: ";
                                        aux_masini=garaje[id-1].getMasiniGaraj();
                                        while(aux_masini.size()>0 && poz2!=0)
                                        {
                                            sum=sum+aux_masini.front()->getTimp();
                                            poz2--;
                                            aux_masini.pop();
                                        }
                                        char acord;
                                        cout<<sum<<"(unit. de timp). Sunteti de acord? (daca nu, masina va parasi coada) (y/n)\n";
                                        cin>>acord;
                                        if(acord=='n')
                                        {
                                            waiting_q.pop();
                                            break;
                                        }
                                        else
                                        {
                                            for(int i=sum; i>0; i--)
                                            {
                                                cout<<i<<"s...";
                                            }
                                            cout<<endl;
                                            while((garaje[id-1].getMasiniGaraj()).size()>0 && poz!=0)
                                            {
                                                garaje[id-1].deleteCar();
                                                poz--;
                                            }
                                            waiting_q.front()->setTimp();
                                            garaje[id-1].AddCar(waiting_q.front());
                                            waiting_q.pop();
                                            break;
                                        }
                                    }
                            }
                        }
                    }
                    else if(tip_masina=="Camion")
                    {
                        if(garaje[1].checkRoom4Camion())
                        {
                            (waiting_q.front())->setTimp();
                            garaje[1].AddCar(waiting_q.front());
                            // garaje[1].afisare_qgaraj();
                            waiting_q.pop();
                            break;
                        }
                        else
                        {
                            cout<<"Exista deja 1 masina Camion la coada. Doriti sa plecati?(y/n)(daca nu, veti fi alocat la alt angajat liber - "<<id-1<<" sau "<<id+1<<")\n";
                            cin>>urm;
                            if(urm=='y')
                            {
                                waiting_q.pop();
                                break;
                            }
                            else
                            {
                                int poz=1;
                                    int n;
                                    cout<<"Vreti sa incercati la alt angajat liber sau sa asteptati eliberarea acestui garaj?(1/2)\n";
                                    cin>>n;
                                    if(n==1)
                                        break;
                                    else
                                    {
                                        poz=1;
                                        queue<Masina*> aux_masini=garaje[id-1].getMasiniGaraj();
                                        while(aux_masini.size()>0)
                                        {
                                            if(aux_masini.front()->getType()=="Camion")
                                            {
                                                break;
                                            }
                                            poz++;
                                            aux_masini.pop();
                                        }
                                        int sum=0,poz2=poz;
                                        cout<<"Pentru a elibera un loc pt. masina '"<<(waiting_q.front())->getID()<<" "<<(waiting_q.front())->getType()<<"' este nevoie sa asteptati timpul de: ";
                                        aux_masini=garaje[id-1].getMasiniGaraj();
                                        while(aux_masini.size()>0 && poz2!=0)
                                        {
                                            sum=sum+aux_masini.front()->getTimp();
                                            poz2--;
                                            aux_masini.pop();
                                        }
                                        char acord;
                                        cout<<sum<<"(unit. de timp). Sunteti de acord? (daca nu, masina va parasi coada) (y/n)\n";
                                        cin>>acord;
                                        if(acord=='n')
                                        {
                                            waiting_q.pop();
                                            break;
                                        }
                                        else
                                        {
                                            for(int i=sum; i>0; i--)
                                            {
                                                cout<<i<<"s...";
                                            }
                                            cout<<endl;
                                            while((garaje[id-1].getMasiniGaraj()).size()>0 && poz!=0)
                                            {
                                                garaje[id-1].deleteCar();
                                                poz--;
                                            }
                                            waiting_q.front()->setTimp();
                                            garaje[id-1].AddCar(waiting_q.front());
                                            waiting_q.pop();
                                            break;
                                        }
                                    }
                            }
                        }
                    }
                }
                case 3:
                {
                    if(tip_masina=="Standard")
                    {
                        if(garaje[2].checkRoom4Standard())
                        {
                            (waiting_q.front())->setTimp();
                            garaje[2].AddCar(waiting_q.front());
                            //garaje[2].afisare_qgaraj();
                            waiting_q.pop();
                            break;

                        }
                        else
                        {
                            cout<<"Exista deja 3 masini Standard la coada. Doriti sa plecati?(y/n)(daca nu, veti fi alocat la alt angajat liber - "<<id-2<<" sau "<<id-1<<")\n";
                            cin>>urm;
                            if(urm=='y')
                            {
                                waiting_q.pop();
                                break;

                            }
                            else
                            {
                                int poz=1;
                                    int n;
                                    cout<<"Vreti sa incercati la alt angajat liber sau sa asteptati eliberarea acestui garaj?(1/2)\n";
                                    cin>>n;
                                    if(n==1)
                                        break;
                                    else
                                    {
                                        poz=1;
                                        queue<Masina*> aux_masini=garaje[id-1].getMasiniGaraj();
                                        while(aux_masini.size()>0)
                                        {
                                            if(aux_masini.front()->getType()=="Standard")
                                            {
                                                break;
                                            }
                                            poz++;
                                            aux_masini.pop();
                                        }
                                        int sum=0,poz2=poz;
                                        cout<<"Pentru a elibera un loc pt. masina '"<<(waiting_q.front())->getID()<<" "<<(waiting_q.front())->getType()<<"' este nevoie sa asteptati timpul de: ";
                                        aux_masini=garaje[id-1].getMasiniGaraj();
                                        while(aux_masini.size()>0 && poz2!=0)
                                        {
                                            sum=sum+aux_masini.front()->getTimp();
                                            poz2--;
                                            aux_masini.pop();
                                        }
                                        char acord;
                                        cout<<sum<<"(unit. de timp). Sunteti de acord? (daca nu, masina va parasi coada) (y/n)\n";
                                        cin>>acord;
                                        if(acord=='n')
                                        {
                                            waiting_q.pop();
                                            break;
                                        }
                                        else
                                        {
                                            for(int i=sum; i>0; i--)
                                            {
                                                cout<<i<<"s...";
                                            }
                                            cout<<endl;
                                            while((garaje[id-1].getMasiniGaraj()).size()>0 && poz!=0)
                                            {
                                                garaje[id-1].deleteCar();
                                                poz--;
                                            }
                                            waiting_q.front()->setTimp();
                                            garaje[id-1].AddCar(waiting_q.front());
                                            waiting_q.pop();
                                            break;
                                        }
                                    }
                            }
                        }
                    }
                    else if(tip_masina=="Autobuz")
                    {
                        if(garaje[2].checkRoom4Bus())
                        {
                            (waiting_q.front())->setTimp();
                            garaje[2].AddCar(waiting_q.front());
                            //garaje[2].afisare_qgaraj();
                            waiting_q.pop();
                            break;
                        }
                        else
                        {

                            cout<<"Exista deja 1 masina Autobuz la coada. Doriti sa plecati?(y/n)(daca nu, veti fi alocat la alt angajat liber - "<<id-2<<" sau "<<id-1<<")\n";
                            cin>>urm;
                            if(urm=='y')
                            {
                                waiting_q.pop();
                                break;

                            }
                            else
                            {
                                int poz=1;
                                    int n;
                                    cout<<"Vreti sa incercati la alt angajat liber sau sa asteptati eliberarea acestui garaj?(1/2)\n";
                                    cin>>n;
                                    if(n==1)
                                        break;
                                    else
                                    {
                                        poz=1;
                                        queue<Masina*> aux_masini=garaje[id-1].getMasiniGaraj();
                                        while(aux_masini.size()>0)
                                        {
                                            if(aux_masini.front()->getType()=="Autobuz")
                                            {
                                                break;
                                            }
                                            poz++;
                                            aux_masini.pop();
                                        }
                                        int sum=0,poz2=poz;
                                        cout<<"Pentru a elibera un loc pt. masina '"<<(waiting_q.front())->getID()<<" "<<(waiting_q.front())->getType()<<"' este nevoie sa asteptati timpul de: ";
                                        aux_masini=garaje[id-1].getMasiniGaraj();
                                        while(aux_masini.size()>0 && poz2!=0)
                                        {
                                            sum=sum+aux_masini.front()->getTimp();
                                            poz2--;
                                            aux_masini.pop();
                                        }
                                        char acord;
                                        cout<<sum<<"(unit. de timp). Sunteti de acord? (daca nu, masina va parasi coada) (y/n)\n";
                                        cin>>acord;
                                        if(acord=='n')
                                        {
                                            waiting_q.pop();
                                            break;
                                        }
                                        else
                                        {
                                            for(int i=sum; i>0; i--)
                                            {
                                                cout<<i<<"s...";
                                            }
                                            cout<<endl;
                                            while((garaje[id-1].getMasiniGaraj()).size()>0 && poz!=0)
                                            {
                                                garaje[id-1].deleteCar();
                                                poz--;
                                            }
                                            waiting_q.front()->setTimp();
                                            garaje[id-1].AddCar(waiting_q.front());
                                            waiting_q.pop();
                                            break;
                                        }
                                    }
                            }
                        }
                    }
                    else if(tip_masina=="Camion")
                    {
                        if(garaje[2].checkRoom4Camion())
                        {
                            (waiting_q.front())->setTimp();
                            garaje[2].AddCar(waiting_q.front());
                            //garaje[2].afisare_qgaraj();
                            waiting_q.pop();
                            break;
                        }
                        else
                        {
                            cout<<"Exista deja 1 masina Camion la coada. Doriti sa plecati?(y/n)(daca nu, veti fi alocat la alt angajat liber - "<<id-2<<" sau "<<id-1<<")\n";
                            cin>>urm;
                            if(urm=='y')
                            {
                                waiting_q.pop();
                                break;
                            }
                            else
                            {
                                int poz=1;
                                    int n;
                                    cout<<"Vreti sa incercati la alt angajat liber sau sa asteptati eliberarea acestui garaj?(1/2)\n";
                                    cin>>n;
                                    if(n==1)
                                        break;
                                    else
                                    {
                                        poz=1;
                                        queue<Masina*> aux_masini=garaje[id-1].getMasiniGaraj();
                                        while(aux_masini.size()>0)
                                        {
                                            if(aux_masini.front()->getType()=="Camion")
                                            {
                                                break;
                                            }
                                            poz++;
                                            aux_masini.pop();
                                        }
                                        int sum=0,poz2=poz;
                                        cout<<"Pentru a elibera un loc pt. masina '"<<(waiting_q.front())->getID()<<" "<<(waiting_q.front())->getType()<<"' este nevoie sa asteptati timpul de: ";
                                        aux_masini=garaje[id-1].getMasiniGaraj();
                                        while(aux_masini.size()>0 && poz2!=0)
                                        {
                                            sum=sum+aux_masini.front()->getTimp();
                                            poz2--;
                                            aux_masini.pop();
                                        }
                                        char acord;
                                        cout<<sum<<"(unit. de timp). Sunteti de acord? (daca nu, masina va parasi coada) (y/n)\n";
                                        cin>>acord;
                                        if(acord=='n')
                                        {
                                            waiting_q.pop();
                                            break;
                                        }
                                        else
                                        {
                                            for(int i=sum; i>0; i--)
                                            {
                                                cout<<i<<"s...";
                                            }
                                            cout<<endl;
                                            while((garaje[id-1].getMasiniGaraj()).size()>0 && poz!=0)
                                            {
                                                garaje[id-1].deleteCar();
                                                poz--;
                                            }
                                            waiting_q.front()->setTimp();
                                            garaje[id-1].AddCar(waiting_q.front());
                                            waiting_q.pop();
                                            break;
                                        }
                                    }
                            }
                        }
                    }
                }
                default:
                    break;
                }
            }
            else
            {
                int full=0;
                for(auto itg=garaje.begin(); itg!=garaje.end(); itg++)
                {
                    if(tip_masina=="Standard")
                    {
                        if(itg->checkRoom4Standard())
                        {
                            (waiting_q.front())->setTimp();
                            itg->AddCar(waiting_q.front());
                            waiting_q.pop();
                            break;

                        }
                        else
                        {
                            full++;
                        }
                    }
                    else if(tip_masina=="Autobuz")
                    {
                        if(itg->checkRoom4Bus())
                        {
                            (waiting_q.front())->setTimp();
                            itg->AddCar(waiting_q.front());
                            waiting_q.pop();
                            break;
                        }
                        else
                        {
                            full++;
                        }
                    }
                    else if(tip_masina=="Camion")
                    {
                        if(itg->checkRoom4Camion())
                        {
                            (waiting_q.front())->setTimp();
                            itg->AddCar(waiting_q.front());
                            waiting_q.pop();
                            break;
                        }
                        else
                        {
                            full++;
                        }
                    }
                    if(full==3)
                        {
                            cout<<"Toti angajatii sunt indisponibil pentru o alocare automata. Incercati alocarea manuala la ce garaj doriti.\n";
                            break;
                        }
                }
            }

            cout<<flush;
            system("CLS");
        }
        continuare1:
        char acord;
        if(waiting_q.size()>0){
        cout<<"\nDoriti sa continuati alocarea? (y/n) (daca nu, va fi afisata lista finala a garajelor)\n";
        cin>>acord;
        }
        if(acord=='y'){
        cout<<"\nALOCAREA MASINILOR DIN COADA RAMASA:\n";
        int poz=0;
        acord='x';
        while(waiting_q.size()>0)
        {
            garaje[0].afisare_qgaraj();
            garaje[1].afisare_qgaraj();
            garaje[2].afisare_qgaraj();
            tip_masina=(waiting_q.front())->getType();
            cout<<"\nMasina '"<<(waiting_q.front())->getID()<<" "<<(waiting_q.front())->getType()<<"' la ce garaj doriti sa intrati?(1/2/3): ";
            cin>>id;
            cout<<endl<<"----------------------------------------------------------------------------\n";
            switch (id)
            {
            case 1:
            {
                if(tip_masina=="Standard")
                {
                    if(garaje[0].checkRoom4Standard())
                    {
                        waiting_q.front()->setTimp();
                        garaje[0].AddCar(waiting_q.front());
                        waiting_q.pop();
                        break;
                    }
                    else{
                    poz=1;
                    queue<Masina*> aux_masini=garaje[0].getMasiniGaraj();
                    while(aux_masini.size()>0)
                    {
                       if(aux_masini.front()->getType()=="Standard")
                       {
                           break;
                       }
                       poz++;
                       aux_masini.pop();
                    }
                    int sum=0,poz2=poz;
                    cout<<"Pentru a elibera un loc pt. masina '"<<(waiting_q.front())->getID()<<" "<<(waiting_q.front())->getType()<<"' este nevoie sa asteptati timpul de: ";
                    aux_masini=garaje[0].getMasiniGaraj();
                    while(aux_masini.size()>0 && poz2!=0)
                    {
                       sum=sum+aux_masini.front()->getTimp();
                       poz2--;
                       aux_masini.pop();
                    }
                        cout<<sum<<"(unit. de timp). Sunteti de acord? (y/n)\n";
                        cin>>acord;
                        if(acord=='n')
                        {
                            char acord2;
                            cout<<"Doriti sa asteptati la alt angajat? (y/n)\n";
                            cin>>acord2;
                            if(acord2=='n')
                            {
                                waiting_q.pop();
                                break;
                            }
                            else
                                break;
                        }
                        else
                        {
                            for(int i=sum;i>0;i--)
                                {
                                    cout<<i<<"s...";
                                }
                                cout<<endl;
                            while((garaje[0].getMasiniGaraj()).size()>0 && poz!=0)
                            {
                                garaje[0].deleteCar();
                                poz--;
                            }
                                waiting_q.front()->setTimp();
                                garaje[0].AddCar(waiting_q.front());
                                waiting_q.pop();
                                break;

                        }
                    }
                }
                else if(tip_masina=="Autobuz")
                {
                    if(garaje[0].checkRoom4Bus())
                    {
                        waiting_q.front()->setTimp();
                        garaje[0].AddCar(waiting_q.front());
                        waiting_q.pop();
                        break;
                    }
                    else{
                    poz=1;
                    queue<Masina*> aux_masini=garaje[0].getMasiniGaraj();
                    while(aux_masini.size()>0)
                    {
                       if(aux_masini.front()->getType()=="Autobuz")
                       {
                           break;
                       }
                       poz++;
                       aux_masini.pop();
                    }

                    int sum=0,poz2=poz;
                    cout<<"Pentru a elibera un loc pt. masina '"<<(waiting_q.front())->getID()<<" "<<(waiting_q.front())->getType()<<"' este nevoie sa asteptati timpul de: ";
                    aux_masini=garaje[0].getMasiniGaraj();
                    while(aux_masini.size()>0 && poz2!=0)
                    {
                       sum=sum+aux_masini.front()->getTimp();
                       poz2--;
                       aux_masini.pop();
                    }
                        cout<<sum<<"(unit. de timp). Sunteti de acord? (y/n)\n";
                        cin>>acord;
                        if(acord=='n')
                        {
                            char acord2;
                            cout<<"Doriti sa asteptati la alt angajat? (y/n)\n";
                            cin>>acord2;
                            if(acord2=='n')
                            {
                                waiting_q.pop();
                                break;
                            }
                            else
                                break;
                        }
                        else
                        {
                            for(int i=sum;i>0;i--)
                                {
                                    cout<<i<<"s...";
                                }
                            while((garaje[0].getMasiniGaraj()).size()>0 && poz!=0)
                            {

                                cout<<endl;
                                garaje[0].deleteCar();
                                poz--;
                            }
                                waiting_q.front()->setTimp();
                                garaje[0].AddCar(waiting_q.front());
                                waiting_q.pop();
                                break;

                        }
                    }
                }
                else if(tip_masina=="Camion")
                {
                    if(garaje[0].checkRoom4Camion())
                    {
                        waiting_q.front()->setTimp();
                        garaje[0].AddCar(waiting_q.front());
                        waiting_q.pop();
                        break;
                    }
                    else{
                    poz=1;
                    queue<Masina*> aux_masini=garaje[0].getMasiniGaraj();
                    while(aux_masini.size()>0)
                    {
                       if(aux_masini.front()->getType()=="Camion")
                       {
                           break;
                       }
                       poz++;
                       aux_masini.pop();
                    }
                    int sum=0,poz2=poz;
                    cout<<"Pentru a elibera un loc pt. masina '"<<(waiting_q.front())->getID()<<" "<<(waiting_q.front())->getType()<<"' este nevoie sa asteptati timpul de: ";
                    aux_masini=garaje[0].getMasiniGaraj();
                    while(aux_masini.size()>0 && poz2!=0)
                    {
                       sum=sum+aux_masini.front()->getTimp();
                       poz2--;
                       aux_masini.pop();
                    }
                        cout<<sum<<"(unit. de timp). Sunteti de acord? (y/n)\n";
                        cin>>acord;
                        if(acord=='n')
                        {
                            char acord2;
                            cout<<"Doriti sa asteptati la alt angajat? (y/n)\n";
                            cin>>acord2;
                            if(acord2=='n')
                            {
                                waiting_q.pop();
                                break;
                            }
                            else
                                break;
                        }
                        else
                        {
                            for(int i=sum;i>0;i--)
                                {
                                    cout<<i<<"s...";
                                }
                            while((garaje[0].getMasiniGaraj()).size()>0 && poz!=0)
                            {

                                cout<<endl;
                                garaje[0].deleteCar();
                                poz--;
                            }
                                waiting_q.front()->setTimp();
                                garaje[0].AddCar(waiting_q.front());
                                waiting_q.pop();
                                break;

                        }
                    }
                }

            }
            case 2:
            {
                if(tip_masina=="Standard")
                {
                    if(garaje[1].checkRoom4Standard())
                    {
                        waiting_q.front()->setTimp();
                        garaje[1].AddCar(waiting_q.front());
                        waiting_q.pop();
                        break;
                    }
                    else{
                    poz=1;
                    queue<Masina*> aux_masini=garaje[1].getMasiniGaraj();
                    while(aux_masini.size()>0)
                    {
                       if(aux_masini.front()->getType()=="Standard")
                       {
                           break;
                       }
                       poz++;
                       aux_masini.pop();
                    }
                    int sum=0,poz2=poz;
                    cout<<"Pentru a elibera un loc pt. masina '"<<(waiting_q.front())->getID()<<" "<<(waiting_q.front())->getType()<<"' este nevoie sa asteptati timpul de: ";
                    aux_masini=garaje[1].getMasiniGaraj();
                    while(aux_masini.size()>0 && poz2!=0)
                    {
                       sum=sum+aux_masini.front()->getTimp();
                       poz2--;
                       aux_masini.pop();
                    }
                        cout<<sum<<"(unit. de timp). Sunteti de acord? (y/n)\n";
                        cin>>acord;
                        if(acord=='n')
                        {
                            char acord2;
                            cout<<"Doriti sa asteptati la alt angajat? (y/n)\n";
                            cin>>acord2;
                            if(acord2=='n')
                            {
                                waiting_q.pop();
                                break;
                            }
                            else
                                break;
                        }
                        else
                        {
                            for(int i=sum;i>0;i--)
                                {
                                    cout<<i<<"s...";
                                }
                                cout<<endl;
                            while((garaje[1].getMasiniGaraj()).size()>0 && poz!=0)
                            {
                                garaje[1].deleteCar();
                                poz--;
                            }
                                waiting_q.front()->setTimp();
                                garaje[1].AddCar(waiting_q.front());
                                waiting_q.pop();
                                break;

                        }
                    }
                }
                else if(tip_masina=="Autobuz")
                {
                    if(garaje[1].checkRoom4Bus())
                    {
                        waiting_q.front()->setTimp();
                        garaje[1].AddCar(waiting_q.front());
                        waiting_q.pop();
                        break;
                    }
                    else{
                    poz=1;
                    queue<Masina*> aux_masini=garaje[1].getMasiniGaraj();
                    while(aux_masini.size()>0)
                    {
                       if(aux_masini.front()->getType()=="Autobuz")
                       {
                           break;
                       }
                       poz++;
                       aux_masini.pop();
                    }

                    int sum=0,poz2=poz;
                    cout<<"Pentru a elibera un loc pt. masina '"<<(waiting_q.front())->getID()<<" "<<(waiting_q.front())->getType()<<"' este nevoie sa asteptati timpul de: ";
                    aux_masini=garaje[1].getMasiniGaraj();
                    while(aux_masini.size()>0 && poz2!=0)
                    {
                       sum=sum+aux_masini.front()->getTimp();
                       poz2--;
                       aux_masini.pop();
                    }
                        cout<<sum<<"(unit. de timp). Sunteti de acord? (y/n)\n";
                        cin>>acord;
                        if(acord=='n')
                        {
                            char acord2;
                            cout<<"Doriti sa asteptati la alt angajat? (y/n)\n";
                            cin>>acord2;
                            if(acord2=='n')
                            {
                                waiting_q.pop();
                                break;
                            }
                            else
                                break;
                        }
                        else
                        {
                            for(int i=sum;i>0;i--)
                                {
                                    cout<<i<<"s...";
                                }
                            while((garaje[1].getMasiniGaraj()).size()>0 && poz!=0)
                            {

                                cout<<endl;
                                garaje[1].deleteCar();
                                poz--;
                            }
                                waiting_q.front()->setTimp();
                                garaje[1].AddCar(waiting_q.front());
                                waiting_q.pop();
                                break;

                        }
                    }
                }
                else if(tip_masina=="Camion")
                {
                    if(garaje[1].checkRoom4Camion())
                    {
                        waiting_q.front()->setTimp();
                        garaje[1].AddCar(waiting_q.front());
                        waiting_q.pop();
                        break;
                    }
                    else{
                    poz=1;
                    queue<Masina*> aux_masini=garaje[1].getMasiniGaraj();
                    while(aux_masini.size()>0)
                    {
                       if(aux_masini.front()->getType()=="Camion")
                       {
                           break;
                       }
                       poz++;
                       aux_masini.pop();
                    }
                    int sum=0,poz2=poz;
                    cout<<"Pentru a elibera un loc pt. masina '"<<(waiting_q.front())->getID()<<" "<<(waiting_q.front())->getType()<<"' este nevoie sa asteptati timpul de: ";
                    aux_masini=garaje[1].getMasiniGaraj();
                    while(aux_masini.size()>0 && poz2!=0)
                    {
                       sum=sum+aux_masini.front()->getTimp();
                       poz2--;
                       aux_masini.pop();
                    }
                        cout<<sum<<"(unit. de timp). Sunteti de acord? (y/n)\n";
                        cin>>acord;
                        if(acord=='n')
                        {
                            char acord2;
                            cout<<"Doriti sa asteptati la alt angajat? (y/n)\n";
                            cin>>acord2;
                            if(acord2=='n')
                            {
                                waiting_q.pop();
                                break;
                            }
                            else
                                break;
                        }
                        else
                        {
                            for(int i=sum;i>0;i--)
                                {
                                    cout<<i<<"s...";
                                }
                            while((garaje[1].getMasiniGaraj()).size()>0 && poz!=0)
                            {

                                cout<<endl;
                                garaje[1].deleteCar();
                                poz--;
                            }
                                waiting_q.front()->setTimp();
                                garaje[1].AddCar(waiting_q.front());
                                waiting_q.pop();
                                break;

                        }
                    }
                }
            }
            case 3:
            {
                if(tip_masina=="Standard")
                {
                    if(garaje[2].checkRoom4Standard())
                    {
                        waiting_q.front()->setTimp();
                        garaje[2].AddCar(waiting_q.front());
                        waiting_q.pop();
                        break;
                    }
                    else{
                    poz=1;
                    queue<Masina*> aux_masini=garaje[2].getMasiniGaraj();
                    while(aux_masini.size()>0)
                    {
                       if(aux_masini.front()->getType()=="Standard")
                       {
                           break;
                       }
                       poz++;
                       aux_masini.pop();
                    }
                    int sum=0,poz2=poz;
                    cout<<"Pentru a elibera un loc pt. masina '"<<(waiting_q.front())->getID()<<" "<<(waiting_q.front())->getType()<<"' este nevoie sa asteptati timpul de: ";
                    aux_masini=garaje[2].getMasiniGaraj();
                    while(aux_masini.size()>0 && poz2!=0)
                    {
                       sum=sum+aux_masini.front()->getTimp();
                       poz2--;
                       aux_masini.pop();
                    }
                        cout<<sum<<"(unit. de timp). Sunteti de acord? (y/n)\n";
                        cin>>acord;
                        if(acord=='n')
                        {
                            char acord2;
                            cout<<"Doriti sa asteptati la alt angajat? (y/n)\n";
                            cin>>acord2;
                            if(acord2=='n')
                            {
                                waiting_q.pop();
                                break;
                            }
                            else
                                break;
                        }
                        else
                        {
                            for(int i=sum;i>0;i--)
                                {
                                    cout<<i<<"s...";
                                }
                                cout<<endl;
                            while((garaje[2].getMasiniGaraj()).size()>0 && poz!=0)
                            {
                                garaje[2].deleteCar();
                                poz--;
                            }
                                waiting_q.front()->setTimp();
                                garaje[2].AddCar(waiting_q.front());
                                waiting_q.pop();
                                break;

                        }
                    }
                }
                else if(tip_masina=="Autobuz")
                {
                    if(garaje[2].checkRoom4Bus())
                    {
                        waiting_q.front()->setTimp();
                        garaje[2].AddCar(waiting_q.front());
                        waiting_q.pop();
                        break;
                    }
                    else{
                    poz=1;
                    queue<Masina*> aux_masini=garaje[2].getMasiniGaraj();
                    while(aux_masini.size()>0)
                    {
                       if(aux_masini.front()->getType()=="Autobuz")
                       {
                           break;
                       }
                       poz++;
                       aux_masini.pop();
                    }

                    int sum=0,poz2=poz;
                    cout<<"Pentru a elibera un loc pt. masina '"<<(waiting_q.front())->getID()<<" "<<(waiting_q.front())->getType()<<"' este nevoie sa asteptati timpul de: ";
                    aux_masini=garaje[2].getMasiniGaraj();
                    while(aux_masini.size()>0 && poz2!=0)
                    {
                       sum=sum+aux_masini.front()->getTimp();
                       poz2--;
                       aux_masini.pop();
                    }
                        cout<<sum<<"(unit. de timp). Sunteti de acord? (y/n)\n";
                        cin>>acord;
                        if(acord=='n')
                        {
                            char acord2;
                            cout<<"Doriti sa asteptati la alt angajat? (y/n)\n";
                            cin>>acord2;
                            if(acord2=='n')
                            {
                                waiting_q.pop();
                                break;
                            }
                            else
                                break;
                        }
                        else
                        {
                            for(int i=sum;i>0;i--)
                                {
                                    cout<<i<<"s...";
                                }
                                cout<<endl;
                            while((garaje[2].getMasiniGaraj()).size()>0 && poz!=0)
                            {
                                garaje[2].deleteCar();
                                poz--;
                            }
                                waiting_q.front()->setTimp();
                                garaje[2].AddCar(waiting_q.front());
                                waiting_q.pop();
                                break;

                        }
                    }
                }
                else if(tip_masina=="Camion")
                {
                    if(garaje[2].checkRoom4Camion())
                    {
                        waiting_q.front()->setTimp();
                        garaje[2].AddCar(waiting_q.front());
                        waiting_q.pop();
                        break;
                    }
                    else{
                    poz=1;
                    queue<Masina*> aux_masini=garaje[2].getMasiniGaraj();
                    while(aux_masini.size()>0)
                    {
                       if(aux_masini.front()->getType()=="Camion")
                       {
                           break;
                       }
                       poz++;
                       aux_masini.pop();
                    }
                    int sum=0,poz2=poz;
                    cout<<"Pentru a elibera un loc pt. masina '"<<(waiting_q.front())->getID()<<" "<<(waiting_q.front())->getType()<<"' este nevoie sa asteptati timpul de: ";
                    aux_masini=garaje[2].getMasiniGaraj();
                    while(aux_masini.size()>0 && poz2!=0)
                    {
                       sum=sum+aux_masini.front()->getTimp();
                       poz2--;
                       aux_masini.pop();
                    }
                        cout<<sum<<"(unit. de timp). Sunteti de acord? (y/n)\n";
                        cin>>acord;
                        if(acord=='n')
                        {
                            char acord2;
                            cout<<"Doriti sa asteptati la alt angajat? (y/n)\n";
                            cin>>acord2;
                            if(acord2=='n')
                            {
                                waiting_q.pop();
                                break;
                            }
                            else
                                break;
                        }
                        else
                        {
                            for(int i=sum;i>0;i--)
                                {
                                    cout<<i<<"s...";
                                }
                            while((garaje[2].getMasiniGaraj()).size()>0 && poz!=0)
                            {

                                cout<<endl;
                                garaje[2].deleteCar();
                                poz--;
                            }
                                waiting_q.front()->setTimp();
                                garaje[2].AddCar(waiting_q.front());
                                waiting_q.pop();
                                break;

                        }
                    }
                }
            }
            default:
                break;
            }
            cout<<flush;
            system("CLS");
        }
        }
    }
///SETARE AUTOMATA TOATE MASINILE:
    else if(urm=='y')
    {
        while(waiting_q.size()>0)
        {
            cout<<"----------------------------------------------------------------------------\n";
            garaje[0].afisare_qgaraj();
            garaje[1].afisare_qgaraj();
            garaje[2].afisare_qgaraj();
            if(garaje[2].checkFULL() && garaje[1].checkFULL() && garaje[0].checkFULL())
            {
                cout<<"\nTOATE GARAJELE SUNT PLINE\n";
                cout<<"Masinile ramase in coada:\n";
                left_out=waiting_q;
                while(left_out.size()>0)
                {
                    left_out.front()->afisare(cout);
                    left_out.pop();
                }
                goto continuare;
                //break;

            }
            tip_masina=(waiting_q.front())->getType();
            int full=0;
            for(auto itg=garaje.begin(); itg!=garaje.end(); itg++)
            {
                if(tip_masina=="Standard")
                {
                    if(itg->checkRoom4Standard())
                    {
                        (waiting_q.front())->setTimp();
                        itg->AddCar(waiting_q.front());
                        waiting_q.pop();
                        break;

                    }
                    else
                    {
                        full++;
                    }
                }
                else if(tip_masina=="Autobuz")
                {
                    if(itg->checkRoom4Bus())
                    {
                        (waiting_q.front())->setTimp();
                        itg->AddCar(waiting_q.front());
                        waiting_q.pop();
                        break;
                    }
                    else
                    {
                        full++;
                    }
                }
                else if(tip_masina=="Camion")
                {
                    if(itg->checkRoom4Camion())
                    {
                        (waiting_q.front())->setTimp();
                        itg->AddCar(waiting_q.front());
                        waiting_q.pop();
                        break;
                    }
                    else
                    {
                        full++;
                    }
                }
                if(full==3)
                    break;
            }


            cout<<flush;
            system("CLS");
        }

        continuare:
        char acord;
        cout<<"\nDoriti sa continuati alocarea? (y/n)\n";
        cin>>acord;
        if(acord=='y'){
        cout<<"\nALOCAREA MASINILOR DIN COADA RAMASA:\n";
        int poz=0;
        acord='x';
        while(waiting_q.size()>0)
        {
            garaje[0].afisare_qgaraj();
            garaje[1].afisare_qgaraj();
            garaje[2].afisare_qgaraj();
            tip_masina=(waiting_q.front())->getType();
            cout<<"\nMasina '"<<(waiting_q.front())->getID()<<" "<<(waiting_q.front())->getType()<<"' la ce garaj doriti sa intrati?(1/2/3): ";
            cin>>id;
            cout<<endl<<"----------------------------------------------------------------------------\n";
            switch (id)
            {
            case 1:
            {
                if(tip_masina=="Standard")
                {
                    if(garaje[0].checkRoom4Standard())
                    {
                        waiting_q.front()->setTimp();
                        garaje[0].AddCar(waiting_q.front());
                        waiting_q.pop();
                        break;
                    }
                    else{
                    poz=1;
                    queue<Masina*> aux_masini=garaje[0].getMasiniGaraj();
                    while(aux_masini.size()>0)
                    {
                       if(aux_masini.front()->getType()=="Standard")
                       {
                           break;
                       }
                       poz++;
                       aux_masini.pop();
                    }
                    int sum=0,poz2=poz;
                    cout<<"Pentru a elibera un loc pt. masina '"<<(waiting_q.front())->getID()<<" "<<(waiting_q.front())->getType()<<"' este nevoie sa asteptati timpul de: ";
                    aux_masini=garaje[0].getMasiniGaraj();
                    while(aux_masini.size()>0 && poz2!=0)
                    {
                       sum=sum+aux_masini.front()->getTimp();
                       poz2--;
                       aux_masini.pop();
                    }
                        cout<<sum<<"(unit. de timp). Sunteti de acord? (y/n)\n";
                        cin>>acord;
                        if(acord=='n')
                        {
                            char acord2;
                            cout<<"Doriti sa asteptati la alt angajat? (y/n)\n";
                            cin>>acord2;
                            if(acord2=='n')
                            {
                                waiting_q.pop();
                                break;
                            }
                            else
                                break;
                        }
                        else
                        {
                            for(int i=sum;i>0;i--)
                                {
                                    cout<<i<<"s...";
                                }
                                cout<<endl;
                            while((garaje[0].getMasiniGaraj()).size()>0 && poz!=0)
                            {
                                garaje[0].deleteCar();
                                poz--;
                            }
                                waiting_q.front()->setTimp();
                                garaje[1].AddCar(waiting_q.front());
                                waiting_q.pop();
                                break;

                        }
                    }
                }
                else if(tip_masina=="Autobuz")
                {
                    if(garaje[0].checkRoom4Bus())
                    {
                        waiting_q.front()->setTimp();
                        garaje[0].AddCar(waiting_q.front());
                        waiting_q.pop();
                        break;
                    }
                    else{
                    poz=1;
                    queue<Masina*> aux_masini=garaje[0].getMasiniGaraj();
                    while(aux_masini.size()>0)
                    {
                       if(aux_masini.front()->getType()=="Autobuz")
                       {
                           break;
                       }
                       poz++;
                       aux_masini.pop();
                    }

                    int sum=0,poz2=poz;
                    cout<<"Pentru a elibera un loc pt. masina '"<<(waiting_q.front())->getID()<<" "<<(waiting_q.front())->getType()<<"' este nevoie sa asteptati timpul de: ";
                    aux_masini=garaje[0].getMasiniGaraj();
                    while(aux_masini.size()>0 && poz2!=0)
                    {
                       sum=sum+aux_masini.front()->getTimp();
                       poz2--;
                       aux_masini.pop();
                    }
                        cout<<sum<<"(unit. de timp). Sunteti de acord? (y/n)\n";
                        cin>>acord;
                        if(acord=='n')
                        {
                            char acord2;
                            cout<<"Doriti sa asteptati la alt angajat? (y/n)\n";
                            cin>>acord2;
                            if(acord2=='n')
                            {
                                waiting_q.pop();
                                break;
                            }
                            else
                                break;
                        }
                        else
                        {
                            for(int i=sum;i>0;i--)
                                {
                                    cout<<i<<"s...";
                                }
                            while((garaje[0].getMasiniGaraj()).size()>0 && poz!=0)
                            {

                                cout<<endl;
                                garaje[0].deleteCar();
                                poz--;
                            }
                                waiting_q.front()->setTimp();
                                garaje[0].AddCar(waiting_q.front());
                                waiting_q.pop();
                                break;

                        }
                    }
                }
                else if(tip_masina=="Camion")
                {
                    if(garaje[0].checkRoom4Camion())
                    {
                        waiting_q.front()->setTimp();
                        garaje[0].AddCar(waiting_q.front());
                        waiting_q.pop();
                        break;
                    }
                    else{
                    poz=1;
                    queue<Masina*> aux_masini=garaje[0].getMasiniGaraj();
                    while(aux_masini.size()>0)
                    {
                       if(aux_masini.front()->getType()=="Camion")
                       {
                           break;
                       }
                       poz++;
                       aux_masini.pop();
                    }
                    int sum=0,poz2=poz;
                    cout<<"Pentru a elibera un loc pt. masina '"<<(waiting_q.front())->getID()<<" "<<(waiting_q.front())->getType()<<"' este nevoie sa asteptati timpul de: ";
                    aux_masini=garaje[0].getMasiniGaraj();
                    while(aux_masini.size()>0 && poz2!=0)
                    {
                       sum=sum+aux_masini.front()->getTimp();
                       poz2--;
                       aux_masini.pop();
                    }
                        cout<<sum<<"(unit. de timp). Sunteti de acord? (y/n)\n";
                        cin>>acord;
                        if(acord=='n')
                        {
                            char acord2;
                            cout<<"Doriti sa asteptati la alt angajat? (y/n)\n";
                            cin>>acord2;
                            if(acord2=='n')
                            {
                                waiting_q.pop();
                                break;
                            }
                            else
                                break;
                        }
                        else
                        {
                            for(int i=sum;i>0;i--)
                                {
                                    cout<<i<<"s...";
                                }
                            while((garaje[0].getMasiniGaraj()).size()>0 && poz!=0)
                            {

                                cout<<endl;
                                garaje[0].deleteCar();
                                poz--;
                            }
                                waiting_q.front()->setTimp();
                                garaje[0].AddCar(waiting_q.front());
                                waiting_q.pop();
                                break;

                        }
                    }
                }

            }
            case 2:
            {
                if(tip_masina=="Standard")
                {
                    if(garaje[1].checkRoom4Standard())
                    {
                        waiting_q.front()->setTimp();
                        garaje[1].AddCar(waiting_q.front());
                        waiting_q.pop();
                        break;
                    }
                    else{
                    poz=1;
                    queue<Masina*> aux_masini=garaje[1].getMasiniGaraj();
                    while(aux_masini.size()>0)
                    {
                       if(aux_masini.front()->getType()=="Standard")
                       {
                           break;
                       }
                       poz++;
                       aux_masini.pop();
                    }
                    int sum=0,poz2=poz;
                    cout<<"Pentru a elibera un loc pt. masina '"<<(waiting_q.front())->getID()<<" "<<(waiting_q.front())->getType()<<"' este nevoie sa asteptati timpul de: ";
                    aux_masini=garaje[1].getMasiniGaraj();
                    while(aux_masini.size()>0 && poz2!=0)
                    {
                       sum=sum+aux_masini.front()->getTimp();
                       poz2--;
                       aux_masini.pop();
                    }
                        cout<<sum<<"(unit. de timp). Sunteti de acord? (y/n)\n";
                        cin>>acord;
                        if(acord=='n')
                        {
                            char acord2;
                            cout<<"Doriti sa asteptati la alt angajat? (y/n)\n";
                            cin>>acord2;
                            if(acord2=='n')
                            {
                                waiting_q.pop();
                                break;
                            }
                            else
                                break;
                        }
                        else
                        {
                            for(int i=sum;i>0;i--)
                                {
                                    cout<<i<<"s...";
                                }
                                cout<<endl;
                            while((garaje[1].getMasiniGaraj()).size()>0 && poz!=0)
                            {
                                garaje[1].deleteCar();
                                poz--;
                            }
                                waiting_q.front()->setTimp();
                                garaje[1].AddCar(waiting_q.front());
                                waiting_q.pop();
                                break;

                        }
                    }
                }
                else if(tip_masina=="Autobuz")
                {
                    if(garaje[1].checkRoom4Bus())
                    {
                        waiting_q.front()->setTimp();
                        garaje[1].AddCar(waiting_q.front());
                        waiting_q.pop();
                        break;
                    }
                    else{
                    poz=1;
                    queue<Masina*> aux_masini=garaje[1].getMasiniGaraj();
                    while(aux_masini.size()>0)
                    {
                       if(aux_masini.front()->getType()=="Autobuz")
                       {
                           break;
                       }
                       poz++;
                       aux_masini.pop();
                    }

                    int sum=0,poz2=poz;
                    cout<<"Pentru a elibera un loc pt. masina '"<<(waiting_q.front())->getID()<<" "<<(waiting_q.front())->getType()<<"' este nevoie sa asteptati timpul de: ";
                    aux_masini=garaje[1].getMasiniGaraj();
                    while(aux_masini.size()>0 && poz2!=0)
                    {
                       sum=sum+aux_masini.front()->getTimp();
                       poz2--;
                       aux_masini.pop();
                    }
                        cout<<sum<<"(unit. de timp). Sunteti de acord? (y/n)\n";
                        cin>>acord;
                        if(acord=='n')
                        {
                            char acord2;
                            cout<<"Doriti sa asteptati la alt angajat? (y/n)\n";
                            cin>>acord2;
                            if(acord2=='n')
                            {
                                waiting_q.pop();
                                break;
                            }
                            else
                                break;
                        }
                        else
                        {
                            for(int i=sum;i>0;i--)
                                {
                                    cout<<i<<"s...";
                                }
                            while((garaje[1].getMasiniGaraj()).size()>0 && poz!=0)
                            {

                                cout<<endl;
                                garaje[1].deleteCar();
                                poz--;
                            }
                                waiting_q.front()->setTimp();
                                garaje[1].AddCar(waiting_q.front());
                                waiting_q.pop();
                                break;

                        }
                    }
                }
                else if(tip_masina=="Camion")
                {
                    if(garaje[1].checkRoom4Camion())
                    {
                        waiting_q.front()->setTimp();
                        garaje[1].AddCar(waiting_q.front());
                        waiting_q.pop();
                        break;
                    }
                    else{
                    poz=1;
                    queue<Masina*> aux_masini=garaje[1].getMasiniGaraj();
                    while(aux_masini.size()>0)
                    {
                       if(aux_masini.front()->getType()=="Camion")
                       {
                           break;
                       }
                       poz++;
                       aux_masini.pop();
                    }
                    int sum=0,poz2=poz;
                    cout<<"Pentru a elibera un loc pt. masina '"<<(waiting_q.front())->getID()<<" "<<(waiting_q.front())->getType()<<"' este nevoie sa asteptati timpul de: ";
                    aux_masini=garaje[1].getMasiniGaraj();
                    while(aux_masini.size()>0 && poz2!=0)
                    {
                       sum=sum+aux_masini.front()->getTimp();
                       poz2--;
                       aux_masini.pop();
                    }
                        cout<<sum<<"(unit. de timp). Sunteti de acord? (y/n)\n";
                        cin>>acord;
                        if(acord=='n')
                        {
                            char acord2;
                            cout<<"Doriti sa asteptati la alt angajat? (y/n)\n";
                            cin>>acord2;
                            if(acord2=='n')
                            {
                                waiting_q.pop();
                                break;
                            }
                            else
                                break;
                        }
                        else
                        {
                            for(int i=sum;i>0;i--)
                                {
                                    cout<<i<<"s...";
                                }
                            while((garaje[1].getMasiniGaraj()).size()>0 && poz!=0)
                            {

                                cout<<endl;
                                garaje[1].deleteCar();
                                poz--;
                            }
                                waiting_q.front()->setTimp();
                                garaje[1].AddCar(waiting_q.front());
                                waiting_q.pop();
                                break;

                        }
                    }
                }
            }
            case 3:
            {
                if(tip_masina=="Standard")
                {
                    if(garaje[2].checkRoom4Standard())
                    {
                        waiting_q.front()->setTimp();
                        garaje[2].AddCar(waiting_q.front());
                        waiting_q.pop();
                        break;
                    }
                    else{
                    poz=1;
                    queue<Masina*> aux_masini=garaje[2].getMasiniGaraj();
                    while(aux_masini.size()>0)
                    {
                       if(aux_masini.front()->getType()=="Standard")
                       {
                           break;
                       }
                       poz++;
                       aux_masini.pop();
                    }
                    int sum=0,poz2=poz;
                    cout<<"Pentru a elibera un loc pt. masina '"<<(waiting_q.front())->getID()<<" "<<(waiting_q.front())->getType()<<"' este nevoie sa asteptati timpul de: ";
                    aux_masini=garaje[2].getMasiniGaraj();
                    while(aux_masini.size()>0 && poz2!=0)
                    {
                       sum=sum+aux_masini.front()->getTimp();
                       poz2--;
                       aux_masini.pop();
                    }
                        cout<<sum<<"(unit. de timp). Sunteti de acord? (y/n)\n";
                        cin>>acord;
                        if(acord=='n')
                        {
                            char acord2;
                            cout<<"Doriti sa asteptati la alt angajat? (y/n)\n";
                            cin>>acord2;
                            if(acord2=='n')
                            {
                                waiting_q.pop();
                                break;
                            }
                            else
                                break;
                        }
                        else
                        {
                            for(int i=sum;i>0;i--)
                                {
                                    cout<<i<<"s...";
                                }
                                cout<<endl;
                            while((garaje[2].getMasiniGaraj()).size()>0 && poz!=0)
                            {
                                garaje[2].deleteCar();
                                poz--;
                            }
                                waiting_q.front()->setTimp();
                                garaje[2].AddCar(waiting_q.front());
                                waiting_q.pop();
                                break;

                        }
                    }
                }
                else if(tip_masina=="Autobuz")
                {
                    if(garaje[2].checkRoom4Bus())
                    {
                        waiting_q.front()->setTimp();
                        garaje[2].AddCar(waiting_q.front());
                        waiting_q.pop();
                        break;
                    }
                    else{
                    poz=1;
                    queue<Masina*> aux_masini=garaje[2].getMasiniGaraj();
                    while(aux_masini.size()>0)
                    {
                       if(aux_masini.front()->getType()=="Autobuz")
                       {
                           break;
                       }
                       poz++;
                       aux_masini.pop();
                    }

                    int sum=0,poz2=poz;
                    cout<<"Pentru a elibera un loc pt. masina '"<<(waiting_q.front())->getID()<<" "<<(waiting_q.front())->getType()<<"' este nevoie sa asteptati timpul de: ";
                    aux_masini=garaje[2].getMasiniGaraj();
                    while(aux_masini.size()>0 && poz2!=0)
                    {
                       sum=sum+aux_masini.front()->getTimp();
                       poz2--;
                       aux_masini.pop();
                    }
                        cout<<sum<<"(unit. de timp). Sunteti de acord? (y/n)\n";
                        cin>>acord;
                        if(acord=='n')
                        {
                            char acord2;
                            cout<<"Doriti sa asteptati la alt angajat? (y/n)\n";
                            cin>>acord2;
                            if(acord2=='n')
                            {
                                waiting_q.pop();
                                break;
                            }
                            else
                                break;
                        }
                        else
                        {
                            for(int i=sum;i>0;i--)
                                {
                                    cout<<i<<"s...";
                                }
                                cout<<endl;
                            while((garaje[2].getMasiniGaraj()).size()>0 && poz!=0)
                            {
                                garaje[2].deleteCar();
                                poz--;
                            }
                                waiting_q.front()->setTimp();
                                garaje[2].AddCar(waiting_q.front());
                                waiting_q.pop();
                                break;

                        }
                    }
                }
                else if(tip_masina=="Camion")
                {
                    if(garaje[2].checkRoom4Camion())
                    {
                        waiting_q.front()->setTimp();
                        garaje[2].AddCar(waiting_q.front());
                        waiting_q.pop();
                        break;
                    }
                    else{
                    poz=1;
                    queue<Masina*> aux_masini=garaje[2].getMasiniGaraj();
                    while(aux_masini.size()>0)
                    {
                       if(aux_masini.front()->getType()=="Camion")
                       {
                           break;
                       }
                       poz++;
                       aux_masini.pop();
                    }
                    int sum=0,poz2=poz;
                    cout<<"Pentru a elibera un loc pt. masina '"<<(waiting_q.front())->getID()<<" "<<(waiting_q.front())->getType()<<"' este nevoie sa asteptati timpul de: ";
                    aux_masini=garaje[2].getMasiniGaraj();
                    while(aux_masini.size()>0 && poz2!=0)
                    {
                       sum=sum+aux_masini.front()->getTimp();
                       poz2--;
                       aux_masini.pop();
                    }
                        cout<<sum<<"(unit. de timp). Sunteti de acord? (y/n)\n";
                        cin>>acord;
                        if(acord=='n')
                        {
                            char acord2;
                            cout<<"Doriti sa asteptati la alt angajat? (y/n)\n";
                            cin>>acord2;
                            if(acord2=='n')
                            {
                                waiting_q.pop();
                                break;
                            }
                            else
                                break;
                        }
                        else
                        {
                            for(int i=sum;i>0;i--)
                                {
                                    cout<<i<<"s...";
                                }
                            while((garaje[2].getMasiniGaraj()).size()>0 && poz!=0)
                            {

                                cout<<endl;
                                garaje[2].deleteCar();
                                poz--;
                            }
                                waiting_q.front()->setTimp();
                                garaje[2].AddCar(waiting_q.front());
                                waiting_q.pop();
                                break;

                        }
                    }
                }
            }
            default:
                break;
            }
            cout<<flush;
            system("CLS");
        }
      }
    }
    cout<<flush;
    system("CLS");
    cout<<"ALOCAREA FINALA A GARAJELOR:\n";
    cout<<"Doriti sa plece toate masinile?(y/n)\n";
    char x;
    cin>>x;
    if(x=='y')
    {
        garaje[0].deleteMasini();
        garaje[1].deleteMasini();
        garaje[2].deleteMasini();
        garaje[0].afisare_qgaraj();
        garaje[1].afisare_qgaraj();
        garaje[2].afisare_qgaraj();
        cout<<"Multumesc pentru utilizarea aplicatiei!";
    }
    else
    {
        garaje[0].afisare_qgaraj();
        garaje[1].afisare_qgaraj();
        garaje[2].afisare_qgaraj();
        cout<<"Multumesc pentru utilizarea aplicatiei!";
    }

}




