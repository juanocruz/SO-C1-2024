#ifndef INICIAR_SERVIDOR_MEMORIA_H_
#define INICIAR_SERVIDOR_MEMORIA_H_

#include <sockets/sockets.h>
#include <pthread.h>
#include "globals/globals.h"
#include <serializacion/serializacion.h>

typedef struct {
    int* fd;
} client_thread_args;

void iniciar_servidor_memoria();

#endif