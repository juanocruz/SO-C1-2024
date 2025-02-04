#include "msj_memoria_cpu.h"

s_memoria_cpu_resize *create_mem_cpu_resize_struct(uint32_t pid, uint32_t size)
{
    s_memoria_cpu_resize *s_mem_cpu_resize = malloc(sizeof(s_memoria_cpu_resize));
    s_mem_cpu_resize->pid = pid;
    s_mem_cpu_resize->size = size;

    return s_mem_cpu_resize;
}

s_memoria_cpu_instruccion *create_mem_cpu_instruccion_struct(uint32_t pid, uint32_t pc)
{
    s_memoria_cpu_instruccion *s_mem_cpu_instruccion = malloc(sizeof(s_memoria_cpu_instruccion));
    s_mem_cpu_instruccion->pid = pid;
    s_mem_cpu_instruccion->pc = pc;

    return s_mem_cpu_instruccion;
}

s_memoria_cpu_marco *create_mem_cpu_marco_struct(uint32_t pid, uint32_t pag)
{
    s_memoria_cpu_marco *s_mem_cpu_marco = malloc(sizeof(s_memoria_cpu_marco));
    s_mem_cpu_marco->pid = pid;
    s_mem_cpu_marco->pag = pag;

    return s_mem_cpu_marco;
}

s_memoria_cpu_resize *deserializar_m_c_resize_struct(t_paquete *paquete)
{
    s_memoria_cpu_resize *s_mem_cpu_resize = malloc(sizeof(s_memoria_cpu_resize));

    deserializar_uint32_t(paquete->buffer, &s_mem_cpu_resize->pid);
    deserializar_uint32_t(paquete->buffer, &s_mem_cpu_resize->size);

    return s_mem_cpu_resize;
}

s_memoria_cpu_instruccion *deserializar_m_c_instruccion_struct(t_paquete *paquete)
{
    s_memoria_cpu_instruccion *s_mem_cpu_instruccion = malloc(sizeof(s_memoria_cpu_instruccion));

    deserializar_uint32_t(paquete->buffer, &s_mem_cpu_instruccion->pid);
    deserializar_uint32_t(paquete->buffer, &s_mem_cpu_instruccion->pc);

    return s_mem_cpu_instruccion;
}

s_memoria_cpu_marco *deserializar_m_c_marco_struct(t_paquete *paquete)
{
    s_memoria_cpu_marco *s_mem_cpu_marco = malloc(sizeof(s_memoria_cpu_marco));

    deserializar_uint32_t(paquete->buffer, &s_mem_cpu_marco->pid);
    deserializar_uint32_t(paquete->buffer, &s_mem_cpu_marco->pag);

    return s_mem_cpu_marco;
}

void destroy_mem_cpu_instruccion_struct(s_memoria_cpu_instruccion *s_mem_cpu_instruccion)
{
    free(s_mem_cpu_instruccion);
    s_mem_cpu_instruccion = NULL;
}

void destroy_mem_cpu_marco_struct(s_memoria_cpu_marco *s_mem_cpu_marco)
{
    free(s_mem_cpu_marco);
    s_mem_cpu_marco = NULL;
}

void destroy_mem_cpu_resize_struct(s_memoria_cpu_resize *s_mem_cpu_resize)
{
    free(s_mem_cpu_resize);
    s_mem_cpu_resize = NULL;
}

t_paquete *serializar_m_c_ok()
{
    t_paquete *paquete = paquete_new();
    paquete->codigo_operacion = OK_GRAL;

    return paquete;
}

t_paquete *serializar_m_c_out_of_memory()
{
    t_paquete *paquete = paquete_new();
    paquete->codigo_operacion = MEMORIA_CPU_OUT_OF_MEMORY;

    return paquete;
}

// Serializacion desde CPU
t_paquete *serializar_c_m_resize(s_memoria_cpu_resize *s_mem_cpu_resize)
{
    t_paquete *paquete = paquete_new();
    paquete->codigo_operacion = CPU_MEMORIA_RESIZE;

    serializar_uint32_t(&paquete->buffer, s_mem_cpu_resize->pid);
    serializar_uint32_t(&paquete->buffer, s_mem_cpu_resize->size);

    return paquete;
}

t_paquete *serializar_c_m_instruccion(s_memoria_cpu_instruccion *s_mem_cpu_instruccion)
{
    t_paquete *paquete = paquete_new();
    paquete->codigo_operacion = CPU_MEMORIA_OBTENER_INSTRUCCIONES;

    serializar_uint32_t(&paquete->buffer, s_mem_cpu_instruccion->pid);
    serializar_uint32_t(&paquete->buffer, s_mem_cpu_instruccion->pc);

    return paquete;
}

t_paquete *serializar_c_m_marco(s_memoria_cpu_marco *s_mem_cpu_marco)
{
    t_paquete *paquete = paquete_new();
    paquete->codigo_operacion = CPU_MEMORIA_OBTENER_MARCO;

    serializar_uint32_t(&paquete->buffer, s_mem_cpu_marco->pid);
    serializar_uint32_t(&paquete->buffer, s_mem_cpu_marco->pag);

    return paquete;
}
