#ifndef INICIAR_COMUNICACION_KERNEL_H_
#define INICIAR_COMUNICACION_KERNEL_H_

#include "globals/globals.h"
#include <pthread.h>
#include <serializacion/mensajes/kernel_io/msj_kernel_io.h>
#include <serializacion/serializacion.h>
#include <sockets/sockets.h>

void iniciar_comunicacion_kernel(char *nombreDeIo);
void send_io_kernel_INICIAR_CONEXION(char *nombreDeIo);
void delegante(t_paquete *paquete_reciv);
#endif