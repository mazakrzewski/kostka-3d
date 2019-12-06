#ifndef MOWIDGET_H
#define MOWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QTimer>
#include "types.h"
#include "rotate_class.h"
#include <krawedz.h>
#include "rotate_3d_class.h"

class mowidget : public QWidget
{
    Q_OBJECT
	
public:
    QImage *im;
    explicit mowidget(QWidget *parent = 0);
    void putPixel(int x, int y, int r, int g , int b);
    void zmienKolor(int r, int g, int b);
    void update_sliders(int);
    bool kolor_compare(kolor a,kolor b);
    void flood_fill(punktcik punkty, kolor zamieniany_kolor);
    void bezier(int x, int y, int r, int g, int b);
    kolor takePixel(int x, int y);
    punktcik nowy_punkt(int x, int y);
    kolor nowy_kolor(int r, int g, int b);
    int leng;

protected:
    void paintEvent(QPaintEvent *);
    void Mouse_left(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
	
signals:

public slots:
    void zmien_r(int);
    void zmien_g(int);
    void zmien_b(int);
    void zmien_h(int);
    void zmien_s(int);
    void zmien_v(int);
    int wczytaj_r();
    int wczytaj_g();
    int wczytaj_b();
    int wczytaj_h();
    int wczytaj_s();
    int wczytaj_v();
    void zmien_aktualny_punkt(int aktualny_punkt);
    int wczytaj_lenght_punkt_list();
    int get_x();
    int get_y();
    void Move_X(int x);
    void Move_Y(int y);
    // void delete_punkt();
    void rotate_OX(int stopnie);
    void rotate_OY(int stopnie);
    void rotate_OZ(int stopnie);
    void Pochyl_OX(float wspolczynnik_pochylenia_OX);
    void Pochyl_OY(float wspolczynnik_pochylenia_OY);
    void Skalowanie_OX(float dlugosc);
    void Skalowanie_OY(float wysokosc);
    void execute();
    void zminen_trojkaty_p1_X(float p1_x_value);
    void zminen_trojkaty_p1_Y(float p1_y_value);
    void zminen_trojkaty_p1_Z(float p1_z_value);
    void zminen_trojkaty_p2_X(float p2_x_value);
    void zminen_trojkaty_p2_Y(float p2_y_value);
    void zminen_trojkaty_p2_Z(float p2_z_value);
    void zminen_trojkaty_p3_X(float p3_x_value);
    void zminen_trojkaty_p3_Y(float p3_y_value);
    void zminen_trojkaty_p3_Z(float p3_z_value);

private:
    int r;
    QSharedPointer<QList<QSharedPointer<punkt_struct>>> listaPunkow;

    QSharedPointer<QList<QSharedPointer<krawedz>>> trojkatKr0;
    QSharedPointer<QList<QSharedPointer<krawedz>>> trojkatKr1;
    QSharedPointer<QList<QSharedPointer<krawedz>>> trojkatKr2;
    QSharedPointer<QList<QSharedPointer<krawedz>>> trojkatKr3;
    QSharedPointer<QList<QSharedPointer<krawedz>>> trojkatKr4;
    QSharedPointer<QList<QSharedPointer<krawedz>>> trojkatKr5;
    QSharedPointer<QList<QSharedPointer<krawedz>>> trojkatKr6;
    QSharedPointer<QList<QSharedPointer<krawedz>>> trojkatKr7;
    QSharedPointer<QList<QSharedPointer<krawedz>>> trojkatKr8;
    QSharedPointer<QList<QSharedPointer<krawedz>>> trojkatKr9;
    QSharedPointer<QList<QSharedPointer<krawedz>>> trojkatKr10;
    QSharedPointer<QList<QSharedPointer<krawedz>>> trojkatKr11;

    QSharedPointer<QList<QSharedPointer<punkt_struct>>> trojkat;
    QSharedPointer<QList<QSharedPointer<punkt_struct>>> przeksztalcony;
    QImage *buffor;
    QImage *buffor2;
    int i = 0;
    punktcik punkt;
    int k;
    int ar, ag, ab;
    float hue, sat, val;
    QTimer timer;
    QSharedPointer<QList<QSharedPointer<krawedz>>> test;
    int aktualny_punkt;
    rotate_3d_class rot;
    QSharedPointer<QList<QSharedPointer<punkt_struct>>> punktuTextury;

};


#endif // MOWIDGET_H
