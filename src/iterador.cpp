/* 5286580 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/iterador.h"
#include <assert.h>
struct nodoIt{
    nat num;
    nodoIt *sig;
};
struct _rep_iterador{
    nodoIt *inicio, *fin, *actual;
    bool bloqueado;
};

TIterador crearIterador(){
    TIterador i = new _rep_iterador;
    i->bloqueado = false;
    i->actual = i->inicio = i->fin = NULL;
    return i;
};

void liberarIterador(TIterador iter){
  iter->actual = iter->inicio;
    while (estaDefinidaActual(iter)){
      nodoIt *a = iter->actual;
      avanzarIterador(iter);
      delete a;
    }
    delete iter;
  }

bool estaDefinidaActual(TIterador iter){
  return iter->actual != NULL;
};

void agregarAIterador(nat elem, TIterador const iter){

    if(!iter->bloqueado){
      nodoIt *l = new nodoIt;
      l->num = elem;
      l->sig = NULL;
      if (iter->fin!= NULL) iter->fin->sig = l;
      else iter->inicio = l;
      iter->fin = l;
   }
}


void reiniciarIterador(TIterador const iter) {
  if (iter != NULL)
    {iter->actual = iter->inicio;} 
}

void avanzarIterador(TIterador const iter) {
  if(estaDefinidaActual(iter))
    iter->actual = iter->actual->sig;
}

nat actualEnIterador(TIterador iter){
    assert(estaDefinidaActual(iter));
    return iter->actual->num;
};