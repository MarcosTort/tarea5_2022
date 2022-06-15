/* 5286580 */ // sustituiir con los 7 dígitos de la cédula
#include "../include/mapping.h"
#include "../include/cadena.h"
#include "../include/aplicaciones.h"
#include "../include/info.h"
#include <limits.h> 
#include <stdlib.h>  

struct _rep_mapping
{
    TCadena *array;
    nat tamanio;
    nat cantidad;
};

nat get_bucket(nat clave, nat tamanio)
{
    return (nat)(clave % tamanio);
}

TMapping crearMap(nat M)
{
    TMapping map = new _rep_mapping;
    map->array = new TCadena[M];
    map->tamanio = M;
    map->cantidad = 0;
    for (nat i = 0; i < M; i++)
    {
        map->array[i] = crearCadena();
    }
    return map;
}



void liberarMap(TMapping map)
{

    for (nat i = 0; i < map->tamanio; i++)
    {
        liberarCadena(map->array[i]);
    }
    delete[] map->array;
    delete map;
}

TMapping asociarEnMap(nat clave, double valor, TMapping map)
{
    nat indice = get_bucket(clave, map->tamanio);
    if (map->array[indice] == NULL)
    {
        map->cantidad++;
    }
    liberarCadena(map->array[indice]);
    map->array[indice] = insertarAlInicio( clave ,valor, map->array[indice]);
    return map;
}

TMapping desasociarEnMap(nat clave, TMapping map)
{
    nat indice = get_bucket(clave, map->tamanio);
    if (map->array[indice] != NULL)
    {
        map->cantidad--;
        map->array[indice] = removerPrimero(map->array[indice]);
    }
    return map;
}

bool esClaveEnMap(nat clave, TMapping map)
{
    nat indice = get_bucket(clave, map->tamanio);
    return (map->array[indice] != NULL);
}

double valorEnMap(nat clave, TMapping map)
{
    nat indice = get_bucket(clave, map->tamanio);
    double res = realInfo(primeroEnCadena(map->array[indice]));
    return res;
}

bool estaLlenoMap(TMapping map)
{
    return map->cantidad == map->tamanio;
}
