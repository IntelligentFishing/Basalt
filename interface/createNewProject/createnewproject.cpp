#include "createnewproject.hpp"
#include "ui_createnewproject.h"
#include <QString>
#include <QFileDialog>
createNewProject::createNewProject(QWidget *parent, QWidget *grandparent,QString theMethod,QString databaseStr) :
  QWidget(parent),
  ui(new Ui::createNewProject)
{
  int i;
  ui->setupUi(this);
  this->setParent(grandparent);

  theGrandparent = grandparent;
  theParent = parent;
  method = theMethod;
   cout << method.toStdString() << endl;
  database = databaseStr;
  ui->projectName->setText("newProject");
  QDir dir(QDir::currentPath() + "/" + ui->projectName->text());
  if(!dir.exists())
    {
      ui->project_dir->setText(QDir::currentPath() + "/" + ui->projectName->text());
    }else
    { for(i = 1;;i++)
        {ui->projectName->setText("newProject" + QString::number(i));
          dir.setPath(QDir::currentPath() + "/" + ui->projectName->text());
          if(!dir.exists())
            {
              ui->project_dir->setText(QDir::currentPath() + "/" + ui->projectName->text());
              break;
            }
        }
    }
}

createNewProject::~createNewProject()
{
  delete ui;
}

void createNewProject::on_Browse_button_clicked()
{
  databaseDirectory = QFileDialog::getExistingDirectory();
  ui->database_dir->setText(databaseDirectory);

}

void createNewProject::on_Create_button_clicked()
{



  string projectName = ui->projectName->text().toStdString();
  string projectDir = ui->project_dir->text().toStdString();
  string databaseDir = ui->database_dir->text().toStdString();
  createProjectFile *newProject = new createProjectFile(projectName,projectDir, method.toStdString(),database.toStdString(),databaseDir);


  QString out;
  out = out.fromStdString(projectDir + "/" + projectName+".proj");
  //YAML::Node projectInfo = YAML::LoadFile(projectDir + "/" + projectName+".proj");
newProject->close();
  emit projectCreated(out);

  //theParent->close();
}

void createNewProject::on_Back_button_clicked()
{
  this->close();
  theParent->show();
}

void createNewProject::on_Cancel_button_clicked()
{
  this->close();
  theParent->close();
}

void createNewProject::on_Browse_new_clicked()
{
  projectDirectory = QFileDialog::getExistingDirectory();
  //ui->project_dir->setText(projectDirectory);
  if(projectDirectory.right(ui->projectName->text().size()) != ui->projectName->text())
    {
      ui->project_dir->setText(projectDirectory +"/"+ ui->projectName->text());

    }
  else {
      ui->project_dir->setText(projectDirectory);
    }
}
