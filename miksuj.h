#ifndef MIKSUJ
#define MIKSUJ

#include <QPainter>
#include <QDebug>
#include <stack>
#include "types.h"

QImage *blend_mode_dodge(QImage *tlo, QImage *front, int x_ile, int y_ile, int x_z, int y_z, int x_do, int y_do);

QImage *blend_mode_burn(QImage *tlo, QImage *front, int x_ile, int y_ile, int x_z, int y_z, int x_do, int y_do);

QImage *blend_mode_quadratic(QImage *tlo, QImage *front, int x_ile, int y_ile, int x_z, int y_z, int x_do, int y_do);

QImage *blend_mode_additive(QImage *tlo, QImage *front, int x_ile, int y_ile, int x_z, int y_z, int x_do, int y_do);

QImage *blend_mode_interpolation(QImage *tlo, QImage *front, int x_ile, int y_ile, int x_z, int y_z, int x_do, int y_do);

QImage *blend_mode_normal(QImage *tlo, QImage *front, int x_ile, int y_ile, int x_z, int y_z, int x_do, int y_do);

QImage *blend_mode_average(QImage *tlo, QImage *front, int x_ile, int y_ile, int x_z, int y_z, int x_do, int y_do);

QImage *blend_mode_multiply(QImage *tlo, QImage *front, int x_ile, int y_ile, int x_z, int y_z, int x_do, int y_do);

QImage *blend_mode_screen(QImage *tlo, QImage *front, int x_ile, int y_ile, int x_z, int y_z, int x_do, int y_do);

QImage *blend_mode_darken(QImage *tlo, QImage *front, int x_ile, int y_ile, int x_z, int y_z, int x_do, int y_do);

QImage *blend_mode_lighten(QImage *tlo, QImage *front, int x_ile, int y_ile, int x_z, int y_z, int x_do, int y_do);

QImage *blend_mode_difference(QImage *tlo, QImage *front, int x_ile, int y_ile, int x_z, int y_z, int x_do, int y_do);

QImage *blend_mode_negation(QImage *tlo, QImage *front, int x_ile, int y_ile, int x_z, int y_z, int x_do, int y_do);

QImage *blend_mode_exclusion(QImage *tlo, QImage *front, int x_ile, int y_ile, int x_z, int y_z, int x_do, int y_do);

QImage *blend_mode_overlay(QImage *tlo, QImage *front, int x_ile, int y_ile, int x_z, int y_z, int x_do, int y_do);

QImage *blend_mode_hard_light(QImage *tlo, QImage *front, int x_ile, int y_ile, int x_z, int y_z, int x_do, int y_do);

QImage *blend_mode_soft_light(QImage *tlo, QImage *front, int x_ile, int y_ile, int x_z, int y_z, int x_do, int y_do);
 
#endif // MIKSUJ

