#include "comunicacion/iniciar_servidor_memoria.h"
#include <globals/globals.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <t_config/t_config.h>
#include <utils/hello.h>

int main(int argc, char *argv[])
{
    setup_signal_handler();
    check_args(argc, argv);
    initialize_cfg(argv[1]);

    iniciar_servidor_memoria(); // se queda loopeado dentro de la funcion

    return EXIT_SUCCESS;
}
