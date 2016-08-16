#pragma once

#include <cmath>
#include <cstdlib>
#include <random>
#include <fstream>
#include <functional>
#include <cstring>
#include "globals.h"
#include "myrandom.h"



double randn();

const double PI = 3.14159265358979323846;

#ifndef _INSIZE
#define _INSIZE
const int INSIZE = 198;
#endif
const int HIDSIZE = 80;

inline double sigmoid(double z)
{
	return 1.0 / (1.0 + exp(-z));
}

inline double sigmoid_prime(double z)
{
	return sigmoid(z)*(1 - sigmoid(z));
}



class evaluatorbase
{
public:
	virtual ~evaluatorbase() {}

	virtual double evaluate(const double input[INSIZE]) const=0;
	virtual void update(const double input[INSIZE], double output)=0;
};

class evaluatorlambda :public evaluatorbase
{
public:
	evaluatorlambda(const std::function<double(const double[INSIZE])>& eval, const std::function<void(const double[INSIZE], double output)>& updt);
	~evaluatorlambda();
	double evaluate(const double input[INSIZE]) const;
	void update(const double input[INSIZE], double output);
private:
	std::function<double(const double[INSIZE])> foo_eval;
	std::function<void(const double[INSIZE], double output)> foo_updt;
};

class random_evaluator:public evaluatorbase
{
public:
	virtual ~random_evaluator() {}

	double evaluate(const double input[INSIZE]) const;
	void update(const double input[INSIZE], double output);
};

class network:public evaluatorbase
{
public:
	network(double eta = 0.01, double decay = 0.7);
	~network();
	double evaluate(const double input[INSIZE]) const;
	double evaluate(const double input[INSIZE], double hidz[HIDSIZE], double* outz) const;
	void update(const double input[INSIZE], double output);
	void set_eta(double neta);
	void export_weights(double ws[INSIZE + 1][HIDSIZE]);
	int no;
	bool operator==(const network& other) const ;
private:
	void backprop(const double input[INSIZE], double nabla_b0[HIDSIZE], double* nabla_b1, double nabla_w0[INSIZE][HIDSIZE], double nabla_w1[HIDSIZE]);
	double biases0[HIDSIZE];
	double biases1;
	double weights0[INSIZE][HIDSIZE];
	double weights1[HIDSIZE];
	double e_b0[HIDSIZE];
	double e_b1;
	double e_w0[INSIZE][HIDSIZE];
	double e_w1[HIDSIZE];
	double eta;
	double decay;
};

double sigmoid_prime(double z);
double sigmoid(double z);
double randn();
