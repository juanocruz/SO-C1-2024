#ifndef T_CONFIG_H_
#define T_CONFIG_H_

#include <stdlib.h>
#include <string.h>

#include <commons/config.h>
#include <commons/log.h>

typedef struct
{
    char *TIPO_INTERFAZ;
    int TIEMPO_UNIDAD_TRABAJO;
    char *IP_KERNEL;
    char *PUERTO_KERNEL;
    char *IP_MEMORIA;
    char *PUERTO_MEMORIA;
    char *PATH_BASE_DIALFS;
    int BLOCK_SIZE;
    int BLOCK_COUNT;
} t_config_io;

int initialize_cfg(char *path_config);
t_config_io *get_config();
void destroy_config_io();

#endif