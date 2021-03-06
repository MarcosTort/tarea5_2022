/* 5286580 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/abb.h"

struct _rep_abb
{
    TInfo dato;
    _rep_abb *izq;
    _rep_abb *der;
};

TAbb crearAbb() { return NULL; }

void liberarAbb(TAbb abb)
{
    if (abb != NULL)
    {
        liberarAbb(abb->der);
        liberarAbb(abb->izq);
        liberarInfo(abb->dato);
        delete abb;
    }
}

bool esVacioAbb(TAbb abb) { return abb == NULL; }

TAbb buscarSubarbol(nat elem, TAbb abb)
{
    if (!esVacioAbb(abb))
    {
        if (elem == natInfo(abb->dato))
        {
            return abb;
        }
        else if (elem < natInfo(abb->dato))
        {
            return buscarSubarbol(elem, izquierdo(abb));
        }
        else if (elem > natInfo(abb->dato))
        {
            return buscarSubarbol(elem, derecho(abb));
        }
        else
            return NULL;
    }
    else
        return NULL;
}

TInfo raiz(TAbb abb) { return abb->dato; }

TAbb izquierdo(TAbb abb) { return abb->izq; }

TAbb derecho(TAbb abb) { return abb->der; }

TInfo menorEnAbb(TAbb abb)
{
    TInfo ret;
    if (abb->izq == NULL)
    {
        ret = abb->dato;
    }
    else
    {
        ret = menorEnAbb(abb->izq);
    }
    return ret;
}

TInfo mayorEnAbb(TAbb abb)
{
    TInfo ret;
    if (abb->der == NULL)
    {
        ret = abb->dato;
    }
    else
    {
        ret = mayorEnAbb(abb->der);
    }
    return ret;
}

TAbb consAbb(TInfo dato, TAbb izq, TAbb der)
{

    TAbb abb = new _rep_abb;
    abb->dato = dato;
    abb->izq = izq;
    abb->der = der;
    return abb;
}

TAbb insertarEnAbb(TInfo dato, TAbb abb)
{
    if (esVacioAbb(abb))
    {
        abb = new _rep_abb;
        abb->dato = dato;
        abb->izq = NULL;
        abb->der = NULL;
    }
    else
    {
        if (natInfo(dato) < natInfo(abb->dato))
        {
            abb->izq = insertarEnAbb(dato, abb->izq);
        }
        else
        {
            abb->der = insertarEnAbb(dato, abb->der);
        }
    }
    return abb;
}

TAbb removerMayor(TAbb b)
{ // LISTO
    if (b->der == NULL)
    {
        TAbb izquierda = b->izq;
        delete (b);
        b = izquierda;
    }
    else
        b->der = removerMayor(b->der);
    return b;
}

TAbb removerDeAbb(nat clave, TAbb abb)
{

    if (abb != NULL)
    {
        if (natInfo(abb->dato) == clave)
        {

            if (abb->der == NULL)
            {
                TAbb aux = abb;
                abb = abb->izq;
                liberarInfo(aux->dato);
                delete aux;
            }
            else if (abb->izq == NULL)
            {
                TAbb aux = abb;
                abb = abb->der;
                liberarInfo(aux->dato);
                delete aux;
            }
            else
            {
                TInfo aux = raiz(abb);
                abb->dato = mayorEnAbb(abb->izq);
                liberarInfo(aux);
                abb->izq = removerMayor(abb->izq);
            }
            // if(b->der == NULL && b->izq == NULL)
        }
        else if (clave < natInfo(abb->dato))
            abb->izq = removerDeAbb(clave, abb->izq);
        else
            abb->der = removerDeAbb(clave, abb->der);
    }
    return abb;
}

TAbb copiaAbb(TAbb abb)
{
    if (abb == NULL)
        return NULL;
    else
    {
        TAbb rt = new _rep_abb;
        rt->dato = copiaInfo(abb->dato);
        rt->izq = copiaAbb(abb->izq);
        rt->der = copiaAbb(abb->der);
        return rt;
    }
}

void rotarDerecha(TAbb &abb)
{
    TAbb l, a, b, c;
    l = abb->der;
    a = abb->izq;
    b = l->izq;
    c = l->der;
    TInfo dato1 = abb->dato;
    TInfo dato2 = l->dato;
    abb->dato = dato2;
    abb->izq = l;
    abb->der = c;
    l->dato = dato1;
    l->der = b;
    l->izq = a;
}
void rotarIzquierda(TAbb &abb)
{
    TAbb k, a, b, c;
    k = abb->izq;
    c = abb->der;
    a = k->izq;
    b = k->der;
    TInfo dato1 = abb->dato;
    TInfo dato2 = k->dato;
    abb->dato = dato2;
    abb->der = k;
    abb->izq = a;
    k->dato = dato1;
    k->der = c;
    k->izq = b;
}

TAbb rotar(nat clave, char tipo[2], TAbb abb)
{
    if (abb == NULL)
        return NULL;
    else
    {
        if (natInfo(abb->dato) == clave)
        {

            if (tipo[0] == 'L' && tipo[1] == 'R' && abb->izq != NULL && abb->izq->der != NULL)
            {
                rotarDerecha(abb->izq);
                rotarIzquierda(abb);
                return abb;
            }
            else if (tipo[0] == 'R' && tipo[1] == 'L' && abb->der != NULL && abb->der->izq != NULL)
            {
                rotarIzquierda(abb->der);
                rotarDerecha(abb);
                return abb;
            }
            else if (tipo[0] == 'R' && tipo[1] == 'R' && abb->der != NULL)
            {
                rotarDerecha(abb);
                return abb;
            }

            else
            {
                if (tipo[0] == 'L' && tipo[1] == 'L' &&  abb->izq != NULL )
                {
                    rotarIzquierda(abb);
                    return abb;
                }
            }
        }
        else if (clave < natInfo(abb->dato))
            rotar(clave, tipo, abb->izq);
        else
            rotar(clave, tipo, abb->der);
    }
    return abb;
}
