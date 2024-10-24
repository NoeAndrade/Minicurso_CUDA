#ifndef CUERR_HEADER
#define CUERR_HEADER
//en este header definiremos la instrucción para asegurar que una API de Cuda se ejecuto correctamente
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

#endif
