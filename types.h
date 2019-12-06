#ifndef TYPES_H
#define TYPES_H

#include <qlist.h>
#include <qmath.h>
#include<QSharedPointer>


typedef struct {
    int x, y;
    bool istnieje;
}punktcik;

typedef struct {
    int x, y, z;
}punkt_struct;

typedef struct {
    int r;
    int g;
    int b;

}kolor;

typedef struct {
    int x, y, z;
}fpunkt_struct;


fpunkt_struct nowy_fpunkt_struct(int x, int y);

fpunkt_struct nowy_fpunkt_struct(int x, int y, int z);

punkt_struct nowy_punkt_struct(int x, int y);

punkt_struct nowy_punkt_struct(int x, int y, int z);

punktcik nowy_punktcik(int x, int y);

kolor nowy_kolor(int r, int g, int b);

float oblicz_odleglosc_2d(punkt_struct *p1, punkt_struct *p2);

float oblicz_odleglosc_3d(punkt_struct *p1, punkt_struct *p2);

punkt_struct srodek_trojkota(punkt_struct *p1,punkt_struct *p2,punkt_struct *p3);

float pole_trojkata_3d(punkt_struct *p1,punkt_struct *p2,punkt_struct *p3);

float pole_trojkata_2d(punkt_struct *p1,punkt_struct *p2,punkt_struct *p3);

void przedksztalc(punkt_struct *p1);

int zwrot_trojkata(QList<QSharedPointer<punkt_struct>> list);

#endif // TYPES_H
