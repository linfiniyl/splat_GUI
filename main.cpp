/*	
	File                 : main.cpp
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

	Description : main function
*/

#include "mainwindow.h"

#include <QApplication>
#include <QSettings>
#include <QTranslator>
#include <QGuiApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("SPLAT! GUI");
    QCoreApplication::setOrganizationName("SPBGUT");
    a.setWindowIcon(QIcon(":/icons/icon.png"));
    QFile style(":/light/stylesheet.qss");
    style.open(QFile::ReadOnly);
    QString stylesheet = QLatin1String(style.readAll());
    style.close();
    a.setStyleSheet(stylesheet);


    MainWindow w;
    w.show();
    return a.exec();
}
