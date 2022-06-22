/*	
	File                 : settings.cpp
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


#include "settings.h"
#include "ui_settings.h"
#include <QFileDialog>
#include <QFile>
#include <QProcess>
#include <QDebug>
#include <QArrayData>
#include <QStringList>
#include <QSettings>

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    language_tr = new QTranslator(this);
    setting = new QSettings("config.conf",QSettings::NativeFormat);
    ui->setupUi(this);
    this->setWindowTitle("Settings");
    if (setting->value("DEFAULT_DIR").toString() == "" ){
    setting->setValue("DEFAULT_DIR", QDir::homePath()+"/");
    ui->default_dir_path->clear();
    ui->default_dir_path->setText(setting->value("DEFAULT_DIR").toString());
        } else {
        ui->default_dir_path->clear();
        ui->default_dir_path->setText(setting->value("DEFAULT_DIR").toString());
    }
    if (setting->value("SDF_DIR").toString() == "" ){
    setting->setValue("SDF_DIR", QDir::homePath()+"/sdf");
    ui->sdf_dir->clear();
    ui->sdf_dir->setText(setting->value("SDF_DIR").toString());
        } else {
        ui->sdf_dir->clear();
        ui->sdf_dir->setText(setting->value("SDF_DIR").toString());
    }
    if (setting->value("GRAPH_DIR").toString() == "" ){
        setting->setValue("GRAPH_DIR", QDir::homePath()+"/");
        ui->graphic_dir_path->clear();
        ui->graphic_dir_path->setText(setting->value("GRAPH_DIR").toString());
        } else {
        ui->graphic_dir_path->clear();
        ui->graphic_dir_path->setText(setting->value("GRAPH_DIR").toString());
    }

    }

Settings::~Settings()
{
    delete ui;
}
QString Settings::get_dir_path()
{
    return setting->value("DEFAULT_DIR").toString();

}
QString Settings::get_dir_sdf()
{
    return setting->value("SDF_DIR").toString();
}

QString Settings::get_dir_grph()
{
    return setting->value("GRAPH_DIR").toString();
}
QString Settings::get_lang_value()
{
    return setting->value("LANGUAGE").toString();
}


void Settings::on_set_dir_path_clicked()
{
    QString dir_path = QFileDialog::getExistingDirectory(this,"Directory selection") + "/";
    setting->setValue("DEFAULT_DIR",dir_path);
     ui->default_dir_path->clear();
     ui->default_dir_path->setText(setting->value("DEFAULT_DIR").toString());

}

void Settings::on_set_sdf_dir_clicked()
{
    QString dir_path = QFileDialog::getExistingDirectory(this,"Directory selection") + "/";
    setting->setValue("SDF_DIR",dir_path);
    ui->sdf_dir->clear();
    ui->sdf_dir->setText(setting->value("SDF_DIR").toString());
    delete setting;
}

void Settings::on_set_graph_dir_clicked()
{
    QString dir_path = QFileDialog::getExistingDirectory(this,"Directory selection") + "/";
    setting->setValue("GRAPH_DIR",dir_path);
    ui->graphic_dir_path->clear();
    ui->graphic_dir_path->setText(setting->value("GRAPH_DIR").toString());
}


void Settings::on_Reset_clicked()
{

    setting->setValue("DEFAULT_DIR", QDir::homePath()+"/");
    ui->default_dir_path->clear();
    ui->default_dir_path->setText(setting->value("DEFAULT_DIR").toString());
    setting->setValue("SDF_DIR", QDir::homePath()+"/sdf");
    ui->sdf_dir->clear();
    ui->sdf_dir->setText(setting->value("SDF_DIR").toString());
    setting->setValue("GRAPH_DIR", QDir::homePath()+"/");
    ui->graphic_dir_path->clear();
    ui->graphic_dir_path->setText(setting->value("GRAPH_DIR").toString());
    setting->setValue("LANGUAGE",  QLocale::system().name());
    if (setting->value("LANGUAGE") == "ru_RU"){
        ui->language_select->setCurrentIndex(0);
        language_tr->load(":/language/language_ru.qm");
        QCoreApplication::installTranslator(language_tr);
    }
    else {
        ui->language_select->setCurrentIndex(1);
        language_tr->load(":/language/language_en.qm");
        QCoreApplication::installTranslator(language_tr);
        }
}


void Settings::on_language_select_activated(int index)
{
    if (index == 0){
    language_tr->load(":/language/language_ru.qm");
    QCoreApplication::installTranslator(language_tr);
    setting->setValue("LANGUAGE", "ru_RU");
    }   else {
        QCoreApplication::removeTranslator(language_tr);
        language_tr->load(":/language/language_en.qm");
        QCoreApplication::installTranslator(language_tr);
        setting->setValue("LANGUAGE", "en_EN");
    }

}

void Settings::set_language()
{
    if (setting->value("LANGUAGE").toString() == ""){
        setting->setValue("LANGUAGE",  QLocale::system().name());

        if  (QLocale::system().name() == "ru_RU"){
            language_tr->load(":/language/language_ru.qm");
            QCoreApplication::installTranslator(language_tr);
        } else {
            language_tr->load(":/language/language_en.qm");
            QCoreApplication::installTranslator(language_tr);
        }
    } else if (setting->value("LANGUAGE") == "ru_RU"){
        ui->language_select->setCurrentIndex(0);
        language_tr->load(":/language/language_ru.qm");
        QCoreApplication::installTranslator(language_tr);
    } else {
        ui->language_select->setCurrentIndex(1);
        language_tr->load(":/language/language_en.qm");
        QCoreApplication::installTranslator(language_tr);
    }
}
void Settings::retranslate(){
    ui->retranslateUi(this);
}
