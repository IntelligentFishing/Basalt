#include <dataloader.hpp>
#include <common.hpp>
void DataLoader::ORL(string from,
                     vector<SingleSample< MatrixXd> > &toVector)
{
    toVector.clear();
    cout << "Loading ORL database of faces...\n" ;
    qout( "Loading ORL database of faces..." );
    Mat Img;
    struct SingleSample< MatrixXd> newSample;
    int i = 0, j = 0;
    for (i = 1; i <= ORL_CLASSES; i++)
        for (j = 1; j <= ORL_NUM_EACH; j++)
        {
            Img = imread(from + "/s" + to_string(i) + "/" + to_string(j) + ".pgm", IMREAD_GRAYSCALE);
             MatrixXd m(Img.rows, Img.cols);
            cv2eigen(Img, m);
            newSample = {j - 1, m, i - 1};
            toVector.push_back(newSample);
        }
cout << "Database loaded.\n";
    qout( "Database loaded.");
}

void DataLoader::split(vector<SingleSample< MatrixXd> > &database,
                       vector<SingleSample< MatrixXd> > &train,
                       vector<SingleSample< MatrixXd> > &eval, char SPLIT,int numOfTrain = 5)
{
    train.clear();
    eval.clear();
    SingleSample< MatrixXd> temp;
    int i = 0, j = 0;
    switch (SPLIT)
    {
    case SPLIT_ORL:
        int shuffleTable[ORL_NUM_EACH];
        for (i = 0; i < ORL_NUM_EACH; i++)
            shuffleTable[i] = i;
        srand((int)time(0));
        for (i = 0; i < ORL_NUM_EACH; i++)
            swap(shuffleTable[i], shuffleTable[random(ORL_NUM_EACH)]);

        for (i = 0; i < ORL_CLASSES; i++)
        {
            for (j = 0; j < numOfTrain; j++)
            {
                temp = database[i * ORL_NUM_EACH + shuffleTable[j]];
                train.push_back(temp);
            }

            for (j = 0; j < ORL_NUM_EACH - numOfTrain; j++)
            {
                temp = database[i * ORL_NUM_EACH + shuffleTable[j]];
                eval.push_back(temp);
            }
        }
        cout << "database splited to train and eval.\n";
        qout( "database splited to train and eval.");
        break;
    default:
        break;
    }
}

void DataLoader::databaseVectorize(vector<SingleSample< MatrixXd> > &samples,
                                   vector<SingleSample< VectorXd> > &sampleVectors)
{
    int i, j;

    for (i = 0; i < samples.size(); i++)
    {
        samples[i].content.resize(samples[i].content.size(), 1);
        sampleVectors[i].content = samples[i].content;
        sampleVectors[i].label = samples[i].label;
        sampleVectors[i].num = samples[i].num;
    }
}

 VectorXd DataLoader::vectorize( MatrixXd &sample)
{
    sample.resize(sample.size(), 1);
     VectorXd newVector = sample;
    return newVector;
}
