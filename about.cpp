/*	
	File                 : about.cpp
    Project              : splat_GUI
	-----------------------------------------------------------
	Copyright 2022, Agafangelos Dmitriy, Vladimirov Sergey <vladimirov.opds@gmail.com>

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program. If not, see <http://www.gnu.org/licenses/>

	Description : about box 
*/
#include "about.h"
#include "ui_about.h"

about::about(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);
    l = new license(this);

    QPixmap pix(":/icons/splatlogo.gif");
    ui->image->setPixmap(pix);
}

about::~about()
{
    delete ui;
}
void about::retranslate(){
    ui->retranslateUi(this);
}

void about::on_close_window_clicked()
{
    this->close();
}


void about::on_license_botton_clicked()
{
    l->show();
}

