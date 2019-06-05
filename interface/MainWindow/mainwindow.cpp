#include <QFileDialog>
#include <QMessageBox>
#include <QLibraryInfo>
#include "mainwindow.h"
#include "kfdapanel.hpp"
#include "common.hpp"
#include <QScrollArea>
#include "fldapanel.hpp"
extern QPlainTextEdit *textEdit;
//! [0]
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
  QString text;
  ui->setupUi(this);
  ui->tabWidget->removeTab(1);
  textEdit = ui->plainTextEdit;
  Qt::WindowFlags flags = Qt::Dialog;
  m_loadProject = new loadProject(this);
  m_loadProject->setWindowFlags(flags);
  m_loadProject->setWindowModality(Qt::ApplicationModal);
  m_newProject = new newProject(this);
  connect(m_newProject, SIGNAL(run(QString)), this, SLOT(run(QString)));
  connect(m_newProject, SIGNAL(next(QString, QString)), this, SLOT(setProject(QString, QString)));
  m_newProject->setWindowFlags(flags);
  m_newProject->setWindowModality(Qt::ApplicationModal);
  connect(m_loadProject, SIGNAL(open(QString)), this, SLOT(run(QString)));
}

void MainWindow::on_actionNew_Project_triggered()
{

  m_newProject->show();
}

void MainWindow::on_actionLoad_Project_triggered()
{

  m_loadProject->show();
}
void MainWindow::setProject(QString theMethod, QString theDatabase)
{
  method = theMethod;
  database = theDatabase;
}

void MainWindow::run(QString projectFileDir)
{
  YAML::Node projectInfo = YAML::LoadFile(projectFileDir.toStdString());

  cout << database.toStdString() << endl;
  if (projectInfo["project"]["method"]["name"].as<string>() == "KFDA")
  {
    m_loadProject->close();
    m_newProject->close();
    KFDAPanel *newFisherKernel = new KFDAPanel(this, projectFileDir, ui->plainTextEdit);
    QScrollArea *scroll = new QScrollArea(ui->tabWidget);
    ui->tabWidget->addTab(scroll, QString::fromStdString(projectInfo["project"]["projectName"].as<string>()));
    scroll->setWidget(newFisherKernel);
    ui->tabWidget->setCurrentIndex(ui->tabWidget->currentIndex() + 1);

    ui->tabWidget->setTabsClosable(true);

    newFisherKernel->show();
  }
  else if (projectInfo["project"]["method"]["name"].as<string>() == "FLDA")
  {
    m_loadProject->close();
    m_newProject->close();
    FLDAPanel *newFLDA = new FLDAPanel(this, projectFileDir, ui->plainTextEdit);
    QScrollArea *scroll = new QScrollArea(ui->tabWidget);
    ui->tabWidget->addTab(scroll, QString::fromStdString(projectInfo["project"]["projectName"].as<string>()));
    scroll->setWidget(newFLDA);
    ui->tabWidget->setCurrentIndex(ui->tabWidget->currentIndex() + 1);
  }
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
  ui->tabWidget->setCurrentIndex(index);
  delete ui->tabWidget->currentWidget();
}
