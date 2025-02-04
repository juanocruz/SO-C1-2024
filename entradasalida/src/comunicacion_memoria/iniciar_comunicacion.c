#include "iniciar_comunicacion.h"

int fd_memoria;

void iniciar_comunicacion_memoria()
{
    t_log *logger = get_logger();
    t_config_io *cfg = get_config();
    if (!generar_conexion(logger, "Server Memoria", &fd_memoria, cfg->IP_MEMORIA, cfg->PUERTO_MEMORIA))
    {
        mem_clean_exit();
    }
}
