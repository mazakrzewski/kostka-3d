#ifndef FIGURY_H
#define FIGURY_H


#include<qlist.h>
#include<types.h>
#include<qimage.h>
#include<types.h>

class figury
{
public:
    figury();

    QList<punkt_struct> pu;
    void draw(QImage obraz, int r, int g, int b);
    punktcik *get_punkt();
};

#endif // FIGURY_H
