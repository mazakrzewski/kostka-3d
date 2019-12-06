
#import "types.h"
#include <qmath.h>
#include<QSharedPointer>
#include<krawedz.h>

punkt_struct nowy_punkt_struct(int x,int y){
    punkt_struct nowy_punkt_struct;
    nowy_punkt_struct.x = x;
    nowy_punkt_struct.y = y;
    return nowy_punkt_struct;
}

punkt_struct nowy_punkt_struct(int x, int y, int z){
    punkt_struct nowy_punkt_struct;
    nowy_punkt_struct.x = x;
    nowy_punkt_struct.y = y;
    nowy_punkt_struct.z = z;
    return nowy_punkt_struct;
}

fpunkt_struct nowy_fpunkt_struct(int x,int y){
    fpunkt_struct nowy_fpunkt_struct;
    nowy_fpunkt_struct.x = x;
    nowy_fpunkt_struct.y = y;
    return nowy_fpunkt_struct;
}

fpunkt_struct nowy_fpunkt_struct(int x, int y, int z){
    fpunkt_struct nowy_fpunkt_struct;
    nowy_fpunkt_struct.x = x;
    nowy_fpunkt_struct.y = y;
    nowy_fpunkt_struct.z = z;
    return nowy_fpunkt_struct;
}

punktcik nowy_punktcik(int x,int y){
    punktcik nowy_punktcik;
    nowy_punktcik.x = x;
    nowy_punktcik.y = y;
    return nowy_punktcik;
}

kolor nowy_kolor(int r,int g,int b){
    kolor nowy_kolor;
    nowy_kolor.r = r;
    nowy_kolor.g = g;
    nowy_kolor.b = b;
    return nowy_kolor;
}

float oblicz_odleglosc_2d(punkt_struct  *p1, punkt_struct  *p2)
{
    return qSqrt(p1->x * p1->x + p2->y * p2->y);
}

float oblicz_odleglosc_3d(punkt_struct  * p1, punkt_struct  *p2)
{
    return sqrt(p1->x * p1->x + p2->y * p2->y + p2->z * p2->z);
}

punkt_struct srodek_trojkota(punkt_struct  *p1, punkt_struct  *p2, punkt_struct  *p3)
{
    punkt_struct wynik;
    wynik.x=(p1->x + p2->x + p3->x)/3;
    wynik.y=(p1->y + p2->y + p3->y)/3;
    wynik.z=(p1->z + p2->z + p3->z)/3;
    return wynik;
}

float pole_trojkata_3d(punkt_struct  * p1, punkt_struct  * p2, punkt_struct  * p3){
  //dlugosci krawedzi
  float a = sqrt(pow(p2->x  -  p1->x, 2)  +  pow(p2->y  -  p1->y, 2)  +  pow(p2->z  -  p1->z, 2));
  float b = sqrt(pow(p3->x  -  p1->x, 2)  +  pow(p3->y  -  p1->y, 2)  +  pow(p2->z  -  p1->z, 2));
  float c = sqrt(pow(p3->x  -  p2->x, 2)  +  pow(p3->y  -  p2->y, 2)  +  pow(p2->z  -  p1->z, 2));
  float p = (a  +  b  +  c) / 2.0f;
  return sqrt(p * (p - a) * (p - b) * (p - c));
}

float pole_trojkata_2d(punkt_struct  * p1, punkt_struct  * p2, punkt_struct  * p3) {
  //dlugosci krawedzi
  float a = sqrt(pow(p2->x - p1->x, 2)  +  pow(p2->y - p1->y, 2));
  float b = sqrt(pow(p3->x - p1->x, 2)  +  pow(p3->y - p1->y, 2));
  float c = sqrt(pow(p3->x - p2->x, 2)  +  pow(p3->y - p2->y, 2));
  float p = (a  +  b  +  c) / 2.0f;
  return sqrt(p * (p - a) * (p - b) * (p - c));
}


int zwrot_trojkata(QList<QSharedPointer<punkt_struct>> list)
{
    if(list.length() < 3)
    {
        return 0;
    }

    punkt_struct p1;
    punkt_struct p2;

    p1.x  =  list[1]->x  -  list[0]->x;
    p1.y  =  list[1]->y  -  list[0]->y;

    p2.x  =  list[2]->x  -  list[0]->x;
    p2.y  =  list[2]->y  -  list[0]->y;

    return p1.x  *  p2.y  -  p2.x  *  p1.y;
}






