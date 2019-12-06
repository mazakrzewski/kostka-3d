#include <rotate_3d_class.h>
#include <armadillo>
#include <QPainter>
#include <armadillo>
#include <qmath.h>
#include <QDebug>
#include <math.h>

rotate_3d_class::rotate_3d_class()
{
    arma::fmat Rotacja;
    Rotacja<< 1 << 0 << 0 << 0 << arma::endr
           << 0 << 1 << 0 << 0 << arma::endr
           << 0 << 0 << 1 << 0 << arma::endr
           << 0 << 0 << 0 << 1;

    this->Mat_Rotate_OX = Rotacja;
    this->Mat_Rotate_OY = Rotacja;
    this->Mat_Rotate_OZ = Rotacja;
    this->Mat_Pochyl_OX = Rotacja;
    this->Mat_Pochyl_OY = Rotacja;
    this->Mat_Size_OX = Rotacja;
    this->Mat_Size_OY = Rotacja;
}

void rotate_3d_class::Rotate_OX(float stopnie){

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

    float radians;
    radians = qDegreesToRadians(stopnie);

    arma::fmat Mat;

    Mat << 1 << 0            <<   0            << 0 << arma::endr
        << 0 << cos(radians) << - sin(radians) << 0 << arma::endr
        << 0 << sin(radians) <<   cos(radians) << 0 << arma::endr
        << 0 << 0            <<   0            << 1;

    this->Mat_Rotate_OX = Mat;
}

void rotate_3d_class::Rotate_OY(float stopnie){

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

    float radians;
    radians = qDegreesToRadians(stopnie);

    arma::fmat Mat;

    Mat <<   cos(radians)<< 0 << sin(radians)  << 0 << arma::endr
        <<   0           << 1 <<  0            << 0 << arma::endr
        << - sin(radians)<< 0 <<  cos(radians) << 0 << arma::endr
        <<   0           << 0 <<  0            << 1;

    this->Mat_Rotate_OY = Mat;
}

void rotate_3d_class::Rotate_OZ(float stopnie){

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

    float radians;
    radians = qDegreesToRadians(stopnie);


    arma::fmat Mat;

    Mat << cos(radians) << - sin(radians) << 0 << 0 << arma::endr
        << sin(radians) <<   cos(radians) << 0 << 0 << arma::endr
        << 0            <<   0            << 1 << 0 << arma::endr
        << 0            <<   0            << 0 << 1;

    this->Mat_Rotate_OZ = Mat;
}

void rotate_3d_class::Pochyl_OX(float wspolczynnik_pochylenia_OX){

    arma::fmat Mat;

    Mat << 1 << wspolczynnik_pochylenia_OX << 0 << 0 << arma::endr
        << 0 << 1                          << 0 << 0 << arma::endr
        << 0 << 0                          << 1 << 0 << arma::endr
        << 0 << 0                          << 0 << 1;

    this->Mat_Pochyl_OX = Mat;

}

void rotate_3d_class::Pochyl_OY(float wspolczynnik_pochylenia_OY){

    arma::fmat Mat;

    Mat << 1                          << 0 << 0 << 0 << arma::endr
        << wspolczynnik_pochylenia_OY << 1 << 0 << 0 << arma::endr
        << 0                          << 0 << 1 << 0 << arma::endr
        << 0                          << 0 << 0 << 1;

    this->Mat_Pochyl_OY = Mat;
}

/*
void rotate_3d_class::Pochyl_OZ(float wspolczynnik_pochylenia_OZ){

    arma::fmat Mat;

    Mat << 1  << 0 << 0 << 0 << arma::endr
        << 0  << 1 << 0 << 0 << arma::endr
        << 0  << 0 << 1 << 0 << arma::endr
        << 0  << 0                          << 0 << 1;

    this->Mat_Pochyl_OZ = Mat;
}

*/

void rotate_3d_class::Skalowanie_OX(float dlugosc){

    arma::fmat Mat;

    Mat << dlugosc << 0 << 0 << 0 << arma::endr
        << 0       << 1 << 0 << 0 << arma::endr
        << 0       << 0 << 1 << 0 << arma::endr
        << 0       << 0 << 0 << 1;

    this->Mat_Size_OX = Mat;
}

void rotate_3d_class::Skalowanie_OY(float wysokosc){

    arma::fmat Mat;

    Mat << 1 << 0        << 0 << 0 << arma::endr
        << 0 << wysokosc << 0 << 0 << arma::endr
        << 0 << 0        << 1 << 0 << arma::endr
        << 0 << 0        << 0 << 1;

    this->Mat_Size_OY = Mat;
}

void  rotate_3d_class::execute(QSharedPointer<QList<QSharedPointer<punkt_struct>>> lista_ponktow, QSharedPointer<QList<QSharedPointer<punkt_struct>>> wynik_list)
{
    if(lista_ponktow->length() != wynik_list->length())
    {
        qDebug()<<"listy nie sa tej samej dlugasci";
        return;
    }

    arma::fmat wek;
    arma::fmat macierz;
    arma::fmat rotacja;

    for(int i = 0; i < lista_ponktow->length(); i++)
    {

        macierz << (*lista_ponktow)[i]->x << arma::endr
                << (*lista_ponktow)[i]->y << arma::endr
                << (*lista_ponktow)[i]->z << arma::endr
                << 1                      << arma::endr;

        rotacja = 
            this->Mat_Rotate_OX *
            this->Mat_Rotate_OY *
            this->Mat_Rotate_OZ *
            this->Mat_Pochyl_OX *
            this->Mat_Pochyl_OY *
            this->Mat_Size_OX *
            this->Mat_Size_OY;

        wek = rotacja*macierz;

        float px = wek(0,0);
        float py = wek(1,0);
        float pz = wek(2,0);

        (*wynik_list)[i]->x = wek(0,0);
        (*wynik_list)[i]->y = wek(1,0);
        (*wynik_list)[i]->z = wek(2,0);
    }

return;
}

QImage *rotate_3d_class::execute(QImage *obraz){

    int width_obraz = obraz->width();
    int height_obraz = obraz->height();

    int width_wynik;
    int height_wynik;

    arma::fmat wek;
    arma::fmat rotacja;

    {
        float szerokosc = width_obraz / 2;
        float wysokosc = height_obraz / 2;
        arma::fmat maciez;

        maciez << szerokosc <<   szerokosc << - szerokosc << - szerokosc << arma::endr
               << wysokosc  << - wysokosc  << - wysokosc  <<   wysokosc  << arma::endr
               << 0         <<   0         <<   0         <<   0         << arma::endr
               << 0         <<   0         <<   0         <<   0 ;
       //wspolrzedne rogow obrazu

        rotacja = 
             this->Mat_Rotate_OX *
             this->Mat_Rotate_OY *
             this->Mat_Rotate_OZ *
             this->Mat_Pochyl_OX *
             this->Mat_Pochyl_OY *
             this->Mat_Size_OX *
             this->Mat_Size_OY;

        wek = rotacja * maciez;

        rotacja = arma::inv(rotacja);

        float x1 = (wek.row(0).min() - 1) * 2 + 100;
        float x2 = (wek.row(0).max() + 1) * 2 + 100;
        float y1 = (wek.row(1).min() - 1) * 2 + 100;
        float y2 = (wek.row(1).max() + 1) * 2 + 100;

        width_wynik  = x2 - x1;
        height_wynik = y2 - y1;
    }


    QImage *wynik = new QImage(width_wynik, height_wynik, QImage::Format_RGB32);
    wynik->fill("black");

    arma::fmat  maciez;
    maciez << (float)( - width_wynik  / 2)  << arma::endr
           << (float)( - height_wynik / 2)  << arma::endr
           <<            0                  << arma::endr
           <<            0;

    arma::fmat dodaj_x;
    dodaj_x << 1 << arma::endr
            << 0 << arma::endr
            << 0 << arma::endr
            << 0 ;

    arma::fmat dodaj_y;
    dodaj_y << - width_wynik  << arma::endr
            <<   1            << arma::endr
            <<   0            << arma::endr
            <<   0;

    uchar *p = obraz -> bits();
    uchar *q = wynik -> bits();

    int szerokosc =  width_obraz / 2;
    int wysokosc  =  height_obraz / 2;

    for(int i = 0; i < height_wynik; i++){
        for(int j = 0; j < width_wynik; j++){
          
            wek = rotacja*maciez;
            maciez += dodaj_x;

            float px = wek(0,0) + szerokosc;
            float py = wek(1,0) + wysokosc;

            int x = px;
            int y = py;
            
            if(x >= 0)
            {                
                if(x <= width_obraz)
                {                    
                    if(y >= 0)
                    {                       
                        if(y < height_obraz)
                        { 
						    float fx = px - (int)px;
                            float fy = py - (int)py;

                            q[0]=(int)(
                                        (1 - fx) * (1 - fy) * (p + 4 * (x     +  y      * width_obraz))[0] +
                                        (fx)     * (1 - fy) * (p + 4 * (x + 1 +  y      * width_obraz))[0] +
                                        (1 - fx) * (fy)     * (p + 4 * (x     + (y + 1) * width_obraz))[0] +
                                        (fx)     * (fy)     * (p + 4 * (x + 1 + (y + 1) * width_obraz))[0]);

                            q[1]= (int)(
                                        (1 - fx) * (1 - fy) * (p + 4 * (x     +  y      * width_obraz))[1] +
                                        (fx)     * (1 - fy) * (p + 4 * (x + 1 +  y      * width_obraz))[1] +
                                        (1 - fx) * (fy)     * (p + 4 * (x     + (y + 1) * width_obraz))[1] +
                                        (fx)     * (fy)     * (p + 4 * (x + 1 + (y + 1) * width_obraz))[1]);

                            q[2]= (int)(
                                        (1 - fx) * (1 - fy) * (p + 4 * (x     +  y      * width_obraz))[2] +
                                        (fx)     * (1 - fy) * (p + 4 * (x + 1 +  y      * width_obraz))[2] +
                                        (1 - fx) * (fy)     * (p + 4 * (x     + (y + 1) * width_obraz))[2] +
                                        (fx)     * (fy)     * (p + 4 * (x + 1 + (y + 1) * width_obraz))[2]);

                        }
                    }
                }
            }
            q+=4;
        }
        maciez+=dodaj_y;
    }
    return wynik;
}
