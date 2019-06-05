#include <kfda.hpp>
KFDA::KFDA(vector<SingleSample<VectorXd>> &sampleVector, int numClasses, double variance, int thePCADimensions)
{
    int i;
    RBF_variance = variance;
    samples = sampleVector;
    numOfSamples = samples.size();
    numOfClasses = numClasses;
	cout << 1 << endl;
    initialDimensions = samples[0].content.size();
    if (thePCADimensions == -1)
        pcaDimensions = numOfClasses;
    else
        pcaDimensions = thePCADimensions;
    
	mean.resize(samples[0].content.size());
    mean.setZero();
    classes.resize(numOfClasses);
    for (i = 0; i < numOfSamples; i++)
    {
        classes[samples[i].label].samplesIndex.push_back(i);
        mean += samples[i].content;
    }	


    mean /= RBF_variance * numOfSamples;

    MatrixXd temp;
    temp.resize(initialDimensions, numOfSamples);
    for (i = 0; i < numOfSamples; i++)
    {
        temp.col(i) = samples[i].content;
    }

    pcaVectors = pca(temp, mean, pcaDimensions);

    resizeAll(pcaVectors);
    //cout << 11 << endl;
    // cout << classes[0].samples[0] << endl;

    computeKernelAll();

    IntraclassScatterMatrix(); cout << 3 << endl;

    BetweenclassScatterMatrix(); cout << 4 << endl;

    FisherFeature();
    for (i = 0; i < numOfClasses; i++)
        classes[i].kernelMean = fisherVectors.transpose() * classes[i].kernelMean;
    // OSM = ISM + BSM;
}

void KFDA::computeKernelAll()
{
    int i, j;
    kernelMatrix.resize(numOfSamples, numOfSamples);

    for (i = 0; i < numOfSamples; i++)
        for (j = i; j < numOfSamples; j++)
            kernelMatrix(i, j) = kernel::RBF(samples[i].content, samples[j].content, RBF_variance);

    for (j = 1; j < numOfSamples; j++)
        for (i = j + 1; i < numOfSamples; i++)
            kernelMatrix(i, j) = kernelMatrix(j, i);

    for (i = 0; i < numOfSamples; i++)
    {
        kernelVectors.push_back(kernelMatrix.col(i));
    }

    kernelMean = kernelMatrix.rowwise().mean();
}

void KFDA::resizeAll(MatrixXd &thepcaVectors)
{
    qout("resizing samples.");
    cout << "resizing samples." << endl;
    int i, j;
    //cout << thepcaVectors.rows() << thepcaVectors.cols() << endl;

    for (i = 0; i < numOfSamples; i++)
        samples[i].content = thepcaVectors.transpose() * samples[i].content;

    for (i = 0; i < numOfClasses; i++)
    {
        classes[i].Mean(samples);
        classes[i].numOfDimensions = samples[classes[i].samplesIndex[0]].content.size();
    }
    currentDimensions = classes[0].numOfDimensions;
    mean = thepcaVectors.transpose() * mean;
    cout << "complete." << endl;
}

void KFDA::IntraclassScatterMatrix()
{
    int i;
	ISM.resize(kernelVectors[0].size(), kernelVectors[0].size());
    ISM.setZero();
    for (i = 0; i < numOfClasses; i++)
    {
		classes[i].KernelMean(kernelVectors); cout << 11 << endl;
        
        classes[i].P = classes[i].samplesIndex.size() / numOfSamples; cout << 33 << endl;
		classes[i].kernelScatterMatrix(kernelVectors); cout << 22 << endl;
        ISM += classes[i].KSM;
    }
}

void KFDA::BetweenclassScatterMatrix()
{
    qout("computing BetweenclassScatterMatrix.");
    cout << "computing BetweenclassScatterMatrix." << endl;
	BSM.resize(ISM.rows(), ISM.cols());
    int i, j;
    BSM.setZero();
    for (i = 0; i < numOfClasses; i++)
        BSM += classes[i].P * (classes[i].kernelMean - kernelMean) *
               (classes[i].kernelMean - kernelMean).transpose();
    //BSM /= numOfSamples * RBF_variance;
}

void KFDA::FisherFeature()
{
    qout("computing Fisher vectors.");
    cout << "computing Fisher vectors." << endl;
    MatrixXd fisherCri, temp;
    int i;
    cout << ISM.rows() << " " << ISM.cols() << endl;
    cout << BSM.rows() << " " << BSM.cols() << endl;

    fisherCri = ISM.inverse() * BSM;

    EigenSolver<MatrixXd> es(BSM);
    //cout << es.eigenvalues().real() << endl;
    temp = es.eigenvectors().real();
    //cout << temp << endl;
    fisherVectors.resize(numOfSamples, numOfSamples);

    for (i = 0; i < numOfSamples; i++)
    {
        fisherVectors.col(i) = temp.col(numOfSamples - i - 1);
    }
}

int KFDA::classify(VectorXd &sample, char method)
{
    VectorXd projectedSample;
    VectorXd SampleKernel(numOfSamples);
    double distance, temp;
    int i, result = -1;
    projectedSample = pcaVectors.transpose() * sample;

    for (i = 0; i < numOfSamples; i++)
    {
        SampleKernel(i) = kernel::RBF(projectedSample, samples[i].content, RBF_variance);
    }

    SampleKernel = fisherVectors.transpose() * SampleKernel;

    switch (method)
    {
    case Euclidean_Distance:

        distance = (SampleKernel - classes[0].kernelMean).squaredNorm();

        result = 0;
        for (i = 1; i < numOfClasses; i++)
        {
            temp = (SampleKernel - classes[i].kernelMean).squaredNorm();
            if (temp < distance)
            {
                distance = temp;
                result = i;
            }
        }
        break;

    default:
        break;
    }
    return result;
}
