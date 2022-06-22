#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "./validator.h"
#include "./reader.h"
#include "./writer.h"

// Variables globales
char *iflag = "";
char *oflag = "";
int nflag = 0;
int dflag = 0;
int bflag = 0;

/**
 * @brief Función que imprime las opciones válidas desde la línea de comandos
 */
void imprimirOpciones() {
  printf("%s%s%s%s%s\n",
         "-------- OPCIONES VÁLIDAS --------\n"
         "-i: nombre de archivo con visibilidades, formato: uv_values_i.csv con i = 0,1,2,....\n",
         "-o: nombre de archivo de salida\n",
         "-n: cantidad de discos\n",
         "-d: ancho de cada disco\n",
         "-b: mostrar salida por consola\n");
}

/**
 * @brief Función principal que recibe una serie de argumentos por línea de comando
 * @param[in] -i: nombre de archivo con visibilidades, el cual tiene como formato uv_values_i.csv con i = 0,1,2,....
 * @param[in] -o: nombre de archivo de salida
 * @param[in] -n: cantidad de discos
 * @param[in] -d: ancho de cada disco.
 * @param[in] -b: bandera o flag que permite indicar si se quiere ver por consola la cantidad de visibilidades encontradas
 *                por cada proceso hijo. Es decir, si se indica el flag, entonces se muestra la salida por consola
 */
int main(int argc, char **argv) {
  int opt;

  while ((opt = getopt(argc, argv, "i:o:n:d:b")) != -1) {
    switch (opt) {
      case 'i':
        iflag = (char *)optarg;
        break;
      case 'o':
        oflag = (char *)optarg;
        break;
      case 'n':
        nflag = atoi(optarg);
        break;
      case 'd':
        dflag = atoi(optarg);
        break;
      case 'b':
        bflag = 1;
        break;
      case '?':
        imprimirOpciones();
        return 1;
    }
  }

  // Valida opciones entregadas por línea de comandos
  if (validarOpciones(iflag, oflag, nflag, dflag, bflag) == -1)
    return -1;

  Disco *discos = (Disco *)malloc(sizeof(Disco) * nflag);

  // Agrega valores por defecto a discos
  inicializarDiscos(discos, nflag);

  // Inicia lectura del archivo de entrada
  empezarLectura(discos, iflag, nflag, dflag);

  if (bflag == 1) {
    imprimirEnConsola(discos, nflag);
  } else {
    escribirArchivo(discos, nflag, oflag);
  }

  free(discos);
  return (0);
}
