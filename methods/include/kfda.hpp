#ifndef _KFDA_H_
#define _KFDA_H_

#include <iostream>
#include <cmath>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <kernel.hpp>
#include <common.hpp>
#define Euclidean_Distance 0
using namespace std;
using namespace Eigen;



class KFDA
{
public:
    KFDA(vector<SingleSample<VectorXd> > &sampleVector, int numClasses,double variance, int thePCADimensions = -1);
    void computeKernelAll();
    void resizeAll(MatrixXd &thepcaVectors);
    void IntraclassScatterMatrix();
    void BetweenclassScatterMatrix();
    void FisherFeature();
    int classify(VectorXd &sample, char method);
private:
    vector<vectorClass> classes;
    vector<SingleSample<VectorXd>> samples;
    MatrixXd ISM;
    MatrixXd BSM;
    MatrixXd OSM;
    MatrixXd pcaVectors;
    VectorXd mean;
    VectorXd kernelMean;
    MatrixXd fisherVectors;
    MatrixXd kernelMatrix;
    int numOfSamples;
    int numOfClasses;
    int currentDimensions;
    int initialDimensions;
    int pcaDimensions;
    double RBF_variance;
    vector<VectorXd> kernelVectors;
};

#endif
