#ifndef INICIAR_COMUNICACION_KERNEL_H_
#define INICIAR_COMUNICACION_KERNEL_H_

#include <sockets/sockets.h>
#include <pthread.h>
#include "globals/globals.h"
#include <serializacion/serializacion.h>

typedef struct {
    int* fd;
} client_thread_args_dipatch;

typedef struct {
    int* fd;
} client_thread_args_interrupt;

void iniciar_servidor_cpu();

#endif