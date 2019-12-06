#ifndef ROTATE_CLASS_H
#define ROTATE_CLASS_H

#include <QPainter>
#include <armadillo>
#include <qmath.h>
#include <math.h>
#include <QDebug>
#include <math.h>

class rotate_class
{
public:
   rotate_class();
   void Rotate(float stopnie);
   void Pochyl_OX(float wspolczynnik_pochylenia_OX);
   void Pochyl_OY(float wspolczynnik_pochylenia_OY);
   void Skalowanie_OX(float dlugosc);
   void Skalowanie_OY(float wysokosc);
   QImage *execute(QImage *obraz);

private:
   arma::fmat Mat_Rotate;
   arma::fmat Mat_Pochyl_OX;
   arma::fmat Mat_Pochyl_OY;
   arma::fmat Mat_Size_OX;
   arma::fmat Mat_Size_OY;

};

#endif // ROTATE_CLASS_H
