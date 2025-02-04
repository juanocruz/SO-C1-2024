#include "iniciar_comunicacion.h"
#include "globals/globals.h"

int fd_kernel;

void send_io_kernel_INICIAR_CONEXION(char *nombreDeIo)
{
    t_log *logger = get_logger();

    t_paquete *paquete_a_enviar = serializar_io_kernel_INICIAR_CONEXION(nombreDeIo);

    if (!send_paquete(fd_kernel, paquete_a_enviar))
    {
        log_error(logger, "Paquete falluto \n");
        mem_clean_exit();
    }
}

void delegante(t_paquete *paquete_reciv)
{
    t_log *logger = get_logger();
    switch (paquete_reciv->codigo_operacion)
    {
    case KERNEL_IO_FS_CREATE:
        log_info(logger, "Kernel nos envio - KERNEL_IO_FS_CREATE");
        // TODO(colo): algo
        break;
    case KERNEL_IO_FS_DELETE:
        log_info(logger, "Kernel nos envio - KERNEL_IO_FS_DELETE");
        // TODO
        break;
    case KERNEL_IO_FS_READ:
        log_info(logger, "Kernel nos envio - KERNEL_IO_FS_READ");
        // TODO
        break;
    case KERNEL_IO_FS_TRUNCATE:
        log_info(logger, "Kernel nos envio - KERNEL_IO_FS_TRUNCATE");
        // TODO
        break;
    case KERNEL_IO_FS_WRITE:
        log_info(logger, "Kernel nos envio - KERNEL_IO_FS_WRITE");
        // TODO
        break;
    case KERNEL_IO_GEN_ZZZ:
        log_info(logger, "Kernel nos envio - KERNEL_IO_GEN_ZZZ");
        // TODO
        break;
    case KERNEL_IO_STDIN_READ:
        log_info(logger, "Kernel nos envio - KERNEL_IO_STDIN_READ");
        // TODO
        break;
    case KERNEL_IO_STDOUT_WRITE:
        log_info(logger, "Kernel nos envio - KERNEL_IO_STDOUT_WRITE");
        // TODO
        break;
    default:
        log_error(logger, "Recibimos de kernel un op code erroneo: %i, seguramente es culpa de juano",
                  paquete_reciv->codigo_operacion);
        mem_clean_exit();
        break;
    }
}

void iniciar_comunicacion_kernel(char *nombreDeIo)
{
    t_log *logger = get_logger();
    t_config_io *cfg = get_config();
    if (!generar_conexion(logger, "Server kernel", &fd_kernel, cfg->IP_KERNEL, cfg->PUERTO_KERNEL))
    {
        mem_clean_exit();
    }
    send_io_kernel_INICIAR_CONEXION(nombreDeIo);

    t_paquete *paquete_a_recibir = paquete_new();
    while (recv_paquete(fd_kernel, &paquete_a_recibir))
    {
        delegante(paquete_a_recibir);
    }
    paquete_destroy(paquete_a_recibir);
    liberar_conexion(&fd_kernel);
}
