#ifndef _FLDA_H_
#define _FLDA_H_
//#define EIGEN_USE_MKL_ALL
#include <iostream>
#include <vector>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
#include <common.hpp>
//#include <omp.h>

#define Euclidean_Distance 0

using namespace std;
using namespace Eigen;

class FLDA
{
public:
    FLDA(vector<SingleSample<VectorXd>> &sampleVector, int numClasses, int thePCADimensions = -1);
    void FisherFeature(int targetDimensions);
    void IntraclassScatterMatrix();
    void BetweenclassScatterMatrix();
    void OverallScatterMatrix();
    void resizeAll(MatrixXd &thepcaVectors);
    int classify(VectorXd &sample, char method = Euclidean_Distance);

private:
    vector<vectorClass> classes;
    vector<SingleSample<VectorXd>> samples;
    MatrixXd ISM;
    MatrixXd BSM;
    MatrixXd OSM;
    MatrixXd pcaVectors;
    VectorXd mean;
    MatrixXd fisherVectors;
    int numOfSamples;
    int numOfClasses;
    int currentDimensions;
    int initialDimensions;
    int pcaDimensions;
};
#endif