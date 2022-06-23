/*	
	File                 : license.cpp
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

	Description : license
*/


#include "license.h"
#include "ui_license.h"

license::license(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::license)
{
    ui->setupUi(this);
}

license::~license()
{
    delete ui;
}

void license::on_close_window_clicked()
{
        this->close();
}

