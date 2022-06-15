/* 5286580 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/colCadenas.h"
#include "../include/cadena.h"
#include "../include/utils.h"


struct _rep_colCadenas{
  TCadena *arr;
  nat tope;
  nat cota;
};

TCadena cadenaDeColCadenas(nat pos, TColCadenas col){

  
  return col->arr[pos];

};

void liberarColCadenas(TColCadenas col){
  nat tamanio = col->cota;

  for (nat i = 0; i < tamanio; i++)
  {
      
      liberarCadena(col->arr[i]);
  }
  delete[] col->arr;
  delete col;

};

TColCadenas crearColCadenas(nat tamanio)
{
  TColCadenas nuevo = new _rep_colCadenas;
  nuevo->arr = new TCadena[tamanio];
  nuevo->cota= tamanio;
  nuevo->tope = 0;
  for (nat i = 0; i < tamanio ; i++)
  {
    nuevo->arr[i] = crearCadena();
  }
  
  return nuevo;
}


nat cantidadColCadenas(nat pos, TColCadenas col)
{
  return cantidadEnCadena(col->arr[pos]);
}

bool estaEnColCadenas(nat natural, nat pos, TColCadenas col)
{
  


  return estaEnCadena(natural, col->arr[pos]);
  
}

TColCadenas insertarEnColCadenas(nat natural, double real, nat pos, TColCadenas col)
{
  col->arr[pos] = insertarAlInicio(natural, real, col->arr[pos]);
  return col;
}

TInfo infoEnColCadenas(nat natural, nat pos, TColCadenas col)
{
 return infoCadena(natural, col->arr[pos]);

}

TColCadenas removerDeColCadenas(nat natural, nat pos, TColCadenas col)
{
  col->arr[pos] = removerDeCadena(natural, col->arr[pos]);
  return col;
}
nat tamanioColCadenas(TColCadenas col){
  return col->tope;
}
