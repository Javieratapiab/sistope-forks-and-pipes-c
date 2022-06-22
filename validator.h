/**
  * @brief Función que valida que opciones entregadas son válidas
  * @param[in] iArg: nombre de archivo con visibilidades, el cual tiene como formato uv_values_i.csv con i = 0,1,2,....
  * @param[in] oArg: nombre de archivo de salida
  * @param[in] nArg: cantidad de discos
  * @param[in] dArg: ancho de cada disco.
  * @param[in] bArg: bandera o flag que permite indicar si se quiere ver por consola la cantidad de visibilidades encontradas
  * @return Resultado de la validación -1 = no válido, 1 = válido
 */
int validarOpciones(char *iArg, char *oArg, int nArg, int dArg, int bArg);
