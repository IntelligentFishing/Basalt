#include <kernel.hpp>

double kernel::Polynomial(VectorXd &x, VectorXd &y, int q)
{
    return pow(x.transpose() * y + 1.0, q);
}

double kernel::RBF(VectorXd &x, VectorXd &y, double variance)
{
    return exp(-(x - y).squaredNorm() / variance);
}

double kernel::Sigmoid(VectorXd &x, VectorXd &y, double v, double c)
{
    double temp = x.transpose() * y;
    return tanh(v * temp + c);
}