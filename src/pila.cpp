/* 5286580 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/pila.h"
typedef TInfo *apuntador;

struct celda
{
    TInfo info;
    celda *sig;
};

struct _rep_pila
{
    celda *casillero;
    int tope;
};

TPila crearPila()
{
    TPila nuevo = new _rep_pila;
    nuevo->tope = 0;
    nuevo->casillero = NULL;
    return nuevo;
}

void liberarPila(TPila p)
{
    celda *aux = p->casillero;
    while (aux != NULL)
    {
        celda *aux2 = aux;
        aux = aux->sig;
        liberarInfo(aux2->info);
        delete aux2;
    }
    delete p;
}

nat cantidadEnPila(TPila p) { return p->tope; }

TPila apilar(TInfo info, TPila p)
{
    p->tope++;
    celda *nueva = new celda;
    nueva->info = copiaInfo(info);
    nueva->sig = p->casillero;
    p->casillero = nueva;

    return p;
}

TInfo cima(TPila p) { return p->casillero->info; }

TPila desapilar(TPila p)
{
    if (p->tope > 0)
    {   
        celda *aux = p->casillero->sig;
        liberarInfo(p->casillero->info);
        p->tope--;
        delete p->casillero;
        p->casillero = aux;
    }
    return p;
}
