#ifndef DRAW_H
#define DRAW_H

class Draw
{

public:
    void static putPixel(QImage *buf, int x, int y, int r, int g , int b);
    void static wstaw8ponktow(QImage *buf, int x1, int x2, int x, int y, int r, int g, int b);
    void static wstaw4ponktow(QImage *buf, int x1, int x2, int x, int y, int r, int g, int b);
    void static drawCirkle(QImage *buf , int x , int y, int r, int red , int g , int b);
    void static drawCirkle2(QImage *buf, int x , int y, int r, int red , int g , int b, int dokladnsc=10);
    void static drawElipsa(QImage *buf, int x , int y, int r, int r2, int red , int g , int b, int dokladnsc=10);
    void static flaga(QImage *buf, int x1, int y1, int x2, int y2);
    void static zmienKolor(QImage *buf, int r, int g, int b);
    void static drawLine(QImage *buf, int x1, int y1, int x2, int y2, int r, int g, int b);
    void static draw4Line(QImage *buf, int x , int y, int x1, int y1, int x2, int y2, int r, int g, int b);
    bool static kolor_compare(kolor a,kolor b);
    void static flood_fill(QImage *buf ,punktcik punkty, kolor zamieniany_kolor);
    void static bezier(QImage *buf, int x, int y, int r, int g, int b);
    void static rgb_to_hsv(float r, float g, float b,float &h, float &s, float &v);
    void static hsv_to_rgb(float h, float s, float v, float &r, float &g, float &b);
    kolor static takePixel(QImage *buf, int x, int y);
    punktcik nowy_punkt(int x, int y);
    kolor nowy_kolor(int r, int g, int b);
    void narysuj_krzywa(QImage *buf);

};

#endif // DRAW_H




