#ifndef TROJKOTY_H
#define TROJKOTY_H

#include<types.h>

class trojkoty
{
public:
    trojkoty(punkt_struct *p1, punkt_struct *p2, punkt_struct *p3);
    void set_p1(punkt_struct *punkt);
    void set_p2(punkt_struct *punkt);
    void set_p3(punkt_struct *punkt);
    punkt_struct get_p1();
    punkt_struct get_p2();
    punkt_struct get_p3();
    punkt_struct *get_location_p1();
    punkt_struct *get_location_p2();
    punkt_struct *get_location_p3();

private:
    punkt_struct *p1;
    punkt_struct *p2;
    punkt_struct *p3;
};

#endif // TROJKOTY_H
