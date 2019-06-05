#include "newproject.hpp"
#include "ui_newproject.h"
#include <iostream>
newProject::newProject(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::newProject)
{

  int i;
  theParent = parent;
  ui->setupUi(this);
  //setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);//设置子窗口属性
  this->setParent(parent);

  projectListItemModel = new QStandardItemModel(this);
  databaseListItemModel = new QStandardItemModel(this);

  QString theString;

  projectStringList.append("FLDA");
  projectStringList.append("KFDA");

  int nCount = projectStringList.size();
  for(i = 0; i < nCount; i++)
    {
      theString = static_cast<QString>(projectStringList.at(i));
      QStandardItem *item = new QStandardItem(theString);

      projectListItemModel->appendRow(item);

    }


  databaseStringList.append("ORL database of faces");

  nCount = databaseStringList.size();

  for(i = 0; i < nCount; i++)
    {
      theString = static_cast<QString>(databaseStringList.at(i));
      QStandardItem *item = new QStandardItem(theString);
      databaseListItemModel->appendRow(item);
    }


  ui->projectList->setModel(projectListItemModel);
  ui->databaseList->setModel(databaseListItemModel);


}

newProject::~newProject()
{
  delete ui;
  delete this;
}





void newProject::on_Next_button_clicked()
{
  int projectRow = ui->projectList->currentIndex().row();
  int databaseRow = ui->databaseList->currentIndex().row();
  if(projectRow!=-1 && databaseRow != -1)
    {
      QModelIndex projectIndex=projectListItemModel->index(projectRow,0);
      QString projectStr=projectListItemModel->data(projectIndex,Qt::DisplayRole).toString();
      QModelIndex databaseIndex=databaseListItemModel->index(databaseRow,0);
      QString databaseStr=databaseListItemModel->data(databaseIndex,Qt::DisplayRole).toString();


      if(projectStr == static_cast<QString>(projectStringList.at(1)) &&
         databaseStr == static_cast<QString>(databaseStringList.at(0)))
        {
          this->hide();
          Project = new createNewProject(this,theParent,projectStr,databaseStr);
          Qt::WindowFlags flags = Qt::Dialog;
          Project->setWindowFlags(flags);
          Project->setWindowModality(Qt::ApplicationModal);
          connect(Project,SIGNAL(projectCreated(QString)), this,SLOT(projectCreated(QString)));
              Project->show();
emit next(projectStr,databaseStr);


        }

      if(projectStr == static_cast<QString>(projectStringList.at(0)) &&
         databaseStr == static_cast<QString>(databaseStringList.at(0)))
        {
          this->hide();
          Project = new createNewProject(this,theParent,projectStr,databaseStr);
          Qt::WindowFlags flags = Qt::Dialog;
          Project->setWindowFlags(flags);
          Project->setWindowModality(Qt::ApplicationModal);
          connect(Project,SIGNAL(projectCreated(QString)), this,SLOT(projectCreated(QString)));
          Project->show();
emit next(projectStr,databaseStr);
        }

    }
  else
    {
      QMessageBox::information(this,tr("information"),tr("please select a item"));
    }
}

void newProject::on_Cancel_button_clicked()
{
   this->close();
}
void newProject::projectCreated(QString projectFileDir)
{



  Project->close();
  delete Project;
  emit run(projectFileDir);

}
