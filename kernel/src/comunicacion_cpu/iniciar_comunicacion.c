#include "iniciar_comunicacion.h"

int fd_server_dispatch_cpu;
int fd_server_interrupt_cpu;

void iniciar_comunicacion_cpu()
{
    t_log *logger = get_logger();
    t_config_kernel *cfg = get_config();
    if (!generar_conexion(logger, "servidor cpu dispatch", &fd_server_dispatch_cpu, cfg->IP_CPU,
                          cfg->PUERTO_CPU_DISPATCH))
    {
        exit(1); // TODO crear funcion para liberar datos de todo.
    }

    if (!generar_conexion(logger, "servidor cpu interrupt", &fd_server_interrupt_cpu, cfg->IP_CPU,
                          cfg->PUERTO_CPU_INTERRUPT))
    {

        exit(1); // TODO crear funcion para liberar datos de todo.
    }
}
