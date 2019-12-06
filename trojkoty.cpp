#include "trojkoty.h"
#include "punkt_struct.h"


trojkoty::trojkoty(punkt_struct *p1, punkt_struct *p2, punkt_struct *p3)
{
    this->p1 = p1;
    this->p2 = p1;
    this->p3 = p1;
}

void trojkoty::set_p1(punkt_struct *punkt)
{
    this->p1 = punkt;
}

void trojkoty::set_p2(punkt_struct *punkt)
{
    this->p2 = punkt;
}

void trojkoty::set_p3(punkt_struct *punkt)
{
    this->p3 = punkt;
}
/*
punkt_class *trojkoty::p1(){
    return this->p1;
}

punkt_class *trojkoty::p2(){
    return this->p2;
}

punkt_class *trojkoty::p3(){
    return this->p3;
}

*/

punkt_struct *trojkoty::get_location_p1(){
    return this->p1;
}

punkt_struct *trojkoty::get_location_p2(){
    return this->p2;
}

punkt_struct *trojkoty::get_location_p3(){
    return this->p3;
}
