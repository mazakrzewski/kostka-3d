#ifndef ROTATE_3D_CLASS_H
#define ROTATE_3D_CLASS_H

#include <QPainter>
#include <armadillo>
#include <qmath.h>
#include <math.h>
#include <QDebug>
#include <math.h>
#include <krawedz.h>

class rotate_3d_class
{
public:
   rotate_3d_class();
   void Rotate_OX(float stopnie);
   void Rotate_OY(float stopnie);
   void Rotate_OZ(float stopnie);
   void Pochyl_OX(float wspolczynnik_pochylenia_OX);
   void Pochyl_OY(float wspolczynnik_pochylenia_OY);
   void Skalowanie_OX(float dlugosc);
   void Skalowanie_OY(float wysokosc);
   void execute(QSharedPointer<QList<QSharedPointer<punkt_struct>>> lista_ponktow, QSharedPointer<QList<QSharedPointer<punkt_struct> > > wynik_list);
   QImage *execute(QImage *obraz);

private:
   arma::fmat Mat_Move;

   arma::fmat Mat_Rotate_OX;
   arma::fmat Mat_Rotate_OY;
   arma::fmat Mat_Rotate_OZ;

   arma::fmat Mat_Pochyl_OX;
   arma::fmat Mat_Pochyl_OY;

   arma::fmat Mat_Size_OX;
   arma::fmat Mat_Size_OY;
   arma::fmat Mat_Size_OZ;

};


#endif // ROTATE_3D_CLASS_H
