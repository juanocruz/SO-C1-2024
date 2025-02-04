#include "iniciar_comunicacion.h"
#include "globals/globals.h"
#include "serializacion/serializacion.h"

void atender_cliente(void *args)
{
    t_log *logger = get_logger();
    log_debug(logger, "se conecto una io");
}

void iniciar_comunicacion_io()
{
    t_log *logger = get_logger();
    t_config_kernel *cfg = get_config();
    int fd_escucha = iniciar_servidor(logger, "Servidor Kernel", cfg->IP_MODULO, cfg->PUERTO_ESCUCHA);

    while (1)
    {
        pthread_t thread;
        int *fd_conexion_ptr = malloc(sizeof(int));
        *fd_conexion_ptr = esperar_cliente(logger, "Server Kernel", fd_escucha);

        t_paquete *paquete_a_recibir = paquete_new();
        recv_paquete(*fd_conexion_ptr, &paquete_a_recibir);
        if (paquete_a_recibir->codigo_operacion != IO_KERNEL_INICIAR_CONEXION)
        {
            log_error(logger, "Recibimos de IO un op code erroneo: %i, que quilombo que tenes aca hermano",
                      paquete_a_recibir->codigo_operacion);
            exit(1);
        }
        char *tipo_de_IO;
        deserializar_string(paquete_a_recibir->buffer, &tipo_de_IO);
        log_info(logger, "Se conecto un IO de %s", tipo_de_IO);
        paquete_destroy(paquete_a_recibir);

        /* aca es donde guardamos el fd en alguna estructura para comunicarnos con la io */
        // Todo
    }
}
