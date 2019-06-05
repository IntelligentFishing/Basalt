#include <common.hpp>
#include <QApplication>
QPlainTextEdit *textEdit;
void qout(string a)
{
  textEdit->appendPlainText(QString::fromStdString(a));
  QApplication::processEvents();
}
void clearLine(int length = 50)
{
    cout << "\r";
    for (int i = 0; i < length; i++)
        cout << " ";
    cout << "\r";
}

void orthonormalize( MatrixXd &ColVecs)
{
    ColVecs.col(0).normalize();
    double temp;
    for (int k = 0; k != ColVecs.cols() - 1; ++k)
    {
        for (int j = 0; j != k + 1; ++j)
        {
            temp = ColVecs.col(j).transpose() * ColVecs.col(k + 1);
            ColVecs.col(k + 1) -= ColVecs.col(j) * temp;
        }
        ColVecs.col(k + 1).normalize();
    }
}

 MatrixXd pca( MatrixXd samples,  VectorXd &mean, int targetDimensions)
{
    int i;
    int numOfDimensions = samples.rows();
    int numOfSamples = samples.cols();
    int K;
     MatrixXd coeffMatrix, U, V, temp;
    coeffMatrix.setZero();
    for (i = 0; i < numOfSamples; i++)
        samples.col(i) -= mean;

	if (numOfDimensions < numOfSamples)
    {
        K = targetDimensions;
       
		coeffMatrix = samples * samples.transpose();

      
		RedSVD::RedSVD< MatrixXd> svd(coeffMatrix, K);
        U = svd.matrixU();
    }
    else
    {
        K = targetDimensions;
        coeffMatrix = samples.transpose()  * samples ;
        cout << "coeffMatrix: " << coeffMatrix.rows() << " x " << coeffMatrix.cols() << endl;

         EigenSolver< MatrixXd> solver(coeffMatrix);
        temp = solver.eigenvectors().real();
        //cout << solver.eigenvalues().real() << endl;
        temp = samples * temp;

        orthonormalize(temp);
        cout << temp.rows() <<" " <<temp.cols() << endl;

        U = temp.leftCols(K);
       // U.resize(numOfDimensions, K);
      //  for (i = 0; i < K; i++)
       //     U.col(i) = temp.col(i);
        cout << U.rows() << " " << U.cols() << endl;
        //cout << U <<endl;
        cout << "done " << endl;
    }
    return U;

}
