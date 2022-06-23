/*	
	File                 : lrp_file.cpp
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

#include "lrp_file.h"
#include "ui_lrp_file.h"
#include <QFileDialog>
#include <QFile>
#include <QProcess>
#include <QDebug>
#include <QArrayData>
#include <QStringList>
#include <QMessageBox>
#include <QAbstractItemView>

bool isdielectric_const_or_conductivity(QString str);
bool isfrequency(QString str);
bool isfraction_of(QString str);

lrp_file::lrp_file(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::lrp_file)
{
    QString default_name = "Untitled";
    QString file_name = default_name;
    ui->setupUi(this);
    this->setWindowTitle(file_name);

    set = new Settings(this);

    ui->file_name->addItem("None");

    ui->file_name->view()->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    set_to_none();
    refresh_file_data();
}

lrp_file::~lrp_file()
{
    delete ui;
}
bool isdielectric_const_or_conductivity(QString str)
{
    QStringList str_s = str.split(" ");
    QRegularExpression re("\\d*");
    if ( str_s.length()!=1){
       return false;
    } else
    if (!re.match(str_s[0]).hasMatch() && str_s[0].toFloat() < 0){
       return false;
    } else {
        return true;
    }
}
bool isfrequency(QString str){
    QStringList str_s = str.split(" ");
    QRegularExpression re("\\d*");
    if ( str_s.length()!=1){
       return false;
    } else
    if (!re.match(str_s[0]).hasMatch()){
       return false;
    } else
    if (str_s[0].toFloat() >= 20 && str_s[0].toFloat() <= 20000){
        return true;
    } else {
        return false;
    }
}
bool isfraction_of(QString str)
{
    QStringList str_s = str.split(" ");
    QRegularExpression re("\\d*");
    if ( str_s.length()!=1){
       return false;
    } else
    if (!re.match(str_s[0]).hasMatch()){
       return false;
    } else
    if (str_s[0].toFloat() >= 0 && str_s[0].toFloat() <= 1){
        return true;
    } else {
        return false;
    }
}

void lrp_file::openFile(QString file_name){
    if (is_exist(file_name.section(set->get_dir_path(),1,1))){
    QString fl = file_name.section(set->get_dir_path(),1,1);
    int index_file = ui->file_name->findText(fl);

    ui->file_name->setCurrentIndex(index_file);
    refresh_file_data();

    this->setWindowTitle(file_name);
    } else {
        QMessageBox::critical(this,tr("Error"),tr("File is not exist"));
        set_to_none();
        refresh_file_data();
    }
}


void lrp_file::on_save_as_file_lrp_clicked()
{
     if (is_exist(ui->file_name->currentText()) || ui->file_name->currentText() == "None"){
    QString file_name = QFileDialog::getSaveFileName(this,
                                                     tr("Save lrp file"),".lrp",
                                                     tr("*.lrp"));
    QString fl = file_name.section(set->get_dir_path(),1,1);
    QFile fileout(file_name);
        if (!isdielectric_const_or_conductivity(ui->dielectric_const->text().trimmed())){
                QMessageBox::critical(this,tr("Error"),tr("Invalid dielectric constant value"));
        } else if (!isdielectric_const_or_conductivity(ui->conductivity->text().trimmed())){
                QMessageBox::critical(this,tr("Error"),tr("Invalid conductivity value"));
        } else if (!isdielectric_const_or_conductivity(ui->atmospheric_bending_const->text().trimmed())){
                QMessageBox::critical(this,tr("Error"),tr("Invalid atmospheric bending constant value"));
        } else if (!isfrequency(ui->frequency->text().trimmed())){
        QMessageBox::critical(this,tr("Error"),tr("Invalid frequency value"));
        } else if (!isfraction_of(ui->fraction_of_situations->text().trimmed())){
        QMessageBox::critical(this,tr("Error"),tr("Invalid fraction of situations value"));
        } else if (!isfraction_of(ui->fraction_of_time->text().trimmed())){
        QMessageBox::critical(this,tr("Error"),tr("Invalid fraction of time value"));
        } else if (!isdielectric_const_or_conductivity(ui->effective_radiated_power->text().trimmed())){
        QMessageBox::critical(this,tr("Error"),tr("Invalid fraction of time value"));
        } else
    if (fileout.open(QIODevice::WriteOnly)){
        QTextStream write_params(&fileout);

        write_params << ui->dielectric_const->text() << Qt::endl;
        write_params << ui->conductivity->text() << Qt::endl;
        write_params << ui->atmospheric_bending_const->text() << Qt::endl;
        write_params << ui->frequency->text() << Qt::endl;
        write_params << ui->radio_climate->currentIndex()+1 << Qt::endl;
        write_params << ui->polarization->currentIndex() << Qt::endl;
        write_params << ui->fraction_of_situations->text() << Qt::endl;
        write_params << ui->fraction_of_time->text() << Qt::endl;
        write_params << ui->effective_radiated_power->text() << Qt::endl;

        fileout.close();
        ui->file_name->addItem(fl);
        int file_index = ui->file_name->findText(fl);
        refresh_file_data();
        ui->file_name->setCurrentIndex(file_index);
        this->setWindowTitle(file_name);
    } else {
        QMessageBox::critical(this,tr("Error"),tr("File not found"));
    }
     } else {
         QMessageBox::critical(this,tr("Error"),tr("File is not exist"));
         set_to_none();
         refresh_file_data();
     }
}


void lrp_file::on_save_file_lrp_clicked()
{
    QString title = this->windowTitle();
    if (title == "Untitled"){
    QString file_name = QFileDialog::getSaveFileName(this,
                                                     tr("Save lrp file"),".lrp",
                                                     tr("*.lrp"));
    QString fl = file_name.section(set->get_dir_path(),1,1);
    QFile fileout(file_name);
    if (!isdielectric_const_or_conductivity(ui->dielectric_const->text().trimmed())){
            QMessageBox::critical(this,tr("Error"),tr("Invalid dielectric constant value"));
    } else if (!isdielectric_const_or_conductivity(ui->conductivity->text().trimmed())){
            QMessageBox::critical(this,tr("Error"),tr("Invalid conductivity value"));
    } else if (!isdielectric_const_or_conductivity(ui->atmospheric_bending_const->text().trimmed())){
            QMessageBox::critical(this,tr("Error"),tr("Invalid atmospheric bending constant value"));
    } else if (!isfrequency(ui->frequency->text().trimmed())){
    QMessageBox::critical(this,tr("Error"),tr("Invalid frequency value"));
    } else if (!isfraction_of(ui->fraction_of_situations->text().trimmed())){
    QMessageBox::critical(this,tr("Error"),tr("Invalid fraction of situations value"));
    } else if (!isfraction_of(ui->fraction_of_time->text().trimmed())){
    QMessageBox::critical(this,tr("Error"),tr("Invalid fraction of time value"));
    } else if (!isdielectric_const_or_conductivity(ui->effective_radiated_power->text().trimmed())){
    QMessageBox::critical(this,tr("Error"),tr("Invalid fraction of time value"));
    } else
    if (fileout.open(QIODevice::WriteOnly)){
        QTextStream write_params(&fileout);

        write_params << ui->dielectric_const->text() << Qt::endl;
        write_params << ui->conductivity->text() << Qt::endl;
        write_params << ui->atmospheric_bending_const->text() << Qt::endl;
        write_params << ui->frequency->text() << Qt::endl;
        write_params << ui->radio_climate->currentIndex()+1 << Qt::endl;
        write_params << ui->polarization->currentIndex() << Qt::endl;
        write_params << ui->fraction_of_situations->text() << Qt::endl;
        write_params << ui->fraction_of_time->text() << Qt::endl;
        write_params << ui->effective_radiated_power->text() << Qt::endl;

        fileout.close();

        this->setWindowTitle(file_name);
        ui->file_name->addItem(fl);
        int file_index = ui->file_name->findText(fl);
        refresh_file_data();
        ui->file_name->setCurrentIndex(file_index);
    } else {
        QMessageBox::critical(this,tr("Error"),tr("File not found"));
    }
    } else if (is_exist(ui->file_name->currentText())) {
        QString file_name = this->windowTitle();
        QFile fileout(file_name);
        if (!isdielectric_const_or_conductivity(ui->dielectric_const->text().trimmed())){
                QMessageBox::critical(this,tr("Error"),tr("Invalid dielectric constant value"));
        } else if (!isdielectric_const_or_conductivity(ui->conductivity->text().trimmed())){
                QMessageBox::critical(this,tr("Error"),tr("Invalid conductivity value"));
        } else if (!isdielectric_const_or_conductivity(ui->atmospheric_bending_const->text().trimmed())){
                QMessageBox::critical(this,tr("Error"),tr("Invalid atmospheric bending constant value"));
        } else if (!isfrequency(ui->frequency->text().trimmed())){
        QMessageBox::critical(this,tr("Error"),tr("Invalid frequency value"));
        } else if (!isfraction_of(ui->fraction_of_situations->text().trimmed())){
        QMessageBox::critical(this,tr("Error"),tr("Invalid fraction of situations value"));
        } else if (!isfraction_of(ui->fraction_of_time->text().trimmed())){
        QMessageBox::critical(this,tr("Error"),tr("Invalid fraction of time value"));
        } else if (!isdielectric_const_or_conductivity(ui->effective_radiated_power->text().trimmed())){
        QMessageBox::critical(this,tr("Error"),tr("Invalid fraction of time value"));
        } else
        if (fileout.open(QIODevice::WriteOnly)){
            QTextStream write_params(&fileout);

            write_params << ui->dielectric_const->text() << Qt::endl;
            write_params << ui->conductivity->text() << Qt::endl;
            write_params << ui->atmospheric_bending_const->text() << Qt::endl;
            write_params << ui->frequency->text() << Qt::endl;
            write_params << ui->radio_climate->currentIndex()+1 << Qt::endl;
            write_params << ui->polarization->currentIndex() << Qt::endl;
            write_params << ui->fraction_of_situations->text() << Qt::endl;
            write_params << ui->fraction_of_time->text() << Qt::endl;
            write_params << ui->effective_radiated_power->text() << Qt::endl;

            fileout.close();
            int file_index = ui->file_name->findText(file_name.section(set->get_dir_path(),1,1));
            refresh_file_data();
            ui->file_name->setCurrentIndex(file_index);
        } else {
            QMessageBox::critical(this,tr("Error"),tr("File not found"));
        }
    } else {
        QMessageBox::critical(this,tr("Error"),tr("File is not exist"));
        set_to_none();
        refresh_file_data();
    }

}


void lrp_file::on_delete_file_lrp_clicked()
{
    QString title = this->windowTitle();
    if (title == "Untitled"){
        QString file_name = QFileDialog::getOpenFileName(this,
                                                         tr("Open file"),"",
                                                         tr("*.lrp"));
    this->setWindowTitle(file_name);
    QProcess *process = new QProcess;
    process->start("rm",QStringList()<< file_name);

    set_to_none();
    refresh_file_data();
    process->close();
    delete process;
    } else {
        if (is_exist(title.section(set->get_dir_path(),1,1))){
        QProcess *process = new QProcess;
        process->start("rm",QStringList()<< title);

        set_to_none();
        refresh_file_data();
        process->close();
        delete process;
    } else {
            QMessageBox::critical(this,tr("Error"), tr("File is not exist"));
            refresh_file_data();
            set_to_none();
        }
        }
}


void lrp_file::on_file_name_activated(int index)
{
    QString file_name = ui->file_name->itemText(index);

    if (file_name == "None"){
        set_to_none();
        refresh_file_data();

    } else{
        this->setWindowTitle(set->get_dir_path() + file_name);
        refresh_file_data();
    }
}

void lrp_file::set_to_none()
{
    this->setWindowTitle("Untitled");
    int none = ui->file_name->findText("None");
    ui-> file_name->setCurrentIndex(none);
    ui->dielectric_const->clear();
    ui->conductivity->clear();
    ui->atmospheric_bending_const->clear();
    ui->frequency->clear();
    ui->radio_climate->setCurrentIndex(0);
    ui->polarization->setCurrentIndex(0) ;
    ui->fraction_of_situations->clear();
    ui->fraction_of_time->clear();
    ui->effective_radiated_power->clear();

}


void lrp_file::refresh_file_data()
{
    QString check_str = ui->file_name->currentText();
    QDir path(set->get_dir_path());
    QStringList files = path.entryList(QStringList() << "*.lrp", QDir:: Files);// Check file if any one file not set on combobox
    for (int i = 0; i < files.length(); i++){
        if (ui->file_name->findText(files[i]) == -1){
            ui->file_name->addItem(files[i]);
        }
    }
    for (int i = 0; i < ui->file_name->count(); i++ ){ // Check file if any one file is not exist in such dir
        if (files.contains(ui->file_name->itemText(i)) == false && ui->file_name->itemText(i)!= "None"){
            ui->file_name->removeItem(i);
        }
    }
    if (ui->file_name->currentText() != "None") {
         this->setWindowTitle(set->get_dir_path() + ui->file_name->currentText()); // set window title
        QFile fileIn(set->get_dir_path() + ui->file_name->currentText()); //file in stream
        QString read_params;                                              //input stream's variable

        if (fileIn.open(QIODevice::ReadOnly)){                            //Stream In start

        read_params = fileIn.readAll();


        ui->dielectric_const->setText(read_params.section("\n",0,0));
        ui->conductivity->setText(read_params.section("\n",1,1));
        ui->atmospheric_bending_const->setText(read_params.section("\n",2,2));
        ui->frequency->setText(read_params.section("\n",3,3));
        ui->radio_climate->setCurrentIndex(read_params.section("\n",4,4).toInt() - 1);
        ui->polarization->setCurrentIndex(read_params.section("\n",5,5).toInt());
        ui->fraction_of_situations->setText(read_params.section("\n",6,6));
        ui->fraction_of_time->setText(read_params.section("\n",7,7));
        ui->effective_radiated_power->setText(read_params.section("\n",8,8));


        }
    }

}

void lrp_file::on_refresh_file_clicked()
{
    refresh_file_data();
}


void lrp_file::on_lrp_file_finished(int result)
{
    refresh_file_data();
    set_to_none();
}
bool lrp_file::is_exist(QString file_name)
{
    QDir path(set->get_dir_path());
    QStringList files = path.entryList(QStringList() << "*.lrp", QDir:: Files);
    if (!files.contains(file_name))
    {
        return false;

    } else {
        return true;
    }
}
void lrp_file::retranslate(){
    ui->retranslateUi(this);
}
