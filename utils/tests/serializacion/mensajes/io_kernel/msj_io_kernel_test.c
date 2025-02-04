
#include "serializacion/serializacion.h"
#include <cspecs/cspec.h>

context
{
    context(msj_memoria_io)
    {
        describe("Mensaje con op_code send_io_kernel_INICIAR_CONEXION")
        {
            char *nombreDeIO = "ImpresoraDelDiegote";
            // char *resultadoDeDeserializar;
            before
            {
                // nada
            }
            end after
            {
                free(resultadoDeDeserializar);
            }
            end it("debería ser serializado y deserializado correctamente")
            {
                t_paquete *el_paquete_del_diego = serializar_io_kernel_INICIAR_CONEXION(nombreDeIO);
                char *resultadoDeDeserializar = deserializar_io_kernel_INICIAR_CONEXION(el_paquete_del_diego);
                should_string((char *)nombreDeIO) be equal to((char *)resultadoDeDeserializar);
            }
            end
        }
        end
    }
}