#include "iniciar_comunicacion.h"
#include "globals/globals.h"

int fd_escucha_dispatch;
int fd_escucha_interrupt;

void atender_cliente_dispatch(void *args)
{
    t_log *logger = get_logger();

    client_thread_args_dipatch *thread_args = (client_thread_args_dipatch *)args;
    t_paquete *paquete_a_recibir = paquete_new();
    while (recv_paquete(*(thread_args->fd), &paquete_a_recibir))
    {
        // aca se manejan todas las peticiones que puede llegar a pedir un cliente
    }
    log_warning(logger, "Se desconecto un cliente");

    free(thread_args->fd);
    free(thread_args);
}

void atender_cliente_interrupt(void *args)
{
    t_log *logger = get_logger();

    client_thread_args_interrupt *thread_args = (client_thread_args_interrupt *)args;
    t_paquete *paquete_a_recibir = paquete_new();
    while (recv_paquete(*(thread_args->fd), &paquete_a_recibir))
    {
        // aca se manejan todas las peticiones que puede llegar a pedir un cliente
    }
    log_warning(logger, "Se desconecto un cliente");

    free(thread_args->fd);
    free(thread_args);
}

void iniciar_servidor_cpu()
{
    t_log *logger = get_logger();
    t_config_cpu *cfg = get_config();

    fd_escucha_dispatch =
        iniciar_servidor(logger, "Servidor CPU Dispatch", cfg->IP_MODULO, cfg->PUERTO_ESCUCHA_DISPATCH);
    fd_escucha_interrupt =
        iniciar_servidor(logger, "Servidor CPU Interrupt", cfg->IP_MODULO, cfg->PUERTO_ESCUCHA_INTERRUPT);

    while (1)
    {
        pthread_t thread_dispatch, thread_interrupt;
        client_thread_args_dipatch *args_dispatch = malloc(sizeof(client_thread_args_dipatch));
        args_dispatch->fd = malloc(sizeof(int));
        client_thread_args_interrupt *args_interrupt = malloc(sizeof(client_thread_args_interrupt));
        args_interrupt->fd = malloc(sizeof(int));

        *(args_dispatch->fd) = esperar_cliente(logger, "Servidor CPU Dispatch", fd_escucha_dispatch);
        *(args_interrupt->fd) = esperar_cliente(logger, "Servidor CPU Interrupt", fd_escucha_interrupt);

        pthread_create(&thread_dispatch, NULL, (void *)atender_cliente_dispatch, (void *)args_dispatch);

        pthread_create(&thread_interrupt, NULL, (void *)atender_cliente_interrupt, (void *)args_interrupt);

        pthread_join(thread_dispatch, NULL);
        pthread_join(thread_interrupt, NULL);
    }
}