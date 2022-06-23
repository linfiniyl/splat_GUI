/*	
	File                 : qth_file.h
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

	Description : .qth file creating form
*/


#ifndef QTH_FILE_H
#define QTH_FILE_H

#include <QDialog>
#include "settings.h"

namespace Ui {
class qth_file;
}

class qth_file : public QDialog
{
    Q_OBJECT

public:
    void retranslate();
    bool is_exist(QString file_name);
    void set_to_none();
    void openFile(QString file_name);
    void refresh_file_data();
    explicit qth_file(QWidget *parent = nullptr);
    ~qth_file();
public slots:


private slots:
    void on_save_file_qth_clicked();

    void on_save_as_file_qth_clicked();

    void on_delete_file_qth_clicked();

    void on_file_name_activated(int index);

    void on_qth_file_finished(int result);


    void on_Refresh_clicked();

    void on_DD_format_latitude_clicked();

    void on_DMS_format_latitude_clicked();

    void on_DD_format_longitude_clicked();

    void on_DMS_format_longitude_clicked();

private:
    Settings *set;
    Ui::qth_file *ui;

};

#endif // QTH_FILE_H
