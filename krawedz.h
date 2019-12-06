#ifndef KRAWEDZ_H
#define KRAWEDZ_H

#include<types.h>
#include<QSharedPointer>
#include<QList>

class krawedz
{
public:
    static  QSharedPointer<QList<QSharedPointer<krawedz>>> na_liste_krawedzi(QSharedPointer<QList<QSharedPointer<punkt_struct>>> lista_ponktow);
    static void dodaj_punkt(QSharedPointer <QList <QSharedPointer <krawedz>>> lista, QSharedPointer<punkt_struct> punkt);
    static void usun_punkt (QSharedPointer <QList <QSharedPointer <krawedz>>> lista);
    static void usun_punkt (QSharedPointer <QList <QSharedPointer <krawedz>>> lista, int pozycja);
    static int zwrot_trojkata(QList<QSharedPointer<krawedz>> list);

    krawedz();
    krawedz( QSharedPointer<punkt_struct> p1,  QSharedPointer<punkt_struct> p2);
    float get_min_y();
    float get_max_y();
    QSharedPointer<punkt_struct> get_p1();
    QSharedPointer<punkt_struct> get_p2();

    float get_przyrost_x();
    float get_x_dla_min_y();
    float get_x_dla_max_y();
    float get_y();
    float get_aktualny_y();
    float get_aktualny_x();

    int aktualizuj();

    void  resetuj_x_y();
    void  resetuj();

private:
    QSharedPointer<punkt_struct> p1;
    QSharedPointer<punkt_struct> p2;

    float min_y;
    float max_y;

    float aktualny_x;
    float aktualny_y;
    float przyrost_x;

    float x_dla_min_y;
    float x_dla_max_y;

};

#endif // KRAWEDZ_H
