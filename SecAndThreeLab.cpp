
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include "diff.h"


void init_consts(double*& consts)  // Инициализируем элементы
{
    srand(time(0));
    consts = new double[4];
    consts[0] = (double)(rand()) / 10000;    
    consts[1] = (double)(rand()) / 10000;   
    consts[2] = (double)(rand()) / 10000;    
    consts[3] = (double)(rand()) / 10000;  
}

Case::Case(int N, double L)
{
    init_consts(consts);
    Lx = L;
    NumPoint = N;
    h = L / N;
    dt = h * h / 4.0;
    T = vector(0.0, NumPoint);
    dT = vector(0.0, NumPoint);
    v = vector(0.0, NumPoint);
    dv = vector(0.0, NumPoint);
};

void diff_T(vector& T, vector& dT)
{
    for (size_t counter = 1; counter < T.size() - 2; ++counter)
        dT[counter] = T[counter + 1] + T[counter - 1] - 2 * T[counter];
}

void diff_v(vector& v, vector& dv)
{
    for (size_t counter = 1; counter < v.size() - 2; ++counter)
        dv[counter] = v[counter + 1] + v[counter - 1] - 2 * v[counter];
}

void Case::setInitial(vector T_in, vector v_in)
{
    T = T_in;
    v = v_in;
};

void Case::step()
{
    double _Nu = consts[0] / (h * h);
    double _Hi = consts[1] / (h * h);
    double dth = dt * h;
    double _param = consts[2] / consts[3];
    diff_v(v, dv);
    v = v + dt * (dv * _Nu - _param);
    diff_T(T, dT);
    T = T + dt * (_Hi * dT + v * (T.shift(-1) - T.shift(1)) / (2 * h));

}

void Case::write(std::string name)
{
    std::ofstream out;
    out.open(name);

    out << std::setw(5) << "x";
    out << std::setw(15) << "v";
    out << std::setw(15) << "T";
    out << std::endl;
    for (int i = 0; i < NumPoint; i++)
    {
        out << std::setw(5) << i * h;
        out << std::setw(15) << v[i];
        out << std::setw(15) << T[i];
        out << std::endl;
    }
    out.close();
}
Case::~Case() { delete[] consts; }
