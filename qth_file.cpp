/*	
	File                 : qth_file.cpp
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


#include "qth_file.h"
#include "mainwindow.h"
#include "ui_qth_file.h"
#include "math.h"
#include <QFileDialog>
#include <QFile>
#include <QProcess>
#include <QDebug>
#include <QArrayData>
#include <QStringList>
#include <QMessageBox>
#include <QRegularExpression>
#include <QAbstractItemView>

QString DD_to_DMS(QString param);
QString DMS_to_DD(QString param);
bool isDMS_format(QString str);
bool isDD_format(QString str);
bool islongitude(QString str);
bool islatitude(QString str);
bool is_not_empty(QString str);

qth_file::qth_file(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::qth_file)
{
    QString file_name = "Untitled";
    ui->setupUi(this);

    set = new Settings(this);

    this->setWindowTitle(file_name);
    ui->DD_format_latitude->setChecked(true);
    ui->DD_format_longitude->setChecked(true);
    ui->file_name->addItem("None");

    ui->file_name->view()->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    refresh_file_data();
}

qth_file::~qth_file()
{
    delete ui;
}

bool is_not_empty(QString str){
    if (str.trimmed() == ""){
        return false;
    } else{
        return true;
    }
}

void qth_file::set_to_none()
{

    int none = ui->file_name->findText("None");
    ui-> file_name->setCurrentIndex(none);
    ui->site_name->clear();
    ui->latitude_qth->clear();
    ui->longitude_qth->clear();
    ui->height_qth->clear();
    ui->DD_format_latitude->setChecked(true);
    ui->DD_format_longitude->setChecked(true);
    ui->DMS_format_latitude->setChecked(false);
    ui->DMS_format_longitude->setChecked(false);
    ui->latitude_choose->setCurrentIndex(0);
    ui->longitude_choose->setCurrentIndex(0);
    ui->metric->setCurrentIndex(0);
    this->setWindowTitle("Untitled");

}

bool isDMS_format(QString str)
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
    } else if (DMS_to_DD(str).toFloat() <= 180 && DMS_to_DD(str).toFloat() >= 0 && str_s[1].toInt() >= 0 && str_s[1].toInt() < 60 && str_s[2].toFloat() >= 0 && str_s[2].toFloat() < 60  ) {
       return true;
    } else {
        return false;
    }
}
}
bool isDD_format(QString str)
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
bool islongitude(QString str)
{
    QStringList str_s = str.split(" ");
    float longitude = str.toFloat();
    if (isDMS_format(str))
    {
        if (str_s[0].toInt() >= 0 && str_s[0].toInt()<= 180 )
        {
            return true;
        } else
        {
            return false;
        }
     } else if (isDD_format(str))
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

bool islatitude(QString str)
{
    QStringList str_s = str.split(" ");
    float longitude = str.toFloat();
    if (isDMS_format(str))
    {
        if (str_s[0].toInt() >= 0 && str_s[0].toInt() <= 90 )
        {
            return true;
        } else
        {
            return false;
        }
     } else if (isDD_format(str))
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

void qth_file::refresh_file_data()
{
    QDir path(set->get_dir_path());
    QStringList files = path.entryList(QStringList() << "*.qth", QDir:: Files);// Check file if any one file not set on combobox
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

        QString metric;                                                   //Check variable Meters or foots
        QString latitude;
        QString longitude;

        if (fileIn.open(QIODevice::ReadOnly)){                            //Stream In start

        read_params = fileIn.readAll();

        if (read_params.section("\n",3,3).contains("m")){                 //Check metric
            metric = read_params.section("\n",3,3).section("m",0,0);
            ui->metric->setCurrentIndex(1);
        } else {
            metric = read_params.section("\n",3,3);
            ui->metric->setCurrentIndex(0);
        }
        latitude = read_params.section("\n",1,1);
        longitude = read_params.section("\n",2,2);

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

        ui->site_name->setText(read_params.section("\n",0,0));
        ui->latitude_qth->setText(latitude);
        ui->longitude_qth->setText(longitude);
        ui->height_qth->setText(metric);

        if (isDD_format(latitude)){       //Set combobox DD or DMS format
            ui->DD_format_latitude->setChecked(true);
            ui->DMS_format_latitude->setChecked(false);

        } else {
            ui->DD_format_latitude->setChecked(false);
            ui->DMS_format_latitude->setChecked(true);
        }
        if (isDD_format(longitude)){      //Set combobox DD or DMS format
            ui->DD_format_longitude->setChecked(true);
            ui->DMS_format_longitude->setChecked(false);

        } else {
            ui->DD_format_longitude->setChecked(false);
            ui->DMS_format_longitude->setChecked(true);
        }
        }
    }

}

void qth_file::openFile(QString file_name){
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

QString DD_to_DMS(QString param){
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
QString DMS_to_DD(QString param){
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


void qth_file::on_save_file_qth_clicked()
{
    QString title = this->windowTitle();
    if (title == "Untitled"){
    QString file_name = QFileDialog::getSaveFileName(this,
                                                     tr("Save qth file"),".qth",
                                                     tr("*.qth"));
    QString fl = file_name.section(set->get_dir_path(),1,1);
    QFile fileout(file_name);

    QString metric;
    if (ui->metric->currentIndex() == 1){
        metric = ui->height_qth->text().trimmed() + "m";
    } else {
        metric = ui->height_qth->text().trimmed();
    }

    QString latitude = ui->latitude_qth->text().trimmed();
    QString longitude = ui->longitude_qth->text().trimmed();

    if (!islatitude(latitude)){
        QMessageBox::critical(this,tr("Error"),tr("Invalid latitude value"));
    } else
    if (!islongitude(longitude)) {
        QMessageBox::critical(this,tr("Error"),tr("Invalid longitude value"));
    } else
    if (!isDD_format(ui->height_qth->text())){
        QMessageBox::critical(this,tr("Error"),tr("Invalid height value"));
    } else if (!is_not_empty(ui->site_name->text().trimmed())){
        QMessageBox::critical(this,tr("Error"),tr("Invalid site name"));
    } else

    if (fileout.open(QIODevice::WriteOnly)){
        if (islatitude(latitude) && ui->latitude_choose->currentIndex() == 1){
            latitude = "-"+latitude;
        }
        if (islongitude(longitude) && ui->longitude_choose->currentIndex() == 0){
            longitude = "-" + longitude;
        }
        QTextStream write_params(&fileout);

        write_params << ui->site_name->text() << Qt::endl;
        write_params << latitude << Qt::endl;
        write_params << longitude << Qt::endl;
        write_params << metric << Qt::endl;


        fileout.close();

        this->setWindowTitle(file_name);
        ui->file_name->addItem(fl);
        int file_index = ui->file_name->findText(fl);
        refresh_file_data();
        ui->file_name->setCurrentIndex(file_index);

    } else {
        qDebug()<<"Can't open this file";
    }
    } else if (is_exist(ui->file_name->currentText())) {

        QString metric;
        if (ui->metric->currentIndex() == 1){
            metric = ui->height_qth->text().trimmed() + "m";
        } else {
            metric = ui->height_qth->text().trimmed();
        }
        QString latitude = ui->latitude_qth->text().trimmed();
        QString longitude = ui->longitude_qth->text().trimmed();
        QString file_name = this->windowTitle();
        QFile fileout(file_name);

        if (!islatitude(latitude)){
            QMessageBox::critical(this,tr("Error"),tr("Invalid latitude value"));
        } else
        if (!islongitude(longitude)) {
            QMessageBox::critical(this,tr("Error"),tr("Invalid longitude value"));
        } else
        if (!isDD_format(ui->height_qth->text())){
            QMessageBox::critical(this,tr("Error"),tr("Invalid height value"));
        } else if (!is_not_empty(ui->site_name->text().trimmed())){
            QMessageBox::critical(this,tr("Error"),tr("Invalid site name"));
        } else
        if (fileout.open(QIODevice::WriteOnly)){
            if (islatitude(latitude) && ui->latitude_choose->currentIndex() == 1){
                latitude = "-"+latitude;
            }
            if (islongitude(longitude) && ui->longitude_choose->currentIndex() == 0){
                longitude = "-" + longitude;
            }
            QTextStream write_params(&fileout);

            write_params << ui->site_name->text() << Qt::endl;
            write_params << latitude << Qt::endl;
            write_params << longitude << Qt::endl;
            write_params << metric << Qt::endl;

            fileout.close();


        int file_index = ui->file_name->findText(file_name.section(set->get_dir_path(),1,1));
        refresh_file_data();
        ui->file_name->setCurrentIndex(file_index);
        }
    } else {
        QMessageBox::critical(this,tr("Error"),tr("File is not exist"));
        set_to_none();
        refresh_file_data();
    }
}


void qth_file::on_save_as_file_qth_clicked()
{
    if (is_exist(ui->file_name->currentText()) || ui->file_name->currentText() == "None"){
    QString metric;
    if (ui->metric->currentIndex() == 1){
        metric = ui->height_qth->text().trimmed() + "m";
    } else {
        metric = ui->height_qth->text().trimmed();
    }
    QString latitude = ui->latitude_qth->text().trimmed();
    QString longitude = ui->longitude_qth->text().trimmed();

    if (!islatitude(latitude)){
        QMessageBox::critical(this,tr("Error"),tr("Invalid latitude value"));
    } else
    if (!islongitude(longitude)) {
        QMessageBox::critical(this,tr("Error"),tr("Invalid longitude value"));
    } else
    if (!isDD_format(ui->height_qth->text())){
        QMessageBox::critical(this,tr("Error"),tr("Invalid height value"));
    } else
    if (!is_not_empty(ui->site_name->text().trimmed())){
        QMessageBox::critical(this,tr("Error"),tr("Invalid site name"));
    } else {
      QString file_name = QFileDialog::getSaveFileName(this,
                                                         tr("Save qth file"),".qth",
                                                         tr("*.qth"));
      QString fl = file_name.section(set->get_dir_path(),1,1);
      QFile fileout(file_name);

    if (fileout.open(QIODevice::WriteOnly)){
        if (islatitude(latitude) && ui->latitude_choose->currentIndex() == 1){
            latitude = "-"+latitude;
        }
        if (islongitude(longitude) && ui->longitude_choose->currentIndex() == 0){
            longitude = "-" + longitude;
        }
        QTextStream write_params(&fileout);

        write_params << ui->site_name->text() << Qt::endl;
        write_params << latitude << Qt::endl;
        write_params << longitude << Qt::endl;
        write_params << metric << Qt::endl;


        fileout.close();



    int file_index;
    ui->file_name->addItem(fl);

    file_index = ui->file_name->findText(fl);
    ui->file_name->setCurrentIndex(file_index);
    this->setWindowTitle(file_name);
    refresh_file_data();
    }
    }
    } else {
        QMessageBox::critical(this,tr("Error"),tr("File is not exist"));
        set_to_none();
        refresh_file_data();
    }
}


void qth_file::on_delete_file_qth_clicked()
{
     QString title = this->windowTitle();
     if (title == "Untitled"){
         QString file_name = QFileDialog::getOpenFileName(this,
                                                          tr("Open file"),"",
                                                          tr("*.qth"));
     this->setWindowTitle(file_name);
     QProcess *process = new QProcess;
     process->start("rm",QStringList()<< file_name);


     refresh_file_data();
     set_to_none();
     this->setWindowTitle("Untitled");
     process->close();
     delete process;
     } else {
         if (is_exist(title.section(set->get_dir_path(),1,1))){
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


void qth_file::on_file_name_activated(int index)
{

    QString file_name = ui->file_name->itemText(index);

    if (file_name == "None"){
        set_to_none();
        refresh_file_data();

    } else{
        refresh_file_data();
    }
}


void qth_file::on_qth_file_finished(int result)
{
    refresh_file_data();
    set_to_none();
}
void qth_file::on_Refresh_clicked()
{
    refresh_file_data();
}


void qth_file::on_DD_format_latitude_clicked()
{
    QString latitude;
    if (ui->DD_format_latitude->isChecked() == false){
    ui->DMS_format_latitude->setChecked(true);
    latitude = ui->latitude_qth ->text();
        if (isDD_format(latitude) == true && latitude != ""){
            ui->latitude_qth->setText(DD_to_DMS(latitude));
        } else if (isDMS_format(latitude) == true && latitude != "") {
            ui->latitude_qth->setText(latitude);
        } else {
            ui->latitude_qth->clear();
        }
    } else {
    ui->DMS_format_latitude->setChecked(false);
    ui->DD_format_latitude->setChecked(true);
    latitude = ui->latitude_qth ->text();
        if (isDD_format(latitude) == true && latitude != ""){
            ui->latitude_qth->setText(latitude);
        } else if (isDMS_format(latitude) == true && latitude != ""){
            ui->latitude_qth->setText(DMS_to_DD(latitude));
        } else {
            ui->latitude_qth->clear();
        }
    }
}


void qth_file::on_DMS_format_latitude_clicked()
{
    QString latitude;
    if (ui->DMS_format_latitude->isChecked() == false){
    ui->DD_format_latitude->setChecked(true);
    latitude = ui->latitude_qth ->text();
        if (isDD_format(latitude) == true && latitude != ""){
            ui->latitude_qth->setText(latitude);
        } else if (isDMS_format(latitude) == true && latitude != ""){
            ui->latitude_qth->setText(DMS_to_DD(latitude));
        } else {
            ui->latitude_qth->clear();
        }
    } else {
    ui->DD_format_latitude->setChecked(false);
    ui->DMS_format_latitude->setChecked(true);
    latitude = ui->latitude_qth ->text();
        if (isDD_format(latitude) == true && latitude != ""){
            ui->latitude_qth->setText(DD_to_DMS(latitude));
        } else if (isDMS_format(latitude) == true && latitude != "") {
            ui->latitude_qth->setText(latitude);
        } else {
            ui->latitude_qth->clear();
        }
    }
}


void qth_file::on_DD_format_longitude_clicked()
{
    QString longitude;
    if (ui->DD_format_longitude->isChecked() == false){
    ui->DMS_format_longitude->setChecked(true);
    longitude = ui->longitude_qth ->text();
        if (isDD_format(longitude) == true && longitude != ""){
            ui->longitude_qth->setText(DD_to_DMS(longitude));
        } else if (isDMS_format(longitude) == true && longitude != "") {
            ui->longitude_qth->setText(longitude);
        } else {
            ui->longitude_qth->clear();
        }
    } else {

    ui->DMS_format_longitude->setChecked(false);
    ui->DD_format_longitude->setChecked(true);
    longitude = ui->longitude_qth ->text();
        if (isDD_format(longitude) == true && longitude != ""){
            ui->longitude_qth->setText(longitude);
        } else if (isDMS_format(longitude) == true && longitude != ""){
            ui->longitude_qth->setText(DMS_to_DD(longitude));
        } else {
            ui->longitude_qth->clear();
        }
    }
}


void qth_file::on_DMS_format_longitude_clicked()
{
    QString longitude;
    if (ui->DMS_format_longitude->isChecked() == false){
    ui->DD_format_longitude->setChecked(true);
    longitude = ui->longitude_qth ->text();
        if (isDD_format(longitude) == true && longitude != ""){
            ui->longitude_qth->setText(longitude);
        } else if (isDMS_format(longitude) == true && longitude != ""){
            ui->longitude_qth->setText(DMS_to_DD(longitude));
        } else {
            ui->longitude_qth->clear();
        }
    } else {
    ui->DD_format_longitude->setChecked(false);
    ui->DMS_format_longitude->setChecked(true);
    longitude = ui->longitude_qth ->text();
        if (isDD_format(longitude) == true && longitude != ""){
            ui->longitude_qth->setText(DD_to_DMS(longitude));
        } else if (isDMS_format(longitude) == true && longitude != "") {
            ui->longitude_qth->setText(longitude);
        } else {
            ui->longitude_qth->clear();
        }
    }
}

bool qth_file::is_exist(QString file_name)
{
    QDir path(set->get_dir_path());
    QStringList files = path.entryList(QStringList() << "*.qth", QDir:: Files);
    if (!files.contains(file_name))
    {
        return false;

    } else {
        return true;
    }
}
void qth_file::retranslate(){
    ui->retranslateUi(this);
}
