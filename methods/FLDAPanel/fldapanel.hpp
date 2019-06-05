#ifndef FLDAPANEL_HPP
#define FLDAPANEL_HPP

#include <QWidget>
#include <vector>
#include <Eigen/Dense>
#include <common.hpp>
#include <dataloader.hpp>
#include <flda.hpp>
#include "yaml-cpp/yaml.h"
namespace Ui {
  class FLDAPanel;
}

class FLDAPanel : public QWidget
{
  Q_OBJECT

public:
  explicit FLDAPanel(QWidget *parent = nullptr,QString theProjectDir = NULL,QPlainTextEdit *textEdit=NULL);
  ~FLDAPanel();

private slots:
  void on_train_button_clicked();

  void on_browse_photo_clicked();

  void on_classify_button_clicked();

  void on_eval_button_clicked();

private:
  Ui::FLDAPanel *ui;
  vector<SingleSample<MatrixXd>> *sampleVectors,
                                 *train,
                                 *eval;
  vector<SingleSample<VectorXd>> trainVectors, evalVectors;
  FLDA *FLDASolver;
  char method;
  fstream projectFile;
  QString projectDir;
  YAML::Node projectInfo;
  QPlainTextEdit *theTextEdit;
};

#endif // FLDAPANEL_HPP
