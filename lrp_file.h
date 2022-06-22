/*	
	File                 : lrp_file.h
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

	Description : .lrp file creating form
*/


#ifndef LRP_FILE_H
#define LRP_FILE_H

#include "settings.h"
#include <QDialog>

namespace Ui {
class lrp_file;
}

class lrp_file : public QDialog
{
    Q_OBJECT

public:
    void retranslate();
    bool is_exist(QString file_name);
    void set_to_none();
    void refresh_file_data();
    explicit lrp_file(QWidget *parent = nullptr);
    ~lrp_file();
    void openFile(QString file_name);

private slots:


    void on_save_as_file_lrp_clicked();

    void on_save_file_lrp_clicked();

    void on_delete_file_lrp_clicked();

    void on_file_name_activated(int index);


    void on_refresh_file_clicked();

    void on_lrp_file_finished(int result);

private:
    Settings *set;
    Ui::lrp_file *ui;
};

#endif // LRP_FILE_H
