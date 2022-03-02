#include "utility.h"
#include <chrono>
#include <random>
using namespace std;
//static vector<Angajat*> angajati;
int main()
{
    cout<<"Doriti sa realizati operatii cu niste angajati?(y/n)\n";
    char c,c2;
    cin>>c;
    if(c=='y') operatii_angajati();


    vector<Angajat*> angajati;
    angajati=creare_lista_angajati();

    list<Masina*> masini;
    masini=creare_lista_masini();
    creare_file_masini(masini);

//    time_t now;
//    time(&now);
//    struct tm t0;
//    t0.tm_sec=0;
//    struct tm acum;
//    acum=*localtime(&now);
//    t0.tm_sec=0;
//    double seconds=difftime(now,mktime(&acum));
//    cout<<"Timpul trecut de acum un minut:";
//    cout<<seconds<<" secunde\n";
//    seconds=acum.tm_sec-t0.tm_sec;
//    cout<<"Timpul trecut de acum un minut:";
//    cout<<seconds<<" secunde";
//    for(int i=0;i<10;i++)
//    {
//        cout<<"\n Apasa 'c' pentru a continua...\n";
//
//        do{
//            cin>>c;
//            //acum=time(&now);
//            if(c=='c')
//            {
//            time(&now);
//            seconds=difftime(now,mktime(&t0));
//            cout<<"Timpul trecut de acum un minut:";
//            cout<<seconds<<" secunde";
//            }
//        }while(c!='c');
//
//    }

    Atelier atelier(angajati);
    if(atelier.checkStatus()=="Deschis")
    {
        cout<<"\nATELIERUL NOSTRU ESTE DESCHIS!\n Angajatii prezenti:\n";
        afisare_angajati(cout,angajati);
        cout<<"---------------------------------------------";
        cout<<"\n Apasa 'c' pentru a continua...\n";

        do{
            cin>>c;
            if(c=='c')
            {
                cout<<flush;
                system("CLS");
                for(auto itm=masini.begin(); itm!=masini.end(); itm++)
                {
                    atelier.addToWait_q((*itm));
                }
                atelier.printWait_q();
                cout<<"\n Apasa 'c' pentru a continua...\n";

               do{
                cin>>c2;
               if(c2=='c')
                {
                cout<<flush;
                system("CLS");
                atelier.creareGaraje();
               }
               }while(c2!='c');
            }
        }while(c!='c');
    }
    else cout<<"Atelierul este inchis, ne pare rau.";


    return 0;
}
