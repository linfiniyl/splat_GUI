/*	
	File                 : dat_file.cpp
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

	Description : .dat file creating form
*/


#include "dat_file.h"
#include "ui_dat_file.h"
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QAbstractItemView>
#include <QProcess>

bool is_not_empty_d(QString str1);
QString DD_to_DMS_d(QString param);
QString DMS_to_DD_d(QString param);
bool isDMS_format_d(QString str);
bool isDD_format_d(QString str);
bool islongitude_d(QString str);
bool islatitude_d(QString str);


dat_file::dat_file(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dat_file)
{
    ui->setupUi(this);

    QString file_name = tr("Untitled");
    set = new Settings(this);

    this->setWindowTitle(file_name);
    ui->DD_format_latitude->setChecked(true);
    ui->DD_format_longitude->setChecked(true);
    ui->city_line->addItem("None");
    ui->city_line->view()->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    refresh_file_data();
}

dat_file::~dat_file()
{
    delete ui;
}

bool is_not_empty_d(QString str){
    if (str.trimmed() == ""){
        return false;
    } else{
        return true;
    }
}

bool isDD_format_d(QString str)
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

bool isDMS_format_d(QString str)
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
    } else if (DMS_to_DD_d(str).toFloat() <= 180 && DMS_to_DD_d(str).toFloat() >= 0 && str_s[1].toInt() >= 0 && str_s[1].toInt() < 60 && str_s[2].toFloat() >= 0 && str_s[2].toFloat() < 60  ) {
       return true;
    } else {
        return false;
    }
}
}

bool islongitude_d(QString str)
{
    QStringList str_s = str.split(" ");
    float longitude = str.toFloat();
    if (isDMS_format_d(str))
    {
        if (str_s[0].toInt() >= 0 && str_s[0].toInt()<= 180 )
        {
            return true;
        } else
        {
            return false;
        }
     } else if (isDD_format_d(str))
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

bool islatitude_d(QString str)
{
    QStringList str_s = str.split(" ");
    float longitude = str.toFloat();
    if (isDMS_format_d(str))
    {
        if (str_s[0].toInt() >= 0 && str_s[0].toInt() <= 90 )
        {
            return true;
        } else
        {
            return false;
        }
     } else if (isDD_format_d(str))
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

QString DD_to_DMS_d(QString param){
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

QString DMS_to_DD_d(QString param){
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

void dat_file::set_to_none()
{
    ui->file_name_2->clear();
    ui->field->clear();
    ui-> file_name->clear();
    ui->city_line->clear();
    ui->city_line->addItem("None");
    ui->site_name->clear();
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
void dat_file::set_to_none_city()
{


    int none_line = ui->city_line->findText("None");
    ui->city_line->setCurrentIndex(none_line);
    ui->site_name->clear();
    ui->latitude->clear();
    ui->longitude->clear();
    ui->DD_format_latitude->setChecked(true);
    ui->DD_format_longitude->setChecked(true);
    ui->DMS_format_latitude->setChecked(false);
    ui->DMS_format_longitude->setChecked(false);
    ui->latitude_choose->setCurrentIndex(0);
    ui->longitude_choose->setCurrentIndex(0);
}

void dat_file::openFile(QString file_name){
    QFile file_check(file_name);
if (file_check.exists()){
 if (is_city_format(file_name) ){

        refresh_file_data();

        this->setWindowTitle(file_name);
 } else {
     QMessageBox::critical(this,tr("Error"),tr("Invalid format"));
     set_to_none();
     refresh_file_data();
 }
} else {
     QMessageBox::critical(this,tr("Error"),tr("File is not exist"));
    set_to_none();
    refresh_file_data();
}
}

void dat_file::refresh_file_data()
{
    QString str_l;
    QStringList list;
    QFile fileIn(ui->file_name->text());
    if (fileIn.open(QIODevice::ReadOnly)){
        str_l = fileIn.readAll();
        list = str_l.split("\n");
        for (int i = 0; i < list.length();i++){
            if (ui->city_line->findText(list[i].section(", ",0,0).trimmed()) == -1 && list[i].section(", ",0,0).trimmed() != ""){
                ui->city_line->insertItem(i+1,list[i].section(", ",0,0).trimmed());
        }
        }
        fileIn.close();
    }
    int count = 0;
    for (int i = 0; i< ui->city_line->count(); i++){
        if (fileIn.open(QIODevice::ReadOnly)){
            str_l = fileIn.readAll();
            list = str_l.split("\n");
        for (int j = 0; j < list.length();j++){
            if (list[j].section(", ",0,0).trimmed() == ui->city_line->itemText(i) || ui->city_line->itemText(i) == "None"){
                count ++;
            }
        }
        if (count == 0){
             ui->city_line->removeItem(i);
             count = 0;
        } else {
            count = 0;
        }
    }
        fileIn.close();
    }

    if (windowTitle() != tr("Untitled")){
        ui->file_name->setText(this->windowTitle());
        ui->file_name_2->setText(this->windowTitle());
        QString read_params;
        if (fileIn.open(QIODevice::ReadOnly)){
            read_params = fileIn.readAll();
        }
        fileIn.close();
        ui->field->clear();
        ui->field->appendPlainText(read_params);
    }
    if (windowTitle() != tr("Untitled") && ui->city_line->currentText() != "None") {
        if (is_city_format(ui->file_name->text())){
        ui->tab->setEnabled(true);
        QFile fileIn(ui->file_name->text()); //file in stream
        QString read_params;                                              //input stream's variable
        QStringList list_str;

        QString name_site;
        QString latitude;
        QString longitude;
        int index_line = ui->city_line->currentIndex();
    if (fileIn.open(QIODevice::ReadOnly)){
        read_params = fileIn.readAll();
        list_str = read_params.split("\n");
        for (int i = 0; i < list_str.length();i++){

        if (i == index_line - 1){
        latitude = list_str[i].section(", ",1,1).trimmed();
        longitude = list_str[i].section(", ",2,2).trimmed();
        name_site =list_str[i].section(", ",0,0).trimmed();
        }}
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
        ui->site_name->setText(name_site);
        ui->latitude->setText(latitude);
        ui->longitude->setText(longitude);

        if (isDD_format_d(latitude)){       //Set combobox DD or DMS format
            ui->DD_format_latitude->setChecked(true);
            ui->DMS_format_latitude->setChecked(false);

        } else {
            ui->DD_format_latitude->setChecked(false);
            ui->DMS_format_latitude->setChecked(true);
        }
        if (isDD_format_d(longitude)){      //Set combobox DD or DMS format
            ui->DD_format_longitude->setChecked(true);
            ui->DMS_format_longitude->setChecked(false);

        } else {
            ui->DD_format_longitude->setChecked(false);
            ui->DMS_format_longitude->setChecked(true);
        }

    }
    fileIn.close();
        } else {
             QString read_params;
             QString file_name = ui->file_name_2->text().trimmed();
             QFile fileIn(file_name);
             if (fileIn.open(QIODevice::ReadOnly)){
                read_params = fileIn.readAll();
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



void dat_file::on_Resfresh_file_list_clicked()
{
    refresh_file_data();
}



void dat_file::on_add_line_clicked()
{
    QString title = this->windowTitle();
    if (title == tr("Untitled")){
        QString site_n = ui->site_name->text().trimmed() + ", ";
        QString latitude = ui->latitude->text().trimmed() + ", ";
        QString longitude = ui->longitude->text().trimmed();

        if (ui->city_line->findText(ui->site_name->text()) != -1){
                QMessageBox::critical(this,tr ("Error"),tr("Invalid site name (duplicate)"));
    } else if (!islatitude_d(ui->latitude->text().trimmed())){
            QMessageBox::critical(this,tr("Error"),tr("Invalid latitude value"));
    } else if (!islongitude_d(ui->longitude->text().trimmed())){
            QMessageBox::critical(this,tr("Error"),tr("Invalid longitude value"));
    } else if (!is_not_empty_d(ui->site_name->text().trimmed())){
            QMessageBox::critical(this,tr("Error"),tr("Invalid site name"));
    }
        else{
        QString file_name = QFileDialog::getSaveFileName(this,
                                                      tr("Save dat file"),".cdat",
                                                      tr("*.cdat"));
        QFile fileout(file_name);

        if (islatitude_d(ui->latitude->text().trimmed()) && ui->latitude_choose->currentIndex() == 1){
                latitude = "-"+latitude;
        }
        if (islongitude_d(ui->longitude->text().trimmed()) && ui->longitude_choose->currentIndex() == 0){
                longitude = "-" + longitude;
        }
            QString str_ll = latitude + longitude;
            QString str = site_n + str_ll;
        if (fileout.open(QIODevice::WriteOnly)){
            QTextStream out(&fileout);
              out << str.trimmed()<<Qt::endl;

        fileout.close();

        } else {
            qDebug()<< "Don't open this file";
        }

        this->setWindowTitle(file_name);
        ui->city_line->addItem(site_n.section(", ",0,0));
        int city_index = ui->city_line->findText(site_n.section(", ",0,0));
        refresh_file_data();
        ui->city_line->setCurrentIndex(city_index);
        refresh_file_data();

        }
    } else {
        QString file_name = title;
        QFile file_check(file_name);
        if (file_check.exists()){
        QString site_n = ui->site_name->text().trimmed() + ", ";
        QString latitude = ui->latitude->text().trimmed() + ", ";
        QString longitude = ui->longitude->text().trimmed();

        if (ui->city_line->findText(ui->site_name->text()) != -1){
                QMessageBox::critical(this,tr ("Error"),tr("Invalid site name (duplicate)"));
    } else if (!islatitude_d(ui->latitude->text().trimmed())){
            QMessageBox::critical(this,tr("Error"),tr("Invalid latitude value"));
    } else if (!islongitude_d(ui->longitude->text().trimmed())){
            QMessageBox::critical(this,tr("Error"),tr("Invalid longitude value"));
    } else if (!is_not_empty_d(ui->site_name->text().trimmed())){
            QMessageBox::critical(this,tr("Error"),tr("Invalid site name"));
    }
        else{
        QFile fileout(file_name);
        if (islatitude_d(ui->latitude->text().trimmed()) && ui->latitude_choose->currentIndex() == 1){
                latitude = "-"+latitude;
        }
        if (islongitude_d(ui->longitude->text().trimmed()) && ui->longitude_choose->currentIndex() == 0){
                longitude = "-" + longitude;
        }
        QString str_ll = latitude + longitude;
        QString str = site_n + str_ll;
        if (fileout.open(QIODevice::Append)){
            QTextStream out(&fileout);
              out << str.trimmed()<<Qt::endl;

        fileout.close();
        } else {
            qDebug()<< "Don't open this file";
        }

        ui->city_line->addItem(site_n.section(", ",0,0));
        int city_index = ui->city_line->findText(site_n.section(", ",0,0));
        refresh_file_data();
        ui->city_line->setCurrentIndex(city_index);
        refresh_file_data();
    }
        } else {
            QMessageBox::critical(this,tr("Error"), tr("File is not exist"));
            refresh_file_data();
            set_to_none();
        }
    }
}




void dat_file::on_save_line_clicked()
{
    QString title = this->windowTitle();
    if (title == tr("Untitled")){


        QString site_n = ui->site_name->text().trimmed() + ", ";
        QString latitude = ui->latitude->text().trimmed() + ", ";
        QString longitude = ui->longitude->text().trimmed();

        if (ui->city_line->findText(ui->site_name->text()) != -1){
                QMessageBox::critical(this,tr ("Error"),tr("Invalid site name (duplicate)"));
        } else if (!islatitude_d(ui->latitude->text().trimmed())){
            QMessageBox::critical(this,tr("Error"),tr("Invalid latitude value"));
    } else if (!islongitude_d(ui->longitude->text().trimmed())){
            QMessageBox::critical(this,tr("Error"),tr("Invalid longitude value"));
    } else if (!is_not_empty_d(ui->site_name->text().trimmed())){
            QMessageBox::critical(this,tr("Error"),tr("Invalid site name"));
    }
          else {
        QString file_name = QFileDialog::getSaveFileName(this,
                                                      tr("Save dat file"),".cdat",
                                                      tr("*.cdat"));
        QFile fileout(file_name);
        if (islatitude_d(ui->latitude->text().trimmed()) && ui->latitude_choose->currentIndex() == 1){
                latitude = "-"+latitude;
        }
        if (islongitude_d(ui->longitude->text().trimmed()) && ui->longitude_choose->currentIndex() == 0){
                longitude = "-" + longitude;
        }
        QString str_ll = latitude + longitude;
        QString str = site_n + str_ll;
        if (fileout.open(QIODevice::WriteOnly)){
            QTextStream out(&fileout);
              out << str.trimmed()<<Qt::endl;

        fileout.close();
        } else {
            qDebug()<< "Don't open this file";
        }

        this->setWindowTitle(file_name);
        ui->city_line->addItem(site_n.section(", ",0,0));
        int city_index = ui->city_line->findText(site_n.section(", ",0,0).trimmed());
        ui->city_line->setCurrentIndex(city_index);
        refresh_file_data();
        }
    } else if (ui->city_line->currentText() == "None") {
        QString file_name = title;
        QFile file_check(file_name);
        if (file_check.exists()){
        QString site_n = ui->site_name->text().trimmed()+ ", ";
        QString latitude = ui->latitude->text().trimmed() + ", ";
        QString longitude = ui->longitude->text().trimmed();

        if (ui->city_line->findText(ui->site_name->text()) != -1){
                QMessageBox::critical(this,tr ("Error"),tr("Invalid site name (duplicate)"));
    } else if (!islatitude_d(ui->latitude->text().trimmed())){
            QMessageBox::critical(this,tr("Error"),tr("Invalid latitude value"));
    } else if (!islongitude_d(ui->longitude->text().trimmed())){
            QMessageBox::critical(this,tr("Error"),tr("Invalid longitude value"));
    } else if (!is_not_empty_d(ui->site_name->text().trimmed())){
            QMessageBox::critical(this,tr("Error"),tr("Invalid site name"));
    }
        else{
            if (islatitude_d(ui->latitude->text().trimmed()) && ui->latitude_choose->currentIndex() == 1){
                    latitude = "-"+latitude;
            }
            if (islongitude_d(ui->longitude->text().trimmed()) && ui->longitude_choose->currentIndex() == 0){
                    longitude = "-" + longitude;
            }
        QString str_ll = latitude + longitude;
        QString str = site_n + str_ll;
        QFile fileout(file_name);
        if (fileout.open(QIODevice::Append)){
            QTextStream out(&fileout);
              out << str.trimmed()<<Qt::endl;

        fileout.close();
        } else {
            qDebug()<< "Don't open this file";
        }

        ui->city_line->addItem(site_n.section(", ",0,0));
        int city_index = ui->city_line->findText(site_n.section(", ",0,0).trimmed());
        ui->city_line->setCurrentIndex(city_index);
        refresh_file_data();
        }
        } else {
            QMessageBox::critical(this,tr("Error"), tr("File is not exist"));
            refresh_file_data();
            set_to_none();
        }
    } else {
        QString file_name = title;
        QFile file_check(file_name);
    if (file_check.exists()){
        QString site_n = ui->site_name->text().trimmed()+ ", ";
        QString latitude = ui->latitude->text().trimmed() + ", ";
        QString longitude = ui->longitude->text().trimmed();

        QStringList list;
        if (ui->city_line->findText(ui->site_name->text())!= -1 && ui->city_line->currentText() != ui->site_name->text()){
                QMessageBox::critical(this,tr ("Error"),tr("Invalid site name (duplicate)"));
    } else if (!islatitude_d(ui->latitude->text().trimmed())){
            QMessageBox::critical(this,tr("Error"),tr("Invalid latitude value"));
    } else if (!islongitude_d(ui->longitude->text().trimmed())){
            QMessageBox::critical(this,tr("Error"),tr("Invalid longitude value"));
    } else if (!is_not_empty_d(ui->site_name->text().trimmed())){
            QMessageBox::critical(this,tr("Error"),tr("Invalid site name"));
    }
        else{
        if (islatitude_d(ui->latitude->text().trimmed()) && ui->latitude_choose->currentIndex() == 1){
                latitude = "-"+latitude;
        }
        if (islongitude_d(ui->longitude->text().trimmed()) && ui->longitude_choose->currentIndex() == 0){
                longitude = "-" + longitude;
        }
        if (is_exist_line( ui->city_line->currentText(),title)){
        QString str_ll = latitude + longitude;
        QString str = site_n + str_ll;
        QString str_read;
        QFile fileout(file_name);
        if (fileout.open(QIODevice::ReadOnly)){
            str_read = fileout.readAll();
            fileout.close();
        }
        str_read = str_read.trimmed();
        list =  str_read.split("\n");
        for (int i = 0; i < list.length(); i++){
            if (i+1 == ui->city_line->currentIndex()){
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
        int city_index = ui->city_line->findText(site_n.section(", ",0,0).trimmed());
        ui->city_line->setCurrentIndex(city_index);
        refresh_file_data();

    } else {
            QMessageBox::critical(this,tr("Error"), tr("line is not exist"));
            refresh_file_data();
            set_to_none_city();
        }
    }
    } else {
        QMessageBox::critical(this,tr("Error"), tr("File is not exist"));
        refresh_file_data();
        set_to_none();
    }
    }
}



void dat_file::on_city_line_activated(int index)
{
    QString city_name = ui->city_line->itemText(index);

    if (city_name == "None"){
        set_to_none_city();
        refresh_file_data();

    } else{
        refresh_file_data();
    }

}


void dat_file::on_dat_file_finished(int result)
{
    refresh_file_data();
    set_to_none();
}


void dat_file::on_DD_format_latitude_clicked()
{
    QString latitude;
    if (ui->DD_format_latitude->isChecked() == false){
    ui->DMS_format_latitude->setChecked(true);
    latitude = ui->latitude ->text();
        if (isDD_format_d(latitude) == true && latitude != ""){
            ui->latitude->setText(DD_to_DMS_d(latitude));
        } else if (isDMS_format_d(latitude) == true && latitude != "") {
            ui->latitude->setText(latitude);
        } else {
            ui->latitude->clear();
        }
    } else {
    ui->DMS_format_latitude->setChecked(false);
    ui->DD_format_latitude->setChecked(true);
    latitude = ui->latitude ->text();
        if (isDD_format_d(latitude) == true && latitude != ""){
            ui->latitude->setText(latitude);
        } else if (isDMS_format_d(latitude) == true && latitude != ""){
            ui->latitude->setText(DMS_to_DD_d(latitude));
        } else {
            ui->latitude->clear();
        }
    }
}


void dat_file::on_DMS_format_latitude_clicked()
{
    QString latitude;
    if (ui->DMS_format_latitude->isChecked() == false){
    ui->DD_format_latitude->setChecked(true);
    latitude = ui->latitude ->text();
        if (isDD_format_d(latitude) == true && latitude != ""){
            ui->latitude->setText(latitude);
        } else if (isDMS_format_d(latitude) == true && latitude != ""){
            ui->latitude->setText(DMS_to_DD_d(latitude));
        } else {
            ui->latitude->clear();
        }
    } else {
    ui->DD_format_latitude->setChecked(false);
    ui->DMS_format_latitude->setChecked(true);
    latitude = ui->latitude ->text();
        if (isDD_format_d(latitude) == true && latitude != ""){
            ui->latitude->setText(DD_to_DMS_d(latitude));
        } else if (isDMS_format_d(latitude) == true && latitude != "") {
            ui->latitude->setText(latitude);
        } else {
            ui->latitude->clear();
        }
    }
}


void dat_file::on_DD_format_longitude_clicked()
{
    QString longitude;
    if (ui->DD_format_longitude->isChecked() == false){
    ui->DMS_format_longitude->setChecked(true);
    longitude = ui->longitude ->text();
        if (isDD_format_d(longitude) == true && longitude != ""){
            ui->longitude->setText(DD_to_DMS_d(longitude));
        } else if (isDMS_format_d(longitude) == true && longitude != "") {
            ui->longitude->setText(longitude);
        } else {
            ui->longitude->clear();
        }
    } else {

    ui->DMS_format_longitude->setChecked(false);
    ui->DD_format_longitude->setChecked(true);
    longitude = ui->longitude ->text();
        if (isDD_format_d(longitude) == true && longitude != ""){
            ui->longitude->setText(longitude);
        } else if (isDMS_format_d(longitude) == true && longitude != ""){
            ui->longitude->setText(DMS_to_DD_d(longitude));
        } else {
            ui->longitude->clear();
        }
    }
}


void dat_file::on_DMS_format_longitude_clicked()
{
    QString longitude;
    if (ui->DMS_format_longitude->isChecked() == false){
    ui->DD_format_longitude->setChecked(true);
    longitude = ui->longitude ->text();
        if (isDD_format_d(longitude) == true && longitude != ""){
            ui->longitude->setText(longitude);
        } else if (isDMS_format_d(longitude) == true && longitude != ""){
            ui->longitude->setText(DMS_to_DD_d(longitude));
        } else {
            ui->longitude->clear();
        }
    } else {
    ui->DD_format_longitude->setChecked(false);
    ui->DMS_format_longitude->setChecked(true);
    longitude = ui->longitude ->text();
        if (isDD_format_d(longitude) == true && longitude != ""){
            ui->longitude->setText(DD_to_DMS_d(longitude));
        } else if (isDMS_format_d(longitude) == true && longitude != "") {
            ui->longitude->setText(longitude);
        } else {
            ui->longitude->clear();
        }
    }
}


void dat_file::on_Delete_line_clicked()
{
    if (ui->city_line->currentText() == "None"){
        QMessageBox::warning(this,tr("Warning"),tr("Select line to delete"));
    } else {
        if (is_exist_line(ui->city_line->currentText(), ui->file_name->text())){
        QFile fileout(this->windowTitle());
        QString str_read;
        QStringList list;
        if (fileout.open(QIODevice::ReadOnly)){
            str_read = fileout.readAll();
            fileout.close();
        }
        list =  str_read.split("\n");
        for (int i = 0; i < list.length(); i++){
            if (i + 1 == ui->city_line->currentIndex()){
                list.remove(i);
                ui->city_line->removeItem(i+1);
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


void dat_file::on_delete_file_clicked()
{
    QString title = this->windowTitle();
    QFile file_check(title);
    if (title == tr("Untitled" )){
        QString file_name = QFileDialog::getOpenFileName(this,
                                                         tr("Open file"),"",
                                                         tr("*.cdat"));
    this->setWindowTitle(file_name);
    QProcess *process = new QProcess;
    process->start("rm",QStringList()<< file_name);

    refresh_file_data();
    set_to_none();
    this->setWindowTitle(tr("Untitled"));
    process->close();
    delete process;
    } else {
        if (file_check.exists()){
        QProcess *process = new QProcess;
        process->start("rm",QStringList()<< title);

        refresh_file_data();
        set_to_none();
        process->close();
        delete process;
    } else {
            QMessageBox::critical(this,tr("Error"), tr("File is not exist"));
            refresh_file_data();
            set_to_none();
        }
    }
}


void dat_file::on_save_as_file_clicked()
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
    set_to_none_city();
    this->setWindowTitle(file_name);
}

bool dat_file::is_exist_line(QString string_name, QString file_name)
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
bool dat_file::is_city_format(QString file_name)
{
    int count = 0;
    QString str;
    QString latitude,longitude, site_name;
    QStringList list;
    QFile fileIn(file_name);
    if (fileIn.open(QIODevice::ReadOnly)){
        str = fileIn.readAll().trimmed();
        list = str.split("\n");
        for (int i = 0; i < list.length();i++){
            site_name = list[i].section(", ",0,0);
            if (list[i].section(", ", 1, 1).contains("-")) {
                 latitude = list[i].section(", ", 1, 1).section("-",1,1);
            } else {
                latitude = list[i].section(", ",1,1);
            }
            if (list[i].section(", ", 2, 2).contains("-")) {
                 longitude = list[i].section(", ", 2, 2).section("-",1,1);
            } else {
                longitude = list[i].section(", ", 2, 2);
            }
            if (!islatitude_d(latitude)|| !is_not_empty_d(latitude) || !islongitude_d(longitude) || !is_not_empty_d(latitude) || !is_not_empty_d(site_name)){
                count ++;

        }

        }
        if (count == 0){
            return true;
        } else {

            return false;
        }
        fileIn.close();
    } else {
        return false;
    }
}
void dat_file::retranslate(){
    ui->retranslateUi(this);
}

void dat_file::on_file_name_ch_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,
                                             tr("Open file"));

    ui->file_name->setText(file_name);
    ui->file_name_2->setText(file_name);
    this->setWindowTitle(file_name);
    if (!is_city_format(file_name)){
        ui->tabWidget->setCurrentIndex(1);
        ui->tab->setEnabled(false);
        QMessageBox::warning(this,tr("Warning"), tr("Invalid file content format"));
    } else {
        ui->tab->setEnabled(true);
    }
    refresh_file_data();
}


void dat_file::on_file_name_ch_2_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,
                                             tr("Open file"));

    ui->file_name->setText(file_name);
    ui->file_name_2->setText(file_name);
    this->setWindowTitle(file_name);
    if (!is_city_format(file_name)){
        ui->tabWidget->setCurrentIndex(1);
        ui->tab->setEnabled(false);
        QMessageBox::warning(this,tr("Warning"), tr("Invalid file content format"));
    } else {
        ui->tab->setEnabled(true);
    }
    refresh_file_data();
}


void dat_file::on_Save_file_clicked()
{
    if (this->windowTitle() == tr("Untitled")){
        QString file_name = QFileDialog::getSaveFileName(this,
                                                         tr("Save city file"),".dat");
        QString str;
        str = ui->field->toPlainText();
        QFile fileout(file_name);
        if (fileout.open(QIODevice::WriteOnly)){
            QTextStream out(&fileout);
              out << str.trimmed()<<Qt::endl;
        fileout.close();
        this->setWindowTitle(file_name);
        refresh_file_data();
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


void dat_file::on_Save_as_file_clicked()
{
    QString file_name = QFileDialog::getSaveFileName(this,
                                                     tr("Save city file"),".dat");
    QString str;
    str = ui->field->toPlainText();
    QFile fileout(file_name);
    if (fileout.open(QIODevice::WriteOnly)){
        QTextStream out(&fileout);
          out << str.trimmed()<<Qt::endl;
    fileout.close();
    this->setWindowTitle(file_name);
    refresh_file_data();
}
}


void dat_file::on_Delete_file_clicked()
{
    QString title = this->windowTitle();
    if (title == tr("Untitled") ){
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


void dat_file::on_tabWidget_currentChanged(int index)
{
    refresh_file_data();
    if (this->windowTitle() != tr("Untitled")){
    QString file_name = this->windowTitle();
    if (!is_city_format(file_name) && index == 0){
        ui->tabWidget->setCurrentIndex(1);
        ui->tab->setEnabled(false);
        QMessageBox::warning(this,tr("Warning"), tr("Invalid file content format"));
    } else {
        ui->tab->setEnabled(true);
    }
    refresh_file_data();
    }
}


void dat_file::on_Resfresh_file_list_2_clicked()
{
    refresh_file_data();
}

