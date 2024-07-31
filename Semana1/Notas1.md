# Clase 31 de Julio 2024
## Motivacion para dinamica molecular
Codigo MD
``````
int main()
{
  DeclaraciondeSistemaInicial();
  Simulacion();
}
``````
La mayorìa del tiempo de la corrida es en la función simulación
Dentro de la funcion de simulación (caso NVE,algoritmo Velocity Verlet)
Siendo N el número de particulas
``````
Simulacion
{
  CalculosEnergiaInicial();
  Aceleraciones();
  iterador
  {
    Posiciones(); <- O(N)
    Velocidades(); <- O(N)
    Aceleraciones();<- O(N²)
    Velocidades();
  }
}
``````
Aceleraciones es la función que peor escala
con el número de partículas

Estructura de Aceleraciones()
``````
Aceleraciones();
{
  IteradorParticula1
  {
    IteradorParticula2
    {
      //Se puede Incluir el calculo de las contribuciones a la EP
      CalculodeFuerza();
      SumaFuerzasenP1();
    }
  }
}
``````
### Propuesta de paralelización:
Seccionar función de aceleración y distribuirla en la GPU O(N²)->O(N)
## Instalacion de CUDA
* Guia de instalacion de cuda toolkit
  https://docs.nvidia.com/cuda/cuda-installation-guide-linux/index.html
* Para Instalar compiladores de c/c++
  * sudo apt install build-essential
* Para Instalar toolkit
  * https://developer.nvidia.com/cuda-downloads?target_os=Linux
* Ejemplo para Ubuntu 24.04 (se descarga el runfile)
  * https://developer.nvidia.com/cuda-downloads?target_os=Linux&target_arch=x86_64&Distribution=Ubuntu&target_version=24.04&target_type=runfile_local

Los pasos importantes para revisar de la guia son:
* paso 2
* paso 8 (ya que la instalacion recomendada es con el runfile)
* paso 13 (por si no se reconoce el nvcc)


