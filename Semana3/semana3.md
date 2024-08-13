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

*Ejemplo para multiples bloques en un grid*
```
...
__global__ void Kernel()
{
  int id=blockDim.x * blockIdx.x + threadIdx.x;
  printf("id: %d\n", id);
}
...
int main()
{
  int bloques=10;
  Kernel<<<bloques,hilosporbloque>>>();
  ...
  return 0;
}
```
*Ejemplo bloque de mas de 1 dimension*


```
...
__global__ void Kernel()
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    int j = blockIdx.y * blockDim.y + threadIdx.y;
  printf("i: %d,j: %d\n", i,j);
}
...
int main()
{
  dim3 hilosporbloque(4, 2);
  dim3 bloques(16 / hilosporbloque.x, 16 / hilosporbloque.y);
  Kernel<<<bloques,hilosporbloque>>>();
  ...
  return 0;
}
```

### ¿Donde puede ser util?

***Suma de vectores/matrices***

*Ejemplo en c++*

*Manejo de memoria
  *malloc()/new
  *free()/delete[]

*Implementación usando CUDA*
 
 * Manejo de memoria
   * cudaMalloc()
   * cudaMemcpy()
   * cudaFree()

*Ejercicio*
Implimentar para una matriz



