/*	
	File                 : udt_file.h
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

	Description : user file creating form
*/

#ifndef UDT_FILE_H
#define UDT_FILE_H

#include <QDialog>
#include "settings.h"

namespace Ui {
class udt_file;
}

class udt_file : public QDialog
{
    Q_OBJECT

public:
    bool is_user_file(QString file_name);
    void retranslate();
    bool is_point_format(QString file_name);
    bool is_exist_line(QString strig_name,QString file_name);
    void set_to_none();
    void set_to_none_city();
    void openFile(QString file_name);
    void refresh_file_data();
    explicit udt_file(QWidget *parent = nullptr);
    ~udt_file();

private slots:
    void on_add_line_clicked();

    void on_point_line_activated(int index);

    void on_Resfresh_file_list_clicked();

    void on_save_line_clicked();

    void on_Delete_line_clicked();

    void on_save_as_file_clicked();

    void on_delete_file_clicked();

    void on_DD_format_latitude_clicked();

    void on_DMS_format_latitude_clicked();

    void on_DD_format_longitude_clicked();

    void on_DMS_format_longitude_clicked();

    void on_udt_file_finished(int result);

    void on_file_name_ch_clicked();

    void on_file_name_ch_2_clicked();

    void on_Resfresh_file_list_2_clicked();

    void on_Save_file_clicked();

    void on_Save_as_file_clicked();

    void on_Delete_file_clicked();

    void on_tabWidget_currentChanged(int index);

private:
    Settings *set;
    Ui::udt_file *ui;
};

#endif // UDT_FILE_H
