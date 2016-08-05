#include <cmath>

const int INSIZE = 198;
const int HIDSIZE = 50;

class network
{
public:
	network(double eta = 0.01, double decay = 0.7);
	~network();
	double evaluate(double input[INSIZE]);
	double evaluate(double input[INSIZE], double hidz[HIDSIZE], double* outz);
	void update(double input[INSIZE], double output);
private:
	void backprop(double input[INSIZE], double nabla_b0[HIDSIZE], double* nabla_b1, double nabla_w0[INSIZE][HIDSIZE], double nabla_w1[HIDSIZE]);
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