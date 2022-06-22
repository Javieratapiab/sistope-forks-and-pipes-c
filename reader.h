#include "./disco.h"

/**
  * @brief Permite lectura de archivo de entrada
  * @param[in] discos Discos
  * @param[in] nombreArchivo Nombre de archivo con visibilidades, el cual tiene como formato uv_values_i.csv con i = 0,1,2,....
  * @param[in] numeroDiscos cantidad de discos
  * @param[in] anchoDiscos ancho de discos
  * @return Disco
*/
void empezarLectura(Disco * discos, char * nombreArchivo, int numeroDiscos, int anchoDiscos);

/**
  * @brief Permite la creación de múltiples procesos hijos con el fin de paralelizar trabajo
  * @param[in] visibilidades Colección de visibilidades
  * @param[in] discos Colección de discos
  * @param[in] numeroDiscos Cantidad de discos
  * @param[in] numeroVisibilidades Número de visibilidades que pertenecen a algún disco
  * @return Disco
*/
void creadorProcesos(Visibilidad * visibilidades, Disco * discos, int numeroDiscos, int numeroVisibilidades);
