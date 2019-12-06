#include "mowidget.h"
#include <QDebug>
#include <stack>
#include "draw.cpp"
#include "files.cpp"
#include "miksuj.cpp"
#include <QPainter>
#include "rotate_3d_class.h"
#include "rotate_class.h"
#include <qlist.h>
#include "krawedz.h"

mowidget::mowidget(QWidget *parent) : QWidget(parent)
{
    buffor  = new QImage (1920, 1200, QImage::Format_RGB32);
    buffor  = open_picture("/home/mz/Pulpit/qt 2/qt/zadanie1/grafika4.jpg");
    buffor2 = open_picture("/home/mz/Pulpit/qt 2/qt/zadanie1/grafika6.jpg");

    rot=rotate_3d_class();
	
    setMouseTracking(true);
	
    ar = 25; ag = 55; ab = 65;

    rgb_to_hsv(ar, ag, ab, hue, sat, val);
    
    listaPunkow    = QSharedPointer<QList<QSharedPointer<punkt_struct>>>(new QList<QSharedPointer<punkt_struct>>);
    this->trojkat  = QSharedPointer<QList<QSharedPointer<punkt_struct>>>(new QList<QSharedPointer<punkt_struct>>);
    przeksztalcony = QSharedPointer<QList<QSharedPointer<punkt_struct>>>(new QList<QSharedPointer<punkt_struct>>);
    punktuTextury  = QSharedPointer<QList<QSharedPointer<punkt_struct>>>(new QList<QSharedPointer<punkt_struct>>);

    QSharedPointer<punkt_struct> p1;
    p1 = QSharedPointer<punkt_struct> (new punkt_struct);

    p1->x = -200;
    p1->y = -200;
    p1->z =  200;

    QSharedPointer<punkt_struct> p2;
    p2 = QSharedPointer<punkt_struct> (new punkt_struct);

    p2->x =  200;
    p2->y = -200;
    p2->z =  200;

    QSharedPointer<punkt_struct> p3;
    p3 = QSharedPointer<punkt_struct> (new punkt_struct);

    p3->x = 200;
    p3->y = 200;
    p3->z = 200;

    QSharedPointer<punkt_struct> p4;
    p4 = QSharedPointer<punkt_struct> (new punkt_struct);

    p4->x = -200;
    p4->y =  200;
    p4->z =  200;

    QSharedPointer<punkt_struct> p5;
    p5 = QSharedPointer<punkt_struct> (new punkt_struct);

    p5->x = -200;
    p5->y = -200;
    p5->z = -200;

    QSharedPointer<punkt_struct> p6;
    p6 = QSharedPointer<punkt_struct> (new punkt_struct);

    p6->x =  200;
    p6->y = -200;
    p6->z = -200;

    QSharedPointer<punkt_struct> p7;
    p7 = QSharedPointer<punkt_struct> (new punkt_struct);

    p7->x =  200;
    p7->y =  200;
    p7->z = -200;

    QSharedPointer<punkt_struct> p8;
    p8 = QSharedPointer<punkt_struct> (new punkt_struct);

    p8->x = -200;
    p8->y =  200;
    p8->z = -200;

    trojkat->push_back(p1);
    trojkat->push_back(p2);
    trojkat->push_back(p3);
    trojkat->push_back(p4);
    trojkat->push_back(p5);
    trojkat->push_back(p6);
    trojkat->push_back(p7);
    trojkat->push_back(p8);
    
    QSharedPointer<punkt_struct> q1;
    QSharedPointer<punkt_struct> q2;
    QSharedPointer<punkt_struct> q3;
    QSharedPointer<punkt_struct> q4;
    QSharedPointer<punkt_struct> q5;
    QSharedPointer<punkt_struct> q6;
    QSharedPointer<punkt_struct> q7;
    QSharedPointer<punkt_struct> q8;

    q1 = QSharedPointer<punkt_struct> (new punkt_struct);
    q2 = QSharedPointer<punkt_struct> (new punkt_struct);
    q3 = QSharedPointer<punkt_struct> (new punkt_struct);
    q4 = QSharedPointer<punkt_struct> (new punkt_struct);
    q5 = QSharedPointer<punkt_struct> (new punkt_struct);
    q6 = QSharedPointer<punkt_struct> (new punkt_struct);
    q7 = QSharedPointer<punkt_struct> (new punkt_struct);
    q8 = QSharedPointer<punkt_struct> (new punkt_struct);

    przeksztalcony->push_back(q1);
    przeksztalcony->push_back(q2);
    przeksztalcony->push_back(q3);
    przeksztalcony->push_back(q4);
    przeksztalcony->push_back(q5);
    przeksztalcony->push_back(q6);
    przeksztalcony->push_back(q7);
    przeksztalcony->push_back(q8);

    rot.execute(trojkat,przeksztalcony);

    QSharedPointer<QList<QSharedPointer<punkt_struct>>> tr0  = QSharedPointer<QList<QSharedPointer<punkt_struct>>> (new QList<QSharedPointer<punkt_struct>>);
    QSharedPointer<QList<QSharedPointer<punkt_struct>>> tr1  = QSharedPointer<QList<QSharedPointer<punkt_struct>>> (new QList<QSharedPointer<punkt_struct>>);
    QSharedPointer<QList<QSharedPointer<punkt_struct>>> tr2  = QSharedPointer<QList<QSharedPointer<punkt_struct>>> (new QList<QSharedPointer<punkt_struct>>);
    QSharedPointer<QList<QSharedPointer<punkt_struct>>> tr3  = QSharedPointer<QList<QSharedPointer<punkt_struct>>> (new QList<QSharedPointer<punkt_struct>>);
    QSharedPointer<QList<QSharedPointer<punkt_struct>>> tr4  = QSharedPointer<QList<QSharedPointer<punkt_struct>>> (new QList<QSharedPointer<punkt_struct>>);
    QSharedPointer<QList<QSharedPointer<punkt_struct>>> tr5  = QSharedPointer<QList<QSharedPointer<punkt_struct>>> (new QList<QSharedPointer<punkt_struct>>);
    QSharedPointer<QList<QSharedPointer<punkt_struct>>> tr6  = QSharedPointer<QList<QSharedPointer<punkt_struct>>> (new QList<QSharedPointer<punkt_struct>>);
    QSharedPointer<QList<QSharedPointer<punkt_struct>>> tr7  = QSharedPointer<QList<QSharedPointer<punkt_struct>>> (new QList<QSharedPointer<punkt_struct>>);
    QSharedPointer<QList<QSharedPointer<punkt_struct>>> tr8  = QSharedPointer<QList<QSharedPointer<punkt_struct>>> (new QList<QSharedPointer<punkt_struct>>);
    QSharedPointer<QList<QSharedPointer<punkt_struct>>> tr9  = QSharedPointer<QList<QSharedPointer<punkt_struct>>> (new QList<QSharedPointer<punkt_struct>>);
    QSharedPointer<QList<QSharedPointer<punkt_struct>>> tr10 = QSharedPointer<QList<QSharedPointer<punkt_struct>>> (new QList<QSharedPointer<punkt_struct>>);
    QSharedPointer<QList<QSharedPointer<punkt_struct>>> tr11 = QSharedPointer<QList<QSharedPointer<punkt_struct>>> (new QList<QSharedPointer<punkt_struct>>);


    tr0->push_back((*przeksztalcony)[0]);
    tr0->push_back((*przeksztalcony)[1]);
    tr0->push_back((*przeksztalcony)[2]);

    tr1->push_back((*przeksztalcony)[5]);
    tr1->push_back((*przeksztalcony)[1]);
    tr1->push_back((*przeksztalcony)[0]);

    tr2->push_back((*przeksztalcony)[2]);
    tr2->push_back((*przeksztalcony)[1]);
    tr2->push_back((*przeksztalcony)[5]);

    tr3->push_back((*przeksztalcony)[0]);
    tr3->push_back((*przeksztalcony)[4]);
    tr3->push_back((*przeksztalcony)[5]);

    tr4->push_back((*przeksztalcony)[5]);
    tr4->push_back((*przeksztalcony)[4]);
    tr4->push_back((*przeksztalcony)[7]);

    tr5->push_back((*przeksztalcony)[7]);
    tr5->push_back((*przeksztalcony)[4]);
    tr5->push_back((*przeksztalcony)[0]);

    tr6->push_back((*przeksztalcony)[2]);
    tr6->push_back((*przeksztalcony)[3]);
    tr6->push_back((*przeksztalcony)[0]);

    tr7->push_back((*przeksztalcony)[0]);
    tr7->push_back((*przeksztalcony)[3]);
    tr7->push_back((*przeksztalcony)[7]);

    tr8->push_back((*przeksztalcony)[7]);
    tr8->push_back((*przeksztalcony)[3]);
    tr8->push_back((*przeksztalcony)[2]);

    tr9->push_back((*przeksztalcony)[5]);
    tr9->push_back((*przeksztalcony)[6]);
    tr9->push_back((*przeksztalcony)[2]);

    tr10->push_back((*przeksztalcony)[2]);
    tr10->push_back((*przeksztalcony)[6]);
    tr10->push_back((*przeksztalcony)[7]);

    tr11->push_back((*przeksztalcony)[7]);
    tr11->push_back((*przeksztalcony)[6]);
    tr11->push_back((*przeksztalcony)[5]);

    this->trojkatKr0=krawedz::na_liste_krawedzi(tr0);
    this->trojkatKr1=krawedz::na_liste_krawedzi(tr1);
    this->trojkatKr2=krawedz::na_liste_krawedzi(tr2);

    this->trojkatKr3=krawedz::na_liste_krawedzi(tr3);
    this->trojkatKr4=krawedz::na_liste_krawedzi(tr4);
    this->trojkatKr5=krawedz::na_liste_krawedzi(tr5);

    this->trojkatKr6=krawedz::na_liste_krawedzi(tr6);
    this->trojkatKr7=krawedz::na_liste_krawedzi(tr7);
    this->trojkatKr8=krawedz::na_liste_krawedzi(tr8);

    this->trojkatKr9 =krawedz::na_liste_krawedzi(tr9);
    this->trojkatKr10=krawedz::na_liste_krawedzi(tr10);
    this->trojkatKr11=krawedz::na_liste_krawedzi(tr11);

    QSharedPointer<punkt_struct>  tp1;
    tp1 = QSharedPointer<punkt_struct> (new punkt_struct);

    tp1->x = -20;
    tp1->y = 20;
    tp1->z = 0;

    QSharedPointer<punkt_struct>  tp2;
    tp2 = QSharedPointer<punkt_struct> (new punkt_struct);

    tp2->x = 600;
    tp2->y = 450;
    tp2->z = 0;

    QSharedPointer<punkt_struct> tp3;
    tp3 = QSharedPointer<punkt_struct> (new punkt_struct);

    tp3->x = 600;
    tp3->y = 20;
    tp3->z = 0;
	
    punktuTextury->push_back(tp1);
    punktuTextury->push_back(tp2);
    punktuTextury->push_back(tp3);

    im = new QImage (*buffor);   
}

void mowidget::zmien_aktualny_punkt(int aktualny_punkt)
{
    this->aktualny_punkt=aktualny_punkt;
}

int mowidget::wczytaj_lenght_punkt_list()
{
    return listaPunkow->length();
}

int mowidget::get_x()
{
    return (*listaPunkow)[aktualny_punkt]->x;
}

int mowidget::get_y()
{
    return (*listaPunkow)[aktualny_punkt]->y;
}

void mowidget::Pochyl_OX(float wspolczynnik_pochylenia_OX)
{
    this->rot.Pochyl_OX(wspolczynnik_pochylenia_OX);
    execute();
}

void mowidget::Pochyl_OY(float wspolczynnik_pochylenia_OY)
{
    this->rot.Pochyl_OY(wspolczynnik_pochylenia_OY);
    execute();
}

void mowidget::rotate_OX(int stopnie)
{
    this->rot.Rotate_OX(stopnie);
    execute();
}

void mowidget::rotate_OY(int stopnie)
{
    this->rot.Rotate_OY(stopnie);
    execute();
}

void mowidget::rotate_OZ(int stopnie)
{
    this->rot.Rotate_OZ(stopnie);
    execute();
}

void mowidget::Skalowanie_OX(float dlugosc)
{
    this->rot.Skalowanie_OX(dlugosc);
    execute();
}

void mowidget::Skalowanie_OY(float wysokosc)
{
    this->rot.Skalowanie_OY(wysokosc);
    execute();
}

void mowidget::Move_X(int x)
{
    this->rot;
     execute();
}

void mowidget::Move_Y(int y)
{
   execute();
}

void mowidget::execute()
{
    delete im;
    QImage *hh = new QImage(*buffor);
    rot.execute(trojkat, przeksztalcony);
    int b;
    if((b = krawedz::zwrot_trojkata(*trojkatKr0)) > 0)
    {       
       im = texturowanie_trojkatow(hh, (*trojkatKr0), buffor2, (*punktuTextury));
       delete(hh);
       hh = im;
    }

    if((b = krawedz::zwrot_trojkata(*trojkatKr1)) > 0)
    {
       im = texturowanie_trojkatow(hh, (*trojkatKr1), buffor2, (*punktuTextury));
       delete(hh);       
       hh = im;
    }

    if((b = krawedz::zwrot_trojkata(*trojkatKr2)) > 0)
    {
       im = texturowanie_trojkatow(hh, (*trojkatKr2), buffor2, (*punktuTextury));
       delete(hh);
       hh = im;
    }

    if((b = krawedz::zwrot_trojkata(*trojkatKr3)) > 0)
    {
       im = texturowanie_trojkatow(hh, (*trojkatKr3), buffor2, (*punktuTextury));
       delete(hh);
       hh = im;
    }

    if((b = krawedz::zwrot_trojkata(*trojkatKr4)) > 0)
    {
       im = texturowanie_trojkatow(hh, (*trojkatKr4), buffor2, (*punktuTextury));
       delete(hh);
       hh = im;
    }

    if((b = krawedz::zwrot_trojkata(*trojkatKr5)) > 0)
    {
       im = texturowanie_trojkatow(hh, (*trojkatKr5), buffor2, (*punktuTextury));
       delete(hh);
       hh = im;
    }

    if((b = krawedz::zwrot_trojkata(*trojkatKr6)) > 0)
    {
       im = texturowanie_trojkatow(hh, (*trojkatKr6), buffor2, (*punktuTextury));
       delete(hh);
       hh = im;
    }

    if((b = krawedz::zwrot_trojkata(*trojkatKr7)) > 0)
    {
       im = texturowanie_trojkatow(hh, (*trojkatKr7), buffor2, (*punktuTextury));
       delete(hh);
       hh = im;
    }

    if((b = krawedz::zwrot_trojkata(*trojkatKr8)) > 0)
    {
       im = texturowanie_trojkatow(hh, (*trojkatKr8), buffor2, (*punktuTextury));
       delete(hh);
       hh = im;
    }

    if((b = krawedz::zwrot_trojkata(*trojkatKr9)) > 0)
    {
       im = texturowanie_trojkatow(hh, (*trojkatKr9), buffor2, (*punktuTextury));
       delete(hh);
       hh = im;
    }

    if((b = krawedz::zwrot_trojkata(*trojkatKr10)) > 0)
    {
       im = texturowanie_trojkatow(hh, (*trojkatKr10), buffor2, (*punktuTextury));
       delete(hh);
       hh = im;
    }

    if((b = krawedz::zwrot_trojkata(*trojkatKr11)) > 0)
    {
       im = texturowanie_trojkatow(hh, (*trojkatKr11), buffor2, (*punktuTextury));
       delete(hh);
       hh = im;
    }
    update();
}

/*
void mowidget::delete_punkt()
{
    delete im;
    im = new QImage(*buffor);
    listaPunkow->removeAt(aktualny_punkt);
    narysuj_krzywa_sklejana(im, (*listaPunkow), 25);
    update();
    aktualny_punkt--;
}
*/

void mowidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawImage(0, 0, *im);
}

void mowidget::Mouse_left(QMouseEvent *e)
{
    qDebug("klik left! %d %d",e->x(), e->y());
}

void mowidget::mousePressEvent(QMouseEvent *e)
{
    qDebug("klik! %d %d",e->x(), e->y());   
}

void mowidget::mouseMoveEvent(QMouseEvent *e)
{

}

void mowidget::zmien_r(int r)
{
    ar = r;
    // rgb_to_hsv(ar,ag,ab,hue,sat, val);
}

void mowidget::zmien_g(int g)
{
    ag = g;
    // rgb_to_hsv(ar,ag,ab,hue,sat, val);
}

void mowidget::zmien_b(int b)
{
    ab = b;
    // rgb_to_hsv(ar,ag,ab,hue,sat, val);
}

void mowidget::zmien_h(int h)
{
    hue = h;
    // hsv_to_rgb(ar,ag,ab,hue,sat, val);
}

void mowidget::zmien_s(int s)
{
    sat = s;
    // hsv_to_rgb(ar,ag,ab,hue,sat, val);
}

void mowidget::zmien_v(int v)
{
    val = v;
    // hsv_to_rgb(ar,ag,ab,hue,sat, val);
}

int mowidget::wczytaj_r()
{
    return ar;
}

int mowidget::wczytaj_g()
{
    return ag;
}

int mowidget::wczytaj_b()
{
    return ab;
}

int mowidget::wczytaj_h()
{
    return hue;
}

int mowidget::wczytaj_s()
{
    return sat;
}

int mowidget::wczytaj_v()
{
    return val;
}

void mowidget::zmienKolor(int r, int g, int b)
{
    ar = r;
    ag = g;
    ab = b;
}

void mowidget::zminen_trojkaty_p1_X(float p1_x_value)
{
   (*trojkat)[0]->x = p1_x_value;   
    execute();
}

void mowidget::zminen_trojkaty_p1_Y(float p1_y_value)
{
    (*trojkat)[0]->y = p1_y_value;
    execute();
}

void mowidget::zminen_trojkaty_p1_Z(float p1_z_value)
{
    (*trojkat)[0]->z = p1_z_value;
    execute();
}

void mowidget::zminen_trojkaty_p2_X(float p2_x_value)
{
    (*trojkat)[1]->x = p2_x_value;
    execute();
}

void mowidget::zminen_trojkaty_p2_Y(float p2_y_value)
{
    (*trojkat)[1]->y = p2_y_value;
    execute();
}

void mowidget::zminen_trojkaty_p2_Z(float p2_z_value)
{
    (*trojkat)[1]->z = p2_z_value;
    execute();
}

void mowidget::zminen_trojkaty_p3_X(float p3_x_value)
{
    (*trojkat)[2]->x = p3_x_value;
    execute();
}

void mowidget::zminen_trojkaty_p3_Y(float p3_y_value)
{
    (*trojkat)[2]->y = p3_y_value;
    execute();
}

void mowidget::zminen_trojkaty_p3_Z(float p3_z_value)
{
    (*trojkat)[2]->z = p3_z_value;
    execute();
}
