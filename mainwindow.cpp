#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QtGui>
#include<QtCore>
#include<qwidget.h>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    timer.setInterval(20);
    connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
    ui->pushButton->setText("Hello");
   
    update_hsv();
    update_rgb();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::tick()
{
    ui->wigbar->update();
}

void MainWindow::on_Slider_r_valueChanged(int value)
{
    ui->wigbar->zmien_r(value);
    update_hsv();
}

void MainWindow::on_Slider_g_valueChanged(int value)
{
    ui->wigbar->zmien_g(value);
    update_hsv();
}

void MainWindow::on_Slider_b_valueChanged(int value)
{
    ui->wigbar->zmien_b(value);
    update_hsv();
}

void MainWindow::on_Slider_h_valueChanged(int value)
{
    ui->wigbar->zmien_h(value);
    update_rgb();
}

void MainWindow::on_Slider_s_valueChanged(int value)
{
    ui->wigbar->zmien_s(value);
    update_rgb();
}

void MainWindow::on_Slider_v_valueChanged(int value)
{
    ui->wigbar->zmien_v(value);
    update_rgb();
}

void MainWindow::update_rgb()
{
    ui->Slider_r->setValue(ui->wigbar->wczytaj_r());
    ui->Slider_g->setValue(ui->wigbar->wczytaj_g());
    ui->Slider_b->setValue(ui->wigbar->wczytaj_b());
}

void MainWindow::update_hsv()
{
    ui->Slider_h->setValue(ui->wigbar->wczytaj_h());
    ui->Slider_s->setValue(ui->wigbar->wczytaj_s());
    ui->Slider_v->setValue(ui->wigbar->wczytaj_v());
}

/*
void MainWindow::on_change_x_valueChanged(int arg1)
{
    ui->wigbar->Move_X(arg1);
}

void MainWindow::on_change_y_valueChanged(int arg1)
{
    ui->wigbar->Move_X(arg1);
}
*/

void MainWindow::on_Rotate_OX_valueChanged(double arg1)
{
     ui->wigbar->rotate_OX(arg1);
}

void MainWindow::on_Rotate_OY_valueChanged(double arg1)
{
     ui->wigbar->rotate_OY(arg1);
}

void MainWindow::on_Rotate_OZ_valueChanged(double arg1)
{
    ui->wigbar->rotate_OZ(arg1);
}

/*
void MainWindow::on_Rotate_valueChanged(double arg1)
{
    ui->wigbar->rotate_OZ(arg1);
}
*/
void MainWindow::on_Pochyl_OX_valueChanged(double arg1)
{
    ui->wigbar->Pochyl_OX(arg1);
}

void MainWindow::on_Pochyl_OY_valueChanged(double arg1)
{
    ui->wigbar->Pochyl_OY(arg1);
}

void MainWindow::on_Skalowanie_OX_valueChanged(double arg1)
{
    ui->wigbar->Skalowanie_OX(arg1);
}

void MainWindow::on_Skalowanie_OY_valueChanged(double arg1)
{
    ui->wigbar->Skalowanie_OY(arg1);
}

void MainWindow::on_Move_X_valueChanged(double arg1)
{
   ui->wigbar->Move_X(arg1);
}

void MainWindow::on_Move_Y_valueChanged(double arg1)
{
    ui->wigbar->Move_Y(arg1);
}

void MainWindow::on_p1_x_valueChanged(double arg1)
{
    //ui->wigbar->zminen_trojkaty_p1_X(arg1);
}

void MainWindow::on_p1_y_valueChanged(double arg1)
{
    //  ui->wigbar->zminen_trojkaty_p1_Y(arg1);
}

void MainWindow::on_p1_z_valueChanged(double arg1)
{
   //   ui->wigbar->zminen_trojkaty_p1_Z(arg1);
}

void MainWindow::on_p2_x_valueChanged(double arg1)
{
      //ui->wigbar->zminen_trojkaty_p2_X(arg1);
}

void MainWindow::on_p2_y_valueChanged(double arg1)
{
    //  ui->wigbar->zminen_trojkaty_p2_Y(arg1);
}

void MainWindow::on_p2_z_valueChanged(double arg1)
{
   //   ui->wigbar->zminen_trojkaty_p2_Z(arg1);
}

void MainWindow::on_p3_x_valueChanged(double arg1)
{
     // ui->wigbar->zminen_trojkaty_p3_X(arg1);
}

void MainWindow::on_p3_y_valueChanged(double arg1)
{
     // ui->wigbar->zminen_trojkaty_p3_Y(arg1);
}

void MainWindow::on_p3_z_valueChanged(double arg1)
{
     // ui->wigbar->zminen_trojkaty_p3_Z(arg1);
}


