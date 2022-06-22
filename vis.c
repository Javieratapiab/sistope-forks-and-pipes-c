#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>

#include "./disco.h"

/**
 * @brief Función principal que se ejecutará por procesos hijos
 *        creados en reader.c
 */
int main(int argc, char *argv[]) {
  int i;
  int fin = 0;
  int tamanoVisibilidades = 0;
  Disco disco = (Disco){ 0, 0, 0, 0, 0, 0, 0 };
  Visibilidad *visibilidadesDiscos = malloc(tamanoVisibilidades * sizeof(Visibilidad));

  // Lectura de datos
  read(STDIN_FILENO, &tamanoVisibilidades, sizeof(tamanoVisibilidades));
  read(STDIN_FILENO, visibilidadesDiscos, tamanoVisibilidades * sizeof(Visibilidad));

  // Calcula propiedades del disco
  for (i = 0; i < tamanoVisibilidades; i++)
    disco = calcularPropiedades(&disco, visibilidadesDiscos[i]);

  // Espera mensaje de fin desde padre
  if (read(STDIN_FILENO, &fin, sizeof(fin)) != 0) {
    write(STDOUT_FILENO, &disco, sizeof(disco));
    exit(EXIT_SUCCESS);
  }

  return 0;
}
