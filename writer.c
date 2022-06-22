#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./disco.h"

/**
 * @brief Función que permite imprimir resultados en consola cuando el flag -b está activado
 * @param[in] discos Discos
 * @param[in] numeroDiscos Número de discos
 * @return Void
 */
void imprimirEnConsola(Disco * discos, int numeroDiscos) {
  for (int i = 0; i < numeroDiscos; i++) {
    printf("Disco %d: \n", i + 1);
    printf("Media real: %.6f \n", calcularMediaReal(&discos[i]));
    printf("Media imaginaria: %.6f \n", calcularMediaImaginaria(&discos[i]));
    printf("Potencia: %.6f \n", discos[i].potencia);
    printf("Ruido total: %.6f \n", discos[i].ruidoTotal);
  }
}

/**
 * @brief Función que permite escribir resultados en output entregado por flag -o
 * @param[in] discos Discos
 * @param[in] numeroDiscos Número de discos
 * @param[in] output Nombre de archivo donde se escribirán los resultados
 * @return Void
 */
void escribirArchivo(Disco * discos, int numeroDiscos, char* output) {
  FILE *fp = fopen(output, "w");

  if (fp == NULL) {
    printf("El archivo de destino no se puede abrir %s\n", output);
    exit(0);
  }

  for (int i = 0; i < numeroDiscos; i++) {
    fprintf(fp, "Disco %d: \n", i + 1);
    fprintf(fp, "Media real: %.6f \n", calcularMediaReal(&discos[i]));
    fprintf(fp, "Media imaginaria: %.6f \n", calcularMediaImaginaria(&discos[i]));
    fprintf(fp, "Potencia: %.6f \n", discos[i].potencia);
    fprintf(fp, "Ruido total: %.6f \n", discos[i].ruidoTotal);
  }

  fclose(fp);
}
