/*	
	File                 : udt_file.cpp
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


#include "udt_file.h"
#include "ui_udt_file.h"
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QAbstractItemView>
#include <QProcess>

bool is_not_empty_u(QString str1);
QString DD_to_DMS_u(QString param);
QString DMS_to_DD_u(QString param);
bool isDMS_format_u(QString str);
bool isDD_format_u(QString str);
bool islongitude_u(QString str);
bool islatitude_u(QString str);
bool isheight(QString str);

udt_file::udt_file(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::udt_file)
{
    ui->setupUi(this);
    QString file_name = tr("Untitled");
    set = new Settings(this);

    this->setWindowTitle(file_name);
    ui->DD_format_latitude->setChecked(true);
    ui->DD_format_longitude->setChecked(true);
    ui->point_line->addItem("None");

    ui->point_line->view()->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    refresh_file_data();
}

udt_file::~udt_file()
{
    delete ui;
}


bool is_not_empty_u(QString str){
    if (str.trimmed() == ""){
        return false;
    } else{
        return true;
    }
}
bool isheight(QString str)
{
    QStringList str_s = str.split(" ");
    if ( str_s.length() != 1){
        return false;

    } else {
    QRegularExpression re("\\d*");
    QRegularExpression str_t("\\D");
    if (str_s[0].contains("m")){
        str_s[0] = str_s[0].section("m",0,0);
    } else if (str_s[0].contains("meters")){
        str_s[0] = str_s[0].section("meters",0,0);
    }
    if (!re.match(str_s[0]).hasMatch()){
        return false;
    } else if ((str_s[0].toFloat() >= 0 && (!str_t.match(str_s[0]).hasMatch() || (str_s[0].contains(".") && str_s[0].toFloat() != 0 )))) {
        return true;
    } else {
        return false;
    }
    }
}

bool isDD_format_u(QString str)
{
    QStringList str_s = str.split(" ");
    if ( str_s.length() != 1){
        return false;

    } else {
    QRegularExpression re("\\d*");
    QRegularExpression str_t("\\D");
    if (!re.match(str_s[0]).hasMatch()){
        return false;
    } else if (str_s[0].toFloat() >= 0 && (!str_t.match(str_s[0]).hasMatch() || (str_s[0].contains(".") && str_s[0].toFloat() != 0 ))) {
        return true;
    } else {
        return false;
    }
    }
}

bool isDMS_format_u(QString str)
{
    QStringList str_s = str.split(" ");
    if ( str_s.length()!=3){
       return false;
    } else {
    QRegularExpression re("\\d*");
    if (!re.match(str_s[0]).hasMatch()){
       return false;
    } else if (!re.match(str_s[1]).hasMatch()){
       return false;
    } else if (!re.match(str_s[2]).hasMatch()){
       return false;
    } else if (DMS_to_DD_u(str).toFloat() <= 180 && DMS_to_DD_u(str).toFloat() >= 0 && str_s[1].toInt() >= 0 && str_s[1].toInt() < 60 && str_s[2].toFloat() >= 0 && str_s[2].toFloat() < 60  ) {
       return true;
    } else {
        return false;
    }
}
}

bool islongitude_u(QString str)
{
    QStringList str_s = str.split(" ");
    float longitude = str.toFloat();
    if (isDMS_format_u(str))
    {
        if (str_s[0].toInt() >= 0 && str_s[0].toInt()<= 180 )
        {
            return true;
        } else
        {
            return false;
        }
     } else if (isDD_format_u(str))
     {
        if (longitude >= 0 && longitude <= 180)
        {
            return true;
        } else
        {
            return false;
        }
     } else {
        return false;
    }
}

bool islatitude_u(QString str)
{
    QStringList str_s = str.split(" ");
    float longitude = str.toFloat();
    if (isDMS_format_u(str))
    {
        if (str_s[0].toInt() >= 0 && str_s[0].toInt() <= 90 )
        {
            return true;
        } else
        {
            return false;
        }
     } else if (isDD_format_u(str))
     {
        if (longitude >= 0 && longitude <= 90)
        {
            return true;
        } else
        {
            return false;
        }
     } else {
        return false;
    }
}

QString DD_to_DMS_u(QString param){
    std::string str = param.toStdString();
    float param_f = param.toFloat();
    int D =  std::stoi( str );
    if (D < 0){
        D *= -1;
    }
    if (param_f < 0 ){
        param_f *= -1;
    }

    float arg_M = (param_f - D) * 60;
    int M = (int) arg_M;
    float S = (arg_M - M ) * 60;

    QString D_str = QString::number(D);
    QString M_str = QString::number(M);
    QString S_str = QString::number(S);

    QString DM = D_str + " " + M_str;
    QString DMS = DM + " " + S_str;

    if (D < 0){
        return "-" + DMS;
    } else {
        return DMS;
    }
}

QString DMS_to_DD_u(QString param){
    QString D_m = param.section(" ",0,0);
    if (D_m.toInt() < 0){
        D_m = D_m.section("-",1,1);
    }
    QString M = param.section(" ",1,1);
    QString S = param.section(" ",2,2);

    float D_arg =  D_m.toFloat();
    float M_arg =  M.toFloat();
    float S_arg =  S.toFloat();

    float DD_str = D_arg + M_arg / 60.0 + S_arg / 3600.0;
    QString DD = QString::number(DD_str);
    if (D_m.contains("-")){
        return "-" + DD;
    } else {

    return DD;
    }
}

void udt_file::set_to_none()
{
    ui->file_name->clear();
    ui->file_name_2->clear();
    ui->field->clear();
    ui->point_line->clear();
    ui->point_line->addItem("None");
    ui->point_height->clear();
    ui->metric->setCurrentIndex(0);
    ui->latitude->clear();
    ui->longitude->clear();
    ui->DD_format_latitude->setChecked(true);
    ui->DD_format_longitude->setChecked(true);
    ui->DMS_format_latitude->setChecked(false);
    ui->DMS_format_longitude->setChecked(false);
    ui->latitude_choose->setCurrentIndex(0);
    ui->longitude_choose->setCurrentIndex(0);
    this->setWindowTitle(tr("Untitled"));

}
void udt_file::set_to_none_city()
{


    int none_line = ui->point_line->findText("None");
    ui->point_line->setCurrentIndex(none_line);
    ui->point_height->clear();
    ui->metric->setCurrentIndex(0);
    ui->latitude->clear();
    ui->longitude->clear();
    ui->DD_format_latitude->setChecked(true);
    ui->DD_format_longitude->setChecked(true);
    ui->DMS_format_latitude->setChecked(false);
    ui->DMS_format_longitude->setChecked(false);
    ui->latitude_choose->setCurrentIndex(0);
    ui->longitude_choose->setCurrentIndex(0);

}

void udt_file::openFile(QString file_name){
 if (is_user_file(file_name)){
        refresh_file_data();

        this->setWindowTitle(file_name); 
} else {
     QMessageBox::critical(this,tr("Error"),tr("Invalid format"));
     set_to_none();
     refresh_file_data();
 }
}


void udt_file::refresh_file_data()
{
    QString str_l;
    QStringList list;
    QFile fileIn( ui->file_name->text());
    if (fileIn.open(QIODevice::ReadOnly)){
        str_l = fileIn.readAll();
        list = str_l.split("\n");
        for (int i = 0; i < list.length();i++){
            if (ui->point_line->findText(list[i].trimmed()) == -1 && list[i].trimmed() != ""){
                ui->point_line->insertItem(i+1,list[i].trimmed());
        }
        }
        fileIn.close();
    }
    int count = 0;
    for (int i = 0; i< ui->point_line->count(); i++){
        if (fileIn.open(QIODevice::ReadOnly)){
            str_l = fileIn.readAll();
            list = str_l.split("\n");
        for (int j = 0; j < list.length();j++){
            if (list[j].trimmed() == ui->point_line->itemText(i) || ui->point_line->itemText(i) == "None"){
                count ++;
            }
        }
        if (count == 0){
             ui->point_line->removeItem(i);
             count = 0;
        } else {
            count = 0;
        }
    }
        fileIn.close();
    }
    ui->file_name->setText(this->windowTitle());
    ui->file_name_2->setText(this->windowTitle());
    if (windowTitle() != tr("Untitled")){
        ui->file_name->setText(this->windowTitle());
        ui->file_name_2->setText(this->windowTitle());
        QString read_params;                                              //input stream's variable
        if (fileIn.open(QIODevice::ReadOnly)){
            read_params = fileIn.readAll();
        }
        fileIn.close();
        ui->field->clear();
        ui->field->appendPlainText(read_params);
    }
    if (windowTitle() != tr("Untitled") && ui->point_line->currentText() != "None" ) {
        if (is_user_file(ui->file_name->text())){
        ui->tab->setEnabled(true);
        QFile fileIn(ui->file_name->text()); //file in stream
        QString read_params;                                              //input stream's variable
        QStringList list_str;

        QString height_point;
        QString latitude;
        QString longitude;
        int index_line = ui->point_line->currentIndex();
    if (fileIn.open(QIODevice::ReadOnly)){
        read_params = fileIn.readAll();
        list_str = read_params.split("\n");
        for (int i = 0; i < list_str.length();i++){

        if (i == index_line - 1){
        latitude = list_str[i].section(", ",0,0).trimmed();
        longitude = list_str[i].section(", ",1,1).trimmed();
        height_point =list_str[i].section(", ",2,2).trimmed();
        }}
        if (height_point.contains("m")){                 //Check metric
            height_point = height_point.section("m",0,0);
            ui->metric->setCurrentIndex(1);
        } else {
            ui->metric->setCurrentIndex(0);
        }
        if (latitude.contains("-")){
            latitude = latitude.section("-",1,1);
            ui->latitude_choose->setCurrentIndex(1);
        } else {
            ui->latitude_choose->setCurrentIndex(0);
        }
        if (longitude.contains("-")){
            longitude = longitude.section("-",1,1);
            ui->longitude_choose->setCurrentIndex(0);
        } else {
            ui->longitude_choose->setCurrentIndex(1);
        }
        ui->point_height->setText(height_point);
        ui->latitude->setText(latitude);
        ui->longitude->setText(longitude);

        if (isDD_format_u(latitude)){       //Set combobox DD or DMS format
            ui->DD_format_latitude->setChecked(true);
            ui->DMS_format_latitude->setChecked(false);

        } else {
            ui->DD_format_latitude->setChecked(false);
            ui->DMS_format_latitude->setChecked(true);
        }
        if (isDD_format_u(longitude)){      //Set combobox DD or DMS format
            ui->DD_format_longitude->setChecked(true);
            ui->DMS_format_longitude->setChecked(false);

        } else {
            ui->DD_format_longitude->setChecked(false);
            ui->DMS_format_longitude->setChecked(true);
        }

    }
    fileIn.close();
    } else {
         qDebug()<<is_user_file(ui->file_name->text());
         QString read_params;
         QString file_name = ui->file_name_2->text().trimmed();
         QFile fileIn(file_name);
         if (fileIn.open(QIODevice::ReadOnly)){
            read_params = fileIn.readAll();
            qDebug()<<read_params<<"111"<< file_name;
            ui->field->clear();
            ui->field->appendPlainText(read_params);
         }
         fileIn.close();
         ui->tab->setEnabled(false);
         ui->tabWidget->setCurrentIndex(1);
    } }  else {
        set_to_none_city();
    }
}


void udt_file::on_Resfresh_file_list_clicked()
{
    refresh_file_data();
}



void udt_file::on_add_line_clicked()
{
    QString title = this->windowTitle();
    if (title == tr("Untitled")){

        QString latitude = ui->latitude->text().trimmed() + ", ";
        QString longitude = ui->longitude->text().trimmed() + ", ";
        QString site_height = ui->point_height->text().trimmed();

        if (islatitude_u(ui->latitude->text().trimmed()) && ui->latitude_choose->currentIndex() == 1){
                latitude = "-"+latitude;
        }
        if (islongitude_u(ui->longitude->text().trimmed()) && ui->longitude_choose->currentIndex() == 0){
                longitude = "-" + longitude;
        }
        QString str = latitude + longitude + site_height;
        if (ui->point_line->findText(str) != -1){
                QMessageBox::critical(this,tr ("Error"),tr("Invalid point line (duplicate)"));
    } else if (!islatitude_u(ui->latitude->text().trimmed())){
            QMessageBox::critical(this,tr("Error"),tr("Invalid latitude value"));
    } else if (!islongitude_u(ui->longitude->text().trimmed())){
            QMessageBox::critical(this,tr("Error"),tr("Invalid longitude value"));
    } else if (!isDD_format_u(ui->point_height->text().trimmed())){
            QMessageBox::critical(this,tr("Error"),tr("Invalid point height"));
    }
        else{
            if (ui->metric->currentIndex() == 1){
                site_height = ui->point_height->text().trimmed() + "m";
            } else {
                site_height = ui->point_height->text().trimmed();
            }
        QString file_name = QFileDialog::getSaveFileName(this,
                                                      tr("Save dat file"),".dat");
        QFile fileout(file_name);

        str = latitude + longitude + site_height;
        if (fileout.open(QIODevice::WriteOnly)){
            QTextStream out(&fileout);
              out << str.trimmed()<<Qt::endl;

        fileout.close();

        } else {
            qDebug()<< "Don't open this file";
        }

        this->setWindowTitle(file_name);
        ui->file_name->setText(file_name);
        ui->point_line->addItem(str);
        int city_index = ui->point_line->findText(str);
        refresh_file_data();
        ui->point_line->setCurrentIndex(city_index);
        refresh_file_data();
        }
    } else {
        QString file_name = title;
            QString latitude = ui->latitude->text().trimmed() + ", ";
            QString longitude = ui->longitude->text().trimmed() + ", ";
            QString site_height = ui->point_height->text().trimmed();

            if (islatitude_u(ui->latitude->text().trimmed()) && ui->latitude_choose->currentIndex() == 1){
                    latitude = "-"+latitude;
            }
            if (islongitude_u(ui->longitude->text().trimmed()) && ui->longitude_choose->currentIndex() == 0){
                    longitude = "-" + longitude;
            }
            QString str = latitude + longitude + site_height;
            if (ui->point_line->findText(str) != -1){
                    QMessageBox::critical(this,tr ("Error"),tr("Invalid point line (duplicate)"));
        } else if (!islatitude_u(ui->latitude->text().trimmed())){
                QMessageBox::critical(this,tr("Error"),tr("Invalid latitude value"));
        } else if (!islongitude_u(ui->longitude->text().trimmed())){
                QMessageBox::critical(this,tr("Error"),tr("Invalid longitude value"));
        } else if (!isDD_format_u(ui->point_height->text().trimmed())){
                QMessageBox::critical(this,tr("Error"),tr("Invalid point height"));
        }
        else{
                if (ui->metric->currentIndex() == 1){
                    site_height = ui->point_height->text().trimmed() + "m";
                } else {
                    site_height = ui->point_height->text().trimmed();
                }
        QFile fileout(file_name);

        QString str = latitude + longitude + site_height;
        if (fileout.open(QIODevice::Append)){
            QTextStream out(&fileout);
              out << str.trimmed()<<Qt::endl;

        fileout.close();
        } else {
            qDebug()<< "Don't open this file";
        }

        ui->point_line->addItem(str);
        int city_index = ui->point_line->findText(str);
        refresh_file_data();
        ui->point_line->setCurrentIndex(city_index);
        refresh_file_data();
    }
    }
}




void udt_file::on_save_line_clicked()
{
    QString title = this->windowTitle();
    if (title == tr("Untitled")){


        QString latitude = ui->latitude->text().trimmed() + ", ";
        QString longitude = ui->longitude->text().trimmed() + ", ";
        QString site_height = ui->point_height->text().trimmed();

        if (islatitude_u(ui->latitude->text().trimmed()) && ui->latitude_choose->currentIndex() == 1){
                latitude = "-"+latitude;
        }
        if (islongitude_u(ui->longitude->text().trimmed()) && ui->longitude_choose->currentIndex() == 0){
                longitude = "-" + longitude;
        }
        QString str = latitude + longitude + site_height;
        if (ui->point_line->findText(str) != -1){
                QMessageBox::critical(this,tr ("Error"),tr("Invalid point line (duplicate)"));
    } else if (!islatitude_u(ui->latitude->text().trimmed())){
            QMessageBox::critical(this,tr("Error"),tr("Invalid latitude value"));
    } else if (!islongitude_u(ui->longitude->text().trimmed())){
            QMessageBox::critical(this,tr("Error"),tr("Invalid longitude value"));
    } else if (!isDD_format_u(ui->point_height->text().trimmed())){
            QMessageBox::critical(this,tr("Error"),tr("Invalid point height"));
    }
          else {
            if (ui->metric->currentIndex() == 1){
                site_height = ui->point_height->text().trimmed() + "m";
            } else {
                site_height = ui->point_height->text().trimmed();
            }
        QString file_name = QFileDialog::getSaveFileName(this,
                                                      tr("Save dat file"),".dat");
        QFile fileout(file_name);

        QString str = latitude + longitude + site_height;
        if (fileout.open(QIODevice::WriteOnly)){
            QTextStream out(&fileout);
              out << str.trimmed()<<Qt::endl;

        fileout.close();
        } else {
            qDebug()<< "Don't open this file";
        }

        this->setWindowTitle(file_name);
        ui->file_name->setText(file_name);
        ui->point_line->addItem(str);
        int city_index = ui->point_line->findText(str);
        refresh_file_data();
        ui->point_line->setCurrentIndex(city_index);
        refresh_file_data();
        }
    } else if (ui->point_line->currentText() == "None") {
        QString file_name = title;

            QString latitude = ui->latitude->text().trimmed() + ", ";
            QString longitude = ui->longitude->text().trimmed() + ", ";
            QString site_height = ui->point_height->text().trimmed();

        if (islatitude_u(ui->latitude->text().trimmed()) && ui->latitude_choose->currentIndex() == 1){
                latitude = "-"+latitude;
        }
        if (islongitude_u(ui->longitude->text().trimmed()) && ui->longitude_choose->currentIndex() == 0){
                longitude = "-" + longitude;
        }
            QString str = latitude + longitude + site_height;
            if (ui->point_line->findText(str) != -1){
                    QMessageBox::critical(this,tr ("Error"),tr("Invalid point line (duplicate)"));
        } else if (!islatitude_u(ui->latitude->text().trimmed())){
                QMessageBox::critical(this,tr("Error"),tr("Invalid latitude value"));
        } else if (!islongitude_u(ui->longitude->text().trimmed())){
                QMessageBox::critical(this,tr("Error"),tr("Invalid longitude value"));
        } else if (!isDD_format_u(ui->point_height->text().trimmed())){
                QMessageBox::critical(this,tr("Error"),tr("Invalid point height"));
        }
        else{
                if (ui->metric->currentIndex() == 1){
                    site_height = ui->point_height->text().trimmed() + "m";
                } else {
                    site_height = ui->point_height->text().trimmed();
                }

        str = latitude + longitude + site_height;
        QFile fileout(file_name);
        if (fileout.open(QIODevice::Append)){
            QTextStream out(&fileout);
              out << str.trimmed()<<Qt::endl;

        fileout.close();
        } else {
            qDebug()<< "Don't open this file";
        }

        ui->point_line->addItem(str);
        int city_index = ui->point_line->findText(str.trimmed());
        ui->point_line->setCurrentIndex(city_index);
        refresh_file_data();
        }
    } else {
        QString file_name = title;
        QString fl = file_name.section(set->get_dir_path(),1,1);
        QString latitude = ui->latitude->text().trimmed() + ", ";
        QString longitude = ui->longitude->text().trimmed() + ", ";
        QString site_height = ui->point_height->text().trimmed();

    if (islatitude_u(ui->latitude->text().trimmed()) && ui->latitude_choose->currentIndex() == 1){
            latitude = "-"+latitude;
    }
    if (islongitude_u(ui->longitude->text().trimmed()) && ui->longitude_choose->currentIndex() == 0){
            longitude = "-" + longitude;
    }
        QString str = latitude + longitude + site_height;
        if (ui->point_line->findText(str) != -1){
                QMessageBox::critical(this,tr ("Error"),tr("Invalid point line (duplicate)"));
    } else if (!islatitude_u(ui->latitude->text().trimmed())){
            QMessageBox::critical(this,tr("Error"),tr("Invalid latitude value"));
    } else if (!islongitude_u(ui->longitude->text().trimmed())){
            QMessageBox::critical(this,tr("Error"),tr("Invalid longitude value"));
    } else if (!isDD_format_u(ui->point_height->text().trimmed())){
            QMessageBox::critical(this,tr("Error"),tr("Invalid point height"));
    }
        else{
            QStringList list;
            if (ui->metric->currentIndex() == 1){
                site_height = ui->point_height->text().trimmed() + "m";
            } else {
                site_height = ui->point_height->text().trimmed();
            }

        if (is_exist_line( ui->point_line->currentText(),fl)){
        QString str = latitude + longitude + site_height;
        QString str_read;
        QFile fileout(file_name);
        if (fileout.open(QIODevice::ReadOnly)){
            str_read = fileout.readAll();
            fileout.close();
        }
        str_read = str_read.trimmed();
        list =  str_read.split("\n");
        for (int i = 0; i < list.length(); i++){
            if (i+1 == ui->point_line->currentIndex()){
                list[i] = str;
            }
        }

        if (fileout.open(QIODevice::WriteOnly)){
           QTextStream out(&fileout);
               for (int i = 0; i < list.length(); i++){
                   out << list[i] << Qt::endl;
               }

           }
           fileout.close();


        refresh_file_data();
        int city_index = ui->point_line->findText(str);
        ui->point_line->setCurrentIndex(city_index);
        refresh_file_data();

    } else {
            QMessageBox::critical(this,tr("Error"), tr("line is not exist"));
            refresh_file_data();
            set_to_none_city();
        }
    }
    }
}


void udt_file::on_point_line_activated(int index)
{
    QString city_name = ui->point_line->itemText(index);

    if (city_name == "None"){
        set_to_none_city();
        refresh_file_data();

    } else{
        refresh_file_data();
    }

}


void udt_file::on_udt_file_finished(int result)
{
    refresh_file_data();
    set_to_none();
}


void udt_file::on_DD_format_latitude_clicked()
{
    QString latitude;
    if (ui->DD_format_latitude->isChecked() == false){
    ui->DMS_format_latitude->setChecked(true);
    latitude = ui->latitude ->text();
        if (isDD_format_u(latitude) == true && latitude != ""){
            ui->latitude->setText(DD_to_DMS_u(latitude));
        } else if (isDMS_format_u(latitude) == true && latitude != "") {
            ui->latitude->setText(latitude);
        } else {
            ui->latitude->clear();
        }
    } else {
    ui->DMS_format_latitude->setChecked(false);
    ui->DD_format_latitude->setChecked(true);
    latitude = ui->latitude ->text();
        if (isDD_format_u(latitude) == true && latitude != ""){
            ui->latitude->setText(latitude);
        } else if (isDMS_format_u(latitude) == true && latitude != ""){
            ui->latitude->setText(DMS_to_DD_u(latitude));
        } else {
            ui->latitude->clear();
        }
    }
}


void udt_file::on_DMS_format_latitude_clicked()
{
    QString latitude;
    if (ui->DMS_format_latitude->isChecked() == false){
    ui->DD_format_latitude->setChecked(true);
    latitude = ui->latitude->text();
        if (isDD_format_u(latitude) == true && latitude != ""){
            ui->latitude->setText(latitude);
        } else if (isDMS_format_u(latitude) == true && latitude != ""){
            ui->latitude->setText(DMS_to_DD_u(latitude));
        } else {
            ui->latitude->clear();
        }
    } else {
    ui->DD_format_latitude->setChecked(false);
    ui->DMS_format_latitude->setChecked(true);
    latitude = ui->latitude->text();
        if (isDD_format_u(latitude) == true && latitude != ""){
            ui->latitude->setText(DD_to_DMS_u(latitude));
        } else if (isDMS_format_u(latitude) == true && latitude != "") {
            ui->latitude->setText(latitude);
        } else {
            ui->latitude->clear();
        }
    }
}


void udt_file::on_DD_format_longitude_clicked()
{
    QString longitude;
    if (ui->DD_format_longitude->isChecked() == false){
    ui->DMS_format_longitude->setChecked(true);
    longitude = ui->longitude ->text();
        if (isDD_format_u(longitude) == true && longitude != ""){
            ui->longitude->setText(DD_to_DMS_u(longitude));
        } else if (isDMS_format_u(longitude) == true && longitude != "") {
            ui->longitude->setText(longitude);
        } else {
            ui->longitude->clear();
        }
    } else {

    ui->DMS_format_longitude->setChecked(false);
    ui->DD_format_longitude->setChecked(true);
    longitude = ui->longitude ->text();
        if (isDD_format_u(longitude) == true && longitude != ""){
            ui->longitude->setText(longitude);
        } else if (isDMS_format_u(longitude) == true && longitude != ""){
            ui->longitude->setText(DMS_to_DD_u(longitude));
        } else {
            ui->longitude->clear();
        }
    }
}


void udt_file::on_DMS_format_longitude_clicked()
{
    QString longitude;
    if (ui->DMS_format_longitude->isChecked() == false){
    ui->DD_format_longitude->setChecked(true);
    longitude = ui->longitude ->text();
        if (isDD_format_u(longitude) == true && longitude != ""){
            ui->longitude->setText(longitude);
        } else if (isDMS_format_u(longitude) == true && longitude != ""){
            ui->longitude->setText(DMS_to_DD_u(longitude));
        } else {
            ui->longitude->clear();
        }
    } else {
    ui->DD_format_longitude->setChecked(false);
    ui->DMS_format_longitude->setChecked(true);
    longitude = ui->longitude ->text();
        if (isDD_format_u(longitude) == true && longitude != ""){
            ui->longitude->setText(DD_to_DMS_u(longitude));
        } else if (isDMS_format_u(longitude) == true && longitude != "") {
            ui->longitude->setText(longitude);
        } else {
            ui->longitude->clear();
        }
    }
}


void udt_file::on_Delete_line_clicked()
{
    if (ui->point_line->currentText() == "None"){
        QMessageBox::warning(this,tr("Warning"),tr("Select line to delete"));
    } else {
        if (is_exist_line(ui->point_line->currentText(), ui->file_name->text())){
        QFile fileout(this->windowTitle());
        QString str_read;
        QStringList list;
        if (fileout.open(QIODevice::ReadOnly)){
            str_read = fileout.readAll();
            fileout.close();
        }
        list =  str_read.split("\n");
        for (int i = 0; i < list.length(); i++){
            if (i + 1 == ui->point_line->currentIndex()){
                list.remove(i);
                ui->point_line->removeItem(i+1);
                set_to_none_city();
            }
        }

        if (fileout.open(QIODevice::WriteOnly)){
           QTextStream out(&fileout);
               for (int i = 0; i < list.length(); i++){
                   out << list[i] << Qt::endl;
               }

           }
           fileout.close();
        refresh_file_data();
    } else {
            QMessageBox::critical(this,tr("Error"), tr("line is not exist"));
            refresh_file_data();
            set_to_none_city();
        }
    }
}


void udt_file::on_delete_file_clicked()
{
    QString title = this->windowTitle();
    if (title == tr("Untitled")){
        QString file_name = QFileDialog::getOpenFileName(this,
                                                         tr("Open file"),"");
    this->setWindowTitle(file_name);
    QProcess *process = new QProcess;
    process->start("rm",QStringList()<< file_name);


    refresh_file_data();
    set_to_none();
    this->setWindowTitle(tr("Untitled"));
    process->close();
    delete process;
    } else {
        QProcess *process = new QProcess;
        process->start("rm",QStringList()<< title);
        QString error = process->readAllStandardError();
        refresh_file_data();
        set_to_none();
        process->close();
        delete process;
        if (error != ""){
            QMessageBox::critical(this,tr("Error"), error);
            refresh_file_data();
            set_to_none();
        }
    }
}


void udt_file::on_save_as_file_clicked()
{
    QString file_name = QFileDialog::getSaveFileName(this,
                                                     tr("Save dat file"),".dat");
    QString str_read;
    QStringList list;
    QString file_name_source = this->windowTitle();
    QFile fileout(file_name);
    QFile fileout_source(file_name_source);
    if (fileout_source.open(QIODevice::ReadOnly)){
        str_read = fileout_source.readAll();
        fileout_source.close();
    }
    str_read = str_read.trimmed();
    list =  str_read.split("\n");

    if (fileout.open(QIODevice::WriteOnly)){
       QTextStream out(&fileout);
           for (int i = 0; i < list.length(); i++){
               out << list[i] << Qt::endl;
           }

       }
       fileout.close();

    refresh_file_data();
    this->setWindowTitle(file_name);
    ui->file_name->setText(file_name);
    ui->file_name_2->setText(file_name);
}

bool udt_file::is_exist_line(QString string_name, QString file_name)
{
    QFile fileIn(file_name);
    QString str;
    QStringList list;
    int counter = 0;
    if (fileIn.open(QIODevice::ReadOnly)){
        str = fileIn.readAll();
        list = str.split("\n");
        for (int i = 0; i<list.length(); i++){
            if (list[i].contains(string_name)){
                counter ++;
            }
        }
        if (counter == 0 ) {
            return false;
        } else {
            return true;
        }
    fileIn.close();
    }
}


void udt_file::retranslate(){
    ui->retranslateUi(this);
}







void udt_file::on_file_name_ch_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,
                                             tr("Open file"));

    ui->file_name->setText(file_name);
    ui->file_name_2->setText(file_name);
    this->setWindowTitle(file_name);
    if (!is_user_file(file_name)){
        ui->tabWidget->setCurrentIndex(1);
        ui->tab->setEnabled(false);
        QMessageBox::warning(this,tr("Warning"), tr("Invalid file content format"));
    } else {
        ui->tab->setEnabled(true);
    }
    refresh_file_data();
}


void udt_file::on_file_name_ch_2_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,
                                             tr("Open file"));
    ui->file_name->setText(file_name.trimmed());
    ui->file_name_2->setText(file_name.trimmed());
    this->setWindowTitle(file_name);
    if (!is_user_file(file_name)){

        ui->tabWidget->setCurrentIndex(1);
        ui->tab->setEnabled(false);
        QMessageBox::warning(this,tr("Warning"), tr("Invalid file content format"));
    } else {
        ui->tab->setEnabled(true);
    }
    refresh_file_data();
}
bool udt_file::is_user_file(QString file_name)
{
    QString height_point;
    QString latitude;
    QString longitude;
    QString read_params;
    QStringList list_str;
    QFile fileIn(file_name);
    if (fileIn.open(QIODevice::ReadOnly)){
        read_params = fileIn.readAll();
        list_str = read_params.split("\n");
        for (int i = 0; i < list_str.length();i++){
        latitude = list_str[i].section(", ",0,0).trimmed();
        longitude = list_str[i].section(", ",1,1).trimmed();
        height_point =list_str[i].section(", ",2,2).trimmed();
        if (longitude.contains("-")){
            longitude = longitude.section("-",1,1);
        }
        if (latitude.contains("-")){
            latitude = latitude.section("-",1,1);
        }
        if (!islatitude_u(latitude) || !is_not_empty_u(latitude)){

            return false;
        } else if (!islongitude_u(longitude) || !is_not_empty_u(longitude)){

            return false;
        } else if (!isheight(height_point) || !is_not_empty_u(height_point)){

            return false;
        } else {

            return true;
        }
        }}
        fileIn.close();

}

void udt_file::on_Resfresh_file_list_2_clicked()
{
    refresh_file_data();
}


void udt_file::on_Save_file_clicked()
{
    if (this->windowTitle() == tr("Untitled")){
        QString file_name = QFileDialog::getSaveFileName(this,
                                                         tr("Save user file"),".dat");
        QString str;
        str = ui->field->toPlainText();
        QFile fileout(file_name);
        if (fileout.open(QIODevice::WriteOnly)){
            QTextStream out(&fileout);
              out << str.trimmed()<<Qt::endl;
        fileout.close();
        refresh_file_data();
        this->setWindowTitle(file_name);
    }} else {
            QString file_name = this->windowTitle();
            QString str;
            str = ui->field->toPlainText();
            QFile fileout(file_name);
            if (fileout.open(QIODevice::WriteOnly)){
                QTextStream out(&fileout);
                  out << str.trimmed()<<Qt::endl;
            fileout.close();
        }
            refresh_file_data();
        }
}

void udt_file::on_Save_as_file_clicked()
{
    QString file_name = QFileDialog::getSaveFileName(this,
                                                     tr("Save user file"),".dat");
    QString str;
    str = ui->field->toPlainText();
    QFile fileout(file_name);
    if (fileout.open(QIODevice::WriteOnly)){
        QTextStream out(&fileout);
          out << str.trimmed()<<Qt::endl;
    fileout.close();
    refresh_file_data();
    this->setWindowTitle(file_name);
}
}


void udt_file::on_Delete_file_clicked()
{
    QString title = this->windowTitle();
    if (title == tr("Untitled")){
        QString file_name = QFileDialog::getOpenFileName(this,
                                                         tr("Open file"),"");
    this->setWindowTitle(file_name);
    QProcess *process = new QProcess;
    process->start("rm",QStringList()<< file_name);


    refresh_file_data();
    set_to_none();
    this->setWindowTitle(tr("Untitled"));
    process->close();
    delete process;
    } else {

        QProcess *process = new QProcess;
        process->start("rm",QStringList()<< title);
        QString error = process->readAllStandardError();
        refresh_file_data();
        set_to_none();
        process->close();
        delete process;
        if (error != ""){
            QMessageBox::critical(this,tr("Error"), error);
            refresh_file_data();
            set_to_none();
        }
    }
}


void udt_file::on_tabWidget_currentChanged(int index)
{
    refresh_file_data();
    if (this->windowTitle() != tr("Untitled")){
    QString file_name = this->windowTitle();
    if (!is_user_file(file_name) && index == 0){

        ui->tabWidget->setCurrentIndex(1);
        ui->tab->setEnabled(false);
        QMessageBox::warning(this,tr("Warning"), tr("Invalid file content format"));
    } else {
        ui->tab->setEnabled(true);
    }
    refresh_file_data();
    }
}

