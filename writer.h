/**
 * @brief Función que permite imprimir resultados en consola cuando el flag -b está activado
 * @param[in] discos Discos
 * @param[in] numeroDiscos Número de discos
 * @return Void
 */
void imprimirEnConsola(Disco * discos, int numeroDiscos);

/**
 * @brief Función que permite escribir resultados en output entregado por flag -o
 * @param[in] discos Discos
 * @param[in] numeroDiscos Número de discos
 * @param[in] output Nombre de archivo donde se escribirán los resultados
 * @return Void
 */
void escribirArchivo(Disco * discos, int numeroDiscos, char* output);
