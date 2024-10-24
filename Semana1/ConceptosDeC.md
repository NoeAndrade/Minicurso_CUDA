# ¿Que tengo que saber de C?

_En este documento explicaremos conceptos de C necesarios para el curso_

## Funcion principal

`````C
#include <stdio.h>

int main()
{
  printf("Hola Mundo\n");
  return 0;
}
`````

#include es una directiva que se le da al compilador para que busque cierta libreria de C.

Una libreria es un conjunto de funciones de uso general, en este caso la funcion printf proviene de la libreria stdio.h, la cual nos permite mostrar una cadena de texto con formato.

_ver: https://cplusplus.com/reference/cstdio/printf/ para mas información sobre la seleccion de formato._

El programa debe contener al menos una función, main() la cual indica que sucede en nuestro programa.

main() es una funcion de tipo int, es decir realiza un conjunto de instrucciones y al final de esto nos regresa un valor de tipo int, de ahí la linea _return 0;_

_Notese que siempre despues de una instrucción se debe escribir un punto y coma (;)_

## Tipos de datos

Ejemplo:

**int a = 5;** Crea una variable entera y le asigna un valor de 5.

_Tiene un tamaño de 4 bytes, es decir 32 bits._

**_Nota: si uno le asigna un número no entero a una variable tipo int se descarta la parte fraccional, es decir int a=5.998 se redondea a 5._**
<p>&nbsp;</p>

**float a = 0.15;** Crea una variable de tipo real con presicion simple.

_Tiene un tamaño de 4 bytes, es decir 32 bits._
<p>&nbsp;</p>

**double a = 0.15;** Crea una variable de tipo real con presicion doble.

_Tiene un tamaño de 8 bytes, es decir 64 bits._
<p>&nbsp;</p>

**char[N] = "Hola";** Crea una cadena de N caracteres.

_Cada char tiene un tamaño de 1 byte por lo que char[N] tiene N bytes._
<p>&nbsp;</p>

**bool a=true;** Crea una variable booleana.

_Solo puede ser true o false, en terminos numericos, si es 0 es false, cualquier otro numero es true._
<p>&nbsp;</p>

**string a = "Hola";** Simplificación de char.

Pertenece a la libreria "string", No es necesario indicar el tamaño de la cadena de caracteres.

## Otras funciones utiles

**std::cout << "a" << a << std::endl;** Alternativa a printf, pertenece a la libreria iostream, no es necesario indicar el formato de las variables que imprime.

**ifstream var(arch)** crea una variable var que permite leer información que se encuentra en el archivo arch (arch es una cadena de texto que contiene la ruta del archivo deseado).

## Funciones

`````C
int Funcion(int param,double param2)
{
  int i=param
  //Instrucciones
  return i;
}
`````
Las funciones en general deben de ser de algun tipo, en este caso Funcion es de tipo int, contienen ciertos parametros que requieren para su ejecución los cuales fueron declarados fuera de la función
y regresan una variable de la misma naturaleza de la función, en este caso al final de Funcion se regresa i la cual tambien es una variable de tipo int.

El conjunto de instrucciones que se realizan al llamar a la función Funcion se deben escribir dentro de las llaves **{}**.

Las funciones tipo void no regresan ningun tipo de variable.

## Memoria estatica y dinámica

La memoria estática se asigna durante el tiempo de compilación y no puede ser cambiada, ejemplo ``int arr[3];`` crea un arreglo de 3 enteros.

La memoria dinámica se asigna durante el tiempo de ejecución, ejemplo ``int *arr=malloc(x*sizeof(int));``. La función malloc asigna un numero de bytes en la memoria, para x enteros
(donde x es una variable cuyo valor calcule en alguna instruccion anterior) necesito x*sizeof(int)bytes.

_La ventaja de la memoria dinámica es que nos permite dejar el tamaño de un arreglo como una variable que puede tener un valor diferente cada vez que se ejecuta el programa._

__Una vez que ya no se use el arreglo arr asignado con memoria dinámica se recomienda liberar la memoria usando ``free(arr)``._

En c++ se tiene la alternativa ``int *arr = new[x]`` lo cual es equivalente a la asignación de memoria con malloc que se presento anteriormente.

El equivalente a la liberación de memoria es ``delete[] arr``.

_Nota: el liberar memoria significa que se puede usar sobre la misma, es decir, no borra la información que se encontraba en esa dirección de memoria._

