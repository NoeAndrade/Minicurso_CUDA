## Mini-curso de CUDA semana 3
*Esta semana se implementa la identificación de hilos, la comunicación entre CPU (host) y la GPU (device) y se realizarán más ejercicios para reforzar el aprendizaje.*

### Hilos

Consideremos el siguiente fragmento de código:
```
...
__global__ void Kernel()
{
  int id=threadIdx.x;
  printf("id: %d\n", id);
}
...
int main()
{
  Kernel<<<bloques,hilosporbloque>>>();
  ...
  return 0;
}
```
`threadIdx` es el identificador del hilo, es un vector con 3D, el poder acceder a las otras dimensiones depende de como se definió hilos por bloque.

### ¿Donde puede ser util?

***Suma de vectores/matrices***

*Ejemplo en c++*

*Implementación usando CUDA*
 
 * Manejo de memoria
   * cudaMalloc()
   * cudaMemcpy()
   * cudaFree()

*Ejercicio*
Implimentar para una matriz



