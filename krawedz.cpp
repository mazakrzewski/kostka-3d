#include "krawedz.h"
#include "types.h"
#include <QList>
#include <QDebug>

QSharedPointer<QList<QSharedPointer<krawedz>>> krawedz::na_liste_krawedzi(QSharedPointer<QList<QSharedPointer<punkt_struct>>> lista_ponktow)
{    
    QSharedPointer<QList<QSharedPointer<krawedz>>> lista_wynik(new QList<QSharedPointer<krawedz>>);

    if(lista_ponktow->length() < 2)
    {
          return lista_wynik;
    }
    
    if(lista_ponktow->length() == 2)
    {
        lista_wynik->push_back(QSharedPointer<krawedz>(new krawedz((*lista_ponktow)[0], (*lista_ponktow)[1])));
        lista_wynik->push_back(QSharedPointer<krawedz>(new krawedz((*lista_ponktow)[1], (*lista_ponktow)[0])));
        return lista_wynik;
    }

    for (int i = 1; i < lista_ponktow->length(); i++)
    {
        lista_wynik->push_back(QSharedPointer<krawedz>(new krawedz((*lista_ponktow)[i - 1], (*lista_ponktow)[i])));
    }

    lista_wynik->push_back(QSharedPointer<krawedz>(new krawedz((*lista_ponktow)[lista_ponktow->length() - 1], (*lista_ponktow)[0])));

    return lista_wynik;
}

void krawedz::dodaj_punkt(QSharedPointer <QList <QSharedPointer <krawedz>>> lista, QSharedPointer<punkt_struct> punkt)
{
    if(lista.isNull())
    {
        return;
    }

    if(lista->length() < 2)
    {
		//bledna lista
        return;    
    }

    lista->removeLast();
    lista->push_back(QSharedPointer<krawedz>(new krawedz((*lista)[(*lista).length() - 1]->get_p2(),  punkt)));
    lista->push_back(QSharedPointer<krawedz>(new krawedz( punkt, (*lista)[0]->get_p1())));

    return;

}

void krawedz::usun_punkt (QSharedPointer <QList <QSharedPointer <krawedz>>> lista)
{
    if(lista.isNull())
    {
        return;
    }

    if(lista->isEmpty())
    {
        return;
    }
	
    if(lista->length()<=2)
    {
        if(lista->length() == 2){
            lista->removeLast();
            lista->removeLast();
              return;
        }
        if(lista->length() == 1){
            lista->removeLast();

        }
        return;
    }

    lista->removeLast();
    lista->removeLast();

    lista->push_back(QSharedPointer <krawedz>(new krawedz((*lista)[lista->length() - 1]->get_p2(), (*lista)[0]->get_p1())));

    return;

}

void krawedz::usun_punkt (QSharedPointer <QList <QSharedPointer <krawedz>>> lista, int pozycja)
{
    if(pozycja < 0)
    {
        return;
    }

    if(lista.isNull())
    {
        return;
    }

    if(lista->isEmpty())
    {
        return;
    }

    if(lista->length() >= pozycja){
         return;
    }

    if(lista->length() <= 2)
    {
        if(lista->length() == 2){
            lista->removeLast();
            lista->removeLast();
            return;
        }
        if(lista->length() == 1){
            lista->removeLast();

        }
        return;
    }

    if(pozycja != 0)
    {

        lista->removeAt(pozycja);
        lista->removeAt(pozycja);


        lista->insert(pozycja,QSharedPointer <krawedz>(new krawedz((*lista)[pozycja - 1]->get_p2(), (*lista)[pozycja]->get_p1())));
        return;
    }

    lista->removeAt(pozycja);
    lista->removeAt(lista->length() - 1);

    lista->push_back(QSharedPointer <krawedz>(new krawedz((*lista)[lista->length() - 1]->get_p2(), (*lista)[0]->get_p1())));

    return;

}

krawedz::krawedz( QSharedPointer<punkt_struct> p1,  QSharedPointer<punkt_struct> p2)
{
    this->p1 = p1;
    this->p2 = p2;
    this->resetuj();
}

void krawedz::resetuj()
{
    if(p1->y > p2->y)
    {
        this->max_y = p1->y;
        this->min_y = p2->y;
        this->x_dla_max_y = p1->x;
        this->x_dla_min_y = p2->x;
    }
    else
    {
        this->max_y = p2->y;
        this->min_y = p1->y;
        this->x_dla_max_y = p2->x;
        this->x_dla_min_y = p1->x;
    }
	
    float y; 
    y =  this->max_y - this->min_y;
	
    if(y != 0)
    {
        this->przyrost_x = (this->x_dla_max_y - this->x_dla_min_y) / y;
    }
    else
    {
        this->przyrost_x = 0;
    }

    this->aktualny_x = this->x_dla_min_y;
    this->aktualny_y = this->min_y;


}

QSharedPointer<punkt_struct> krawedz::get_p1(){
    return this->p1;
}

QSharedPointer<punkt_struct> krawedz::get_p2(){
     return this->p2;
}

void krawedz::resetuj_x_y()
{    
    this->aktualny_x = this->x_dla_min_y;
    this->aktualny_y = this->min_y;
}

float krawedz::get_min_y()
{
   return this->min_y;
}

float krawedz::get_max_y()
{
   return this->max_y;
}

float krawedz::get_przyrost_x()
{
    return this->przyrost_x;
}

float krawedz::get_aktualny_x()
{
    return this->aktualny_x;
}

float krawedz::get_aktualny_y()
{
    return this->aktualny_y;
}


float krawedz::get_x_dla_min_y()
{
    return this->x_dla_min_y;
}

float krawedz::get_x_dla_max_y()
{
    return this->x_dla_max_y;
}

int krawedz::aktualizuj(){
   
    this->aktualny_x += this->przyrost_x;
    this->aktualny_y++;
    

    if(max_y < aktualny_y)
    {       
        this->resetuj();
        return 0;
    }
    return 1;
}

int krawedz::zwrot_trojkata(QList<QSharedPointer<krawedz>> list)
{
    if(list.length() < 3)
    {
        return 0;
    }

    punkt_struct p1;
    punkt_struct p2;

    p1.x = list[1]->get_p1()->x - list[0]->get_p1()->x;
    p1.y = list[1]->get_p1()->y - list[0]->get_p1()->y;

    p2.x = list[2]->get_p1()->x - list[0]->get_p1()->x;
    p2.y = list[2]->get_p1()->y - list[0]->get_p1()->y;

    return p1.x * p2.y - p2.x * p1.y;

}