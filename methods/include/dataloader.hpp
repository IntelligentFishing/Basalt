#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/eigen.hpp>
#include <common.hpp>

#define ORL_ROWS 112
#define ORL_COLS 92
#define ORL_CLASSES 40
#define ORL_NUM_EACH 10

#define SPLIT_ORL 0

using namespace std;
using namespace cv;
using namespace Eigen;

namespace DataLoader
{
void ORL(string from,
         vector<SingleSample< MatrixXd> > &toVector);

void split(vector<SingleSample< MatrixXd> > &database,
           vector<SingleSample< MatrixXd> > &train,
           vector<SingleSample< MatrixXd> > &eval, char SPLIT_WHITCH,int numOfTrain);
 VectorXd vectorize( MatrixXd &sample);

void databaseVectorize(vector<SingleSample< MatrixXd> > &samples,
                       vector<SingleSample< VectorXd> > &sampleVectors);
}; // namespace DataLoader
