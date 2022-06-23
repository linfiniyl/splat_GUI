/*	
	File                 : mainwindow.cpp
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

	Description : main window of UI
*/


#include "mainwindow.h"
#include "graphics_view_zoom.h"
#include "qscrollbar.h"
#include "qth_file.h"
#include <QFileDialog>
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QProcess>
#include <QAbstractItemView>
#include <QDesktopServices>
#include <QProgressDialog>
#include <QScrollArea>
#include <QAbstractScrollArea>
#include <QGraphicsView>
#include <QSizeGrip>
#include <QDesktopServices>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     scene = new QGraphicsScene(this);
     QPixmap pix(":/icons/black.png");
     int w = pix.width();
     int h = pix.height();
     ui->image->fitInView(0,0,w,h);
     scene->addPixmap(QPixmap(pix));
     ui->image->setScene(scene);
     Graphics_view_zoom *z = new Graphics_view_zoom(ui->image);
     z->set_modifiers(Qt::NoModifier);

     QSizeGrip * size_grip  = new QSizeGrip(ui->image);
     ui->view->addWidget(size_grip,0,Qt::AlignRight | Qt::AlignBottom);


    about_info = new about(this);
    file = new qth_file(this);
    file_lrp = new lrp_file(this);
    set = new Settings(this);
    dat = new dat_file(this);
    udt = new udt_file(this);


    ui->receiver_number->setCurrentIndex(1);
    ui->ch_cart_b_file_1->hide();
    ui->ch_cart_b_file_2->hide();
    ui->ch_cart_b_file_3->hide();
    ui->ch_cart_b_file_4->hide();
    ui->ch_cart_b_file_5->hide();
    ui->ch_city_file_1->hide();
    ui->ch_city_file_2->hide();
    ui->ch_city_file_3->hide();
    ui->ch_city_file_4->hide();
    ui->ch_city_file_5->hide();
    ui->transmitter_2->hide();
    ui->transmitter_3->hide();
    ui->transmitter_4->hide();
    ui->city_file_1->hide();
    ui->city_file_2->hide();
    ui->city_file_3->hide();
    ui->city_file_4->hide();
    ui->city_file_5->hide();
    ui->cart_b_file_1->hide();
    ui->cart_b_file_2->hide();
    ui->cart_b_file_3->hide();
    ui->cart_b_file_4->hide();
    ui->cart_b_file_5->hide();
    ui->tr2_l->hide();
    ui->tr3_l->hide();
    ui->tr4_l->hide();
    ui->city1_l->hide();
    ui->city2_l->hide();
    ui->city3_l->hide();
    ui->city4_l->hide();
    ui->city5_l->hide();
    ui->cart_b_l1->hide();
    ui->cart_b_l2->hide();
    ui->cart_b_l3->hide();
    ui->cart_b_l4->hide();
    ui->cart_b_l5->hide();

    ui->ani_file_name->addItem("None");
    ui->graph_file->addItem("None");
    ui->transmitter_1->addItem("None");
    ui->transmitter_2->addItem("None");
    ui->transmitter_3->addItem("None");
    ui->transmitter_4->addItem("None");
    ui->receiver->addItem("None");
    ui->txt_files->addItem("None");

    ui->transmitter_1->view()->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->transmitter_2->view()->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->transmitter_3->view()->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->transmitter_4->view()->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->receiver->view()->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->graph_file->view()->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->txt_files->view()->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    set->set_language();
    refresh();


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionqth_file_triggered()
{

    file->show();
}


void MainWindow::on_actionqth_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this,
                                                     tr("Open file"),"",
                                                     tr("*.qth"));

    file->show();
    file->openFile(file_name);

}


void MainWindow::on_action_lrp_triggered()
{

    file_lrp->show();
}


void MainWindow::on_action_lrp_2_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this,
                                                     tr("Open file"),"",
                                                     tr("*.lrp"));

    file_lrp->show();
    file_lrp->openFile(file_name);
}


void MainWindow::on_Create_clicked()
{
    QString sdf_file = set->get_dir_sdf();
    QString trm_1 =set->get_dir_path() + ui->transmitter_1->currentText();
    QString trm_2 =set->get_dir_path() + ui->transmitter_2->currentText();
    QString trm_3 =set->get_dir_path() + ui->transmitter_3->currentText();
    QString trm_4 =set->get_dir_path() + ui->transmitter_4->currentText();
    QString rcv = set->get_dir_path() + ui->receiver->currentText();
    QString city_1 = ui->city_file_1->text();
    QString city_2 = ui->city_file_2->text();
    QString city_3 = ui->city_file_3->text();
    QString city_4 = ui->city_file_4->text();
    QString city_5 = ui->city_file_5->text();
    QString country_1 = ui->cart_b_file_1->text();
    QString country_2 = ui->cart_b_file_2->text();
    QString country_3 = ui->cart_b_file_3->text();
    QString country_4 = ui->cart_b_file_4->text();
    QString country_5 = ui->cart_b_file_5->text();
    QString log_file = set->get_dir_path() + ui->save_log_text->text() + ui->log_res->text();
    QString p = set->get_dir_grph() + ui->graphic_file_p->text() + ui->res_p->currentText();
    QString e = set->get_dir_grph() + ui->graphic_file_e->text() + ui->res_e->currentText();
    QString h = set->get_dir_grph() + ui->graphic_file_h->text() + ui->res_h->currentText();
    QString H = set->get_dir_grph() + ui->graphic_file_H->text() + ui->res_H->currentText();
    QString l = set->get_dir_grph() + ui->graphic_file_l->text() + ui->res_l->currentText();
    QString c = ui->c_out->text();
    QString L = ui->L_out->text();
    QString o = set->get_dir_grph() + ui-> map_name ->text() + ui->map_res->text();
    QString R = ui->R_out->text();
    QString ano = set->get_dir_path() + ui->ano_out->text() + ui->ano_res->text();
    QString ani = set->get_dir_path() + ui->ani_file_name->currentText();
    QString udt = ui->udt_file->text();
    QString m = ui->m_out->text();
    QString frequency = ui->frequency -> text();
    QString erp = ui->erp->text();
    QString db = ui->db->text();
    QString fz = ui->fz->text();
    QString gc = ui->gc->text();
    int counter = 0;

    QStringList command;

    command.append("-d");
    command.append(sdf_file);
    command.append("-t");
    command.append(trm_1);

    if (ui->transmitter_2->currentText() != "None"){
        command.append(trm_2);
    }
    if (ui->transmitter_3->currentText() != "None"){
        command.append(trm_3);
    }
    if (ui->transmitter_4->currentText() != "None"){
        command.append(trm_4);
    }
    if (ui->receiver->currentText() != "None"){
        command.append("-r");
        command.append(rcv);
    }
    if (ui->city_file_1->text() != ""){
        command.append("-s");
        command.append(city_1);
    }
    if (ui->city_file_2->text() != ""){
        command.append(city_2);
    }
    if (ui->city_file_3->text() != ""){
        command.append(city_3);
    }
    if (ui->city_file_4->text() != ""){
        command.append(city_4);
    }
    if (ui->city_file_5->text() != ""){
        command.append(city_5);
    }
    if (ui->cart_b_file_1->text() != ""){
        command.append("-b");
        command.append(country_1);
    }
    if (ui->cart_b_file_2->text() != ""){
        command.append(country_2);
    }
    if (ui->cart_b_file_3->text() != ""){
        command.append(country_3);
    }
    if (ui->cart_b_file_4->text() != ""){
        command.append(country_4);
    }
    if (ui->cart_b_file_5->text() != ""){
        command.append(country_5);
    }
    if (ui->user_file_check->isChecked() == true){
        command.append("-udt");
        command.append(udt);
    }
    if (ui->p_mode->isChecked() == true){
        command.append("-p");
        command.append(p);
    }
    if (ui->e_mode->isChecked() == true){
        command.append("-e");
        command.append(e);
    }
    if (ui->h_mode->isChecked() == true){
        command.append("-h");
        command.append(h);
    }
    if (ui->H_mode->isChecked() == true){
        command.append("-H");
        command.append(H);
    }
    if (ui->l_mode->isChecked() == true){
        command.append("-l");
        command.append(l);
    }
    if (ui->frequency_mode->isChecked() == true){
        if (frequency.toFloat() >= 20 && frequency.toFloat() <= 20000){
        command.append("-f");
        command.append(frequency);
    } else {
            counter++;
            QMessageBox::critical(this,tr("Error"),tr("Invalid frequency value"));
        }
    }
    if (ui->erp_mode->isChecked() == true){
        command.append("-erp");
        command.append(erp);
    }
    if (ui->fz_mode->isChecked() == true){
        command.append("-fz");
        command.append(fz);
    }
    if (ui->gc_mode->isChecked() == true){
        command.append("-gc");
        command.append(gc);
    }
    if (ui->db_mode->isChecked() == true){
        command.append("-db");
        command.append(db);
    }
    if (ui->c_mode->isChecked() == true){
        command.append("-c");
        command.append(c);
    }
    if (ui->L_mode->isChecked() == true){
        command.append("-L");
        command.append(L);
    }
    if (ui->R_mode->isChecked() == true){
        command.append("-R");
        command.append(R);
    }
    if (ui->o_mode->isChecked() == true){
        command.append("-o");
        command.append(o);
    }
    if (ui->ano_file->isChecked() == true){
        command.append("-ano");
        command.append(ano);
    }
    if (ui->ani_file->isChecked() == true){
        command.append("-ani");
        command.append(ani);
    }
    if (ui->m_mode->isChecked() == true){
        command.append("-m");
        command.append(m);
    }
    if (ui->metric->isChecked() == true){
        command.append("-metric");
    }
    if (ui->save_log->isChecked() == true){
        command.append("-log");
        command.append(log_file);
    }
    if (ui->save_temp_files->isChecked() == true){
        command.append("-gpsav");
    }
    if (ui->n_mode->isChecked() == true){
        command.append("-n");
    }
    if (ui->N_mode->isChecked() == true){
        command.append("-N");
    }
    if (ui->nf->isChecked() == true){
        command.append("-nf");
    }
    if (ui->ngs_mode->isChecked() == true){
        command.append("-ngs");
    }
    if (ui->dbm_mode->isChecked() == true){
        command.append("-dbm");
    }
    if (ui->geo_mode->isChecked() == true){
        command.append("-geo");
    }
    if (ui->kml->isChecked() == true){
        command.append("-kml");
    }
    if (ui->oldtim->isChecked() == true){
        command.append("-oldtim");
    }
    if (counter == 0) {
    QProcess *process = new QProcess;

    process->start("splat", command);
    QProgressDialog progress ;
    progress.setRange(0,0);
    progress.setCancelButtonText(tr("Cancel"));
    progress.setLabelText(tr("Please wait"));
    progress.setWindowTitle(tr("In the process of counting data"));
    connect(process,SIGNAL(finished(int)),&progress,SLOT(close()));
    progress.exec();
    ui->terminal_out->appendPlainText(process->readAllStandardOutput());
    QString error = process->readAllStandardError();
    if (error != ""){
        QMessageBox::critical(this,tr("Error"),error);
    }
    delete process;
    refresh();
    QString pic;
    if (command.contains("-o") or command.contains("-L") or command.contains("-c") or command.contains("-R") or command.contains("-p")
            or command.contains("-e") or command.contains("-h") or command.contains("-H") or command.contains("-l")){
    if (command.contains("-o") or command.contains("-L") or command.contains("-c") or command.contains("-R")){
        pic = o;
    } else if (command.contains(p)){
        pic = p;
    } else if (command.contains(e)){
        pic = e;
    } else if (command.contains(h)){
        pic = h;
    } else if (command.contains(H)){
        pic = H;
    } else if (command.contains(l)){
        pic = l;
    }

    QFileInfo check_file(pic.trimmed().section(set->get_dir_grph(),1,1));
    if (error ==""){
    if (check_file.exists() and check_file.isFile()){
        if (pic != o && ui->res_p->currentText() == ".ps" ){
            scene->clear();
            QPixmap pix(":/icons/Error_preview.png");
            int w = pix.width();
            int h = pix.height();
            ui->image->fitInView(0,0,w,h);
            scene->setSceneRect(0,0,w,h);
            scene->addPixmap(QPixmap(pix));
            ui->image->setScene(scene);
            int grp_index;
            ui->graph_file->addItem(pic.section(set->get_dir_grph(),1,1));
            refresh();
            grp_index = ui->graph_file->findText(pic.section(set->get_dir_grph(),1,1));
            ui->graph_file->setCurrentIndex(grp_index);
        } else {
        scene->clear();
        QPixmap pix(pic.trimmed());
        int w = pix.width();
        int h = pix.height();
        ui->image->fitInView(0,0,w,h);
        scene->setSceneRect(0,0,w,h);
        scene->addPixmap(QPixmap(pix));
        ui->image->setScene(scene);
        int grp_index;
        ui->graph_file->addItem(pic.section(set->get_dir_grph(),1,1));
        refresh();
        grp_index = ui->graph_file->findText(pic.section(set->get_dir_grph(),1,1));
        ui->graph_file->setCurrentIndex(grp_index);
        }
    } else {
        QMessageBox::critical(this,tr("Error"),tr("File not found"));
    }
    }
    }
    }
}


void MainWindow::on_refresh_trrc_clicked()
{
    refresh();
}

void MainWindow::refresh()
{
    QDir path(set->get_dir_path());
    QStringList files = path.entryList(QStringList() << "*.qth", QDir:: Files);// Check file if any one file not set on combobox
    for (int i = 0; i < files.length(); i++){
        if (ui->transmitter_1->findText(files[i]) == -1){
            ui->transmitter_1->addItem(files[i]);
            ui->receiver->addItem(files[i]);
            ui->transmitter_2->addItem(files[i]);
            ui->transmitter_3->addItem(files[i]);
            ui->transmitter_4->addItem(files[i]);
        }
    }
    for (int i = 0; i < ui->transmitter_1->count(); i++ ){ // Check file if any one file is not exist in such dir
        if (files.contains(ui->transmitter_1->itemText(i)) == false && ui->transmitter_1->itemText(i)!= "None"){
            ui->transmitter_1->removeItem(i);
            ui->receiver->removeItem(i);
            ui->transmitter_2->removeItem(i);
            ui->transmitter_3->removeItem(i);
            ui->transmitter_4->removeItem(i);
        }
    }
    QDir graph_path(set->get_dir_grph());
    QStringList files_gif = graph_path.entryList(QStringList() << "*.gif", QDir:: Files);
    QStringList files_ps = graph_path.entryList(QStringList() << "*.ps", QDir:: Files);
    QStringList files_ppm = graph_path.entryList(QStringList() << "*.ppm", QDir:: Files);
    QStringList files_png = graph_path.entryList(QStringList() << "*.png", QDir:: Files);
    for (int i = 0; i < files_png.length(); i++){
        if (ui->graph_file->findText(files_png[i]) == -1){
            ui->graph_file->addItem(files_png[i]);
        }
    }
    for (int i = 0; i < files_ppm.length(); i++){
        if (ui->graph_file->findText(files_ppm[i]) == -1){
            ui->graph_file->addItem(files_ppm[i]);
        }
    }
    for (int i = 0; i < files_ps.length(); i++){
        if (ui->graph_file->findText(files_ps[i]) == -1){
            ui->graph_file->addItem(files_ps[i]);
        }
    }
    for (int i = 0; i < files_gif.length(); i++){
        if (ui->graph_file->findText(files_gif[i]) == -1){
            ui->graph_file->addItem(files_gif[i]);
        }
    }
    for (int i = 0; i < ui->graph_file->count(); i++ ){ // Check file if any one file is not exist in such dir
        if (files_png.contains(ui->graph_file->itemText(i)) == false && files_ps.contains(ui->graph_file->itemText(i)) == false
                && files_ppm.contains(ui->graph_file->itemText(i)) == false && files_gif.contains(ui->graph_file->itemText(i)) == false
                && ui->graph_file->itemText(i)!= "None"){
            ui->graph_file->removeItem(i);
        }
    }

   QDir txt_path(set->get_dir_path());
   QStringList files_txt = txt_path.entryList(QStringList() << "*.txt", QDir::Files);
   for (int i = 0; i < files_txt.length(); i++){
       if (ui->txt_files->findText(files_txt[i]) == -1){
           ui->txt_files->addItem(files_txt[i]);
       }
   }
   for (int i = 0; i < ui->txt_files->count(); i++ ){ // Check file if any one file is not exist in such dir
       if (files_txt.contains(ui->txt_files->itemText(i)) == false && ui->txt_files->itemText(i)!= "None"){
           ui->txt_files->removeItem(i);
       }
   }
   QDir dat_path(set->get_dir_path());
   QStringList files_dat = dat_path.entryList(QStringList() << "*.dat",QDir :: Files);
   for (int i = 0; i < files_dat.length(); i++){
       if (ui->ani_file_name->findText(files_dat[i]) == -1){
           ui->ani_file_name->addItem(files_dat[i]);
       }
   }
   for (int i = 0; i < ui->ani_file_name->count(); i++ ){ // Check file if any one file is not exist in such dir
       if (files_dat.contains(ui->ani_file_name->itemText(i)) == false && ui->ani_file_name->itemText(i)!= "None"){
           ui->ani_file_name->removeItem(i);
       }
   }
}








void MainWindow::on_graph_file_activated(int index)
{
    scene->clear();
    QDir path(set->get_dir_grph());
    QStringList file_ps = path.entryList(QStringList() <<"*.ps", QDir:: Files);
    refresh();
    if (ui->graph_file->currentText()=="None"){
        QPixmap pix(":/icons/black.png");
        int w = pix.width();
        int h = pix.height();
        ui->image->fitInView(0,0,w,h);
        scene->setSceneRect(0,0,w,h);
        scene->addPixmap(QPixmap(pix));
        ui->image->setScene(scene);
    } else if (file_ps.contains(ui->graph_file->currentText())){
        QPixmap pix(":/img/Error_preview.png");
        int w = pix.width();
        int h = pix.height();
        ui->image->fitInView(0,0,w,h);
        scene->setSceneRect(0,0,w,h);
        scene->addPixmap(QPixmap(pix));
        ui->image->setScene(scene);
    } else {
    QPixmap pix(set->get_dir_grph()+ui->graph_file->currentText());
    int w = pix.width();
    int h = pix.height();
    ui->image->fitInView(0,0,w,h);
    scene->setSceneRect(0,0,w,h);
    scene->addPixmap(QPixmap(pix));
    ui->image->setScene(scene);
    }
}






void MainWindow::on_delete_graph_file_clicked()
{

    if (ui->graph_file->currentText() != "None"){
    QString file_name = set->get_dir_grph() + ui->graph_file->currentText();
    QProcess *process = new QProcess;
    process->start("rm",QStringList()<< file_name);
    refresh();
    int index = ui->graph_file->findText("None");
    ui->graph_file->setCurrentIndex(index);
    QString error = process->readAllStandardError();
    if (error != ""){
        QMessageBox::critical(this,tr("Error"),error);
    }
    scene->clear();
    QPixmap pix(":/img/black.png");
    int w = pix.width();
    int h = pix.height();
    ui->image->fitInView(0,0,w,h);
    scene->setSceneRect(0,0,w,h);
    scene->addPixmap(QPixmap(pix));
    ui->image->setScene(scene);
    process->close();
    delete process;
    } else {
        QMessageBox::warning(this,tr("Warning"),tr("Please select a file"));
    }
}


void MainWindow::on_actionSettings_triggered()
{
    set->show();
}


void MainWindow::on_action_dat_triggered()
{
    dat->show();
}


void MainWindow::on_action_dat_2_triggered()
{

    QString file_name = QFileDialog::getOpenFileName(this,
                                                     tr("Open file"),"");
    dat->show();
    dat->openFile(file_name);
}


void MainWindow::on_Clear_terminal_clicked()
{
    ui->terminal_out->clear();
}


void MainWindow::on_open_txt_file_clicked()
{
    if (ui->txt_files->currentText() != "None") {
    QProcess *process = new QProcess;
    QString file_name = set->get_dir_path() + ui->txt_files->currentText();
    QFile fileIn(file_name);
    QString str;
    if (fileIn.open(QIODevice::ReadOnly)){
        str = fileIn.readAll();
        ui->terminal_out->appendPlainText(str);
    }
    fileIn.close();
    delete process;
    }
}


void MainWindow::on_transmitter_number_currentIndexChanged(int index)
{
    if (index == 0){
        int index2 = ui->transmitter_2->findText("None");
        int index3 = ui->transmitter_3->findText("None");
        int index4 = ui->transmitter_4->findText("None");
        ui->transmitter_2->hide();
        ui->transmitter_2->setCurrentIndex(index2);
        ui->transmitter_3->hide();
        ui->transmitter_3->setCurrentIndex(index3);
        ui->transmitter_4->hide();
        ui->transmitter_4->setCurrentIndex(index4);
        ui->tr2_l->hide();
        ui->tr3_l->hide();
        ui->tr4_l->hide();
    } else if (index == 1){
        int index3 = ui->transmitter_3->findText("None");
        int index4 = ui->transmitter_4->findText("None");
        ui->transmitter_2->show();
        ui->transmitter_3->setCurrentIndex(index3);
        ui->transmitter_4->hide();
        ui->transmitter_4->setCurrentIndex(index4);
        ui->tr2_l->show();
        ui->tr3_l->hide();
        ui->tr4_l->hide();
    } else if (index == 2){
        int index4 = ui->transmitter_4->findText("None");
        ui->transmitter_2->show();
        ui->transmitter_3->show();
        ui->transmitter_4->hide();
        ui->transmitter_4->setCurrentIndex(index4);
        ui->tr2_l->show();
        ui->tr3_l->show();
        ui->tr4_l->hide();
    } else if (index == 3){
        ui->transmitter_2->show();
        ui->transmitter_3->show();
        ui->transmitter_4->show();
        ui->tr2_l->show();
        ui->tr3_l->show();
        ui->tr4_l->show();
    }
}


void MainWindow::on_receiver_number_currentIndexChanged(int index)
{
    if (index == 0){
        ui->receiver->hide();
        ui->rcv_l->hide();
    } else {
        ui->receiver->show();
        ui->rcv_l->show();
    }
}





void MainWindow::on_city_file_number_currentIndexChanged(int index)
{
    if (index == 0 ){
        ui->ch_city_file_1->hide();
        ui->ch_city_file_2->hide();
        ui->ch_city_file_3->hide();
        ui->ch_city_file_4->hide();
        ui->ch_city_file_5->hide();
        ui->city_file_1->hide();
        ui->city_file_2->hide();
        ui->city_file_3->hide();
        ui->city_file_4->hide();
        ui->city_file_5->hide();
        ui->city_file_1->clear();
        ui->city_file_2->clear();
        ui->city_file_3->clear();
        ui->city_file_4->clear();
        ui->city_file_5->clear();
        ui->city1_l->hide();
        ui->city2_l->hide();
        ui->city3_l->hide();
        ui->city4_l->hide();
        ui->city5_l->hide();
    } else if (index == 1) {
        ui->ch_city_file_1->show();
        ui->ch_city_file_2->hide();
        ui->ch_city_file_3->hide();
        ui->ch_city_file_4->hide();
        ui->ch_city_file_5->hide();
        ui->city_file_1->show();
        ui->city_file_2->hide();
        ui->city_file_3->hide();
        ui->city_file_4->hide();
        ui->city_file_5->hide();
        ui->city_file_2->clear();
        ui->city_file_3->clear();
        ui->city_file_4->clear();
        ui->city_file_5->clear();
        ui->city1_l->show();
        ui->city2_l->hide();
        ui->city3_l->hide();
        ui->city4_l->hide();
        ui->city5_l->hide();
    } else if (index == 2) {
        ui->ch_city_file_1->show();
        ui->ch_city_file_2->show();
        ui->ch_city_file_3->hide();
        ui->ch_city_file_4->hide();
        ui->ch_city_file_5->hide();
        ui->city_file_1->show();
        ui->city_file_2->show();
        ui->city_file_3->hide();
        ui->city_file_4->hide();
        ui->city_file_5->hide();
        ui->city_file_3->clear();
        ui->city_file_4->clear();
        ui->city_file_5->clear();
        ui->city1_l->show();
        ui->city2_l->show();
        ui->city3_l->hide();
        ui->city4_l->hide();
        ui->city5_l->hide();
    } else if (index == 3) {
        ui->ch_city_file_1->show();
        ui->ch_city_file_2->show();
        ui->ch_city_file_3->show();
        ui->ch_city_file_4->hide();
        ui->ch_city_file_5->hide();
        ui->city_file_1->show();
        ui->city_file_2->show();
        ui->city_file_3->show();
        ui->city_file_4->hide();
        ui->city_file_5->hide();
        ui->city_file_4->clear();
        ui->city_file_5->clear();
        ui->city1_l->show();
        ui->city2_l->show();
        ui->city3_l->show();
        ui->city4_l->hide();
        ui->city5_l->hide();
    } else if (index == 4) {
        ui->ch_city_file_1->show();
        ui->ch_city_file_2->show();
        ui->ch_city_file_3->show();
        ui->ch_city_file_4->show();
        ui->ch_city_file_5->hide();
        ui->city_file_1->show();
        ui->city_file_2->show();
        ui->city_file_3->show();
        ui->city_file_4->show();
        ui->city_file_5->hide();
        ui->city_file_5->clear();
        ui->city1_l->show();
        ui->city2_l->show();
        ui->city3_l->show();
        ui->city4_l->show();
        ui->city5_l->hide();
    } else if (index == 5) {
        ui->ch_city_file_1->show();
        ui->ch_city_file_2->show();
        ui->ch_city_file_3->show();
        ui->ch_city_file_4->show();
        ui->ch_city_file_5->show();
        ui->city_file_1->show();
        ui->city_file_2->show();
        ui->city_file_3->show();
        ui->city_file_4->show();
        ui->city_file_5->show();
        ui->city1_l->show();
        ui->city2_l->show();
        ui->city3_l->show();
        ui->city4_l->show();
        ui->city5_l->show();
    }
}


void MainWindow::on_cart_bound_file_number_currentIndexChanged(int index)
{
    if (index == 0 ){
        ui->ch_cart_b_file_1->hide();
        ui->ch_cart_b_file_2->hide();
        ui->ch_cart_b_file_3->hide();
        ui->ch_cart_b_file_4->hide();
        ui->ch_cart_b_file_5->hide();
        ui->cart_b_file_1->hide();
        ui->cart_b_file_2->hide();
        ui->cart_b_file_3->hide();
        ui->cart_b_file_4->hide();
        ui->cart_b_file_5->hide();
        ui->cart_b_file_1->clear();
        ui->cart_b_file_2->clear();
        ui->cart_b_file_3->clear();
        ui->cart_b_file_4->clear();
        ui->cart_b_file_5->clear();
        ui->cart_b_l1->hide();
        ui->cart_b_l2->hide();
        ui->cart_b_l3->hide();
        ui->cart_b_l4->hide();
        ui->cart_b_l5->hide();
    } else if (index == 1) {
        ui->ch_cart_b_file_1->show();
        ui->ch_cart_b_file_2->hide();
        ui->ch_cart_b_file_3->hide();
        ui->ch_cart_b_file_4->hide();
        ui->ch_cart_b_file_5->hide();
        ui->cart_b_file_1->show();
        ui->cart_b_file_2->hide();
        ui->cart_b_file_3->hide();
        ui->cart_b_file_4->hide();
        ui->cart_b_file_5->hide();
        ui->cart_b_file_2->clear();
        ui->cart_b_file_3->clear();
        ui->cart_b_file_4->clear();
        ui->cart_b_file_5->clear();
        ui->cart_b_l1->show();
        ui->cart_b_l2->hide();
        ui->cart_b_l3->hide();
        ui->cart_b_l4->hide();
        ui->cart_b_l5->hide();
    } else if (index == 2) {
        ui->ch_cart_b_file_1->show();
        ui->ch_cart_b_file_2->show();
        ui->ch_cart_b_file_3->hide();
        ui->ch_cart_b_file_4->hide();
        ui->ch_cart_b_file_5->hide();
        ui->cart_b_file_1->show();
        ui->cart_b_file_2->show();
        ui->cart_b_file_3->hide();
        ui->cart_b_file_4->hide();
        ui->cart_b_file_5->hide();
        ui->cart_b_file_3->clear();
        ui->cart_b_file_4->clear();
        ui->cart_b_file_5->clear();
        ui->cart_b_l1->show();
        ui->cart_b_l2->show();
        ui->cart_b_l3->hide();
        ui->cart_b_l4->hide();
        ui->cart_b_l5->hide();
    } else if (index == 3) {
        ui->ch_cart_b_file_1->show();
        ui->ch_cart_b_file_2->show();
        ui->ch_cart_b_file_3->show();
        ui->ch_cart_b_file_4->hide();
        ui->ch_cart_b_file_5->hide();
        ui->cart_b_file_1->show();
        ui->cart_b_file_2->show();
        ui->cart_b_file_3->show();
        ui->cart_b_file_4->hide();
        ui->cart_b_file_5->hide();
        ui->cart_b_file_4->clear();
        ui->cart_b_file_5->clear();
        ui->cart_b_l1->show();
        ui->cart_b_l2->show();
        ui->cart_b_l3->show();
        ui->cart_b_l4->hide();
        ui->cart_b_l5->hide();
    } else if (index == 4) {
        ui->ch_cart_b_file_1->show();
        ui->ch_cart_b_file_2->show();
        ui->ch_cart_b_file_3->show();
        ui->ch_cart_b_file_4->show();
        ui->ch_cart_b_file_5->hide();
        ui->cart_b_file_1->show();
        ui->cart_b_file_2->show();
        ui->cart_b_file_3->show();
        ui->cart_b_file_4->show();
        ui->cart_b_file_5->hide();
        ui->cart_b_file_5->clear();
        ui->cart_b_l1->show();
        ui->cart_b_l2->show();
        ui->cart_b_l3->show();
        ui->cart_b_l4->show();
        ui->cart_b_l5->hide();
    } else if (index == 5) {
        ui->ch_cart_b_file_1->show();
        ui->ch_cart_b_file_2->show();
        ui->ch_cart_b_file_3->show();
        ui->ch_cart_b_file_4->show();
        ui->ch_cart_b_file_5->show();
        ui->cart_b_file_1->show();
        ui->cart_b_file_2->show();
        ui->cart_b_file_3->show();
        ui->cart_b_file_4->show();
        ui->cart_b_file_5->show();
        ui->cart_b_l1->show();
        ui->cart_b_l2->show();
        ui->cart_b_l3->show();
        ui->cart_b_l4->show();
        ui->cart_b_l5->show();
    }
}





void MainWindow::on_open_pic_clicked()
{   if (ui->graph_file->currentText() != "None"){
    QProcess *process = new QProcess;
    process->start("xdg-open", QStringList()<<set->get_dir_grph() + ui->graph_file->currentText());
    if (!process->waitForStarted() || !process->waitForFinished()) {
        return;
    }
    ui->terminal_out->appendPlainText(process->readAllStandardError());
    delete process;
    refresh();
    } else {
        QMessageBox::warning(this, tr("Warning"),tr("Select file to open"));
        refresh();
    }
}


void MainWindow::on_actionuser_file_triggered()
{
    udt->show();
}


void MainWindow::on_actionuser_file_2_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this,
                                                     tr("Open file"),"");
    udt->show();
    udt->openFile(file_name);
}




void MainWindow::on_p_mode_stateChanged(int arg1)
{
    if (arg1 == 2){
        ui->graphic_file_p->setText("terrain_profile");
        ui->graphic_file_p->setEnabled(true);
        ui->res_p->setEnabled(true);
    } else {
        ui->graphic_file_p->setEnabled(false);
        ui->res_p->setEnabled(false);
        ui->graphic_file_p->clear();
    }
}


void MainWindow::on_e_mode_stateChanged(int arg1)
{
    if (arg1 == 2){
        ui->graphic_file_e->setEnabled(true);
        ui->res_e->setEnabled(true);
        ui->graphic_file_e->setText("elevation_profile");
    } else {
        ui->graphic_file_e->setEnabled(false);
        ui->res_e->setEnabled(false);
        ui->graphic_file_e->clear();
    }
}


void MainWindow::on_h_mode_stateChanged(int arg1)
{
    if (arg1 == 2){
        ui->graphic_file_h->setEnabled(true);
        ui->res_h->setEnabled(true);
        ui->graphic_file_h->setText("height_profile");
    } else {
        ui->graphic_file_h->setEnabled(false);
        ui->res_h->setEnabled(false);
        ui->graphic_file_h->clear();
    }
}


void MainWindow::on_H_mode_stateChanged(int arg1)
{
    if (arg1 == 2){
        ui->graphic_file_H->setEnabled(true);
        ui->res_H->setEnabled(true);
        ui->graphic_file_H->setText("normalized_height_profile");
    } else {
        ui->graphic_file_H->setEnabled(false);
        ui->res_H->setEnabled(false);
        ui->graphic_file_H->clear();
    }
}


void MainWindow::on_l_mode_stateChanged(int arg1)
{
    if (arg1 == 2){
        ui->graphic_file_l->setEnabled(true);
        ui->res_l->setEnabled(true);
        ui->graphic_file_l->setText("path_loss_profile");
    } else {
        ui->graphic_file_l->setEnabled(false);
        ui->res_l->setEnabled(false);
        ui->graphic_file_l->clear();
    }
}


void MainWindow::on_c_mode_stateChanged(int arg1)
{
    if (arg1 == 2){
        ui->c_out->setEnabled(true);
    } else {
        ui->c_out->setEnabled(false);
        ui->c_out->clear();
    }
}


void MainWindow::on_L_mode_stateChanged(int arg1)
{
    if (arg1 == 2){
        ui->L_out->setEnabled(true);
    } else {
        ui->L_out->setEnabled(false);
        ui->L_out->clear();
    }
}


void MainWindow::on_o_mode_stateChanged(int arg1)
{
    if (arg1 == 2){
        ui->map_name->setEnabled(true);
        ui->map_res->setEnabled(true);
        ui->map_name->setText("topographic_map");
    } else {
        ui->map_name->setEnabled(false);
        ui->map_res->setEnabled(false);
        ui->map_name->clear();
    }
}


void MainWindow::on_R_mode_stateChanged(int arg1)
{
    if (arg1 == 2){
        ui->R_out->setEnabled(true);
    } else {
        ui->R_out->setEnabled(false);
        ui->R_out->clear();
    }
}


void MainWindow::on_ano_file_stateChanged(int arg1)
{
    if (arg1 == 2){
        ui->ano_out->setEnabled(true);
        ui->ano_res->setEnabled(true);
        ui->ano_out->setText("pathloss");
    } else {
        ui->ano_res->setEnabled(false);
        ui->ano_out->setEnabled(false);
        ui->ano_out->clear();
    }
}


void MainWindow::on_ani_file_stateChanged(int arg1)
{
    if (arg1 == 2){
        ui->ani_file_name->setEnabled(true);
    } else {
        ui->ani_file_name->setEnabled(false);
    }
}


void MainWindow::on_m_mode_stateChanged(int arg1)
{
    if (arg1 == 2){
        ui->m_out->setEnabled(true);
    } else {
        ui->m_out->setEnabled(false);
        ui->m_out->clear();
    }
}


void MainWindow::on_frequency_mode_stateChanged(int arg1)
{
    if (arg1 == 2){
        ui->frequency->setEnabled(true);
    } else {
        ui->frequency->setEnabled(false);
        ui->frequency->clear();
    }
}


void MainWindow::on_erp_mode_stateChanged(int arg1)
{
    if (arg1 == 2){
        ui->erp->setEnabled(true);
    } else {
        ui->erp->setEnabled(false);
        ui->erp->clear();
    }
}


void MainWindow::on_db_mode_stateChanged(int arg1)
{
    if (arg1 == 2){
        ui->db->setEnabled(true);
    } else {
        ui->db->setEnabled(false);
        ui->db->clear();
    }
}


void MainWindow::on_fz_mode_stateChanged(int arg1)
{
    if (arg1 == 2){
        ui->fz->setEnabled(true);
    } else {
        ui->fz->setEnabled(false);
        ui->fz->clear();
    }
}


void MainWindow::on_gc_mode_stateChanged(int arg1)
{
    if (arg1 == 2){
        ui->gc->setEnabled(true);
    } else {
        ui->gc->setEnabled(false);
        ui->gc->clear();
    }
}
void MainWindow::changeEvent(QEvent *event){


    if (event->type() == QEvent::LanguageChange){
        ui->retranslateUi(this);
        set->retranslate();
        file->retranslate();
        udt->retranslate();
        file_lrp->retranslate();
        dat->retranslate();
        about_info->retranslate();
    }
    else {
        QWidget::changeEvent(event);
    }
}

void MainWindow::on_save_log_stateChanged(int arg1)
{
    if (arg1 == 2){
        ui->save_log_text->setEnabled(true);
        ui->save_log_text->setReadOnly(false);
        ui->log_res->setEnabled(true);
        ui->save_log_text->setText("log_file");
    } else {
        ui->log_res->setEnabled(false);
        ui->save_log_text->setEnabled(false);
        ui->save_log_text->clear();
    }
}


void MainWindow::on_res_p_currentIndexChanged(int index)
{
        ui->res_p->setCurrentIndex(index);
        ui->res_e->setCurrentIndex(index);
        ui->res_h->setCurrentIndex(index);
        ui->res_H->setCurrentIndex(index);
        ui->res_l->setCurrentIndex(index);
}


void MainWindow::on_res_e_currentIndexChanged(int index)
{
    ui->res_p->setCurrentIndex(index);
    ui->res_e->setCurrentIndex(index);
    ui->res_h->setCurrentIndex(index);
    ui->res_H->setCurrentIndex(index);
    ui->res_l->setCurrentIndex(index);
}


void MainWindow::on_res_h_currentIndexChanged(int index)
{
    ui->res_p->setCurrentIndex(index);
    ui->res_e->setCurrentIndex(index);
    ui->res_h->setCurrentIndex(index);
    ui->res_H->setCurrentIndex(index);
    ui->res_l->setCurrentIndex(index);
}


void MainWindow::on_res_H_currentIndexChanged(int index)
{
    ui->res_p->setCurrentIndex(index);
    ui->res_e->setCurrentIndex(index);
    ui->res_h->setCurrentIndex(index);
    ui->res_H->setCurrentIndex(index);
    ui->res_l->setCurrentIndex(index);
}


void MainWindow::on_res_l_currentIndexChanged(int index)
{
    ui->res_p->setCurrentIndex(index);
    ui->res_e->setCurrentIndex(index);
    ui->res_h->setCurrentIndex(index);
    ui->res_H->setCurrentIndex(index);
    ui->res_l->setCurrentIndex(index);
}





void MainWindow::on_actionAbout_2_triggered()
{
    about_info->show();
}
void  MainWindow::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        rightMousePressed = true;
        _panStartX = event->pos().x();
        _panStartY = event->pos().y();
        QGuiApplication::setOverrideCursor(Qt::ClosedHandCursor);
        event->accept();
        return;
    }
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton)
    {
        rightMousePressed = false;
        QGuiApplication::setOverrideCursor(Qt::ArrowCursor);
        event->accept();
        return;
    }
    event->ignore();
}
void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    if (rightMousePressed)
    {
        ui->image->horizontalScrollBar()->setValue(ui->image->horizontalScrollBar()->value() - (event->pos().x() - _panStartX));
        ui->image->verticalScrollBar()->setValue(ui->image->verticalScrollBar()->value() - (event->pos().y() - _panStartY));
        _panStartX = event->pos().x();
        _panStartY = event->pos().y();
        event->accept();
        return;
    }
    event->ignore();
}





void MainWindow::on_ch_user_file_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,
                                             tr("Open file"));
    ui->udt_file->setText(file_name);
}


void MainWindow::on_ch_city_file_1_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,
                                             tr("Open file"));
    ui->city_file_1->setText(file_name);
}


void MainWindow::on_ch_city_file_2_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,
                                             tr("Open file"));
    ui->city_file_2->setText(file_name);
}


void MainWindow::on_ch_city_file_3_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,
                                             tr("Open file"));
    ui->city_file_3->setText(file_name);
}


void MainWindow::on_ch_city_file_4_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,
                                             tr("Open file"));
    ui->city_file_4->setText(file_name);
}


void MainWindow::on_ch_city_file_5_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,
                                             tr("Open file"));
    ui->city_file_5->setText(file_name);
}


void MainWindow::on_ch_cart_b_file_1_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,
                                             tr("Open file"));
    ui->cart_b_file_1->setText(file_name);
}


void MainWindow::on_ch_cart_b_file_2_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,
                                             tr("Open file"));
    ui->cart_b_file_2->setText(file_name);
}


void MainWindow::on_ch_cart_b_file_3_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,
                                             tr("Open file"));
    ui->cart_b_file_3->setText(file_name);
}


void MainWindow::on_ch_cart_b_file_4_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,
                                             tr("Open file"));
    ui->cart_b_file_4->setText(file_name);
}


void MainWindow::on_ch_cart_b_file_5_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,
                                             tr("Open file"));
    ui->cart_b_file_5->setText(file_name);
}




void MainWindow::on_user_file_check_stateChanged(int arg1)
{
    if (arg1 == 2){
        ui->ch_user_file->setEnabled(true);
        ui->udt_file->setEnabled(true);
    } else {
        ui->ch_user_file->setEnabled(false);
        ui->udt_file->setEnabled(false);
        ui->udt_file->clear();
    }
}

