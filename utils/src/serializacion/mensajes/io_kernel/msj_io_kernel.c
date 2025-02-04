#include "msj_io_kernel.h"

t_paquete *serializar_io_kernel_INICIAR_CONEXION(char *nombreDeIO)
{
    t_paquete *paquete = paquete_new();
    paquete->codigo_operacion = IO_KERNEL_INICIAR_CONEXION;
    serializar_string(&paquete->buffer, nombreDeIO);
    return paquete;
}

char *deserializar_io_kernel_INICIAR_CONEXION(t_paquete *paqueteDeserializar)
{
    char *nombreDeIO;
    deserializar_string(paqueteDeserializar->buffer, &nombreDeIO);
    paquete_destroy(paqueteDeserializar);
    return nombreDeIO;
}