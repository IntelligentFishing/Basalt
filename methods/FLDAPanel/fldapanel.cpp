#include "fldapanel.hpp"
#include "ui_fldapanel.h"
#include <QFileDialog>
FLDAPanel::FLDAPanel(QWidget *parent,QString theProjectDir,QPlainTextEdit *textEdit) :
  QWidget(parent),
  ui(new Ui::FLDAPanel)
{
theTextEdit = textEdit;
  ui->setupUi(this);
  projectDir = theProjectDir;
  projectInfo = YAML::LoadFile(projectDir.toStdString());
  if(projectInfo["project"]["status"].as<string>() == "trained")
    {
      ui->dimension->setText(QString::fromStdString(projectInfo["project"]["method"]["Dimension after PCA"].as<string>()));
      ui->samples->setText(QString::fromStdString(projectInfo["project"]["database"]["train"].as<string>()));
    }
}

FLDAPanel::~FLDAPanel()
{
  delete ui;
}

void FLDAPanel::on_train_button_clicked()
{

theTextEdit->clear();
theTextEdit->appendPlainText("/************Start Training*************/");
theTextEdit->appendPlainText("/************Don't do anything till it is finished!!*************/");
QApplication::processEvents();
  projectInfo["project"]["method"]["Dimension after PCA"] = ui->dimension->text().toInt();
  projectInfo["project"]["database"]["train"] = ui->samples->text().toInt();
  projectFile.open(projectDir.toStdString());

      sampleVectors = new vector<SingleSample< MatrixXd> >;
                                            train = new vector<SingleSample< MatrixXd> >;
                                            eval = new vector<SingleSample< MatrixXd> >;

      DataLoader::ORL(projectInfo["project"]["database"]["directory"].as<string>(), *sampleVectors);
      DataLoader::split(*sampleVectors, *train, *eval,
                        SPLIT_ORL,projectInfo["project"]["database"]["train"].as<int>());
      trainVectors.resize(train->size());
      evalVectors.resize(eval->size());
      DataLoader::databaseVectorize(*train, trainVectors);
      DataLoader::databaseVectorize(*eval, evalVectors);
      delete sampleVectors, train;
      FLDASolver = new FLDA(trainVectors, 40,
                            projectInfo["project"]["method"]["Dimension after PCA"].as<int>());

      projectInfo["project"]["status"] = "trained";
      projectFile << projectInfo;
      projectFile.close();
	  theTextEdit->appendPlainText("/************Finish Training*************/");
}

void FLDAPanel::on_browse_photo_clicked()
{
      ui->photo_dir->setText(QFileDialog::getOpenFileName());
}

void FLDAPanel::on_classify_button_clicked()
{
  Mat Img = imread(ui->photo_dir->text().toStdString(),IMREAD_GRAYSCALE);
  QImage *newImage = new QImage(ui->photo_dir->text());
 ui->photo_label->setScaledContents(true);
  ui->photo_label->setPixmap(QPixmap::fromImage(*newImage));
 MatrixXd m(Img.rows,Img.cols);
  cv2eigen(Img,m);
  VectorXd v = DataLoader::vectorize(m);
  int label = FLDASolver->classify(v,Euclidean_Distance);
  theTextEdit->clear();
theTextEdit->setPlainText("The label of the photo is class: "+ QString::number(label+1));
}

void FLDAPanel::on_eval_button_clicked()
{

  int i,correct = 0;

  theTextEdit->clear();
  theTextEdit->appendPlainText("/************Start Evaluating*************/");
  theTextEdit->appendPlainText("/************Don't do anything till it is finished!!*************/");
  QApplication::processEvents();
  for (i = 0; i < evalVectors.size(); i++)
    {
      if(FLDASolver->classify(evalVectors[i].content, Euclidean_Distance) == evalVectors[i].label)
        {
          correct++;
        }
     
      //cout << KFDASolver->classify(evalVectors[i].content, Euclidean_Distance) << " " << evalVectors[i].label << endl;
} theTextEdit->appendPlainText("accuracy: " + QString::number(double(correct*1.0/evalVectors.size())));
  theTextEdit->appendPlainText("/************Finish Evaluating*************/");
}
