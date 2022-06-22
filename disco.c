#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "./disco.h"

#define EXPONENTE 2

/**
  * @brief Permite setear valores por defecto a propiedades de discos
  * @param[in] discos Discos
  * @param[in] numerDiscos Número de discos
  * @return Void
*/
void inicializarDiscos(Disco *discos, int numeroDiscos) {
  for (int i = 0; i < numeroDiscos; i++) {
    discos[i] = (Disco){ 0, 0, 0, 0, 0, 0, 0 };
  }
}

/**
  * @brief Permite obtener la distancia de una visibilidad al centro
  *        Formula: distancia = d(u,v) = (u^2 + v^2)^1/2
  * @param[in] u Posición en el eje u
  * @param[in] v Posición en el eje v
  * @return distancia
*/
double calcularDistancia(float u, float v) {
  return sqrt(pow((double) u, EXPONENTE) + pow((double) v, EXPONENTE));
}

/**
  * @brief Permite obtener la posición del disco al que pertenece una visibilidad
  * @param[in] distancia Distancia de una visibilidad al centro
  * @param[in] numeroDiscos Número de discos
  * @param[in] anchoDiscos Ancho de discos
  * @return Posición de disco
*/
int obtenerPosicionDisco(double distancia,  int numeroDiscos, int anchoDiscos) {
  Intervalo *intervalos = (Intervalo *)malloc(sizeof(Intervalo) * numeroDiscos);
  int i;
  int posicion = -1;
  
  for (i = 0; i < numeroDiscos; i++) {
    if (i == 0) {
      if (distancia >= 0 && distancia <= anchoDiscos) {
        posicion = i;
      }
      intervalos[0].min = 0;
      intervalos[0].max = anchoDiscos;
      continue;
    }

    intervalos[i].min =  intervalos[i - 1].max;
    intervalos[i].max = anchoDiscos * (i + 1);

    if (distancia >= intervalos[i].min && distancia <= intervalos[i].max) {
      posicion = i;
    }
  }
  return posicion;
}

/**
  * @brief Permite calcular la potencia de un disco
  * @param[in] visibilidadReal Visibilidad real
  * @param[in] visibilidadImaginario Visibilidad imaginario
  * @return Potencia
*/
float calcularPotencia(float visibilidadReal, float visibilidadImaginario) {
  double powReal = pow((double)visibilidadReal, EXPONENTE);
  double powImaginario = pow((double)visibilidadImaginario, EXPONENTE);
  return (float)sqrt(powReal + powImaginario);
}

/**
  * @brief Permite calcular las propiedades de un disco
  * @param[in] disco Disco
  * @param[in] visibilidad Visibilidad
  * @return Disco
*/
Disco calcularPropiedades(Disco *disco, Visibilidad visibilidad) {
  disco->sumatoriaVisibilidadesReales += visibilidad.real;
  disco->sumatoriaVisibilidadesImaginarios += visibilidad.imaginario;
  disco->potencia += calcularPotencia(visibilidad.real, visibilidad.imaginario);
  disco->ruidoTotal += visibilidad.ruido;
  disco->numeroVisibilidades++;
  return * disco;
}

/**
  * @brief Permite calcular la media real de un disco
  * @param[in] disco Disco
  * @return Media real
*/
float calcularMediaReal(Disco *disco) {
  return (disco->numeroVisibilidades == 0) ? 0.0f : (disco->sumatoriaVisibilidadesReales / disco->numeroVisibilidades);
}

/**
  * @brief Permite calcular la media imaginaria de un disco
  * @param[in] disco Disco
  * @return Media imaginaria
*/
float calcularMediaImaginaria(Disco *disco) {
  return (disco->numeroVisibilidades == 0) ? 0.0f : (disco->sumatoriaVisibilidadesImaginarios / disco->numeroVisibilidades);
}
