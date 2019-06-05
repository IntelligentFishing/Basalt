#ifndef _COMMON_H_
#define _COMMON_H_
//#define EIGEN_USE_MKL_ALL
#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
#include <RedSVD-h>
#include <vector>
#include <QPlainTextEdit>
#define random(x) (rand() % x)



using namespace std;
using namespace Eigen;




void qout(string a);



template <class T>
struct SingleSample
{
    int num;
    T content;
    int label;
};

struct vectorClass
{
    VectorXd mean;
    VectorXd pcaMean;
    VectorXd fisherMean;
    VectorXd kernelMean;
    double P;
    MatrixXd pcaVectors;
    MatrixXd fisherVectors;
    vector<int> samplesIndex;
    MatrixXd SM;
    MatrixXd KSM;

    int numOfDimensions;

    vectorClass()
    {
        mean.setZero();
        P = 0;
        fisherMean.setZero();
        SM.setZero();
    }

    void init(vector<VectorXd> &theSamples)
    {
        //int i;
        numOfDimensions = theSamples[0].size();
    }

    void Mean(vector<SingleSample<VectorXd>> &samples)
    {
        int i;
        mean = samples[samplesIndex[0]].content;
        for (i = 1; i < samplesIndex.size(); i++)
            mean += samples[samplesIndex[i]].content;
        mean /= 1.0 * samplesIndex.size();
    }

    void KernelMean(vector<VectorXd> &kernelVectors)
    {
        int i;
        kernelMean = kernelVectors[samplesIndex[0]];
        for (i = 1; i < samplesIndex.size(); i++)
            kernelMean += kernelVectors[samplesIndex[i]];
        kernelMean /= 1.0 * samplesIndex.size();
    }

    void ScatterMatrix(vector<SingleSample<VectorXd>> &samples)
    {
        int i;
        MatrixXd temp(mean.rows(), mean.cols());
		SM.resize(mean.rows(),mean.rows());
        SM.setZero();
        for (i = 0; i < samplesIndex.size(); i++)
        {
            temp = samples[samplesIndex[i]].content - mean;
            SM += temp * temp.transpose();
        }
		SM /= samplesIndex.size();
        //SM *= P / samplesIndex.size();
    }
    void kernelScatterMatrix(vector<VectorXd> &kernelVectors)
    {
        int i;
		KSM.resize(kernelMean.size(), kernelMean.size());
        KSM.setZero();
        for (i = 0; i < samplesIndex.size(); i++)
        {
            KSM += (kernelVectors[samplesIndex[i]] - kernelMean) *
                   (kernelVectors[samplesIndex[i]] - kernelMean).transpose();
        }
		KSM /= samplesIndex.size();
        //KSM *= P / samplesIndex.size();
    }
};

void clearLine(int length);

MatrixXd pca(MatrixXd samples, VectorXd &mean, int targetDimensions);
#endif
