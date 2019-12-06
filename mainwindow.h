#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	
private slots:
    void tick();

    void on_Slider_r_valueChanged(int value);
    void on_Slider_g_valueChanged(int value);
    void on_Slider_b_valueChanged(int value);
    void on_Slider_h_valueChanged(int value);
    void on_Slider_s_valueChanged(int value);
    void on_Slider_v_valueChanged(int value);
    void update_rgb();
    void update_hsv();

    //void on_change_x_valueChanged(int arg1);
    //void on_change_y_valueChanged(int arg1);

    //void on_Rotate_valueChanged(double arg1);

    void on_Pochyl_OX_valueChanged(double arg1);
    void on_Pochyl_OY_valueChanged(double arg1);

    void on_Move_X_valueChanged(double arg1);
    void on_Move_Y_valueChanged(double arg1);

    void on_Skalowanie_OY_valueChanged(double arg1);
    void on_Skalowanie_OX_valueChanged(double arg1);

    void on_Rotate_OX_valueChanged(double arg1);
    void on_Rotate_OY_valueChanged(double arg1);
    void on_Rotate_OZ_valueChanged(double arg1);

    void on_p1_x_valueChanged(double arg1);
    void on_p1_y_valueChanged(double arg1);
    void on_p1_z_valueChanged(double arg1);

    void on_p2_x_valueChanged(double arg1);
    void on_p2_y_valueChanged(double arg1);
    void on_p2_z_valueChanged(double arg1);

    void on_p3_x_valueChanged(double arg1);
    void on_p3_y_valueChanged(double arg1);
    void on_p3_z_valueChanged(double arg1);


private:
    Ui::MainWindow *ui;
    QTimer timer;
};

#endif // MAINWINDOW_H
