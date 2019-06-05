#ifndef KFDAPANEL_HPP
#define KFDAPANEL_HPP

#include <QWidget>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QLabel>
 #include <QTextStream>
#include <vector>
#include <string>
#include <Eigen/Dense>
#include <common.hpp>
#include <dataloader.hpp>
#include <kfda.hpp>
#include "yaml-cpp/yaml.h"
namespace Ui {
  class KFDAPanel;
}

class KFDAPanel : public QWidget
{
  Q_OBJECT

public:
  explicit KFDAPanel(QWidget *parent = nullptr,QString theProjectDir = NULL,QPlainTextEdit *textEdit=NULL);
  ~KFDAPanel();

private slots:
  void on_train_button_clicked();

  void on_eval_button_clicked();

  void on_browse_photo_clicked();

  void on_classify_button_clicked();

private:
  Ui::KFDAPanel *ui;
  vector<SingleSample<MatrixXd>> *sampleVectors,
                                 *train,
                                 *eval;
  vector<SingleSample<VectorXd>> trainVectors, evalVectors;
  KFDA *KFDASolver;
  char method;
  fstream projectFile;
  QString projectDir;
  QLabel *label1;
  QLineEdit *variance;
  YAML::Node projectInfo;
  QPlainTextEdit *theTextEdit;
};

#endif // KFDAPANEL_HPP
