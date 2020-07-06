#pragma once
#include <valarray>
#include <string>

using vector = std::valarray<double>;


class Case
{
public:
	int NumPoint;
	double* consts;
	double Lx;
	double dt;
	double h;
	vector v;
	vector dv;
	vector T;
	vector dT;
	Case(int NumPoint, double L);
	void setInitial(vector T, vector v);
	void step();
	void write(std::string);

	~Case();
};
