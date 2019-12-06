#include <QPainter>
#include <QDebug>
#include <stack>
#include <qstack.h>
#include "types.h"
#include "trojkoty.h"
#include <qlist.h>
#include <krawedz.h>
#include <QListIterator>
#include <qmath.h>

bool compare(QSharedPointer<krawedz> p1, QSharedPointer<krawedz> p2)
{
    return p1->get_min_y() < p2->get_min_y();
}

bool compare2(QSharedPointer<krawedz> p1, QSharedPointer<krawedz> p2)
{
    return p1->get_aktualny_x() < p2->get_aktualny_x();
}

QImage *texturowanie(QImage *obraz, QList<QSharedPointer<krawedz>> list, int  r, int g, int b)
{
    if(obraz->isNull())
        return new QImage();
    QImage *wynik;
    wynik = new QImage(*obraz);

    //jezeli lista ma mniej niz 3 krawedzie zakoncz alogorytm
    if(list.length()<2){
        return wynik;
    }
    std::sort(list.begin(),list.end(),compare);

    QList<QSharedPointer<krawedz>> pomocnicza;
    QListIterator<QSharedPointer<krawedz>> iterator(list);

    uchar *p = wynik->bits();
    int width = obraz->width();
    int height = obraz->height();

    QSharedPointer<krawedz> nastepna = iterator.next();
    int dodana = 1;
    int k = 1;

    for(int i = 0; i < height; i++){
        //dodaje krawedze zaczynajace sie na odpowiedniej  wysokosci

        if(dodana == 1)
        {
            while(nastepna->get_min_y() < = i){

                pomocnicza.push_back(nastepna);

                if (iterator.hasNext())
                {
                    nastepna = (iterator.next());
                }
                else
                {
                    dodana = 0;
                    break;
                }
            }
        }

        if(height != 0)
        {
            for(int j = 0; j < pomocnicza.length(); j++)
            {
                //mozliwy blad z dokladnoscia z powodu dzialaniam i na intach i floatach
                if(pomocnicza[j]->aktualizuj() != 1)
                {
                    //usuwa krawedzie narysowane
                    pomocnicza[j]->resetuj();
                    pomocnicza.removeAt(j);
                    j--;
                }
            }
        }
		
        std::sort(pomocnicza.begin(), pomocnicza.end(), compare2);

        if(pomocnicza.length() == 0)
        {
           p += 4 * width;
        }
        else
        {
            //teraz texturowanie
            int j = 0;
            int x;
			
            for(int z = 0; z < pomocnicza.length() - 1  && j < width; z++)
            {
                x = pomocnicza[z]->get_aktualny_x();

                if (x > = 0)
                {
                    if(x > = width)
                    {
                        p += 4 * (width - j);
                        break;
                    }
                    else
                    {
                        p += 4 * (x - j);
                        j = x;
                    }
                }

                z++;

                x = pomocnicza[z]->get_aktualny_x();

                if (x > = 0)
                {
					if(x > width)
                    {
                       x = width;
                    }		
                    
					while(j < = x)
                    {
                        p[0] = r;
                        p[1] = g;
                        p[2] = b;
                        p += 4;
                        j++;
                    }
                }
            }
            p += 4 * (width - j);
        }
    }
    return wynik;
}


QImage *texturowanie_trojkatow(QImage *obraz, QList<QSharedPointer<krawedz>> list, int r, int g, int b)
{
    if(obraz->isNull())
        return new QImage();

    QImage *wynik;
    wynik = new QImage(*obraz);

    //jezeli lista ma mniej niz 3 krawedzie zakoncz alogorytm
    if(list.length()<2){
        return wynik;
    }

    list[0]->resetuj();
    list[1]->resetuj();
    list[2]->resetuj();

    int i = 0;

    //wykrywa poziome krawedzie
    if(list[0]-> get_min_y() + 1 > = list[0]-> get_max_y())
    {
        i++;
    }

    if(list[1]-> get_min_y() + 1 > = list[1]-> get_max_y())
    {
        i += 2;
    }

    if(list[2]-> get_min_y() + 1 > = list[2]-> get_max_y())
    {
        i += 4;
    }

    uchar *p = wynik->bits();
    int width = obraz->width();
    int height = obraz->height();


    if(i == 7){
        return wynik;
    }

    QList<QSharedPointer<krawedz>> pomocnicza;

    if(i == 0){
       std::sort(list.begin(), list.end(), compare);
       pomocnicza.push_back(list[0]);
       pomocnicza.push_back(list[1]);
    }

    if(i == 1){

       pomocnicza.push_back(list[1]);
       pomocnicza.push_back(list[2]);
        std::sort(pomocnicza.begin(), pomocnicza.end(), compare);
    }

    if(i == 2){
       pomocnicza.push_back(list[0]);
       pomocnicza.push_back(list[2]);
        std::sort(pomocnicza.begin(), pomocnicza.end(), compare);
    }

    if(i == 4){
        pomocnicza.push_back(list[0]);
        pomocnicza.push_back(list[1]);
        std::sort(pomocnicza.begin(), pomocnicza.end(), compare);
    }

    int w = 0;
    int k = 0;

    if(pomocnicza[1]->get_min_y() < - height / 2)
    {
        //mozliwy problem na krawedzi obrazow;
        if(pomocnicza[1]->get_max_y()< - height / 2)
        {
            if(i == 0)
            {
                pomocnicza.removeLast();
                pomocnicza.push_back(list[2]);
                k += 1;
            }
            else
            {
                //trojkat poza obrazem
                return wynik;
            }
        }
        else
        {
            while(pomocnicza[1]->get_aktualny_y()< - height / 2)
            {
                pomocnicza[1]->aktualizuj();
            }
            w = 1;
        }
    }

    if(pomocnicza[0]->get_min_y() < - height / 2)
    {
        //mozliwy problem na krawedzi obrazow;
        if(pomocnicza[0]->get_max_y() < - height / 2)
        {
            if(i == 0)
            {
                if(k == 0)
                {
                    pomocnicza.removeFirst();
                    pomocnicza.push_back(list[2]);
                    k += 2;
                }
                else
                {
                    //trojkat poza obrazem
                    return wynik;
                }
            }
            else
            {
                //trojkat poza obrazem
                return wynik;
            }
        }
        else
        {
            while(pomocnicza[0]->get_aktualny_y()< - height / 2)
            {
                pomocnicza[0]->aktualizuj();
            }
            w = 1;
        }
    }

    if(pomocnicza.length() == 1)
    {
        return wynik;
    }

    i += k;
   
    int n = 0;
    if(w != 1){
        n = pomocnicza[0]->get_min_y() + height / 2;
        p += 4 * width * n;       
    }

    for(; n < height; n++)
    {
        std::sort(pomocnicza.begin(), pomocnicza.end(), compare2);
        {
            //teraz texturowanie
            int j = 0;
            int x;

            //nie malowany fragment;
            x = pomocnicza[0]->get_aktualny_x() + width / 2;

            if(x > = width)
            {
               p += 4 * (width - j);
            }
            else
            {
                if (x > = 0)
                {
                    p += 4 * (x - j);
                    j = x;
                }
                x = pomocnicza[1]->get_aktualny_x() + width / 2;

                if (x > = 0)
                {                   
                    if(x > width)
                    {                        
                        //przyciecie do lini                       
                        x = width;
                    }

                    while(j < = x)
                    {
                        p[0] = r;
                        p[1] = g;
                        p[2] = b;
                        p += 4;
                        j++;
                    }
                }                
                p += 4 * (width - j);
            }
        }

        for(int j = 0;j < pomocnicza.length(); j++)
        {
            //mozliwy blad z dokladnoscia z powodu dzialaniam i na intach i floatach
            if(pomocnicza[j]->aktualizuj() != 1)
            {
                //usuwa krawedzie narysowane
                pomocnicza.removeAt(j);
                if(i == 0)
				{
					//mozliwa koniecznosc aktualizacji dodanej listy
                    pomocnicza.push_back(list[2]);
                    i = 7;//nastepne usuniecie krawedzi konczy rysowanie trojkata
                }
                else
                {
                     return wynik;
                }                
                j--;
            }
        }
    }
    
    return wynik;
}

QImage *texturowanie_trojkatow(QImage *obraz, QList<QSharedPointer<krawedz>> list,  QImage *textura, QList<QSharedPointer<punkt_struct>> wspolrzedne)
{
    if(obraz->isNull())
        return new QImage();

    QImage *wynik;
    wynik = new QImage(*obraz);

    //jezeli lista ma mniej niz 3 krawedzie zakoncz alogorytm
    if(list.length() < 2){
        return wynik;
    }

    list[0]->resetuj();
    list[1]->resetuj();
    list[2]->resetuj();

    int i = 0;

    //wykrywa poziome krawedzie
    if(list[0]-> get_min_y() + 1 > = list[0]-> get_max_y())
    {
        i++;
    }

    if(list[1]-> get_min_y() + 1 > = list[1]-> get_max_y())
    {
        i += 2;
    }

    if(list[2]-> get_min_y() + 1 > = list[2]-> get_max_y())
    {
        i += 4;
    }

    uchar *p = wynik->bits();   
    int width = obraz->width();
    int height = obraz->height();

    uchar *q = textura->bits();
    int width_textury = textura->width();
    int height_textury = textura->height();


    if(i == 7){
        return wynik;
    }

    punkt_struct *p1 = &(*(list[0]->get_p1()));
    punkt_struct *p2 = &(*(list[1]->get_p1()));
    punkt_struct *p3 = &(*(list[2]->get_p1()));

    QList<QSharedPointer<krawedz>> pomocnicza;

    if(i == 0)
	{
        std::sort(list.begin(), list.end(), compare);
        pomocnicza.push_back(list[0]);
        pomocnicza.push_back(list[1]);
    }

    if(i == 1)
	{
        pomocnicza.push_back(list[1]);
        pomocnicza.push_back(list[2]);
        std::sort(pomocnicza.begin(), pomocnicza.end(), compare);
    }

    if(i == 2)
	{
        pomocnicza.push_back(list[0]);
        pomocnicza.push_back(list[2]);
        std::sort(pomocnicza.begin(), pomocnicza.end(), compare);
    }

    if(i == 4){
        pomocnicza.push_back(list[0]);
        pomocnicza.push_back(list[1]);
        std::sort(pomocnicza.begin(), pomocnicza.end(), compare);
    }

    int w = 0;
    int k = 0;

    if(pomocnicza[1]->get_min_y()< - height / 2)
    {
        //mozliwy problem na krawedzi obrazow;
        if(pomocnicza[1]->get_max_y()< - height / 2)
        {
            if(i == 0)
            {
                pomocnicza.removeLast();
                pomocnicza.push_back(list[2]);
                k += 1;
            }
            else
            {
                //trojkat poza obrazem
                return wynik;
            }
        }
        else
        {
            while(pomocnicza[1]->get_aktualny_y()< - height / 2)
            {
                pomocnicza[1]->aktualizuj();
            }
            w = 1;
        }
    }

    if(pomocnicza[0]->get_min_y() < - height / 2)
    {
        //mozliwy problem na krawedzi obrazow;
        if(pomocnicza[0]->get_max_y()< - height / 2)
        {
            if(i == 0)
            {
                if(k == 0)
                {
                    pomocnicza.removeFirst();
                    pomocnicza.push_back(list[2]);
                    k += 2;
                }
                else
                {
                    //trojkat poza obrazem
                    return wynik;
                }
            }
            else
            {
                //trojkat poza obrazem
                return wynik;
            }
        }
        else
        {
            while(pomocnicza[0]->get_aktualny_y()< - height / 2)
            {
                pomocnicza[0]->aktualizuj();
            }
            w = 1;
        }
    }

    if(pomocnicza.length() == 1)
    {
        return wynik;
    }
    
    i += k;
   
    int n = 0;
    if(w != 1){
        n = pomocnicza[0]->get_min_y() + height / 2;
        p += 4 * width * n;       
    }

    punkt_struct *punkt = new  punkt_struct();

    for(; n < height - 1; n++)
    {
        //glowna pentla rysujaca
        //dodaje krawedze zaczynajace sie na odpowiedniej  wysokosci
        std::sort(pomocnicza.begin(), pomocnicza.end(), compare2);

        {
            //teraz texturowanie
            int j = 0;
            int x;

            //nie malowany fragment;
            x = pomocnicza[0]->get_aktualny_x() + width / 2;

            if(x > = width)
            {
                p += 4 * (width - j);

            }
            else
            {
                if (x > = 0)
                {
                    p += 4 * (x - j);
                    j = x;
                }
                x = pomocnicza[1]->get_aktualny_x() + width / 2;

                if (x > = 0)
                {
                    if(x > width)
                    {                        
                        //przyciecie do lini                      
                        x = width;
                    }

                    fpunkt_struct map;

                    while(j < = x)
                    {                       

                        punkt->x = j - width / 2;
                        punkt->y = n - height / 2;

                        float abc = pole_trojkata_2d(p1, p2, p3);
                        float   r = pole_trojkata_2d(punkt, p2, p3) / abc;
                        float   s = pole_trojkata_2d(p1, punkt, p3) / abc;
                        float   v = 1.0f - r - s;

                        map.x = wspolrzedne[0]->x * r + wspolrzedne[1]->x * s + wspolrzedne[2]->x * v;
                        map.y = wspolrzedne[0]->y * r + wspolrzedne[1]->y * s + wspolrzedne[2]->y * v;
                        map.z = wspolrzedne[0]->z * r + wspolrzedne[1]->z * s + wspolrzedne[2]->z * v;

                        int qx = (int)map.x;
                        int qy = (int)map.y;

                        float fx = map.x - (int)map.x;
                        float fy = map.y - (int)map.y;

                        if(!(map.x < 0 || map.x + 1.0f >= width_textury || map.y < 0 || map.y + 1.0f >= height_textury))
                        {
                            
                            p[0] = (int)(
                                    (1 - fx) * (1 - fy) * (q + 4 * (qx     + (qy)     * width_textury))[0] + 
                                    (fx)     * (1 - fy) * (q + 4 * (qx + 1 + (qy)     * width_textury))[0] + 
                                    (1 - fx) * (fy)     * (q + 4 * (qx     + (qy + 1) * width_textury))[0] + 
                                    (fx)     * (fy)     * (q + 4 * (qx + 1 + (qy + 1) * width_textury))[0]);

                            p[1] = (int)(
                                    (1 - fx) * (1 - fy) * (q + 4 * (qx     +  qy      * width_textury))[1] + 
                                    (fx)     * (1 - fy) * (q + 4 * (qx + 1 +  qy      * width_textury))[1] + 
                                    (1 - fx) * (fy)     * (q + 4 * (qx     + (qy + 1) * width_textury))[1] + 
                                    (fx)     * (fy)     * (q + 4 * (qx + 1 + (qy + 1) * width_textury))[1]);
									
                            p[2] = (int)(
                                    (1 - fx) * (1 - fy) * (q + 4 * (qx     +  qy      * width_textury))[2] + 
                                    (fx)     * (1 - fy) * (q + 4 * (qx + 1 +  qy      * width_textury))[2] + 
                                    (1 - fx) * (fy)     * (q + 4 * (qx     + (qy + 1) * width_textury))[2] + 
                                    (fx)     * (fy)     * (q + 4 * (qx + 1 + (qy + 1) * width_textury))[2]);
                        }
                        else
                        {
                            p[0] = 0;
                            p[1] = 0;
                            p[2] = 0;
                        }
						
                        p += 4;
                        j++;
                    }
                }
                p += 4 * (width - j);
            }
        }

        for(int j = 0;j < pomocnicza.length(); j++)
        {

            if(pomocnicza[j]->aktualizuj() != 1)
            {
                //usuwa krawedzie narysowane

                pomocnicza.removeAt(j);
                if(i == 0){					
                    //mozliwa koniecznosc aktualizacji dodanej listy					
                    pomocnicza.push_back(list[2]);
                    i = 7;//nastepne usuniecie krawedzi konczy rysowanie trojkata
                }
                else
                {
                    return wynik;
                }                
                j--;
            }
        }
    }    
    return wynik;
}


QImage *erozja(QImage *obraz){

    QImage *wynik;
    wynik = new QImage(*obraz);
    wynik->fill(Qt::white);

    int width = obraz->width();
    int height = obraz->height();

    uchar *p = obraz->bits();
    uchar *q = wynik->bits();



    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if((q[0] != 0||q[1] != 0||q[2] != 0)){

                uchar *z;

                if(i != 0 && j != 0){
                    z = p - 4 - 4 * width;
                    if(q[0] > z[0]){q[0] = z[0];}
                    if(q[1] > z[1]){q[1] = z[1];}
                    if(q[2] > z[2]){q[2] = z[2];}
                }

                if(i != 0){
                    z = p - 4 * width;
                    if(q[0] > z[0]){q[0] = z[0];}
                    if(q[1] > z[1]){q[1] = z[1];}
                    if(q[2] > z[2]){q[2] = z[2];}
                }

                if(i != 0 && j != width - 1){
                    z = p + 4 - 4 * width;
                    if(q[0] > z[0]){q[0] = z[0];}
                    if(q[1] > z[1]){q[1] = z[1];}
                    if(q[2] > z[2]){q[2] = z[2];}
                }


                if(j != 0){
                    z = p - 4;
                    if(q[0] > z[0]){q[0] = z[0];}
                    if(q[1] > z[1]){q[1] = z[1];}
                    if(q[2] > z[2]){q[2] = z[2];}
                }

                if(j != width - 1){
                    z = p + 4;
                    if(q[0] > z[0]){q[0] = z[0];}
                    if(q[1] > z[1]){q[1] = z[1];}
                    if(q[2] > z[2]){q[2] = z[2];}
                }

                if(i != height - 1 && j != 0){
                    if(q[0] > z[0]){q[0] = z[0];}
                    if(q[1] > z[1]){q[1] = z[1];}
                    if(q[2] > z[2]){q[2] = z[2];}
                     z = p - 4 + 4 * width;
                }

                if(i != height - 1){
                    z = p + 4 * width;
                    if(q[0] > z[0]){q[0] = z[0];}
                    if(q[1] > z[1]){q[1] = z[1];}
                    if(q[2] > z[2]){q[2] = z[2];}
                }

                if(i != height - 1 && j != width - 1){
                     z = p + 4 + 4 * width;
                     if(q[0] > z[0]){q[0] = z[0];}
                     if(q[1] > z[1]){q[1] = z[1];}
                     if(q[2] > z[2]){q[2] = z[2];}
                }
            }
			p = p + 4;
			q = q + 4;
        }
    }
    return wynik;
}

QImage *dylatacja(QImage *obraz){

    QImage *wynik;
    wynik = new QImage( *obraz);
    wynik->fill(Qt::black);

    int width = obraz->width();
    int height = obraz->height();

    uchar *p = obraz->bits();
    uchar *q = wynik->bits();

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if((q[0] != 255 || q[1] != 255 || q[2] != 255)){

                uchar * z;

                if(i != 0 && j != 0){
                    z = p - 4 - 4 * width;
                    if(q[0] < z[0]){q[0] = z[0];}
                    if(q[1] < z[1]){q[1] = z[1];}
                    if(q[2] < z[2]){q[2] = z[2];}
                }

                if(i != 0){
                    z = p - 4 * width;
                    if(q[0] < z[0]){q[0] = z[0];}
                    if(q[1] < z[1]){q[1] = z[1];}
                    if(q[2] < z[2]){q[2] = z[2];} 
                }

                if(i != 0 && j != width - 1){
                    z = p + 4 - 4 * width;
                    if(q[0] < z[0]){q[0] = z[0];}
                    if(q[1] < z[1]){q[1] = z[1];}
                    if(q[2] < z[2]){q[2] = z[2];}
                }

                if(j != 0){
                    z = p - 4;
                    if(q[0] < z[0]){q[0] = z[0];}
                    if(q[1] < z[1]){q[1] = z[1];}
                    if(q[2] < z[2]){q[2] = z[2];}
                }

                if(j != width - 1){
                    z = p + 4;
                    if(q[0] < z[0]){q[0] = z[0];}
                    if(q[1] < z[1]){q[1] = z[1];}
                    if(q[2] < z[2]){q[2] = z[2];}

                }

                if(i != height - 1 && j != 0){
                    if(q[0] < z[0]){q[0] = z[0];}
                    if(q[1] < z[1]){q[1] = z[1];}
                    if(q[2] < z[2]){q[2] = z[2];}
                    z = p - 4 + 4 * width;
                }
				
                if(i != height - 1){
                    z = p + 4 * width;
                    if(q[0] < z[0]){q[0] = z[0];}
                    if(q[1] < z[1]){q[1] = z[1];}
                    if(q[2] < z[2]){q[2] = z[2];}
                }
				
                if(i != height - 1 && j != width - 1){
                     z = p + 4 + 4 * width;
                     if(q[0] < z[0]){q[0] = z[0];}
                     if(q[1] < z[1]){q[1] = z[1];}
                     if(q[2] < z[2]){q[2] = z[2];}
                }
            }
			p = p + 4;
			q = q + 4;
        }
    }
    return wynik;
}

kolor takePixel(QImage *buf, int x, int y)
{
    kolor rgb;
    int w = buf->width();
    int h = buf->height();
    if(x < w && x >= 0 && y < h && y >= 0)
    {
        uchar *p = buf->bits() + 4 * (y * w + x);
        rgb.b = p[0];
        rgb.g = p[1];
        rgb.r = p[2];
    }
    return rgb;
}

void putPixel(QImage *buf, int x, int y, int r, int g, int b)
{
    int w = buf->width();
    int h = buf->height();

    if(x < w && x >= 0 && y < h && y >= 0)
    {
        uchar *p = buf->bits() + 4 * (y * w + x);
        p[0] = b;
        p[1] = g;
        p[2] = r;
    }
}

void wstaw8ponktow(QImage *buf, int x1, int y1, int x, int y, int r, int g, int b)
{
    putPixel(buf, x1 + x, y1 + y , r, g, b);
    putPixel(buf, x1 + x, y1 - y , r, g, b);
    putPixel(buf, x1 - x, y1 + y , r, g, b);
    putPixel(buf, x1 - x, y1 - y , r, g, b);
    putPixel(buf, x1 + y, y1 + x , r, g, b);
    putPixel(buf, x1 + y, y1 - x , r, g, b);
    putPixel(buf, x1 - y, y1 + x , r, g, b);
    putPixel(buf, x1 - y, y1 - x , r, g, b);
}

void wstaw4ponktow(QImage *buf, int x1, int y1, int x, int y, int r, int g, int b)
{
    putPixel(buf, x1 + x, y1 + y, r, g, b);
    putPixel(buf, x1 + x, y1 - y, r, g, b);
    putPixel(buf, x1 - x, y1 + y, r, g, b);
    putPixel(buf, x1 - x, y1 - y, r, g, b);
}

void drawLine(QImage *buf, int x1, int y1, int x2, int y2, int r, int g, int blue)
{
    if(x1 > x2)
    {
       int i = x1;
       x1 = x2;
       x2 = i;
       i = y1;
       y1 = y2;
       y2 = i;
    }
    int k = y1 - y2;
    if(k < 0)
       k = - k;

    if(x2 - x1 < k)
    {
        if(y1 > y2)
         {
            int i = x1;
            x1 = x2;
            x2 = i;
            i = y1;
            y1 = y2;
            y2 = i;
        }

        float a = (float(x1) - x2) / (y1 - y2);
        float b = x1 - a * y1;
        for(int y = y1; y <= y2; y++)
        {
            float x = (a * y + b);
            putPixel(buf, x, y, r, g, blue);
        }
    }
    else
    {
        float a = (float(y1) - y2) / (x1 - x2);
        float b = y1 - a * x1;
        for(int x = x1; x <= x2; x++)
        {
            float y = (a * x + b);
            putPixel(buf, x, y, r, g, blue);
        }
    }
}

void draw4Line(QImage *buf, int xx, int yy, int x1, int y1, int x2, int y2, int r, int g, int blue)
{
    if(x1 > x2)
    {
       int i = x1;
       x1 = x2;
       x2 = i;
       i = y1;
       y1 = y2;
       y2 = i;
    }
    int k = y1 - y2;
    if(k < 0)
       k = - k;

    if(x2 - x1 < k)
    {
        if(y1 > y2)
         {
            int i = x1;
            x1 = x2;
            x2 = i;
            i = y1;
            y1 = y2;
            y2 = i;
        }

        float a = (float(x1) - x2) / (y1 - y2);
        float b = x1 - a * y1;
        for(int y = y1; y <= y2; y++)
        {
            float x = (a * y + b);
            wstaw4ponktow(buf, xx, yy, x, y, r, g, blue);
        }
    }
    else
    {
        float a = (float(y1) - y2) / (x1 - x2);
        float b = y1 - a * x1;
        for(int x = x1; x <= x2; x++)
        {
            float y = (a * x + b);
            wstaw4ponktow(buf, xx, yy, x, y, r, g, blue);
        }
    }
}

void flaga(QImage *buf, int x1, int y1, int x2, int y2)
{
    if(x1 < x2 && y1 < y2)
    {
        for(int i = x1; i < x2; i++)
        {
            for(int j = y1; j < y2; j++)
            {
                if(j < y2 / 2 + y1 / 2)
                {
                    putPixel(buf, i, j, 255, 255, 255);
                }
                else
                {
                    putPixel(buf, i, j, 255, 0, 0);
                }
            }
        }
    }
}

void narysuj_krzywa_beziera(QImage *buf, QList<punkt_struct> punktList, int liczba_odcinkow){
    float n;
    n = punktList.length();
    if(n < 4)
    {
        return;
    }

    if(liczba_odcinkow == 0)
    {
        return;
    }

    int ar = 12;
    int ag = 34;
    int ab = 123;

    for (int j = 0; j < n - 1; j++){
        drawLine(buf, punktList[j].x, punktList[j].y ,punktList[j + 1].x, punktList[j + 1].y, ar, ag, ab);
    }

    float  x = 1 / (float)liczba_odcinkow;
    punkt_struct p = punktList[0];
    punkt_struct q;
    float i = 0;

    for (float z = 0; z < = liczba_odcinkow; z++) {

    float t = z * x;

    q.x = (1 - t) * (1 - t) * (1 - t) *     punktList[i    ].x + 
                3 * (1 - t) * (1 - t) * t * punktList[i + 1].x + 
                3 * (1 - t) * t       * t * punktList[i + 2].x + 
                     t      * t       * t * punktList[i + 3].x;


    q.y = (1 - t) * (1 - t) * (1 - t) *       punktList[i    ].y + 
                3 * (1 - t) * (1 - t) * t *   punktList[i + 1].y + 
                3 * (1 - t) * t       * t *   punktList[i + 2].y + 
                     t      * t       * t *   punktList[i + 3].y;

    drawLine(buf, p.x, p.y, q.x, q.y, ar, ag, ab);
    p = q;

    }
}

void narysuj_krzywa_sklejana(QImage *buf , QList<QSharedPointer<punkt_struct>> punktList, int liczba_odcinkow)
{
    float n;
    n = punktList.length();
    if(n < 4)
    {
        return;
    }

    if(liczba_odcinkow == 0)
    {
        return;
    }

    int ar = 12;
    int ag = 34;
    int ab = 123;

    for (int j = 0; j < n - 1; j++){
        drawLine(buf, punktList[j]->x, punktList[j]->y, punktList[j + 1]->x, punktList[j + 1]->y, ar, ag, ab);
    }

    float  x = 1 / ((float)liczba_odcinkow);
    punkt_struct p;
    p.x = punktList[0]->x;
    p.y = punktList[0]->y;
    punkt_struct q;
    float i = 0;

    while ( i < n - 3) {
        for (float z = 0; z <= liczba_odcinkow; z++) {

        float t = z * x;

        q.x = 
                ((       - t * t * t + 3 * t * t - 3 *   t + 1) / 6) * punktList[i    ]->x + 
                ((   3 *   t * t * t - 6 * t * t + 4          ) / 6) * punktList[i + 1]->x + 
                (( - 3 *   t * t * t + 3 * t * t + 3 *   t + 1) / 6) * punktList[i + 2]->x + 
                ((         t * t * t                          ) / 6) * punktList[i + 3]->x;
        q.y = 
                ((       - t * t * t + 3 * t * t - 3 * t + 1) / 6) *   punktList[i    ]->y + 
                ((   3 *   t * t * t - 6 * t * t + 4        ) / 6) *   punktList[i + 1]->y + 
                (( - 3 *   t * t * t + 3 * t * t + 3 * t + 1) / 6) *   punktList[i + 2]->y + 
                ((         t * t * t                        ) / 6) *   punktList[i + 3]->y;
        drawLine(buf, p.x, p.y, q.x, q.y, ar, ag, ab);
        p = q;
       }
    i += 1;

    }
}

/* 
void narysuj_krzywa(QImage *buf){
    double t = 1;
    float n = 3;
    int ar = 12;
    int ag = 34;
    int ab = 123;
    punktcik P[4];
    P[0] = nowy_punkt(100, 100);
    P[1] = nowy_punkt(300, 300);
    P[2] = nowy_punkt(500, 100);
    P[3] = nowy_punkt(700, 550);

    punktcik D[4];
    D[0] = P[0];
    D[1] = P[1];
    D[2] = P[2];
    D[3] = P[3];

    punktcik Q[4];

    //drawLine(P[0].x, P[0].y, P[1].x, P[1].y, ar, ag, ab);
    //drawLine(P[1].x, P[1].y, P[2].x, P[2].y, ar, ag, ab);
    //drawLine(P[2].x, P[2].y, P[3].x, P[3].y, ar, ag, ab);
    //drawLine(P[3].x, P[3].y, P[4].x, P[4].y, ar, ag, ab);

    float  x = 1 / 100.0;

    for (float z = 0; z <= 100; ++z) {
        float t = z * x;

        for (int i = 0; i <= n; i++){
            Q[i] = P[i];

            for (int k = 1; k <= n; k++){
                for (int g = 0; g <= n - k; g++){
                    Q[g].x = (1 - t) * Q[g].x + t * Q[g + 1].x;
                    Q[g].y = (1 - t) * Q[g].y + t * Q[g + 1].y;
                }
            }
        }

        drawLine(buf, Q[0].x, Q[0].y, Q[1].x, Q[1].y, ar, ag, ab);
        drawLine(buf, Q[1].x, Q[1].y, Q[2].x, Q[2].y, ar, ag, ab);
        drawLine(buf, Q[2].x, Q[2].y, Q[3].x, Q[3].y, ar, ag, ab);


        drawLine(buf, Q[0].x, Q[0].y, D[0].x, D[0].y, ar, ag, ab);
        //drawLine(Q[1].x, Q[1].y, D[1].x, D[1].y, ar, ag, ab);
        //drawLine(Q[2].x, Q[2].y, D[2].x, D[2].y, ar, ag, ab);
        //drawLine(Q[3].x, Q[3].y, D[3].x, D[3].y, ar, ag, ab);

        D[0] = Q[0];
        D[1] = Q[1];
        D[2] = Q[2];
        D[3] = Q[3];

    }

    P[0] = nowy_punkt(100, 100);
    P[1] = nowy_punkt(300, 300);
    P[2] = nowy_punkt(500, 600);
    P[3] = nowy_punkt(200, 550);

    //drawElipsa(punkt.x, punkt.y, sqrt((punkt.x - e->x()) * (punkt.x - e->x()) + (punkt.y - e->y()) * (punkt.y - e->y())), sqrt((punkt.x - e->x()) * (punkt.x - e->x()) + (punkt.y - e->y()) * (punkt.y - e->y())) / 2, ar, ag, ab);
    //flood_fill(punkt,nowy_kolor(ar,ag,ab));

    //drawLine(punkt.x, punkt.y, e->x(), e->y(), ar, ag, ab);

}
*/ 

void drawCirkle(QImage *buf, int x1, int y1, int r, int red, int g, int b)
{
    int x, y, d;
    x = 0;
    y = r;
    d = 1 - r;
    wstaw8ponktow(buf, x1, y1, x, y, red, g, b);
    while (y > x)
    {
        if (d < 0)
        {
            d = d + 2 * x + 3;
            x++;
        }
        else
        {
            d = d + 2 * (x - y) + 5;
            x++;
           y--;
        }
        wstaw8ponktow(buf, x1, y1, x, y, red, g, b);
    }
}

void drawCirkle2(QImage *buf, int x1, int y1, int r, int red, int  g, int b, int dokladnsc)
{
    double p = dokladnsc;

    double x, y;
    x = 0;
    y = r;

    wstaw8ponktow(buf, x1, y1, x, y, red, g, b);

    for(double i = 0; i < p + 1; i++)
    {
        drawLine(buf, x1 + x, y1 + y, x1 + sin(i * M_PI/(4 * p)) * r, y1 + cos(i * M_PI/(4 * p)) * r, red, g, b);
        draw4Line(buf, x1, y1, x, y, sin(i * M_PI/(4 * p)) * r, cos(i * M_PI/(4 * p)) * r, red, g, b);
        x = sin(i * M_PI/(4 * p)) * r;
        y = cos(i * M_PI/(4 * p)) * r;
    }
}

void drawElipsa(QImage *buf, int x1, int y1, int r, int r2 , int red, int  g, int b, int dokladnsc)
{
    double p = dokladnsc;

    double x, y;
    x = 0;
    y = r2;


    for(double i = 0; i < 2 * p + 1; i++)
    {        
        draw4Line(buf, x1, y1, x, y, sin(i * M_PI/(4 * p)) * r, cos(i * M_PI/(4 * p)) * r2, red, g, b);
        x = sin(i * M_PI/(4 * p)) * r;
        y = cos(i * M_PI/(4 * p)) * r2;
    }

}

void rgb_to_hsv(float r, float g, float b, float &h, float &s, float &v){
    float K = 0.f;
    if (g < b)
    {
        std::swap(g, b);
        K = - 1.f;
    }
    if (r < g)
    {
        std::swap(r, g);
        K = - 2.f / 6.f - K;
    }
    float chroma = r - std::min(g, b);
    h = fabs(K + (g - b) / (6.f *   chroma + 1e - 20f));
    s = chroma / (r + 1e - 20f);
    v = r;
}

void hsv_to_rgb(float h, float s, float v, float &r, float &g, float &b)
{

}

bool kolor_compare(kolor a,kolor b)
{   
    if(a.r != b.r)
       if(a.g != b.g)
           if(a.b != b.b)
               return 1;
	return 0;	   
}

void flood_fill(QImage *buf, punktcik punkty, kolor nowy_kolor){
    std::stack <punktcik> Q;
    if (kolor_compare(takePixel(buf,punkty.x, punkty.y), nowy_kolor)) return;
        Q.push(punkty);
		
    while (!Q.empty()) {
        punkty = Q.top();
        Q.pop();
        
        //Zdejmij ze stosu ostatni piksel //załóżmy, że jest to (x,y);
        if (!kolor_compare(takePixel(buf, punkty.x, punkty.y), nowy_kolor)) {
            int w = punkty.x;
			int e = punkty.x;
            while ((!kolor_compare(takePixel(buf, w, punkty.y), nowy_kolor)) && (w)) {w--;}
            while ((!kolor_compare(takePixel(buf, e, punkty.y), nowy_kolor)) && (e < 1000)){e++;}
            for (int i = w + 1; i < e; i++)
                putPixel(buf, i, punkty.y, nowy_kolor.r, nowy_kolor.g, nowy_kolor.b);
            for (int i = w + 1; i < e; i++) {
                if (!kolor_compare(takePixel(buf, i, punkty.y + 1), nowy_kolor)){} //Q.push(nowy_punkt(i,punkty.y + 1));
                if (!kolor_compare(takePixel(buf, i, punkty.y - 1), nowy_kolor)){} //Q.push(nowy_punkt(i,punkty.y - 1));
            } 
        }
    }
    return;
}

void flood_fill(QImage *obraz, punkt_struct punkt, kolor stary_kolor, kolor nowy_kolor) {
    QStack<punkt_struct> stos;
    if (!kolor_compare(takePixel(obraz, punkt.x, punkt.y), stary_kolor))
    {
        return;
    }
    stos.push(punkt);

    while (!stos.empty()) {

        stos.pop();

        if (kolor_compare(takePixel(obraz, punkt.x, punkt.y), stary_kolor))
        {
            int w = punkt.x;
            int e = punkt.x;

            while (kolor_compare(takePixel(obraz, w, punkt.y), stary_kolor))
            {
                w--;
            }
            while (kolor_compare(takePixel(obraz, e, punkt.y), stary_kolor))
            {
                e++;
            }
            for (int i = w + 1; i < e; i++)
            {
                putPixel(obraz, i, punkt.y, nowy_kolor.r, nowy_kolor.g, nowy_kolor.b);
            }
            for (int i = w + 1; i < e; i++)
            {
                if (kolor_compare(takePixel(obraz, i, punkt.y + 1), stary_kolor))
                {
                    stos.push(nowy_punkt_struct(i, punkt.y + 1));
                }
                if (kolor_compare(takePixel(obraz, i, punkt.y - 1), stary_kolor))
                    stos.push(nowy_punkt_struct(i, punkt.y - 1));
            }
        }
    }
    return;
}

