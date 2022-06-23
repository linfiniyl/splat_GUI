/*	
	File                 : mainwindow.h
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


#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "qth_file.h"
#include "lrp_file.h"
#include "settings.h"
#include "dat_file.h"
#include "udt_file.h"
#include <QMainWindow>
#include <QTranslator>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QNetworkAccessManager>
#include <QGraphicsView>
#include <about.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void refresh();
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionqth_file_triggered();

    void on_actionqth_triggered();

    void on_action_lrp_triggered();

    void on_action_lrp_2_triggered();

    void on_Create_clicked();

    void on_refresh_trrc_clicked();

    void on_graph_file_activated(int index);


    void on_delete_graph_file_clicked();

    void on_actionSettings_triggered();

    void on_action_dat_triggered();

    void on_action_dat_2_triggered();

    void on_Clear_terminal_clicked();

    void on_open_txt_file_clicked();

    void on_transmitter_number_currentIndexChanged(int index);

    void on_receiver_number_currentIndexChanged(int index);

    void on_city_file_number_currentIndexChanged(int index);

    void on_cart_bound_file_number_currentIndexChanged(int index);

    void on_open_pic_clicked();

    void on_actionuser_file_triggered();

    void on_actionuser_file_2_triggered();

    void on_p_mode_stateChanged(int arg1);

    void on_e_mode_stateChanged(int arg1);

    void on_h_mode_stateChanged(int arg1);

    void on_H_mode_stateChanged(int arg1);

    void on_l_mode_stateChanged(int arg1);

    void on_c_mode_stateChanged(int arg1);

    void on_L_mode_stateChanged(int arg1);

    void on_o_mode_stateChanged(int arg1);

    void on_R_mode_stateChanged(int arg1);

    void on_ano_file_stateChanged(int arg1);

    void on_ani_file_stateChanged(int arg1);

    void on_m_mode_stateChanged(int arg1);

    void on_frequency_mode_stateChanged(int arg1);

    void on_erp_mode_stateChanged(int arg1);

    void on_db_mode_stateChanged(int arg1);

    void on_fz_mode_stateChanged(int arg1);

    void on_gc_mode_stateChanged(int arg1);
    void on_save_log_stateChanged(int arg1);

    void on_res_p_currentIndexChanged(int index);

    void on_res_e_currentIndexChanged(int index);

    void on_res_h_currentIndexChanged(int index);

    void on_res_H_currentIndexChanged(int index);

    void on_res_l_currentIndexChanged(int index);


    void on_actionAbout_2_triggered();

    void on_ch_user_file_clicked();

    void on_ch_city_file_1_clicked();

    void on_ch_city_file_2_clicked();

    void on_ch_city_file_3_clicked();

    void on_ch_city_file_4_clicked();

    void on_ch_city_file_5_clicked();

    void on_ch_cart_b_file_1_clicked();

    void on_ch_cart_b_file_2_clicked();

    void on_ch_cart_b_file_3_clicked();

    void on_ch_cart_b_file_4_clicked();

    void on_ch_cart_b_file_5_clicked();


    void on_user_file_check_stateChanged(int arg1);

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent* event) override ;
    void mousePressEvent(QMouseEvent* event) override;
    void changeEvent(QEvent *event) override;
private:
    bool rightMousePressed;
    int _panStartX,_panStartY;
    about *about_info;
    QGraphicsScene *scene;
    udt_file *udt;
    Ui::MainWindow *ui;
    lrp_file *file_lrp;
    qth_file *file;
    Settings *set;
    dat_file *dat;
    //QNetworkAccessManager *network;
};
#endif // MAINWINDOW_H
