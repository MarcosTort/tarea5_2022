/* 5286580 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/cola.h"
struct celda
{
    TInfo info;
    celda *sig;
};
struct _rep_cola
{
    celda *frente;
    celda *final;
    int cantidad;
};

TCola crearCola()
{
    TCola nueva = new _rep_cola;
    nueva->frente = NULL;
    nueva->final = NULL;
    nueva->cantidad = 0;
    return nueva;
}

void liberarCola(TCola c)
{
    celda *aux = c->frente;
    while (aux != NULL)
    {
        celda *aux2 = aux;
        aux = aux->sig;
        liberarInfo(aux2->info);
        delete aux2;
    }
    delete c;
}

nat cantidadEnCola(TCola c)
{
    return c->cantidad;
}

TCola encolar(TInfo info, TCola c)
{
    celda *nueva = new celda;
    nueva->info = copiaInfo(info);
    nueva->sig = NULL;
    if (c->final == NULL)
    {
        c->frente = nueva;
        c->final = nueva;
    }
    else
    {
        nueva->sig = NULL;
        c->final->sig = nueva;
        c->final = nueva;
    }
    c->cantidad++;
    return c;
}

TInfo frente(TCola c)
{
    return c->frente->info;
}

bool estaVaciaColaBinarios(TCola c)
{
    return c->frente == NULL;
}
TCola desencolar(TCola c)
{
    celda *aux = c->frente;
    if (!estaVaciaColaBinarios(c))
    {
        c->frente = c->frente->sig;
        liberarInfo(aux->info);
        if (aux->sig == NULL)
            c->final = NULL;
        c->cantidad--;
    }
    delete aux;
    return c;
}
