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

#ifndef PROJECTCREATER_HPP
#define PROJECTCREATER_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include <QDir>
#define Polynomial_Kernel 0
#define RBF_Kernel 1
#define Sigmoid_Kernel 2
#define ORL_Database 0

using namespace std;

class createProjectFile
{
public:
  createProjectFile(string theProjectName, string theProjectDir,
                   string theMethod, string theDatabaseType,string theDatabaseDir);
  void setRBF(double variance);
  void setDatabase();
void close();


private:
  ofstream projectFile;
  YAML::Node projectInfo;
  string projectName;
  string projectDir;
  string databaseType;
  string databaseDir;
  char kernelType;
  string method;



};



#endif // PROJECTCREATER_HPP
