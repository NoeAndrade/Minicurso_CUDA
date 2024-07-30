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
Dentro de la funcion de simulación (caso NVE,algoritmo Verlet)
``````
Simulacion
{
  CalculosEnergiaInicial();
  Aceleraciones();
  iterador
  {
    Posiciones();
    Velocidades();
    Aceleraciones();
    Velocidades();
  }
}
``````
Estructura de Aceleraciones();
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
## Instalacion de CUDA
* Para Instalar compiladores de c/c++
  * sudo apt install build-essential
* Para Instalar toolkit
  * https://developer.nvidia.com/cuda-downloads?target_os=Linux
* Ejemplo para Ubuntu 24.04 
  * https://developer.nvidia.com/cuda-downloads?target_os=Linux&target_arch=x86_64&Distribution=Ubuntu&target_version=24.04&target_type=runfile_local
