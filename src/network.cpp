#include "network.h"






evaluatorlambda::evaluatorlambda(const std::function<double(const double[INSIZE])>& eval, const std::function<void(const double[INSIZE], double output)>& updt)
{
	this->foo_eval = eval;
	this->foo_updt = updt;
}

evaluatorlambda::~evaluatorlambda() {}

double evaluatorlambda::evaluate(const double input[INSIZE]) const
{
	return this->foo_eval(input);
}

void evaluatorlambda::update(const double input[INSIZE], double output)
{
	this->foo_updt(input, output);
}



/*double randn()
{
    double u1 = fRand(); //these are uniform(0,1) random doubles
    double u2 = fRand();
    double randStdNormal = sqrt(-2.0 * log(u1)) *
                sin(2.0 * PI * u2); //random normal(0,1)
    return randStdNormal;
}*/

double random_evaluator::evaluate(const double input[INSIZE]) const
{
    return randf();
}
void random_evaluator::update(const double input[INSIZE], double output)
{
    return;
}

union snet 
{
	network net;
	char bytes[sizeof(network)];
	snet() {}
	~snet() {}
};
network::network(double eta, double decay)
{
    this->no = 0;
    this->eta = eta;
    this->decay = decay;
    
    biases1 = randn();
    e_b1 = 0;
    for (int i = 0; i < HIDSIZE; i++)
    {
        biases0[i] = randn();
        weights1[i] = randn();
        e_b0[i] = 0;
        e_w1[i] = 0;
    }
    for (int k = 0; k < INSIZE ; k++)
     for (int i = 0; i < HIDSIZE; i++)
     {
         weights0[k][i] = randn();
         e_w0[k][i] = 0;
     }
}
network::~network()
{
    this->eta = 0.01;
    this->decay = 0.7;
}
void network::set_eta(double neta)
{
	this->eta = neta;
}
void network::export_weights(double ws[INSIZE + 3][HIDSIZE])
{
	for (int i = 0; i < INSIZE; i++)
		for (int k = 0; k < HIDSIZE; k++)
		{
			ws[i][k] = weights0[i][k];
		}
	for (int k = 0; k < HIDSIZE; k++)
	{
		ws[INSIZE][k] = weights1[k];
	}
	for (int k = 0; k < HIDSIZE; k++)
	{
		ws[INSIZE + 1][k] = biases0[k];
	}
	for (int k = 0; k < HIDSIZE; k++)
	{
		ws[INSIZE + 2][k] = 0.0;
	}
	ws[INSIZE + 2][0] = biases1;
}
double network::evaluate(const double input[INSIZE]) const
{
	static double hidden[HIDSIZE] = { 0.0 };
	double output = 0.0;

	#pragma omp parallel for
	for (int i = 0; i < HIDSIZE; i++)
	{
		double mval = 0.0;
		for (int k = 0; k < INSIZE; k++)
			mval += input[k] * weights0[k][i];
		mval += biases0[i];
		hidden[i] = sigmoid(mval);
	}

	{
		double mval = 0.0;
		for (int k = 0; k < HIDSIZE; k++)
			mval += hidden[k] * weights1[k];
		mval += biases1;
		output = sigmoid(mval);
	}


	return output;
}
double network::evaluate(const double input[INSIZE], double hidz[HIDSIZE], double* outz) const
{
    static double hidden[HIDSIZE] = {0.0};
    double output = 0.0;
    
    for (int i = 0; i < HIDSIZE; i++)
    {
        double mval = 0.0;
        for (int k = 0; k < INSIZE; k++)
            mval += input[k] * weights0[k][i];
        mval += biases0[i];
        hidz[i] = mval;
        hidden[i] = sigmoid(mval);
    }
    
    {
        double mval = 0.0;
        for (int k = 0; k < HIDSIZE; k++)
            mval += hidden[k] * weights1[k];
        mval +=  biases1;
        *outz = mval;
        output = sigmoid(mval);
    }
    
    
    return output;
}
void network::update(const double input[INSIZE], double output)
{
    //double* nabla_b[2], nabla_w[2];
    double nabla_b0[HIDSIZE];
    double nabla_b1 = 0.0;
    double nabla_w0[INSIZE][HIDSIZE];
    double nabla_w1[HIDSIZE];
    
	double prediction = backprop(input, nabla_b0, &nabla_b1, nabla_w0, nabla_w1);
    
    //printf("%lf\n",nabla_b0[0]);
    
    e_b1 = decay * e_b1 + nabla_b1;
    for (int i = 0; i < HIDSIZE; i++)
    {
        e_b0[i] = decay * e_b0[i] + nabla_b0[i];
        e_w1[i] = decay * e_w1[i] + nabla_w1[i];
    }
    for (int k = 0; k < INSIZE ; k++)
     for (int i = 0; i < HIDSIZE; i++)
     {
         e_w0[k][i] = decay * e_w0[k][i] + nabla_w0[k][i];
     }
    
    
    //done decay
    
    //double prediction = this->evaluate(input);
    double gamma = -(output - prediction);
    
    biases1 = biases1 - eta * gamma * e_b1;
    for (int i = 0; i < HIDSIZE; i++)
    {
        biases0[i] = biases0[i] - eta * gamma * e_b0[i];
        weights1[i] = weights1[i] - eta * gamma * e_w1[i];
    }
    for (int k = 0; k < INSIZE ; k++)
     for (int i = 0; i < HIDSIZE; i++)
     {
         weights0[k][i] = weights0[k][i] - eta * gamma * e_w0[k][i];
     }
    
}
double network::backprop(const double input[INSIZE], double nabla_b0[HIDSIZE], double* nabla_b1, double nabla_w0[INSIZE][HIDSIZE], double nabla_w1[HIDSIZE])
{
    //printf("%d\n",nono);
    
    double outerror = 0.0;
    double hiderror[HIDSIZE];
    
    double hidz[HIDSIZE];
    double outz = 0.0;
    double output = evaluate(input, hidz, &outz);
    double hidden[HIDSIZE];
    
    for (int i = 0; i < HIDSIZE; i++)
        hidden[i] = sigmoid(hidz[i]);
    
    outerror = 1 * sigmoid_prime(outz);
    for (int i = 0; i < HIDSIZE; i++)
    {
        hiderror[i] = weights1[i] * outerror * sigmoid_prime(hidz[i]);
    }
    
    *nabla_b1 = outerror;
    for (int j = 0; j < HIDSIZE; j++)
        nabla_b0[j] = hiderror[j];
        
    for (int k = 0; k < HIDSIZE; k++)
        nabla_w1[k] = hidden[k] * outerror;
    
    for (int k = 0; k < INSIZE; k++)
     for (int j = 0; j < HIDSIZE; j++)
     {
         nabla_w0[k][j] = input[k] * hiderror[j];
     }
	return output;
}


bool network::operator==(const network& other) const
{
    bool result = true;
    result &= no == other.no;
    result &= biases1 == other.biases1;
    result &= e_b1 == other.e_b1;
    result &= eta == other.eta;
    result &= decay == other.decay;
    result &= memcmp(biases0, other.biases0, HIDSIZE * sizeof(double)) == 0;
    result &= memcmp(weights0, other.weights0, INSIZE * HIDSIZE * sizeof(double)) == 0;
    result &= memcmp(weights1, other.weights1, HIDSIZE * sizeof(double)) == 0;
    result &= memcmp(e_b0, other.e_b0, HIDSIZE * sizeof(double)) == 0;
    result &= memcmp(e_w0, other.e_w0, INSIZE * HIDSIZE * sizeof(double)) == 0;
    result &= memcmp(e_w1, other.e_w1, HIDSIZE * sizeof(double)) == 0;
    return result;
}
/*
int no;
double biases1;
double e_b1;
double eta;
double decay;
double biases0[HIDSIZE];
double weights0[INSIZE][HIDSIZE];
double weights1[HIDSIZE];
double e_b0[HIDSIZE];
double e_w0[INSIZE][HIDSIZE];
double e_w1[HIDSIZE];

    */