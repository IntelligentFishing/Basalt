#include <iostream>
#include <cmath>
#include <Eigen/Core>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

namespace kernel
{
double Polynomial(VectorXd &x, VectorXd &y, int q);
double RBF(VectorXd &x, VectorXd &y, double variance);
double Sigmoid(VectorXd &x, VectorXd &y, double v, double c);

}; // namespace kernel
