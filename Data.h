#pragma once
#include <ctime>
#include <iostream>
#include <string>
using namespace std;
static time_t now=time(0);
static tm *ltm=localtime(&now);
class Data
{
    int zi;
    int luna;
    int an;
    static int zi_azi;
    static int luna_azi;
    static int an_azi;
public:
    Data() {};
    Data(int x, int y, int z);
    Data(Data &x);
    ~Data() {};
    Data& operator=(Data &x);
    int getZi();
    int getLuna();
    int getAn();

    Data getAzi();

    bool check_18(Data data_a2);
    bool check_viitor();
    void afisare_data(ostream &out);

    void set_data(int x, int y, int z);
    //void set_zi(int zi2);
    //void set_luna(int luna2);
    //void set_an(int an2);

};
