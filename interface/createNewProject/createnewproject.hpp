/****************************************************************************
**
** Copyright (C) 2019 Lyu Sicong. All rights reserved.
**
** This file is part of Basalt.
**
** This software may be distributed and modified under the terms of the GNU
** General Public License version 3 (GPLv3, https://www.gnu.org/licenses/gpl-3.0.txt)
** as published by the Free Software Foundation and appearing in the file 
** "gpl-3.0.txt" included in the packaging of this file. Please note that 
** all works based on this software must also be made publicly available 
** under the terms of the GPLv3 ("Copyleft").
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
**
** Contact information:
** e-mail: 2468197564@qq.com
** 
** 
****************************************************************************/

#ifndef createNewProject_HPP
#define createNewProject_HPP

#include <QWidget>
#include <createprojectfile.hpp>
//#include <yaml-cpp/yaml.h>
using namespace std;
namespace Ui {
  class createNewProject;
}

class createNewProject : public QWidget
{
  Q_OBJECT

public:
  explicit createNewProject(QWidget *parent = nullptr,QWidget *grandparent = nullptr,
                        QString theMethod = NULL,QString databaseStr = NULL);
  ~createNewProject();

private:

  Ui::createNewProject *ui;
  QWidget *theParent;
  QWidget *theGrandparent;
  QString databaseDirectory;
  QString projectDirectory;
  QString method;
  QString database;
private slots:


  void on_Browse_button_clicked();
  void on_Create_button_clicked();
  void on_Back_button_clicked();
  void on_Cancel_button_clicked();
  void on_Browse_new_clicked();

signals:
  void projectCreated(QString projectFileDir);
};

#endif // createNewProject_HPP
