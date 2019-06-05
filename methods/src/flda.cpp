#include <flda.hpp>

FLDA::FLDA(vector<SingleSample<VectorXd>> &sampleVector, int numClasses, int thePCADimensions)
{
    int i;
    samples = sampleVector;
    numOfSamples = samples.size();
    numOfClasses = numClasses;

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
    mean /= 1.0 * numOfSamples;

    MatrixXd temp;
    temp.resize(initialDimensions, numOfSamples);
    for (i = 0; i < numOfSamples; i++)
    {
        temp.col(i) = samples[i].content;
    }
    pcaVectors = pca(temp, mean, pcaDimensions);

    resizeAll(pcaVectors);

    IntraclassScatterMatrix();

    BetweenclassScatterMatrix();

    FisherFeature(numOfClasses - 1);

    for (i = 0; i < numOfClasses; i++)
        classes[i].fisherMean = fisherVectors.transpose() * classes[i].mean;
	cout << 222 << endl;
}

void FLDA::resizeAll(MatrixXd &thepcaVectors)
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

void FLDA::IntraclassScatterMatrix()
{
    qout("computing IntraclassScatterMatrix.");
    cout << "computing IntraclassScatterMatrix." << endl;
    int i;
	ISM.resize(samples[0].content.size(), samples[0].content.size());
    ISM.setZero();
    for (i = 0; i < numOfClasses; i++)
    {
        classes[i].P = 1.0 * classes[i].samplesIndex.size() / numOfSamples;
        //classes[i].Mean();
        classes[i].ScatterMatrix(samples);
        ISM += classes[i].P * classes[i].SM;
    }
}

void FLDA::BetweenclassScatterMatrix()
{
    qout("computing BetweenclassScatterMatrix.");
    cout << "computing BetweenclassScatterMatrix." << endl;
    int i, j;
	BSM.resize(mean.size(), mean.size());
    BSM.setZero();
    for (i = 0; i < numOfClasses; i++)
        BSM += classes[i].P * (classes[i].mean - mean) *
               (classes[i].mean - mean).transpose();
    //BSM /= numOfSamples * 1.0;
}

void FLDA::OverallScatterMatrix()
{
    int i, j;
    OSM.setZero();
    for (i = 0; i < numOfClasses; i++)
        for (j = 0; j < classes[i].samplesIndex.size(); j++)
            OSM += (samples[classes[i].samplesIndex[j]].content - mean) *
                   (samples[classes[i].samplesIndex[j]].content - mean).transpose();
    OSM /= numOfSamples * 1.0;
}

void FLDA::FisherFeature(int targetDimensions)
{
    qout("computing Fisher vectors.");
    cout << "computing Fisher vectors." << endl;
    MatrixXd fisherCri, temp;
    int i;
	cout << 111 << endl;
    fisherCri = ISM.inverse() * BSM;
	cout << 111 << endl;
    EigenSolver<MatrixXd> es(BSM);
    //cout << es.eigenvalues().real() << endl;
    temp = es.eigenvectors().real();
    //cout << temp << endl;
	cout << 111 << endl;
    fisherVectors.resize(classes[0].numOfDimensions, targetDimensions);
    for (i = 0; i < targetDimensions; i++)
    {
        fisherVectors.col(i) = temp.col(targetDimensions - i - 1);
    }
	cout << 111 << endl;
}

int FLDA::classify(VectorXd &sample, char method)
{
    VectorXd projectedSample;
    double distance, temp;
    int i, result = -1;
    switch (method)
    {
    case Euclidean_Distance: 

        projectedSample = pcaVectors.transpose() * sample;
        projectedSample = fisherVectors.transpose() * projectedSample;
        distance = (projectedSample - classes[0].fisherMean).squaredNorm();

        result = 0;
        for (i = 1; i < numOfClasses; i++)
        {
            temp = (projectedSample - classes[i].fisherMean).squaredNorm();
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
