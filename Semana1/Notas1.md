# Clase 31 de Julio 2024
## Motivacion para dinamica molecular
Codigo MD
``````C
int main()
{
  DeclaraciondeSistemaInicial();
  Simulacion();
}
``````
Ejemplo de rutina de simulación para algoritmo de Velocity Verlet (NVE)

*Notacion:*

Iterador(i,j,k){proceso(k)} <- *se realiza el proceso(k) j-i veces, donde k va de i a j*

Iterador(j,k){proceso(k)} <- *lo mismo que arriba pero con i=0*

Iterador(j){proceso()} <- *proceso() no depende de el valor del iterador*
``````C
void Simulacion()
{
  CalculoDePropiedadesMacroscópicas();
  Aceleraciones();
  Iterador(np) //np es el numero de pasos de simulacion
  {
    Posiciones();
    Velocidades();
    Aceleraciones();
    Velocidades();
    Iterador(np/porc)  //este iterador indica cada cuantos pasos de simulacion se calculan las propiedades macroscopicas
    {
      CalculoDePropiedadesMacroscópicas();
    }
  }
}
``````
### ¿Como escala el tiempo de ejecución de las funciones?

N <- número de partículas

dt <- tamaño del paso de integración
``````C
void Posiciones()
{
  Iterador(N,k)  //iterando sobre todas las particulas
  { 
    Iterador(nd,l)  //si nd=2 no se calcula la posicion en z, todas las particulas estan el plano z=0
    { 
      posicion[k][l]=posicion[k][l]+velocidad[k][l]*dt+aceleracion[k][l]*dt*dt*0.5;
    }
  }
//Orden del tiempo de ejecución O(N)

void Velocidades()
{
  Iterador(N,k){ //iterando sobre todas las particulas
    Iterador(nd,l){ //si nd=2 no se calcula la posicion en z, todas las particulas estan el plano z=0
      velocidad[k][l]=velocidad[k][l]+aceleracion[k][l]*dt;
    }
  }
//Orden del tiempo de ejecución O(N)
``````

El calculo de las aceleraciones depende de los potenciales de interaccion entre partículas.

Caso de interaccion por pares:
``````C
Aceleraciones()
{
  Iterador(N,i)
  {
    Iterador(N,j)
    {
      ConsiderarExclusiones(i,j); //No se calcula autointeraccion i==j
      CalculodeFuerza(i,j);
      //En caso de que la fuerza sea derivable de la energía potencial se puede realizar el calculo en la misma funcion
    }
    SumaFuerza_i(j); //se suman las contribuciones de las fuerzas de cada particula j a i
  }
}
//Orden del tiempo de ejecución O(N²)
``````
La rutina de aceleraciones tiene el peor escalamiento en terminos de ejecucion, ¡N veces mas que las demas rutinas!.

*La rutina de aceleraciones puede ocupar hasta el 90% del tiempo de simulación*


### ¿Como reducir el tiempo de ejecución? ¡Computo en paralelo!

#### ¿Que es computo en paralelo?

Acción de dividir un proceso grande en diferentes subprocesos, que se pueden realizar al mismo tiempo y se pueden comunicar mediante una memoria compartida. 

#### ¿Que es CUDA?
Modelo de programación y plataforma de computo en paralelo de uso general.

Permite acceso a GPUs de NVIDIA. 

La rutina de aceleraciones es un proceso suficientemente simple que se presta mejor para la paralelizacion en GPU. 



### Propuesta de paralelización:
Seccionar función de aceleración y distribuirla en la GPU buscando O(N²)->O(N)
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


