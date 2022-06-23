/*	
	File                 : about.h
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



#ifndef ABOUT_H
#define ABOUT_H

#include "license.h"
#include <QDialog>
#include <QPlainTextEdit>
#include <QFile>
#include <QDebug>

namespace Ui {
class about;
}

class about : public QDialog
{
    Q_OBJECT

public:
    void retranslate();
    explicit about(QWidget *parent = nullptr);
    ~about();

private slots:
    void on_close_window_clicked();

    void on_license_botton_clicked();

private:
    license *l;
    Ui::about *ui;
};

#endif // ABOUT_H
