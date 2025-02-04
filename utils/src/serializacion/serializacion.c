#include "serializacion.h"

t_paquete* paquete_new() {
    t_paquete* p = malloc(sizeof(t_paquete));
    p->buffer = malloc(sizeof(t_buffer));
    p->buffer->size = 0;
    /* no hago un malloc para el stream porque de eso
     * se encargan las funciones para serializar */
    return p;
}

void paquete_destroy(t_paquete* p) {
    if(p->buffer->size > 0)
        free(p->buffer->stream);
    free(p->buffer);
    free(p);
}

bool recv_paquete(int fd, t_paquete** p) {
    *p = malloc(sizeof(t_paquete));
    (*p)->buffer = malloc(sizeof(t_buffer));

    int recv_status;
    recv_status = recv(fd, &(*p)->codigo_operacion, sizeof(op_code), MSG_WAITALL);
    
    if (recv_status != sizeof(op_code)) {
        free((*p)->buffer);
        free(*p);
        return false;
    }
    
    /*
    if( recv_status < 0) {
        free((*p)->buffer);
        free(*p);
        return false;
    }
    */

    //printf("recv error: %s\n", strerror(recv_status));

    if( recv(fd, &(*p)->buffer->size, sizeof(uint32_t), 0) == -1) {
        free((*p)->buffer);
        free(*p);
        return false;
    }

    if((*p)->buffer->size != 0) {
        (*p)->buffer->stream = malloc((*p)->buffer->size);

        if(recv(fd, (*p)->buffer->stream, (*p)->buffer->size, 0) == -1) {
            paquete_destroy(*p);
            return false;
        }
    }

    return true;
}

bool send_paquete(int fd, t_paquete* p) {
    int offset = 0;
    uint32_t size_paquete_serializado = sizeof(op_code) + sizeof(uint32_t) + p->buffer->size;
    void* paquete_serializado = malloc(size_paquete_serializado);
    
    memcpy(paquete_serializado + offset, &p->codigo_operacion, sizeof(op_code));
    offset += sizeof(op_code);
    memcpy(paquete_serializado + offset, &p->buffer->size, sizeof(uint32_t));
    offset += sizeof(uint32_t);
    if (p->buffer->size != 0)
        memcpy(paquete_serializado + offset, p->buffer->stream, p->buffer->size);

    if (send(fd, paquete_serializado, size_paquete_serializado, 0) == -1) {
        free(paquete_serializado);
        return false;
    }
    //printf("%d",p->codigo_operacion);
    free(paquete_serializado);
    free(p->buffer->stream);
    free(p->buffer);
    free(p);

    return true;
}


void serializar_uint8_t(t_buffer** b, uint8_t int8) {
    if( (*b)->size == 0 )
        (*b)->stream = malloc(sizeof(uint8_t));
    else
        (*b)->stream = realloc((*b)->stream, (*b)->size + sizeof(uint8_t));
    
    memcpy((*b)->stream + (*b)->size, &int8, sizeof(uint8_t));
    (*b)->size += sizeof(uint8_t);
}

void serializar_uint16_t(t_buffer** b, uint16_t int16) {
    if( (*b)->size == 0 )
        (*b)->stream = malloc(sizeof(uint16_t));
    else
        (*b)->stream = realloc((*b)->stream, (*b)->size + sizeof(uint16_t));
    
    memcpy((*b)->stream + (*b)->size, &int16, sizeof(uint16_t));
    (*b)->size += sizeof(uint16_t);
}

void serializar_uint32_t(t_buffer** b, uint32_t int32) {
    if( (*b)->size == 0 )
        (*b)->stream = malloc(sizeof(uint32_t));
    else
        (*b)->stream = realloc((*b)->stream, (*b)->size + sizeof(uint32_t));
    
    memcpy((*b)->stream + (*b)->size, &int32, sizeof(uint32_t));
    (*b)->size += sizeof(uint32_t);
}

void serializar_string(t_buffer** b, char* string) {
    uint32_t str_length = string_length(string) +1;
    serializar_uint32_t(b, str_length);
    
    if( (*b)->size == 0 )
        (*b)->stream = malloc(str_length);
    else
        (*b)->stream = realloc((*b)->stream, (*b)->size + str_length);
    
    memcpy((*b)->stream + (*b)->size, string, str_length);
    (*b)->size += str_length;
}

void serializar_motivo_de_devolucion(t_buffer** b, motivo_devolucion motivo) {
    if( (*b)->size == 0 )
        (*b)->stream = malloc(sizeof(motivo_devolucion));
    else
        (*b)->stream = realloc((*b)->stream, (*b)->size + sizeof(motivo_devolucion));
    
    memcpy((*b)->stream + (*b)->size, &motivo, sizeof(motivo_devolucion));
    (*b)->size += sizeof(motivo_devolucion);
}

void deserializar_uint8_t(t_buffer* b, uint8_t* int8) {
    if(b->size == 0) {
        printf("El stream esta vacio.\n");
        return;
        
    }
    if (b->size < sizeof(uint8_t)) {
        printf("Estas deserializando mas bytes de los que hay en el stream.\n");
        return;
    }
    memcpy(int8, b->stream, sizeof(uint8_t));
    b->stream += sizeof(uint8_t);
    b->size -= sizeof(uint8_t);
}

void deserializar_uint16_t(t_buffer* b, uint16_t* int16) {
    if(b->size == 0) {
        printf("El stream esta vacio.\n");
        return;
    }
    if (b->size < sizeof(16)) {
        printf("Estas deserializando mas bytes de los que hay en el stream.\n");
        return;
    }
    memcpy(int16, b->stream, sizeof(uint16_t));
    b->stream += sizeof(uint16_t);
    b->size -= sizeof(uint16_t);
}

void deserializar_uint32_t(t_buffer* b, uint32_t* int32) {
    if(b->size == 0) {
        printf("El stream esta vacio.\n");
        return;
    }
    if (b->size < sizeof(uint32_t)) {
        printf("Estas deserializando mas bytes de los que hay en el stream.\n");
        return;
    }
    memcpy(int32, b->stream, sizeof(uint32_t));
    b->stream += sizeof(uint32_t);
    b->size -= sizeof(uint32_t);
}

void deserializar_string(t_buffer* b, char** string) {
    if(b->size == 0) {
        printf("El stream esta vacio.\n");
        return;
    }
    
    uint32_t str_length;
    deserializar_uint32_t(b, &str_length);
    if (b->size < str_length) {
        printf("Estas deserializando mas bytes de los que hay en el stream.\n");
        return;
    }
    *string = malloc(str_length);

    memcpy(*string, b->stream, str_length);
    b->stream += str_length;
    b->size -= str_length;
}


void serializar_t_list(t_buffer** b, t_list* l, void(*serializador)(void*, void*)) {
    serializar_uint32_t(b, (uint32_t) list_size(l));
    
    t_list_iterator* iterator = list_iterator_create(l);

    while (list_iterator_has_next(iterator)) {
        serializador(b, list_iterator_next(iterator));
    }
    

    list_iterator_destroy(iterator);
}

void deserializar_t_list(t_buffer* b, t_list** l, void*(*deserializador)(void*)) {
    uint32_t largo;
    deserializar_uint32_t(b, &largo);

    for (uint32_t i = 0; i < largo; i++) {
        
        list_add(*l, deserializador(b));
    }

}

void deserializar_motivo_de_devolucion(t_buffer* b, motivo_devolucion* motivo) {
    if(b->size == 0) {
        printf("El stream esta vacio.\n");
        return;
        
    }
    if (b->size < sizeof(motivo_devolucion)) {
        printf("Estas deserializando mas bytes de los que hay en el stream.\n");
        return;
    }
    memcpy(motivo, b->stream, sizeof(motivo_devolucion));
    b->stream += sizeof(motivo_devolucion);
    b->size -= sizeof(motivo_devolucion);
}