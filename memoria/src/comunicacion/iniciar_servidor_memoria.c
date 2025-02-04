#include "iniciar_servidor_memoria.h"
#include "globals/globals.h"

void atender_cliente(void *args)
{
    t_log *logger = get_logger();
    client_thread_args *thread_args = (client_thread_args *)args;
    t_paquete *paquete_a_recibir = paquete_new();
    while (recv_paquete(*(thread_args->fd), &paquete_a_recibir))
    {
        // aca se manejan todas las peticiones que puede llegar a pedir un cliente
    }
    log_warning(logger, "Se desconecto un cliente");

    free(thread_args->fd);
    free(thread_args);
}

void iniciar_servidor_memoria()
{
    t_log *logger = get_logger();
    t_config_memoria *cfg = get_config();
    int fd_escucha = iniciar_servidor(logger, "Servidor Memoria", cfg->IP_MODULO, cfg->PUERTO_ESCUCHA);

    while (1)
    {
        pthread_t thread;
        client_thread_args *args = malloc(sizeof(client_thread_args));
        args->fd = malloc(sizeof(int));
        *(args->fd) = esperar_cliente(logger, "Server Memoria", fd_escucha);
        pthread_create(&thread, NULL, (void *)atender_cliente, (void *)args);
        pthread_detach(thread);
    }
}
