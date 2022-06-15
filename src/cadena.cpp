/* 5286580 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// los elementos se mantienen entre 0 y cantidad - 1, incluidos

struct _rep_cadena
{
  TInfo dato;
  TCadena sig;
  TCadena ant;
};

TCadena crearCadena()
{

  return NULL;
}

void liberarCadena(TCadena cad)
{
  if (cad == NULL)
  {
    return;
  }

  TCadena prox_a_borrar = cad;
  TCadena final = cad->ant;
  while (cad != final)
  {
    prox_a_borrar = cad;
    cad = cad->sig;
    liberarInfo(prox_a_borrar->dato);
    delete (prox_a_borrar);
  }
  liberarInfo(cad->dato);
  delete cad;
}

// TInfo inicioCad(TCadena cad)
// {
//   return cad->inicio->dato;
// }
// TInfo finalCad(TCadena cad)
// {
//   return cad->final->dato;
// }

TInfo primeroEnCadena(TCadena cad)
{
  return cad->dato;
};

TCadena cadenaSiguiente(TCadena cad)
{
  if (cad == NULL || cad == cad->sig)
  {
    return cad;
  }
  else
  {
    
    return cad->sig;
  }
};

nat cantidadEnCadena(TCadena cad)
{
  TCadena inicio = cad;
  nat count = 0;
  if (cad != NULL)
  {
    TCadena rec = cad->sig;

    count = 1;

    while (rec != inicio)
    {
      count++;

      rec = rec->sig;
    }
  }

  return count;
}

bool estaEnCadena(nat natural, TCadena cad)
{
  if (cad == NULL)
  {
    return false;
  }
  else
  {
    TCadena inicio = cad;
    TCadena rec = inicio;
    while ((rec != NULL) && (natInfo(rec->dato) != natural))
    {
      if (rec->sig != inicio)
      {
        rec = rec->sig;
      }
      else
      {
        break;
      }
    }
    if (natInfo(rec->dato) == natural)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
}

TCadena insertarAlInicio(nat natural, double real, TCadena cad)
{
  TCadena in = new _rep_cadena;
  TInfo dato = crearInfo(natural, real);
  in->dato = dato;
  if (cad == NULL)
  {
    in->sig = in;
    in->ant = in;
    cad = in;
  }
  else
  {
    TCadena ultimo = cad->ant;
    in->sig = cad;
    in->ant = ultimo;
    cad->ant = in;
    ultimo->sig = in;
    cad = in;
  }
  return cad;
}

TInfo infoCadena(nat natural, TCadena cad)
{
  TCadena inicio = cad;
  TCadena rec = inicio;
  while (natInfo(rec->dato) != natural)
  {
    rec = rec->sig;
  }

  return rec->dato;
}
/*
  Remueve el primer elemento de 'cad' cuyo componente natural es 'natural'.
  Se libera la memoria asignada al mismo.
  Devuelve 'cad'.
  Precondición: estaEnCadena(natural, cad).
 */
TCadena removerDeCadena(nat natural, TCadena cad)

{
  TCadena rec = cad;
  // si tiene solo un elemento, borro info y cad
  if (rec->sig == rec)
  {

    liberarInfo(rec->dato);
    delete rec;
    cad = NULL;
    return cad;
  }
  else
  // si tiene mas de un elemento, busco
  {

    bool primero = true;
    TCadena anteriorABorrar = rec->ant;
    while (natInfo(rec->dato) != natural)
    {
      anteriorABorrar = rec;
      rec = rec->sig;
      primero = false;
    }
    anteriorABorrar->sig = rec->sig;

    rec->sig->ant = anteriorABorrar;
    liberarInfo(rec->dato);
    delete rec;
    if (primero)
    {

      cad = anteriorABorrar->sig;
    }
    return cad;
  }
}

void imprimirCadena(TCadena cad)

{
  if (cad == NULL)
  {
    printf("\n");
    return;
  }
  TCadena inicio = cad;
  TCadena rec = cad;
  if (rec != NULL)
  {
    char *dat = infoATexto(rec->dato);
    printf("%s", dat);
    delete[] dat;
    rec = rec->sig;
    while (rec != inicio)
    {
      char *dat = infoATexto(rec->dato);
      printf("%s", dat);
      delete[] dat;
      rec = rec->sig;
    }
  }
  printf("\n");
}

TCadena insertarAlFinal(nat natural, double real, TCadena cad)
{
  cad = insertarAlInicio(natural, real, cad);
  cad = cadenaSiguiente(cad);
  return cad;
}

TCadena copiaCadena(TCadena cad)
{
  if (cad != NULL)
  {
    TCadena copia = crearCadena();
    TCadena partida = cad;
    TCadena siguiente = cad;
    TInfo info = primeroEnCadena(cad);
    copia = insertarAlFinal(natInfo(info), realInfo(info), copia);
    siguiente = cadenaSiguiente(siguiente);

    while (siguiente != partida)
    {
      TInfo info = primeroEnCadena(siguiente);
      copia = insertarAlFinal(natInfo(info), realInfo(info), copia);
      siguiente = cadenaSiguiente(siguiente);
    }
    return copia;
  }
  else
    return NULL;
}
TCadena removerPrimero(TCadena cad)
{
  cad = removerDeCadena(natInfo(primeroEnCadena(cad)), cad);
  return cad;
}