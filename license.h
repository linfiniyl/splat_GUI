/*	
	File                 : license.h
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

*/


#ifndef LICENSE_H
#define LICENSE_H

#include <QDialog>

namespace Ui {
class license;
}

class license : public QDialog
{
    Q_OBJECT

public:
    explicit license(QWidget *parent = nullptr);
    ~license();

private slots:
    void on_close_window_clicked();

private:
    Ui::license *ui;
};

#endif // LICENSE_H
