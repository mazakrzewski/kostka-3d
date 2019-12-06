#include <QPainter>
#include <armadillo>
#include <QtMath>
#include <rotate.h>
#include <QDebug>
#include <math.h>

using namespace arma;

QImage  * pochyl(QImage *obraz, float stopnie ){
   return obraz;
}

QImage  * rotate(QImage *obraz, float stopnie )
{
    if (stopnie < 0){
        while(stopnie < 0){
            stopnie = stopnie + 360;
        }
    }
    else
    {
        while (stopnie > 360)
        {
            stopnie = stopnie - 360;
        }
    }   

    int width_obraz = obraz->width();
    int height_obraz = obraz->height();

    float r = sqrt((float)(width_obraz * width_obraz + height_obraz * height_obraz));
    float kx = stopnie;
    
    kx+=qRadiansToDegrees(acos(height_obraz / (r)));

    float ky = stopnie + 180 - qRadiansToDegrees(acos(height_obraz / (r)));


    float radians;
    radians = qDegreesToRadians(stopnie);

    if(kx >= 360)
    {
        kx -= 360;
    }
    else
    {
        if(kx >= 180)
        {
            kx -= 180;
        }
        if(kx > 90)
        {
            kx = 180 - kx;
        }
    }

    if(ky >= 360)
    {
        ky -= 360;
    }
    else
    {
        if(ky >= 180)
        {
            ky -= 180;
        }
        if(ky > 90)
        {
            ky = 180 - ky;
        }
    }

    int width_wynik = 0;
    int height_wynik = 0;

    if (ky > kx)
    {
         width_wynik  = r * sin(qDegreesToRadians(ky)) + 1;
         height_wynik = r * cos(qDegreesToRadians(kx)) + 1;
    }
    else
    {
        width_wynik  = r * sin(qDegreesToRadians(kx)) + 1;
        height_wynik = r * cos(qDegreesToRadians(ky)) + 1;
    }    

    arma::fmat Rotacja;

    Rotacja << cos(radians) <<  - sin(radians)   << 0 << arma::endr
            << sin(radians) <<    cos(radians)   << 0 << arma::endr
            << 0            <<    0              << 1;

    Rotacja = Rotacja.i();

    fmat mkjh;

    QImage  *wynik;
    wynik = new QImage(width_wynik,height_wynik, QImage::Format_RGB32);

    uchar *p = obraz -> bits();
    uchar *q = wynik -> bits();
    int szerokosc  =  width_obraz  / 2;
    int wysokosc   =  height_obraz / 2;

    fmat  maciez;
    maciez << (float)(-width_wynik  / 2) << arma::endr
           << (float)(-height_wynik / 2) << arma::endr
           << 0;

    fmat dodaj_x;
    dodaj_x << 1 << arma::endr
            << 0 << arma::endr
            << 0;

    fmat dodaj_y;
    dodaj_y <<  - width_wynik << arma::endr
            << 1              << arma::endr
            << 0;

    for(int i = 0; i < height_wynik; i++){
        for(int j = 0; j < width_wynik; j++){
            
            arma::fmat wek;
			
            wek = Rotacja * maciez;
            maciez += dodaj_x;

            float px = wek(0,0) + szerokosc;
            float py = wek(1,0) + wysokosc;

            int x  =  px;
            int y  =  py;

            if(x >= 0)
            {
                if(x <= width_obraz)
                {
                    if(y >= 0)
                    {
                        if(y < height_obraz)
                        {
                            float fx  =  px  -  (int)px;
                            float fy  =  py  -  (int)py;

                            q[0]=(int)(
                                        (1 - fx)  *  (1 - fy)  *  (p  +  4  *  (x      +   y       *  width_obraz))[0] + 
                                        (fx)      *  (1 - fy)  *  (p  +  4  *  (x + 1  +   y       *  width_obraz))[0] + 
                                        (1 - fx)  *  (fy)      *  (p  +  4  *  (x      +  (y + 1)  *  width_obraz))[0] + 
                                        (fx)      *  (fy)      *  (p  +  4  *  (x + 1  +  (y + 1)  *  width_obraz))[0]);

                            q[1]= (int)(
                                        (1 - fx)  *  (1 - fy)  *  (p  +  4  *  (x      +   y       *  width_obraz))[1] + 
                                        (fx)      *  (1 - fy)  *  (p  +  4  *  (x + 1  +   y       *  width_obraz))[1] + 
                                        (1 - fx)  *  (fy)      *  (p  +  4  *  (x      +  (y + 1)  *  width_obraz))[1] + 
                                        (fx)      *  (fy)      *  (p  +  4  *  (x + 1  +  (y + 1)  *  width_obraz))[1]);



                            q[2]= (int)(
                                        (1 - fx)  *  (1 - fy)  *  (p  +  4  *  (x      +   y       *  width_obraz))[2] + 
                                        (fx)      *  (1 - fy)  *  (p  +  4  *  (x + 1  +   y       *  width_obraz))[2] + 
                                        (1 - fx)  *  (fy)      *  (p  +  4  *  (x      +  (y + 1)  *  width_obraz))[2] + 
                                        (fx)      *  (fy)      *  (p  +  4  *  (x + 1  +  (y + 1)  *  width_obraz))[2]);

                        }
                    }
                }
            }
            q+=4;
        }
        maciez += dodaj_y;
    }
   return wynik;
}






