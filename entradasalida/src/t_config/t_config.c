#include "t_config.h"
#include "globals/globals.h"

static t_config_io *config = NULL;

int initialize_cfg(char *path_config)
{
    t_log *logger = get_logger();
    t_config *cfg = config_create(path_config);

    if (cfg == NULL)
    {
        log_error(logger, "No se encontro  el entradasalida.config\n");
        mem_clean_exit();
    }

    if (!config_has_property(cfg, "TIPO_INTERFAZ") || !config_has_property(cfg, "TIEMPO_UNIDAD_TRABAJO") ||
        !config_has_property(cfg, "IP_KERNEL") || !config_has_property(cfg, "PUERTO_KERNEL") ||
        !config_has_property(cfg, "IP_MEMORIA") || !config_has_property(cfg, "PUERTO_MEMORIA") ||
        !config_has_property(cfg, "PATH_BASE_DIALFS") || !config_has_property(cfg, "BLOCK_SIZE") ||
        !config_has_property(cfg, "BLOCK_COUNT"))
    {
        log_error(logger, "Le faltan propiedades a entradasalida.config\n");
        mem_clean_exit();
    }

    config = malloc(sizeof(t_config_io));

    config->TIPO_INTERFAZ = strdup(config_get_string_value(cfg, "TIPO_INTERFAZ"));
    config->TIEMPO_UNIDAD_TRABAJO = config_get_int_value(cfg, "TIEMPO_UNIDAD_TRABAJO");
    config->IP_KERNEL = strdup(config_get_string_value(cfg, "IP_KERNEL"));
    config->PUERTO_KERNEL = strdup(config_get_string_value(cfg, "PUERTO_KERNEL"));
    config->IP_MEMORIA = strdup(config_get_string_value(cfg, "IP_MEMORIA"));
    config->PUERTO_MEMORIA = strdup(config_get_string_value(cfg, "PUERTO_MEMORIA"));
    config->PATH_BASE_DIALFS = strdup(config_get_string_value(cfg, "PATH_BASE_DIALFS"));
    config->BLOCK_SIZE = config_get_int_value(cfg, "BLOCK_SIZE");
    config->BLOCK_COUNT = config_get_int_value(cfg, "BLOCK_COUNT");

    log_trace(logger, "Se cargo entradasalida.config correctamente :)\n");

    config_destroy(cfg);
    return 0;
}

t_config_io *get_config()
{
    return config;
}

void destroy_config_io()
{
    free(config->TIPO_INTERFAZ);
    free(config->IP_KERNEL);
    free(config->PUERTO_KERNEL);
    free(config->IP_MEMORIA);
    free(config->PUERTO_MEMORIA);
    free(config->PATH_BASE_DIALFS);

    free(config);
    config = NULL;
}