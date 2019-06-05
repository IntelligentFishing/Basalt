#include "kfdapanel.hpp"
#include "ui_kfdapanel.h"
#include <QPixmap>
#include <QFileDialog>
#include <opencv2/opencv.hpp>
using namespace cv;
KFDAPanel::KFDAPanel(QWidget *parent,QString theProjectDir,QPlainTextEdit *textEdit) :
  QWidget(parent),
  ui(new Ui::KFDAPanel)
{
  theTextEdit = textEdit;
  projectDir = theProjectDir;
  ui->setupUi(this);
projectInfo = YAML::LoadFile(projectDir.toStdString());
  label1 = new QLabel(ui->groupBox);
  label1->move(10,150);
  label1->setText("Variance:");
  label1->resize(80,31);
  variance = new QLineEdit(ui->groupBox);
  variance->move(80,150);
  variance->resize(41,28);



  if(projectInfo["project"]["status"].as<string>() == "trained")
    {
      ui->dimension->setText(QString::fromStdString(projectInfo["project"]["method"]["Dimension after PCA"].as<string>()));
      ui->samples->setText(QString::fromStdString(projectInfo["project"]["database"]["train"].as<string>()));

       variance->setText(QString::fromStdString(projectInfo["project"]["method"]["kernelType"]["variance"].as<string>()));



    }
  else
    {
      variance->setText("1e7");
    }

}

KFDAPanel::~KFDAPanel()
{
  delete ui;
}

void KFDAPanel::on_train_button_clicked()
{


theTextEdit->clear();
theTextEdit->appendPlainText("/************Start Training*************/");
theTextEdit->appendPlainText("/************Don't do anything till it is finished!!*************/");
QApplication::processEvents();
  projectInfo["project"]["method"]["kernelType"]["name"] = ui->comboBox->currentText().toStdString();
  projectInfo["project"]["database"]["train"] = ui->samples->text().toInt();
  projectInfo["project"]["method"]["Dimension after PCA"] = ui->dimension->text().toInt();
  cout << projectInfo["project"]["method"]["kernelType"]["name"].as<string>() << endl;
  cout << projectInfo["project"]["database"]["directory"].as<string>() << endl;
  if(projectInfo["project"]["method"]["kernelType"]["name"].as<string>() == "RBF")
    {
      projectInfo["project"]["method"]["kernelType"]["variance"] = variance->text().toDouble();
    }
  projectFile.open(projectDir.toStdString());
  sampleVectors = new vector<SingleSample<MatrixXd>>;
  train = new vector<SingleSample<MatrixXd>>;
  eval = new vector<SingleSample<MatrixXd>>;

cout << 1 << endl;

    DataLoader::ORL(projectInfo["project"]["database"]["directory"].as<string>(), *sampleVectors);
  cout << 2 << endl;
  DataLoader::split(*sampleVectors, *train, *eval, SPLIT_ORL,
                    projectInfo["project"]["database"]["train"].as<int>());
  cout << 3 << endl;
  trainVectors.resize(train->size());
  evalVectors.resize(eval->size());
  cout << 4 << endl;
  DataLoader::databaseVectorize(*train, trainVectors);
  DataLoader::databaseVectorize(*eval, evalVectors);
  cout << 5 << endl;
  delete sampleVectors, train;
  KFDASolver = new KFDA(trainVectors, 40,
                        projectInfo["project"]["method"]["kernelType"]["variance"].as<double>(),
      projectInfo["project"]["method"]["Dimension after PCA"].as<int>());

  projectInfo["project"]["status"] = "trained";

  projectFile << projectInfo;
  projectFile.close();
  theTextEdit->appendPlainText("/************Finish Training*************/");
}



void KFDAPanel::on_eval_button_clicked()
{
  int i,correct = 0;

  theTextEdit->clear();
  theTextEdit->appendPlainText("/************Start Evaluating*************/");
  theTextEdit->appendPlainText("/************Don't do anything till it is finished!!*************/");
  QApplication::processEvents();
  for (i = 0; i < evalVectors.size(); i++)
    {
      if(KFDASolver->classify(evalVectors[i].content, Euclidean_Distance) == evalVectors[i].label)
        {
          correct++;
        }
      
      //cout << KFDASolver->classify(evalVectors[i].content, Euclidean_Distance) << " " << evalVectors[i].label << endl;
}theTextEdit->appendPlainText("accuracy: " + QString::number(double(correct*1.0/evalVectors.size())));
  theTextEdit->appendPlainText("/************Finish Evaluating*************/");
}

void KFDAPanel::on_browse_photo_clicked()
{
  ui->photo_dir->setText(QFileDialog::getOpenFileName());
}


void KFDAPanel::on_classify_button_clicked()
{
  Mat Img = imread(ui->photo_dir->text().toStdString(),IMREAD_GRAYSCALE);
  QImage *newImage = new QImage(ui->photo_dir->text());
  ui->photo_label->setScaledContents(true);
  ui->photo_label->setPixmap(QPixmap::fromImage(*newImage));
  MatrixXd m(Img.rows,Img.cols);
  cv2eigen(Img,m);
  VectorXd v = DataLoader::vectorize(m);
  int label = KFDASolver->classify(v,Euclidean_Distance);
  cout << label << endl;
  theTextEdit->clear();
theTextEdit->setPlainText("The label of the photo is class: "+ QString::number(label+1));
}
