#include "comunicacion_cpu/iniciar_comunicacion.h"
#include "comunicacion_entradasalida/iniciar_comunicacion.h"
#include "comunicacion_memoria/iniciar_comunicacion.h"
#include <globals/globals.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    setup_signal_handler();
    check_args(argc, argv);
    initialize_cfg(argv[1]);

    iniciar_comunicacion_memoria();
    iniciar_comunicacion_cpu();
    iniciar_comunicacion_io(); // se queda loopeado esperando conexion/desconexion de kernel

    return EXIT_SUCCESS;
}
