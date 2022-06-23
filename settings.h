/*	
	File                 : settings.h
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

	Description : settings window
*/


#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QSettings>
#include <QTranslator>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    void retranslate();
    void set_language();
    QString get_lang_value();
    QString get_dir_grph();
    QString get_dir_sdf();
    QString get_dir_path();
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

private slots:
    void on_set_dir_path_clicked();

    void on_set_sdf_dir_clicked();

    void on_set_graph_dir_clicked();

    void on_Reset_clicked();

    void on_language_select_activated(int index);

private:
    QTranslator *language_tr;
    QSettings *setting;
    Ui::Settings *ui;
};

#endif // SETTINGS_H
