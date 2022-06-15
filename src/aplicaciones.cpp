/* 5286580 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/aplicaciones.h"
#include "../include/cadena.h"
#include "../include/iterador.h"
#include "../include/mapping.h"
#include <string.h>

#include "../include/colCadenas.h"

TIterador reversoDeIterador(TIterador iter)
{
  TIterador reverso = crearIterador();

  reiniciarIterador(iter);
  reiniciarIterador(reverso);
  TCadena aux = crearCadena();
  int count = 0;
  while (estaDefinidaActual(iter))
  {
    nat entrante = actualEnIterador(iter);
    aux = insertarAlInicio(entrante, 0, aux);
    avanzarIterador(iter);
    count++;
  }

  for (int i = 0; i < count; i++)
  {
    agregarAIterador(natInfo(primeroEnCadena(aux)), reverso);
    aux = cadenaSiguiente(aux);
  }
  liberarCadena(aux);
  reiniciarIterador(reverso);

  return reverso;
}

TCadena lineaux(TCadena cad, TAbb b)
{ // LISTO
  if (!esVacioAbb(b))
  {

    cad = lineaux(cad, izquierdo(b)); // llegar al menor
    TInfo dato = raiz(b);
    cad = insertarAlFinal(natInfo(dato), realInfo(dato), cad); // insertar de mayor a menor de izq
    cad = lineaux(cad, derecho(b));
    return cad;
  }
  else
    return cad;
}

TCadena linealizacion(TAbb abb)
{

  TCadena cad = crearCadena();
  cad = lineaux(cad, abb);
  return cad;
}
void aux2(nat nivel, TAbb b)
{

  for (nat i = 0; i < nivel; i++)
    printf("-");
  char *infotxt = infoATexto(raiz(b));
  printf("%s", infotxt);
  delete[] infotxt;
}
void imprimiraux(nat nivel, TAbb b)
{
  if (!esVacioAbb(b))
  {
    imprimiraux(nivel + 1, derecho(b));
    aux2(nivel, b);
    printf("\n");
    imprimiraux(nivel + 1, izquierdo(b));
  }
}
void imprimirAbb(TAbb abb)
{
  if (esVacioAbb(abb))
  {
    return;
  }
  imprimiraux(0, abb);
}

bool esPerfectoAUX(TAbb abb, nat profundidad, nat nivel)
{

  if (esVacioAbb(abb))
  {
    // printf("%d", __LINE__);

    return true;
  }
  else if (esVacioAbb(izquierdo(abb)) && esVacioAbb(derecho(abb)))
  {
    // printf("%d", __LINE__);
    return (profundidad == nivel);
  }
  else if (esVacioAbb(izquierdo(abb)) || esVacioAbb(derecho(abb)))
  {
    // printf("%d", __LINE__);
    return false;
  }

  else
  {
    // printf("%d", __LINE__);
    return esPerfectoAUX(izquierdo(abb), profundidad, nivel + 1) && esPerfectoAUX(derecho(abb), profundidad, nivel + 1);
  }
}
int maxDepth(TAbb node)
{
  if (node == NULL)
    return -1;
  else
  {
    /* compute the depth of each subtree */
    int lDepth = maxDepth(izquierdo(node));
    int rDepth = maxDepth(derecho(node));

    /* use the larger one */
    if (lDepth > rDepth)
      return (lDepth + 1);
    else
      return (rDepth + 1);
  }
}
bool esPerfecto(TAbb abb)
{
  int profundidad = maxDepth(abb);
  int nivelInicial = 0;
  return esPerfectoAUX(abb, profundidad, nivelInicial);
}

TAbb menores(double cota, TAbb b)
{
  TAbb res;
  if (cota > 0 && b != NULL)
  {
    TAbb bizq, bder;
    bizq = menores(cota, izquierdo(b));
    bder = menores(cota, derecho(b));
    if (realInfo(raiz(b)) < cota)
    {
      res = consAbb(copiaInfo(raiz(b)), bizq, bder);
    }
    else
    {
      if (bizq == NULL)
        res = bder;
      else if (bder == NULL)
        res = bizq;
      else
      {
        res = consAbb(copiaInfo(raiz(b)), bizq, bder);
        removerDeAbb(natInfo(raiz(res)), res);
      }
    }
  }
  else
    res = NULL;
  return res;
}

int minimo(int a, int b)
{
  if (a < b)
    return a;
  else
    return b;
}
TIterador caminoAscendente(nat clave, nat k, TAbb abb)
{
  int count = 1;
  TIterador iter = crearIterador();
  TAbb aux = abb;
  while (clave != natInfo(raiz(aux)))
  {
    if (!esVacioAbb(aux))
    {
      agregarAIterador(natInfo(raiz(aux)), iter);
      count++;
      // SI EL BUSCADO ES MAS GRANDE QUE LA RAIZ ACTUAL
      if (clave > natInfo(raiz(aux)))
      {
        aux = derecho(aux);
      }
      else if (clave < natInfo(raiz(aux)))

      {
        aux = izquierdo(aux);
      }
    }
  }
  agregarAIterador(natInfo(raiz(aux)), iter);

  TIterador res = reversoDeIterador(iter);
  reiniciarIterador(res);
  liberarIterador(iter);
  TIterador auxIter = crearIterador();

  for (int i = 0; i < minimo(count, k); i++)
  {
    nat auxNat = actualEnIterador(res);
    agregarAIterador(auxNat, auxIter);
    avanzarIterador(res);
  }
  liberarIterador(res);
  return auxIter;
}

void imprimirPalabrasCortasAux(int i, int k, TPalabras palabras, ArregloChars salida)
{

  if (palabras != NULL)
  {
    // printf("nashe    %c\n", letra(palabras));
    // printf("%d\n", k);
    salida[i - k] = letra(palabras);

    if (k >= 0 && letra(palabras) == '\0')
    {
      // printf("%d\n", k);
      printf("%s\n", salida);
    }

    imprimirPalabrasCortasAux(i, k - 1, subarboles(palabras), salida);
    if (k != i)
      imprimirPalabrasCortasAux(i, k, siguientes(palabras), salida);
  }
}

void imprimirPalabrasCortas(nat k, TPalabras palabras)
{
  ArregloChars salida = new char[1000];
  palabras = subarboles(palabras);
  while (palabras != NULL)
  {

    imprimirPalabrasCortasAux(k, k, palabras, salida);
    palabras = siguientes(palabras);
  }
  delete[] salida;
}

TPalabras buscarFinPrefijoAux(ArregloChars prefijo, TPalabras palabras, int nivel)
{
  if (palabras != NULL)
  {
    palabras = subarboles(palabras);
    while (palabras != NULL && prefijo[nivel] != letra(palabras))
    {
      palabras = siguientes(palabras);
    }
    if (palabras != NULL && prefijo[nivel + 1] != '\0')

    {
      palabras = buscarFinPrefijoAux(prefijo, palabras, nivel + 1);
    }
    return palabras;
  }
  else
    return NULL;
}

TPalabras buscarFinPrefijo(ArregloChars prefijo, TPalabras palabras)
{
  return buscarFinPrefijoAux(prefijo, palabras, 0);
}

// auxiliares

void aux2(nat nivel, TPalabras b)
{
  for (nat i = 0; i < nivel; i++)
    printf("-");
  char infotxt = letra(b);
  printf("%c", infotxt);
}
void imprimiraux(nat nivel, TPalabras b)
{
  if (b != NULL)
  {
    imprimiraux(nivel + 1, subarboles(b));
    aux2(nivel, b);
    printf("\n");
    imprimiraux(nivel + 1, siguientes(b));
  }
}

void pal(TPalabras abb)
{
  if (abb == NULL)
  {
    return;
  }
  imprimiraux(0, abb);
}

bool estaOrdenada(TCadena cad)
{
  TCadena stop = cad;
  TCadena inicio = cad;
  TCadena siguiente = cadenaSiguiente(inicio);
  while (siguiente != stop)
  {
    if (natInfo(primeroEnCadena(inicio)) >= natInfo(primeroEnCadena(siguiente)))
    {
      return false;
    }
    inicio = siguiente;
    siguiente = cadenaSiguiente(inicio);
  }
  return true;
}

TCadena mezclaCadenas(TCadena cad1, TCadena cad2)
{
  TCadena res = crearCadena();
  TCadena aux1 = cad1;
  TCadena aux2 = cad2;
  bool avanzo1 = false;
  bool avanzo2 = false;
  TCadena inicio1 = cad1;
  TCadena inicio2 = cad2;
  bool termino1 = false;
  bool termino2 = false;

  while (aux1 != NULL && aux2 != NULL)
  {
    if (natInfo(primeroEnCadena(aux1)) < natInfo(primeroEnCadena(aux2)))
    {
      res = insertarAlFinal(natInfo(primeroEnCadena(aux1)), realInfo(primeroEnCadena(aux1)), res);
      aux1 = cadenaSiguiente(aux1);
      avanzo1 = true;
    }
    else if (natInfo(primeroEnCadena(aux1)) > natInfo(primeroEnCadena(aux2)))
    {
      res = insertarAlFinal(natInfo(primeroEnCadena(aux2)), realInfo(primeroEnCadena(aux2)), res);
      aux2 = cadenaSiguiente(aux2);
      avanzo2 = true;
    }
    else
    {
      res = insertarAlFinal(natInfo(primeroEnCadena(aux1)), realInfo(primeroEnCadena(aux1)), res);
      aux1 = cadenaSiguiente(aux1);
      aux2 = cadenaSiguiente(aux2);
      avanzo1 = true;
      avanzo2 = true;
    }
    if ((avanzo1 && (aux1 == inicio1)) || (avanzo2 && (aux2 == inicio2)))
    {
      if (avanzo1 && (aux1 == inicio1))
      {
        termino1 = true;
      }
      if (avanzo2 && (aux2 == inicio2))
      {
        termino2 = true;
      }
      break;
    };
  }
  while (aux1 != NULL && !termino1)
  {

    res = insertarAlFinal(natInfo(primeroEnCadena(aux1)), realInfo(primeroEnCadena(aux1)), res);
    aux1 = cadenaSiguiente(aux1);
    avanzo1 = true;

    if (avanzo1 && (aux1 == inicio1))
    {
      break;
    };
  }
  while (aux2 != NULL && !termino2)
  {

    res = insertarAlFinal(natInfo(primeroEnCadena(aux2)), realInfo(primeroEnCadena(aux2)), res);
    aux2 = cadenaSiguiente(aux2);
    avanzo2 = true;
    if (avanzo2 && (aux2 == inicio2))
    {
      break;
    };
  }
  return res;
}

TAbb balanceado(int start, int end, TInfo *elems)
{

  if (start > end)
    return NULL;
  TAbb b = crearAbb();
  int elementoMedio = (start + end) / 2;
  b = consAbb(crearInfo(natInfo(elems[elementoMedio]), realInfo(elems[elementoMedio])), balanceado(start, elementoMedio - 1, elems), balanceado(elementoMedio + 1, end, elems));
  return b;
}

TAbb crearBalanceado(TInfo *arreglo, nat n)
{

  return balanceado(0, n - 1, arreglo);
}

TAbb unionAbbs(TAbb abb1, TAbb abb2)
{

  TCadena linAbb1 = linealizacion(abb1);
  TCadena linAbb2 = linealizacion(abb2);
  TCadena linUnion = mezclaCadenas(linAbb1, linAbb2);
  nat n = cantidadEnCadena(linUnion);
  TInfo *arr = new TInfo[n];
  nat i = 0;
  while (i < n)
  {
    arr[i] = primeroEnCadena(linUnion);
    linUnion = cadenaSiguiente(linUnion);
    i++;
  }
  TAbb res = crearBalanceado(arr, n);
  delete[] arr;
  liberarCadena(linUnion);
  liberarCadena(linAbb1);
  liberarCadena(linAbb2);
  return res;
}

TCola ordenadaPorModulo(nat p, TCadena cad)
{
  TColCadenas colModulos = crearColCadenas(p);
  bool empezo = false;
  TCadena aux = cad;
  TCadena inicio = cad;
  TCola res = crearCola();
  if (aux != NULL)
  {
    while (true)
    {
      if (!empezo)
      {
        empezo = true;
      }
      colModulos = insertarEnColCadenas(
          natInfo(primeroEnCadena(aux)),
          realInfo(primeroEnCadena(aux)),
          natInfo(primeroEnCadena(aux)) % p,
          colModulos);
      aux = cadenaSiguiente(aux);

      if (aux == inicio && empezo)
      {
        break;
      }
    }

    for (nat i = 0; i < p; i++)
    {
      TCadena cadaux = cadenaDeColCadenas(i, colModulos);
      TCadena inicioAux = cadaux;
      TPila pila = crearPila();
      while (cadaux != NULL)
      {
        pila = apilar(primeroEnCadena(cadaux), pila);
        cadaux = cadenaSiguiente(cadaux);
        if (cadaux == inicioAux)
        {
          break;
        }
      }
      while (cantidadEnPila(pila) > 0)
      {
        res = encolar(cima(pila), res);
        pila = desapilar(pila);
      }
      liberarPila(pila);
    }
  }
  liberarColCadenas(colModulos);
  return res;
}

TPila menoresQueElResto(TCadena cad, nat cantidad)
{
  TPila p = crearPila();
  if (cad != NULL)
  {
    TCadena aux = cad;
    p = apilar(primeroEnCadena(aux), p);
    aux = cadenaSiguiente(aux);
    cantidad--;
    for (nat i = 0; i < cantidad; i++)
    {
      if (cantidadEnPila(p) > 0)
      {

        if (natInfo(cima(p)) < natInfo(primeroEnCadena(aux)))
        {

          p = apilar(primeroEnCadena(aux), p);
          aux = cadenaSiguiente(aux);
        }
        else
        {

          while (cantidadEnPila(p) > 0 && natInfo(cima(p)) >= natInfo(primeroEnCadena(aux)))
          {

            p = desapilar(p);
          }
          p = apilar(primeroEnCadena(aux), p);
          aux = cadenaSiguiente(aux);
        }
      }
      else
      {

        p = apilar(primeroEnCadena(aux), p);
        aux = cadenaSiguiente(aux);
      }
    }
  }
  return p;
}

int absolut(int n)
{
  return (n >= 0) ? (n) : (-n);
}
TAbb auxMin(nat h, nat &c)
{
  TAbb res = crearAbb();

  if (h <= 0)
  {
    return res;
  }
  else if (h == 1)
  {
    res = consAbb(crearInfo(c, 0.0), NULL, NULL);
    c++;
    return res;
  }
  else
  {
    TAbb izq = auxMin(h - 1, c);
    nat dato = c;
    c++;
    TAbb der = auxMin(h - 2, c);
    res = consAbb(crearInfo(dato, 0.0), izq, der);
    return res;
  }
  return res;
}

TAbb avlMin(nat h)
{

  nat x = 1;
  return auxMin(h, x);
}

int check_AVL(TAbb b)
{
  if (b == NULL)
  {
    return 0;
  }
  int der = check_AVL(derecho(b));
  if (der == -1)
  {
    return -1;
  }

  int izq = check_AVL(izquierdo(b));
  if (izq == -1)
  {
    return -1;
  }

  if (absolut(izq - der) > 1)
  {
    return -1;
  }

  return (1 + ((izq >= der) ? izq : der));
}

bool esAvl(TAbb abb)
{
  int resp = check_AVL(abb);
  if (resp < 0)
    return false;
  else
    return true;
}

TCadena filtradaOrdenada(TCadena cad, TIterador it)
{
  TCadena res = crearCadena();

  TCadena inicio = cad;

  nat tamanio = cantidadEnCadena(cad);
  if (tamanio == 0)
  {
    return res;
  }

  TMapping mapa = crearMap(tamanio * 7);

  while (true)
  {
    double valor = 0.0;
    if (esClaveEnMap(natInfo(primeroEnCadena(cad)), mapa))
    {
      valor = valorEnMap(natInfo(primeroEnCadena(cad)), mapa);
    }
    double nuevoValor = valor + realInfo(primeroEnCadena(cad));
    mapa = asociarEnMap(natInfo(primeroEnCadena(cad)), nuevoValor, mapa);
    cad = cadenaSiguiente(cad);
    if (cad == inicio)
    {
      break;
    }
  }
  reiniciarIterador(it);
  cad = inicio;
  while (estaDefinidaActual(it))
  {
    if (esClaveEnMap(actualEnIterador(it), mapa))
    {
      nat clave = actualEnIterador(it);
      double valor = valorEnMap(clave, mapa);
      res = insertarAlFinal(clave, valor, res);
    }
    avanzarIterador(it);
  }
  reiniciarIterador(it);
  liberarMap(mapa);
  return res;
}
