#include <comunicacion_kernel/iniciar_comunicacion.h>
#include <comunicacion_memoria/iniciar_comunicacion.h>
#include <globals/globals.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <utils/hello.h>

int main(int argc, char *argv[])
{

    setup_signal_handler();
    check_args(argc, argv);
    initialize_cfg(argv[1]);

    iniciar_comunicacion_memoria();
    iniciar_comunicacion_kernel(argv[2]);

    return EXIT_SUCCESS;
}
