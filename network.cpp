#include "network.h"

double sigmoid(double z)
{
    return 1.0/(1.0+exp(-z));
}

double sigmoid_prime(double z)
{
    return sigmoid(z)*(1-sigmoid(z));
}

double randn()
{
    return 0;
}


network::network(double eta, double decay)
{
    /*this->eta = eta;
    this->decay = decay;
    this->biases0 = new double[HIDSIZE];
    this->biases1 = new double[1];
    this->weights0 = new double[INSIZE][HIDSIZE];
    this->weights1 = new double[HIDSIZE];
    this->e_b0 = new double[HIDSIZE];
    this->e_b1 = new double[1];
    this->e_w0 = new double[INSIZE][HIDSIZE];
    this->e_w1 = new double[HIDSIZE];*/
    
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
    /*delete this->biases0;
    delete this->biases1;
    delete this->weights0;
    delete this->weights1;
    delete this->e_b0;
    delete this->e_b1;
    delete this->e_w0;
    delete this->e_w1;*/
}
double network::evaluate(double input[INSIZE])
{
    double hidz[HIDSIZE];// = {0.0}
    double outz = 0.0;
    return evaluate(input, hidz, &outz);
}
double network::evaluate(double input[INSIZE], double hidz[HIDSIZE], double* outz)
{
    double hidden[HIDSIZE] = {0.0};
    double output = 0.0;
    
    for (int i = 0; i < HIDSIZE; i++)
    {
        double mval = 0.0;
        for (int k = 0; k < INSIZE; k++)
            mval += input[k] * weights0[k][i];
        mval +=  biases0[i];
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
void network::update(double input[INSIZE], double output)
{
    //double* nabla_b[2], nabla_w[2];
    double nabla_b0[HIDSIZE];
    double nabla_b1 = 0.0;
    double nabla_w0[192][HIDSIZE];
    double nabla_w1[HIDSIZE];
    
    backprop(input, 0.0, nabla_b0, &nabla_b1, nabla_w0, nabla_w1);
    
    
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
    
    double prediction = this->evaluate(input);
    double gamma = output - prediction;
    
    
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
void network::backprop(double input[INSIZE], double output, double nabla_b0[HIDSIZE], double* nabla_b1, double nabla_w0[INSIZE][HIDSIZE], double* nabla_w1)
{
    
}