# Manual de uso de laboratorio

>> Autora: Javiera Tapia Bobadilla
>> Asignatura: Sistemas Operativos

## Comandos

`make`: Crea archivos ejecutables y objetos necesarios para hacer funcionar los programas usando configuraciones de Makefile.

`make clean`: Elimina ejecutables, objetos y .depends

## Operaciones

Ejemplo 1:

```shell
>> make
>> ./lab2 -i uv_values_1.csv -d 8 -n 15 -b
```
En este caso, se invoca el ejecutable lab2 indicando que el archivo de entrada (`-i`)
será `uv_values_1.csv`, con un ancho de discos (`-d`) de 8, número de discos
de tamaño 15 (`-n`) y que se espera salida de resultados por consola.

Ejemplo 2:

```shell
>> make
>> ./lab2 -i uv_values_1.csv -d 8 -n 15 -o output.txt
```
En este caso, se invoca el ejecutable lab2 indicando que el archivo de entrada (`-i`)
será `uv_values_1.csv`, con un ancho de discos (`-d`) de 8, número de discos
de tamaño 15 (`-n`) y que se esperan resultados en archivo de salida (`-o`)
output.txt
