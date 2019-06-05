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

#include "loadproject.hpp"
#include "ui_loadproject.h"
#include <QFileDialog>
loadProject::loadProject(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::loadProject)
{
  ui->setupUi(this);
}

loadProject::~loadProject()
{
  delete ui;
  delete this;
}



void loadProject::on_browse_button_clicked()
{
      ui->projectFileDir->setText(QFileDialog::getOpenFileName(this,"Select File",".","Project File(*.proj)"));
}

void loadProject::on_open_button_clicked()
{
    emit open(ui->projectFileDir->text());
}
