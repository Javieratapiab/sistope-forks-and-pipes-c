#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

#include "./disco.h"

#define MAX_CHARS 1024
#define LECTURA 0
#define ESCRITURA 1

/**
  * @brief Permite la creación de múltiples procesos hijos con el fin de paralelizar trabajo
  * @param[in] visibilidades Colección de visibilidades
  * @param[in] discos Colección de discos
  * @param[in] numeroDiscos Cantidad de discos
  * @param[in] numeroVisibilidades Número de visibilidades que pertenecen a algún disco
  * @return Disco
*/
void creadorProcesos(Visibilidad *visibilidades, Disco *discos, int numeroDiscos, int visibilidadesLeidas) {
  int fin = 0;
  int status;
  Disco disco = (Disco){ 0, 0, 0, 0, 0, 0, 0 };
  Visibilidad visibilidad;
  Visibilidad *visibilidadesDiscos = (Visibilidad *)malloc(sizeof(Visibilidad));
  int cantidadVisibilidadesDisco = 0;
  char *argumentos[4] = {"./vis", cantidadVisibilidadesDisco, &visibilidadesDiscos, fin};
  int pipes[numeroDiscos][2];
  pid_t pids[numeroDiscos];

  for(int i = 0; i < numeroDiscos; i++) {
    // Abre descriptores
    pipe(pipes[i]);
  }

  for (int i = 0; i < numeroDiscos; i++) {
    cantidadVisibilidadesDisco = 0;

    // Genera arreglo de visibilidades que pertenecen al disco
    for(int j = 0; j < visibilidadesLeidas; j++) {
      if (visibilidades[j].posicionDisco == i) {
        visibilidadesDiscos = (Visibilidad *)realloc(visibilidadesDiscos, sizeof(visibilidadesDiscos) + sizeof(visibilidad));
        visibilidadesDiscos[cantidadVisibilidadesDisco] = visibilidades[j];
        cantidadVisibilidadesDisco++;
      }
    }

    if ((pids[i] = fork()) < 0) { // Error
      perror("fork");
      abort();
    } else if (pids[i] > 0) {  // Procesos padres
      write(pipes[i][ESCRITURA], &cantidadVisibilidadesDisco, sizeof(int));
      write(pipes[i][ESCRITURA], visibilidadesDiscos, cantidadVisibilidadesDisco * sizeof(Visibilidad));
      write(pipes[i][ESCRITURA], &fin, sizeof(fin));
      waitpid(pids[i], &status, 0);
    } else if (pids[i] == 0) { // Procesos hijos
      dup2(pipes[i][LECTURA], STDIN_FILENO);
      dup2(pipes[i][ESCRITURA], STDOUT_FILENO);
      execv(argumentos[0], argumentos);
      exit(0);
    }
  }

  fin = 1;
  // Cierra todos los procesos
  for (int i = 0; i < numeroDiscos; i++) {
    // Envía mensaje de fin
    write(pipes[i][ESCRITURA], &fin, sizeof(fin));
    // Lee disco con propiedades
    read(pipes[i][LECTURA], &disco, sizeof(disco));
    // Actualiza disco con disco actualizado
    discos[i] = disco;
    // Cierra pipes
    close(pipes[i][ESCRITURA]);
    close(pipes[i][LECTURA]);
    // Mata procesos hijos creados
    kill(pids[i], SIGKILL);
  }

  // Libera memoria
  free(visibilidadesDiscos);
  free(visibilidades);
}

/**
 * @brief Permite lectura de archivo de entrada
 * @param[in] discos Discos
 * @param[in] nombreArchivo Nombre de archivo con visibilidades, el cual tiene como formato uv_values_i.csv con i = 0,1,2,....
 * @param[in] numeroDiscos cantidad de discos
 * @param[in] anchoDiscos ancho de discos
 * @return Disco
 */
void empezarLectura(Disco *discos, char *nombreArchivo, int numeroDiscos, int anchoDiscos) {
  FILE *fp = fopen(nombreArchivo, "r");
  char line[MAX_CHARS];
  int col, visibilidadesLeidas = 0;
  Visibilidad *visibilidades = malloc(sizeof(Visibilidad));

  // Valida que archivo se pueda abrir correctamente
  if (fp == NULL) {
    printf("El archivo no se puede abrir o no existe %s\n", nombreArchivo);
    exit(0);
  }

  while (fgets(line, MAX_CHARS, fp)) {
    col = 0;
    char *current = strtok(line, ", ");
    Visibilidad visibilidad;

    while (current) {
      switch (col) {
        case 0:
          visibilidad.u = atof(current);
          break;
        case 1:
          visibilidad.v = atof(current);
          break;
        case 2:
          visibilidad.real = atof(current);
          break;
        case 3:
          visibilidad.imaginario = atof(current);
          break;
        case 4:
          visibilidad.ruido = atof(current);
          break;
        default:
          printf("Existe un offset en una propiedad ingresada: %s\n", current);
          break;
      }
      current = strtok(NULL, ", ");
      col++;
    }

    double distancia = calcularDistancia(visibilidad.u, visibilidad.v);

    // Obtiene posición del disco al que pertenece la visibilidad
    int posicionDisco = obtenerPosicionDisco(distancia, numeroDiscos, anchoDiscos);

    // No logra determinar a qué disco pertenece la visibilidad
    if (posicionDisco == -1) {
      continue;
    }
    visibilidad.posicionDisco = posicionDisco;
    visibilidades[visibilidadesLeidas] = visibilidad;
    visibilidades = realloc(visibilidades, sizeof(visibilidades) * sizeof(visibilidad));
    visibilidadesLeidas++;
  }

  // Cierra el archivo
  fclose(fp);

  // Inicia creador de procesos
  creadorProcesos(visibilidades, discos, numeroDiscos, visibilidadesLeidas);
}
