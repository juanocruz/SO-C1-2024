#ifndef MSJ_MEMORIA_CPU_H_
#define MSJ_MEMORIA_CPU_H_

#include "serializacion/serializacion.h"
typedef struct
{
    uint32_t pid;
    uint32_t size;
} s_memoria_cpu_resize;

typedef struct
{
    uint32_t pid;
    uint32_t pc;
} s_memoria_cpu_instruccion;

typedef struct
{
    uint32_t pid;
    uint32_t pag;
} s_memoria_cpu_marco;

s_memoria_cpu_resize *create_mem_cpu_resize_struct(uint32_t pid, uint32_t size);
s_memoria_cpu_instruccion *create_mem_cpu_instruccion_struct(uint32_t pid, uint32_t pc);
s_memoria_cpu_marco *create_mem_cpu_marco_struct(uint32_t pid, uint32_t pag);

// Desde CPU
t_paquete *serializar_c_m_resize(s_memoria_cpu_resize *s_mem_cpu_resize);
t_paquete *serializar_c_m_instruccion(s_memoria_cpu_instruccion *s_mem_cpu_instruccion);
t_paquete *serializar_c_m_marco(s_memoria_cpu_marco *s_mem_cpu_marco);

s_memoria_cpu_resize *deserializar_m_c_resize_struct(t_paquete *paquete);
s_memoria_cpu_instruccion *deserializar_m_c_instruccion_struct(t_paquete *paquete);
s_memoria_cpu_marco *deserializar_m_c_marco_struct(t_paquete *paquete);

void destroy_mem_cpu_instruccion_struct(s_memoria_cpu_instruccion *s_mem_cpu_instruccion);
void destroy_mem_cpu_marco_struct(s_memoria_cpu_marco *s_mem_cpu_marco);
void destroy_mem_cpu_resize_struct(s_memoria_cpu_resize *s_mem_cpu_resize);

// Desde Memoria
t_paquete *serializar_m_c_ok();
t_paquete *serializar_m_c_out_of_memory();

#endif