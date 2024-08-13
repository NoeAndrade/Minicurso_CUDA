/*
Tipos de errores de cuda:

Asignación de memoria   ->  0
copia de datos h->d     ->  1
copia de datos d->h     ->  2
ejecucion de kernel     ->  3
liberar memoria         ->  4
*/
#define Errorcuda(err,vectortemp,error)  if (err != cudaSuccess) {\
    switch(error){\
        case 0: fprintf(stderr, "Failed to allocate device vector %s (error code %s)!\n",\
        vectortemp,cudaGetErrorString(err));\
        break;\
        case 1: fprintf(stderr, "Failed to copy vector %s from host to device (error code %s)!\n",\
        vectortemp,cudaGetErrorString(err));\
        break;\
        case 2: fprintf(stderr, "Failed to copy vector %s from device to host (error code %s)!\n",\
        vectortemp,cudaGetErrorString(err));\
        break;\
        case 3: fprintf(stderr, "Failed to launch %s kernel (error code %s)!\n",\
        vectortemp,cudaGetErrorString(err));\
        break;\
        case 4: fprintf(stderr, "Failed to free device vector %s (error code %s)!\n",\
        vectortemp,cudaGetErrorString(err));\
        break;\
    }\
    exit(EXIT_FAILURE);\
}

//Ejemplo para asignacion de memoria
int *arr;
int size=10*sizeof(int);
err = cudaMalloc(&arr,size);
Errorcuda(err,"arr",0);
