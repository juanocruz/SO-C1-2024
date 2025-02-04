#ifndef MSJ_MEMORIA_IO_H_
#define MSJ_MEMORIA_IO_H_

#include "assert.h"
#include "serializacion/serializacion.h"

// KERNEL_IO_READ

t_paquete *serializar_io_kernel_INICIAR_CONEXION(char *nombreDeIO);
char *deserializar_io_kernel_INICIAR_CONEXION(t_paquete *paqueteDeserializar);

#endif