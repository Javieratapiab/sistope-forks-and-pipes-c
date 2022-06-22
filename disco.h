/**
 * Guarda una señal llamada visibilidad.
 * Cada visibilidad es un número complejo, es
 * decir, posee una parte real y otra imaginaria.
*/
typedef struct visibilidad {
  float u;           // Posición en el eje u
  float v;           // Posición en el eje v
  float real;        // Valor real de la visibilidad
  float imaginario;  // Valor imaginario de la visibilidad
  float ruido;       // Ruido de la visibilidad
  int posicionDisco; // Posición disco
} Visibilidad;

/**
 * Guarda una imagen reconstruida a partir de visibilidades,
 * a esta reconstrucción se le denomina disco.
*/
typedef struct disco {
  float sumatoriaVisibilidadesReales;       // Sumatoria de visibilidades reales
  float sumatoriaVisibilidadesImaginarios;  // Sumatoria de visibilidades imaginarias
  float mediaReal;                          // Cálculo de la media real de un disco
  float mediaImaginaria;                    // Cálculo de la media imaginaria de las visibilidades del disco
  float potencia;                           // Cálculo de la potencia de un disco
  float ruidoTotal;                         // Cálculo del ruido total de un disco
  int numeroVisibilidades;                  // Número de visibilidades que componen un disco
} Disco;

/**
  * @brief Permite setear valores por defecto a propiedades de discos
  * @param[in] discos Discos
  * @param[in] numerDiscos Número de discos
  * @return Void
*/
void inicializarDiscos(Disco *disco, int numeroDiscos);

/**
 * Permite construir un intérvalo a partir de los anchos de disco
*/
typedef struct intervalo {
  int min; // Rango mínimo del ancho de disco
  int max; // Rango máximo del ancho de disco
} Intervalo;

/**
  * @brief Permite obtener la distancia de una visibilidad al centro
  *        Formula: distancia = d(u,v) = (u^2 + v^2)^1/2
  * @param[in] u Posición en el eje u
  * @param[in] v Posición en el eje v
  * @return distancia
*/
double calcularDistancia(float u, float v);

/**
  * @brief Permite obtener la posición del disco al que pertenece una visibilidad
  * @param[in] distancia Distancia de una visibilidad al centro
  * @param[in] numeroDiscos Número de discos
  * @param[in] anchoDiscos Ancho de discos
  * @return Posición de disco
*/
int obtenerPosicionDisco(double distancia, int numeroDiscos, int anchoDiscos);

/**
  * @brief Permite calcular la potencia de un disco
  * @param[in] visibilidadReal Visibilidad real
  * @param[in] visibilidadImaginario Visibilidad imaginario
  * @return Potencia
*/
float calcularPotencia(float visibilidadReal, float visibilidadImaginario);

/**
  * @brief Permite calcular las propiedades de un disco
  * @param[in] disco Disco
  * @param[in] visibilidad Visibilidad
  * @return Disco
*/
Disco calcularPropiedades(Disco *disco, Visibilidad visibilidad);

/**
  * @brief Permite calcular la media real de un disco
  * @param[in] disco Disco
  * @return Media real
*/
float calcularMediaReal(Disco *disco);

/**
  * @brief Permite calcular la media imaginaria de un disco
  * @param[in] disco Disco
  * @return Media imaginaria
*/
float calcularMediaImaginaria(Disco *disco);
