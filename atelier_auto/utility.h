#include "Atelier.h"
#include <bits/stdc++.h>
#include <vector>
#include <list>
#include <time.h>
#include <random>
using namespace std;
///Vector angajati (am prescurtat angajati cu a2):
vector<Angajat*> creare_lista_angajati();
vector<Angajat*> adauga_angajat(vector<Angajat*> a2);
vector<Angajat*> sterge_angajat(int id, vector<Angajat*> a2);
vector<Angajat*> edit_angajat(int id, vector<Angajat*> a2);
void afis_salariu_id(int id,vector<Angajat*>a2);
void afisare_angajati(ostream &out, vector<Angajat*> a2);
void operatii_angajati();

///Masini:
void  creare_file_masini(list<Masina*> aux);
list<Masina*> creare_lista_masini();
