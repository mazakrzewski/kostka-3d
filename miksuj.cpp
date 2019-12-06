#include <QPainter>
#include <QDebug>
#include <stack>
#include "types.h"

QImage *blend_mode_dodge(QImage *tlo, QImage *front, int x_ile, int y_ile, int x_z, int y_z, int x_do, int y_do){

    QImage *wynik;
    wynik = new QImage(*tlo);

    if(x_ile <= 0) {return tlo;}
    if(y_ile <= 0) {return tlo;}

    if(x_z < 0)
    {
        if(x_ile < x_z)
            return tlo;

        x_ile += x_z;
        x_do -= x_z;
        x_z = 0;
    }

    if(y_z < 0)
    {
        if(y_ile < y_z)
            return tlo;

        y_ile += y_z;
        y_do -= y_z;
        y_z = 0;
    }

    if(x_do < 0)
    {
        if(x_ile < x_do)
            return tlo;

        x_ile += x_do;
        x_z -= x_do;
        x_do = 0;
    }

    if(y_do < 0)
    {
        if(y_ile < y_do)
            return tlo;

        y_ile += y_do;
        y_z -= y_do;
        y_do = 0;
    }


    int tlo_width  = tlo->width();
    int tlo_height = tlo->height();

    int front_width  = front->width();
    int front_height = front->height();

    if(tlo_width <= x_z)
        return tlo;

    if(tlo_height <= y_z)
        return tlo;

    if(front_width <= x_do)
        return tlo;

    if(front_height <= y_do)
        return tlo;

    int width;
    int height;

    if(tlo_width - x_z < x_ile) {width = tlo_width - x_z;}
        else {width = x_ile;}

    if(tlo_height - y_z < y_ile) {height = tlo_height - y_z;}
        else {height = y_ile;}

    if(front_width - x_do < width){width = front_width - x_do;}

    if(front_height - y_do < height) {height = front_height - y_do;}

    uchar *p = wynik->bits() + 4*(y_do * tlo_width   + x_do);
    uchar *q = front->bits() + 4*(y_z  * front_width + x_z);

    tlo_width   -= width;
    front_width -= width;

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            p[0] = (p[0] + q[0]) / 2;
            p[1] = (p[1] + q[1]) / 2;
            p[2] = (p[2] + q[2]) / 2;
            p = p + 4;
            q = q + 4;
        }
        p = p + 4 * tlo_width;
        q = q + 4 * front_width;
    }
    return wynik;
}


QImage *blend_mode_quadratic(QImage *tlo, QImage *front, int x_ile, int y_ile, int x_z, int y_z, int x_do, int y_do){

    QImage *wynik;
    wynik = new QImage(*tlo);

    if(x_ile <= 0) {return tlo;}
    if(y_ile <= 0) {return tlo;}

    if(x_z < 0)
    {
        if(x_ile < x_z)
            return tlo;

        x_ile += x_z;
        x_do -= x_z;
        x_z = 0;
    }

    if(y_z < 0)
    {
        if(y_ile < y_z)
            return tlo;

        y_ile += y_z;
        y_do -= y_z;
        y_z = 0;
    }

    if(x_do < 0)
    {
        if(x_ile < x_do)
            return tlo;

        x_ile += x_do;
        x_z -= x_do;
        x_do = 0;
    }

    if(y_do < 0)
    {
        if(y_ile < y_do)
            return tlo;

        y_ile += y_do;
        y_z -= y_do;
        y_do = 0;
    }


    int tlo_width  = tlo->width();
    int tlo_height = tlo->height();

    int front_width  = front->width();
    int front_height = front->height();

    if(tlo_width <= x_z)
        return tlo;

    if(tlo_height <= y_z)
        return tlo;

    if(front_width <= x_do)
        return tlo;

    if(front_height <= y_do)
        return tlo;

    int width;
    int height;

    if(tlo_width - x_z < x_ile) {width = tlo_width - x_z;}
        else {width = x_ile;}

    if(tlo_height - y_z < y_ile) {height = tlo_height - y_z;}
        else {height = y_ile;}

    if(front_width - x_do < width) { width = front_width - x_do;}

    if(front_height - y_do < height) {height = front_height - y_do;}


    uchar *p = wynik->bits() + 4*(y_do * tlo_width + x_do);
    uchar *q = front->bits() + 4*(y_z * front_width + x_z);

    tlo_width   -=  width;
    front_width -=  width;


    for(int i = 0; i < height; i++)
    {        
        for(int j = 0;j < width;j++)
        {
            p[0] = (p[0] + q[0]) / 2;
            p[1] = (p[1] + q[1]) / 2;
            p[2] = (p[2] + q[2]) / 2;
            p = p + 4;
            q = q + 4;            
        }
        p = p + 4 * tlo_width;
        q = q + 4 * front_width;
    }
    return wynik;
}

QImage *blend_mode_additive(QImage *tlo, QImage *front, int x_ile, int y_ile, int x_z, int y_z, int x_do, int y_do){

    QImage *wynik;
    wynik = new QImage(*tlo);


    if(x_ile <= 0) {return tlo;}
    if(y_ile <= 0) {return tlo;}

    if(x_z < 0)
    {
        if(x_ile < x_z)
            return tlo;

        x_ile += x_z;
        x_do -= x_z;
        x_z = 0;
    }

    if(y_z < 0)
    {
        if(y_ile < y_z)
            return tlo;

        y_ile += y_z;
        y_do -= y_z;
        y_z = 0;
    }

    if(x_do < 0)
    {
        if(x_ile < x_do)
            return tlo;

        x_ile += x_do;
        x_z -= x_do;
        x_do = 0;
    }

    if(y_do < 0)
    {
        if(y_ile < y_do)
            return tlo;

        y_ile += y_do;
        y_z -= y_do;
        y_do = 0;
    }


    int tlo_width  = tlo->width();
    int tlo_height = tlo->height();

    int front_width  = front->width();
    int front_height = front->height();

    if(tlo_width <= x_z)
        return tlo;

    if(tlo_height <= y_z)
        return tlo;

    if(front_width <= x_do)
        return tlo;

    if(front_height <= y_do)
        return tlo;

    int width;
    int height;

    if(tlo_width - x_z < x_ile) {width = tlo_width - x_z;}
        else {width = x_ile;}

    if(tlo_height - y_z < y_ile) {height = tlo_height - y_z;}
        else {height = y_ile;}

    if(front_width - x_do < width) { width = front_width - x_do;}

    if(front_height - y_do < height) {height = front_height - y_do;}


    uchar *p = wynik->bits() + 4 * (y_do * tlo_width   + x_do);
    uchar *q = front->bits() + 4 * (y_z  * front_width + x_z);

    tlo_width   -=  width;
    front_width -=  width;

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            p[0] = (p[0] + q[0]) / 2;
            p[1] = (p[1] + q[1]) / 2;
            p[2] = (p[2] + q[2]) / 2;
            p = p + 4;
            q = q + 4;            
        }
        p = p + 4 * tlo_width;
        q = q + 4 * front_width;
    }
    return wynik;
}

QImage *blend_mode_interpolation(QImage *tlo, QImage *front, int x_ile, int y_ile, int x_z, int y_z, int x_do, int y_do){

    QImage *wynik;
    wynik = new QImage(*tlo);


    if(x_ile <= 0) {return tlo;}
    if(y_ile <= 0) {return tlo;}

    if(x_z < 0)
    {
        if(x_ile < x_z)
            return tlo;

        x_ile += x_z;
        x_do -= x_z;
        x_z = 0;
    }

    if(y_z < 0)
    {
        if(y_ile < y_z)
            return tlo;

        y_ile += y_z;
        y_do -= y_z;
        y_z = 0;
    }

    if(x_do < 0)
    {
        if(x_ile < x_do)
            return tlo;

        x_ile += x_do;
        x_z -= x_do;
        x_do = 0;
    }

    if(y_do < 0)
    {
        if(y_ile < y_do)
            return tlo;

        y_ile += y_do;
        y_z -= y_do;
        y_do = 0;
    }

    int tlo_width   = tlo->width();
    int tlo_height  = tlo->height();

    int front_width  = front->width();
    int front_height = front->height();

    if(tlo_width <= x_z)
        return tlo;

    if(tlo_height <= y_z)
        return tlo;

    if(front_width <= x_do)
        return tlo;

    if(front_height <= y_do)
        return tlo;

    int width;
    int height;

    if(tlo_width - x_z < x_ile) {width = tlo_width - x_z;}
        else {width = x_ile;}

    if(tlo_height - y_z < y_ile) {height = tlo_height - y_z;}
        else {height = y_ile;}

    if(front_width - x_do <  width) { width = front_width - x_do;}

    if(front_height - y_do < height) {height = front_height - y_do;}

    uchar *p = wynik->bits() + 4 * (y_do * tlo_width   + x_do);
    uchar *q = front->bits() + 4 * (y_z  * front_width + x_z);

    tlo_width   -= width;
    front_width -= width;

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            p[0] = (p[0] + q[0]) / 2;
            p[1] = (p[1] + q[1]) / 2;
            p[2] = (p[2] + q[2]) / 2;
            p = p + 4;
            q = q + 4;
        }
        p = p + 4 * tlo_width;
        q = q + 4 * front_width;
    }
    return wynik;
}

QImage *blend_mode_normal(QImage *tlo, QImage *front, int x_ile, int y_ile, int x_z, int y_z, int x_do, int y_do){

    QImage *wynik;
    wynik = new QImage(*tlo);

    if(x_ile <= 0) {return tlo;}
    if(y_ile <= 0) {return tlo;}

    if(x_z < 0)
    {
        if(x_ile < x_z)
            return tlo;

        x_ile += x_z;
        x_do -= x_z;
        x_z = 0;
    }

    if(y_z < 0)
    {
        if(y_ile < y_z)
            return tlo;

        y_ile += y_z;
        y_do -= y_z;
        y_z = 0;
    }

    if(x_do < 0)
    {
        if(x_ile < x_do)
            return tlo;

        x_ile += x_do;
        x_z -= x_do;
        x_do = 0;
    }

    if(y_do < 0)
    {
        if(y_ile < y_do)
            return tlo;

        y_ile += y_do;
        y_z -= y_do;
        y_do = 0;
    }


    int tlo_width  = tlo->width();
    int tlo_height = tlo->height();

    int front_width  = front->width();
    int front_height = front->height();

    if(tlo_width <= x_z)
        return tlo;

    if(tlo_height  <= y_z)
        return tlo;

    if(front_width <= x_do)
        return tlo;

    if(front_height <= y_do)
        return tlo;

    int width;
    int height;

    if(tlo_width - x_z < x_ile) {width = tlo_width - x_z;}
        else {width = x_ile;}

    if(tlo_height - y_z < y_ile) {height = tlo_height - y_z;}
        else {height = y_ile;}

    if(front_width - x_do < width) {width = front_width - x_do;}

    if(front_height - y_do < height) {height = front_height - y_do;}

    uchar *p = wynik->bits() + 4 * (y_do * tlo_width   + x_do);
    uchar *q = front->bits() + 4 * (y_z  * front_width + x_z);

    tlo_width   -= width;
    front_width -= width;

    for(int i = 0; i < height; i++)
    {
        for(int j = 0;j < width;j++)
        {
            p[0] = q[0];
            p[1] = q[1];
            p[2] = q[2];
            p = p + 4;
            q = q + 4;
        }
        p = p + 4 * tlo_width;
        q = q + 4 * front_width;

    }
    return wynik;
}

QImage *blend_mode_average(QImage *tlo, QImage *front, int x_ile, int y_ile, int x_z, int y_z, int x_do, int y_do){

    QImage *wynik;
    wynik = new QImage(*tlo);

    if(x_ile <= 0) {return tlo;}
    if(y_ile <= 0) {return tlo;}

    if(x_z < 0)
    {
        if(x_ile < x_z)
            return tlo;

        x_ile += x_z;
        x_do -= x_z;
        x_z = 0;
    }

    if(y_z < 0)
    {
        if(y_ile < y_z)
            return tlo;

        y_ile += y_z;
        y_do -= y_z;
        y_z = 0;
    }

    if(x_do < 0)
    {
        if(x_ile < x_do)
            return tlo;

        x_ile += x_do;
        x_z -= x_do;
        x_do = 0;
    }

    if(y_do < 0)
    {
        if(y_ile < y_do)
            return tlo;

        y_ile += y_do;
        y_z -= y_do;
        y_do = 0;
    }


    int tlo_width  = tlo->width();
    int tlo_height = tlo->height();

    int front_width  = front->width();
    int front_height = front->height();

    if(tlo_width <= x_z)
        return tlo;

    if(tlo_height <= y_z)
        return tlo;

    if(front_width <= x_do)
        return tlo;

    if(front_height <= y_do)
        return tlo;

    int width;
    int height;

    if(tlo_width - x_z < x_ile) {width = tlo_width - x_z;}
        else {width = x_ile;}

    if(tlo_height - y_z < y_ile) {height = tlo_height - y_z;}
        else {height = y_ile;}

    if(front_width - x_do < width) {width = front_width - x_do;}

    if(front_height - y_do < height) {height = front_height - y_do;}

    uchar *p = wynik->bits() + 4 * (y_do * tlo_width   + x_do);
    uchar *q = front->bits() + 4 * (y_z  * front_width + x_z);

    tlo_width   -= width;
    front_width -= width;

    for(int i = 0; i < height; i++)
    {        
        for(int j = 0; j < width; j++)
        {
            p[0] = (p[0] + q[0]) / 2;
            p[1] = (p[1] + q[1]) / 2;
            p[2] = (p[2] + q[2]) / 2;
            p = p + 4;
            q = q + 4;
        }
        p = p + 4 * tlo_width;
        q = q + 4 * front_width;

    }
    return wynik;
}

QImage *blend_mode_multiply(QImage *tlo, QImage *front, int x_ile, int y_ile, int x_z, int y_z, int x_do, int y_do){

    QImage *wynik;
    wynik = new QImage(*tlo);

    if(x_ile <= 0) {return tlo;}
    if(y_ile <= 0) {return tlo;}

    if(x_z < 0)
    {
        if(x_ile < x_z)
            return tlo;

        x_ile += x_z;
        x_do -= x_z;
        x_z = 0;
    }

    if(y_z < 0)
    {
        if(y_ile < y_z)
            return tlo;

        y_ile += y_z;
        y_do -= y_z;
        y_z = 0;
    }

    if(x_do < 0)
    {
        if(x_ile < x_do)
            return tlo;

        x_ile += x_do;
        x_z -= x_do;
        x_do = 0;
    }

    if(y_do < 0)
    {
        if(y_ile < y_do)
            return tlo;

        y_ile += y_do;
        y_z -= y_do;
        y_do = 0;
    }


    int tlo_width  = tlo->width();
    int tlo_height = tlo->height();

    int front_width  = front->width();
    int front_height = front->height();

    if(tlo_width <= x_z)
        return tlo;

    if(tlo_height <= y_z)
        return tlo;

    if(front_width <= x_do)
        return tlo;

    if(front_height <= y_do)
        return tlo;

    int width;
    int height;

    if(tlo_width - x_z < x_ile) {width = tlo_width - x_z;}
        else {width = x_ile;}

    if(tlo_height - y_z < y_ile) {height = tlo_height - y_z;}
        else {height = y_ile;}

    if(front_width - x_do < width) {width = front_width - x_do;}

    if(front_height - y_do < height) {height = front_height - y_do;}

    uchar *p = wynik->bits() + 4 * (y_do * tlo_width   + x_do);
    uchar *q = front->bits() + 4 * (y_z  * front_width + x_z);

    tlo_width   -= width;
    front_width -= width;

}

QImage *blend_mode_screen(QImage *tlo,QImage *front, int x_ile, int y_ile, int x_z, int y_z, int x_do , int y_do){

    QImage *wynik;
    wynik = new QImage(*tlo);

    if(x_ile <= 0) {return tlo;}
    if(y_ile <= 0) {return tlo;}

    if(x_z < 0)
    {
        if(x_ile < x_z)
            return tlo;

        x_ile += x_z;
        x_do -= x_z;
        x_z = 0;
    }

    if(y_z < 0)
    {
        if(y_ile < y_z)
            return tlo;

        y_ile += y_z;
        y_do -= y_z;
        y_z = 0;
    }

    if(x_do < 0)
    {
        if(x_ile < x_do)
            return tlo;

        x_ile += x_do;
        x_z -= x_do;
        x_do = 0;
    }

    if(y_do < 0)
    {
        if(y_ile < y_do)
            return tlo;

        y_ile += y_do;
        y_z -= y_do;
        y_do = 0;
    }

    int tlo_width  = tlo->width();
    int tlo_height = tlo->height();

    int front_width  = front->width();
    int front_height = front->height();

    if(tlo_width <= x_z)
        return tlo;

    if(tlo_height <= y_z)
        return tlo;

    if(front_width <= x_do)
        return tlo;

    if(front_height <= y_do)
        return tlo;

    int width;
    int height;

    if(tlo_width - x_z < x_ile) {width = tlo_width - x_z;}
        else {width = x_ile;}

    if(tlo_height - y_z < y_ile) {height = tlo_height - y_z;}
        else {height = y_ile;}

    if(front_width - x_do < width) {width = front_width - x_do;}

    if(front_height - y_do < height) {height = front_height - y_do;}

    uchar *p = wynik->bits() + 4 * (y_do * tlo_width   + x_do);
    uchar *q = front->bits() + 4 * (y_z  * front_width + x_z);

    tlo_width   -= width;
    front_width -= width;

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width;j++)
        {
            p[0] = 255 - ((255 - p[0]) * (255 - q[0]) >> 8);
            p[1] = 255 - ((255 - p[1]) * (255 - q[1]) >> 8);
            p[2] = 255 - ((255 - p[2]) * (255 - q[2]) >> 8);
            p = p + 4;
            q = q + 4;          
        }
        p = p + 4 * tlo_width;
        q = q + 4 * front_width;

    }
    return wynik;
}

QImage *blend_mode_darken(QImage *tlo, QImage *front, int x_ile, int y_ile, int x_z, int y_z, int x_do, int y_do){

    QImage *wynik;
    wynik = new QImage(*tlo);


    if(x_ile <= 0) {return tlo;}
    if(y_ile <= 0) {return tlo;}

    if(x_z < 0)
    {
        if(x_ile < x_z)
            return tlo;

        x_ile += x_z;
        x_do -= x_z;
        x_z = 0;
    }

    if(y_z < 0)
    {
        if(y_ile < y_z)
            return tlo;

        y_ile += y_z;
        y_do -= y_z;
        y_z = 0;
    }

    if(x_do < 0)
    {
        if(x_ile < x_do)
            return tlo;

        x_ile += x_do;
        x_z -= x_do;
        x_do = 0;
    }

    if(y_do < 0)
    {
        if(y_ile < y_do)
            return tlo;

        y_ile += y_do;
        y_z -= y_do;
        y_do = 0;
    }


    int tlo_width  = tlo->width();
    int tlo_height = tlo->height();

    int front_width  = front->width();
    int front_height = front->height();

    if(tlo_width <= x_z)
        return tlo;

    if(tlo_height <= y_z)
        return tlo;

    if(front_width <= x_do)
        return tlo;

    if(front_height <= y_do)
        return tlo;

    int width;
    int height;

    if(tlo_width - x_z < x_ile) {width = tlo_width - x_z;}
        else {width = x_ile;}

    if(tlo_height - y_z < y_ile) {height = tlo_height - y_z;}
        else {height = y_ile;}

    if(front_width - x_do < width) {width = front_width - x_do;}

    if(front_height - y_do < height) {height = front_height - y_do;}


    uchar *p = wynik->bits() + 4 * (y_do * tlo_width   + x_do);
    uchar *q = front->bits() + 4 * (y_z  * front_width + x_z);

    tlo_width   -= width;
    front_width -= width;

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            p[0] = p[0] > q[0] ? p[0] : q[0];
            p[1] = p[1] > q[1] ? p[1] : q[1];
            p[2] = p[2] > q[2] ? p[2] : q[2];
            p = p + 4;
            q = q + 4;
        }
        p = p + 4 * tlo_width;
        q = q + 4 * front_width;

    }
    return wynik;
}

QImage *blend_mode_lighten(QImage *tlo, QImage *front, int x_ile, int y_ile, int x_z, int y_z, int x_do, int y_do){

    QImage *wynik;
    wynik = new QImage(*tlo);

    if(x_ile <= 0) {return tlo;}
    if(y_ile <= 0) {return tlo;}

    if(x_z < 0)
    {
        if(x_ile < x_z)
            return tlo;

        x_ile += x_z;
        x_do -= x_z;
        x_z = 0;
    }

    if(y_z < 0)
    {
        if(y_ile < y_z)
            return tlo;

        y_ile += y_z;
        y_do -= y_z;
        y_z = 0;
    }

    if(x_do < 0)
    {
        if(x_ile < x_do)
            return tlo;

        x_ile += x_do;
        x_z -= x_do;
        x_do = 0;
    }

    if(y_do < 0)
    {
        if(y_ile < y_do)
            return tlo;

        y_ile += y_do;
        y_z -= y_do;
        y_do = 0;
    }


    int tlo_width  = tlo->width();
    int tlo_height = tlo->height();

    int front_width  = front->width();
    int front_height = front->height();

    if(tlo_width <= x_z)
        return tlo;

    if(tlo_height <= y_z)
        return tlo;

    if(front_width <= x_do)
        return tlo;

    if(front_height <= y_do)
        return tlo;

    int width;
    int height;

    if(tlo_width - x_z < x_ile) {width = tlo_width - x_z;}
        else {width = x_ile;}

    if(tlo_height - y_z < y_ile) {height = tlo_height - y_z;}
        else {height = y_ile;}

    if(front_width - x_do < width) {width = front_width - x_do;}

    if(front_height - y_do < height) {height = front_height - y_do;}


    uchar *p = wynik->bits() + 4 * (y_do * tlo_width   + x_do);
    uchar *q = front->bits() + 4 * (y_z  * front_width + x_z);

    tlo_width   -=  width;
    front_width -=  width;

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            p[0] = p[0] < q[0] ? p[0] : q[0];
            p[1] = p[1] < q[1] ? p[1] : q[1];
            p[2] = p[2] < q[2] ? p[2] : q[2];
            p = p + 4;
            q = q + 4;
        }
        p = p + 4 * tlo_width;
        q = q + 4 * front_width;
    }
    return wynik;
}

QImage *blend_mode_difference(QImage *tlo, QImage *front, int x_ile, int y_ile, int x_z, int y_z, int x_do, int y_do){

    QImage *wynik;
    wynik = new QImage(*tlo);

    if(x_ile <= 0) {return tlo;}
    if(y_ile <= 0) {return tlo;}

    if(x_z < 0)
    {
        if(x_ile < x_z)
            return tlo;

        x_ile += x_z;
        x_do -= x_z;
        x_z = 0;
    }

    if(y_z < 0)
    {
        if(y_ile < y_z)
            return tlo;

        y_ile += y_z;
        y_do -= y_z;
        y_z = 0;
    }

    if(x_do < 0)
    {
        if(x_ile < x_do)
            return tlo;

        x_ile += x_do;
        x_z -= x_do;
        x_do = 0;
    }

    if(y_do < 0)
    {
        if(y_ile < y_do)
            return tlo;

        y_ile += y_do;
        y_z -= y_do;
        y_do = 0;
    }


    int tlo_width  = tlo->width();
    int tlo_height = tlo->height();

    int front_width  = front->width();
    int front_height = front->height();

    if(tlo_width <= x_z)
        return tlo;

    if(tlo_height <= y_z)
        return tlo;

    if(front_width <= x_do)
        return tlo;

    if(front_height <= y_do)
        return tlo;

    int width;
    int height;

    if(tlo_width - x_z < x_ile) {width = tlo_width - x_z;}
        else {width = x_ile;}

    if(tlo_height - y_z < y_ile) {height = tlo_height - y_z;}
        else {height = y_ile;}

    if(front_width - x_do < width) {width = front_width - x_do;}

    if(front_height - y_do < height) {height = front_height - y_do;}

    uchar *p = wynik->bits() + 4 * (y_do * tlo_width   + x_do);
    uchar *q = front->bits() + 4 * (y_z  * front_width + x_z);

    tlo_width   -= width;
    front_width -= width;

    for(int i = 0; i < height; i++)
    {        
        for(int j = 0; j < width; j++)
        {
            p[0] = p[0] > q[0] ? p[0] - q[0] : q[0] - p[0];
            p[1] = p[1] > q[1] ? p[1] - q[1] : q[1] - p[1];
            p[2] = p[2] > q[2] ? p[2] - q[2] : q[2] - p[2];
            p = p + 4;
            q = q + 4;          
        }
        p = p + 4 * tlo_width;
        q = q + 4 * front_width;
    }
    return wynik;
}

QImage *blend_mode_negation(QImage *tlo, QImage *front, int x_ile, int y_ile, int x_z, int y_z, int x_do, int y_do){

    QImage *wynik;
    wynik = new QImage(*tlo);

    if(x_ile <= 0) {return tlo;}
    if(y_ile <= 0) {return tlo;}

    if(x_z < 0)
    {
        if(x_ile < x_z)
            return tlo;

        x_ile += x_z;
        x_do -= x_z;
        x_z = 0;
    }

    if(y_z < 0)
    {
        if(y_ile < y_z)
            return tlo;

        y_ile += y_z;
        y_do -= y_z;
        y_z = 0;
    }

    if(x_do < 0)
    {
        if(x_ile < x_do)
            return tlo;

        x_ile += x_do;
        x_z -= x_do;
        x_do = 0;
    }

    if(y_do < 0)
    {
        if(y_ile < y_do)
            return tlo;

        y_ile += y_do;
        y_z -= y_do;
        y_do = 0;
    }


    int tlo_width  = tlo->width();
    int tlo_height = tlo->height();

    int front_width  = front->width();
    int front_height = front->height();

    if(tlo_width <= x_z)
        return tlo;

    if(tlo_height <= y_z)
        return tlo;

    if(front_width <= x_do)
        return tlo;

    if(front_height <= y_do)
        return tlo;

    int width;
    int height;

    if(tlo_width - x_z < x_ile) {width = tlo_width - x_z;}
        else {width = x_ile;}

    if(tlo_height - y_z < y_ile) {height = tlo_height - y_z;}
        else {height = y_ile;}

    if(front_width - x_do < width) {width = front_width - x_do;}

    if(front_height - y_do < height) {height = front_height - y_do;}

    uchar *p = wynik->bits() + 4 * (y_do * tlo_width   + x_do);
    uchar *q = front->bits() + 4 * (y_z  * front_width + x_z);

    tlo_width   -= width;
    front_width -= width;

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            p[0] = 255 < p[0] + q[0] ? 510 - p[0] - q[0] : q[0] + p[0];
            p[1] = 255 < p[1] + q[1] ? 510 - p[1] - q[1] : q[1] + p[1];
            p[2] = 255 < p[2] + q[2] ? 510 - p[2] - q[2] : q[2] + p[2];
            p = p + 4;
            q = q + 4;            
        }
        p = p + 4 * tlo_width;
        q = q + 4 * front_width;
    }
    return wynik;
}

QImage *blend_mode_exclusion(QImage *tlo, QImage *front, int x_ile, int y_+ile, int x_z, int y_z, int x_do, int y_do){

    QImage *wynik;
    wynik = new QImage(*tlo);

    if(x_ile <= 0) {return tlo;}
    if(y_ile <= 0) {return tlo;}

    if(x_z < 0)
    {
        if(x_ile < x_z)
            return tlo;

        x_ile += x_z;
        x_do -= x_z;
        x_z = 0;
    }

    if(y_z < 0)
    {
        if(y_ile < y_z)
            return tlo;

        y_ile += y_z;
        y_do -= y_z;
        y_z = 0;
    }

    if(x_do < 0)
    {
        if(x_ile < x_do)
            return tlo;

        x_ile += x_do;
        x_z -= x_do;
        x_do = 0;
    }

    if(y_do < 0)
    {
        if(y_ile < y_do)
            return tlo;

        y_ile += y_do;
        y_z -= y_do;
        y_do = 0;
    }

    int tlo_width  = tlo->width();
    int tlo_height = tlo->height();

    int front_width  = front->width();
    int front_height = front->height();

    if(tlo_width <= x_z)
        return tlo;

    if(tlo_height <= y_z)
        return tlo;

    if(front_width <= x_do)
        return tlo;

    if(front_height <= y_do)
        return tlo;

    int width;
    int height;

    if(tlo_width - x_z < x_ile) {width = tlo_width - x_z;}
        else {width = x_ile;}

    if(tlo_height - y_z < y_ile) {height = tlo_height - y_z;}
        else {height = y_ile;}

    if(front_width - x_do < width) {width = front_width - x_do;}

    if(front_height - y_do < height) {height = front_height - y_do;}

    uchar *p = wynik->bits() + 4 * (y_do * tlo_width   + x_do);
    uchar *q = front->bits() + 4 * (y_z  * front_width + x_z);

    tlo_width   -= width;
    front_width -= width;

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            p[0] = p[0] + q[0] - (p[0] * q[0] >> 7);
            p[1] = p[0] + q[0] - (p[0] * q[0] >> 7);
            p[2] = p[0] + q[0] - (p[0] * q[0] >> 7);
            p = p + 4;
            q = q + 4;           
        }
        p = p + 4 * tlo_width;
        q = q + 4 * front_width;
    }
    return wynik;
}

QImage *blend_mode_overlay(QImage *tlo, QImage *front, int x_ile, int y_ile, int x_z, int y_z, int x_do, int y_do){

    QImage *wynik;
    wynik = new QImage(*tlo);

    if(x_ile <= 0) {return tlo;}
    if(y_ile <= 0) {return tlo;}

    if(x_z < 0)
    {
        if(x_ile < x_z)
            return tlo;

        x_ile += x_z;
        x_do -= x_z;
        x_z = 0;
    }

    if(y_z < 0)
    {
        if(y_ile < y_z)
            return tlo;

        y_ile += y_z;
        y_do -= y_z;
        y_z = 0;
    }

    if(x_do < 0)
    {
        if(x_ile < x_do)
            return tlo;

        x_ile += x_do;
        x_z -= x_do;
        x_do = 0;
    }

    if(y_do < 0)
    {
        if(y_ile < y_do)
            return tlo;

        y_ile += y_do;
        y_z -= y_do;
        y_do = 0;
    }

    int tlo_width  = tlo->width();
    int tlo_height = tlo->height();

    int front_width  = front->width();
    int front_height = front->height();

    if(tlo_width <= x_z)
        return tlo;

    if(tlo_height <= y_z)
        return tlo;

    if(front_width <= x_do)
        return tlo;

    if(front_height <= y_do)
        return tlo;

    int width;
    int height;

    if(tlo_width - x_z < x_ile) {width = tlo_width - x_z;}
        else {width = x_ile;}

    if(tlo_height - y_z < y_ile) {height = tlo_height - y_z;}
        else {height = y_ile;}

    if(front_width - x_do < width) {width = front_width - x_do;}

    if(front_height - y_do < height) {height = front_height - y_do;}

    uchar *p = wynik->bits() + 4 * (y_do * tlo_width   + x_do);
    uchar *q = front->bits() + 4 * (y_z  * front_width + x_z);

    tlo_width   -= width;
    front_width -= width;

    for(int i = 0; i < height; i++)
    {
        for(int j = 0;j < width;j++)
        {
            p[0] = p[0] < 128 ? p[0] * q[0] >> 7 : 255 - ((255 - p[0]) * (255 - q[0]) >> 7);
            p[1] = p[1] < 128 ? p[1] * q[1] >> 7 : 255 - ((255 - p[1]) * (255 - q[1]) >> 7);
            p[2] = p[2] < 128 ? p[2] * q[2] >> 7 : 255 - ((255 - p[2]) * (255 - q[2]) >> 7);
            p = p + 4;
            q = q + 4;
        }
        p = p + 4 * tlo_width;
        q = q + 4 * front_width;
    }
    return wynik;
}

QImage *blend_mode_hard_light(QImage *tlo, QImage *front, int x_ile, int y_ile, int x_z, int y_z, int x_do, int y_do){

    QImage *wynik;
    wynik = new QImage(*tlo);

    if(x_ile <= 0) {return tlo;}
    if(y_ile <= 0) {return tlo;}

    if(x_z < 0)
    {
        if(x_ile < x_z)
            return tlo;

        x_ile += x_z;
        x_do -= x_z;
        x_z = 0;
    }

    if(y_z < 0)
    {
        if(y_ile < y_z)
            return tlo;

        y_ile += y_z;
        y_do -= y_z;
        y_z = 0;
    }

    if(x_do < 0)
    {
        if(x_ile < x_do)
            return tlo;

        x_ile += x_do;
        x_z -= x_do;
        x_do = 0;
    }

    if(y_do < 0)
    {
        if(y_ile < y_do)
            return tlo;

        y_ile += y_do;
        y_z -= y_do;
        y_do = 0;
    }

    int tlo_width   = tlo->width();
    int tlo_height  = tlo->height();

    int front_width  = front->width();
    int front_height = front->height();

    if(tlo_width <= x_z)
        return tlo;

    if(tlo_height <= y_z)
        return tlo;

    if(front_width <= x_do)
        return tlo;

    if(front_height <= y_do)
        return tlo;

    int width;
    int height;

    if(tlo_width - x_z < x_ile) {width = tlo_width - x_z;}
        else {width = x_ile;}

    if(tlo_height - y_z < y_ile) {height = tlo_height - y_z;}
        else {height = y_ile;}

    if(front_width - x_do < width) {width = front_width - x_do;}

    if(front_height - y_do < height) {height = front_height - y_do;}

    uchar *p = wynik->bits() + 4 * (y_do * tlo_width   + x_do);
    uchar *q = front->bits() + 4 * (y_z  * front_width + x_z);

    tlo_width   -= width;
    front_width -= width;

    for(int i = 0; i < height; i++)
    {
        for(int j = 0;j < width;j++)
        {
            p[0] = q[0] < 128 ? p[0] * q[0] >> 7 : 255 - ((255 - p[0]) * (255 - q[0]) >> 7);
            p[1] = q[1] < 128 ? p[1] * q[1] >> 7 : 255 - ((255 - p[1]) * (255 - q[1]) >> 7);
            p[2] = q[2] < 128 ? p[2] * q[2] >> 7 : 255 - ((255 - p[2]) * (255 - q[2]) >> 7);
            p = p + 4;
            q = q + 4;            
        }
        p = p + 4 * tlo_width;
        q = q + 4 * front_width;
    }
    return wynik;
}

QImage *blend_mode_soft_light(QImage *tlo, QImage *front, int x_ile, int y_ile, int x_z, int y_z, int x_do, int y_do){

    QImage *wynik;
    wynik = new QImage(*tlo);

    if(x_ile <= 0) {return tlo;}
    if(y_ile <= 0) {return tlo;}

    if(x_z < 0)
    {
        if(x_ile < x_z)
            return tlo;

        x_ile += x_z;
        x_do -= x_z;
        x_z = 0;
    }

    if(y_z < 0)
    {
        if(y_ile < y_z)
            return tlo;

        y_ile += y_z;
        y_do -= y_z;
        y_z = 0;
    }

    if(x_do < 0)
    {
        if(x_ile < x_do)
            return tlo;

        x_ile += x_do;
        x_z -= x_do;
        x_do = 0;
    }

    if(y_do < 0)
    {
        if(y_ile < y_do)
            return tlo;

        y_ile += y_do;
        y_z -= y_do;
        y_do = 0;
    }


    int tlo_width  = tlo->width();
    int tlo_height = tlo->height();

    int front_width  = front->width();
    int front_height = front->height();

    if(tlo_width <= x_z)
        return tlo;

    if(tlo_height <= y_z)
        return tlo;

    if(front_width <= x_do)
        return tlo;

    if(front_height <= y_do)
        return tlo;

    int width;
    int height;

    if(tlo_width - x_z < x_ile) {width = tlo_width - x_z;}
        else {width = x_ile;}

    if(tlo_height - y_z < y_ile) {height = tlo_height - y_z;}
        else {height = y_ile;}

    if(front_width - x_do < width) {width = front_width - x_do;}

    if(front_height - y_do < height) {height = front_height - y_do;}


    uchar *p = wynik->bits() + 4 * (y_do * tlo_width   + x_do);
    uchar *q = front->bits() + 4 * (y_z  * front_width + x_z);

    tlo_width   -= width;
    front_width -= width;

    int c;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            c = p[0] * q[0] >> 8;
            p[0] = c + p[0] * (255 - (( 255 - p[0]) * (255 - q[0]) >> 8) - c) >> 8;

            c = p[1] * q[1] >> 8;
            p[0] = c + p[1] * (255 - (( 255 - p[1]) * (255 - q[1]) >> 8) - c) >> 8;

            c = p[2] * q[2] >> 8;
            p[2] = c + p[2] * (255 - (( 255 - p[2]) * (255 - q[2]) >> 8) - c) >> 8;
            p = p + 4;
            q = q + 4;             
        }
        p = p + 4 * tlo_width;
        q = q + 4 * front_width;
    }
    return wynik;
}
