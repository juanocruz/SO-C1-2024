#include "user_mem.h"

static void *user_mem = NULL;

static pthread_mutex_t mutex_user_mem;

void instanciate_user_mem()
{
    t_config_memoria *cfg = get_config();
    if (user_mem == NULL)
    {
        user_mem = malloc(cfg->TAM_MEMORIA);
        pthread_mutex_init(&mutex_user_mem, NULL);
    }
}

void destroy_user_mem()
{
    pthread_mutex_lock(&mutex_user_mem);
    free(user_mem);
    user_mem = NULL;
    pthread_mutex_unlock(&mutex_user_mem);
    pthread_mutex_destroy(&mutex_user_mem);
}

void *get_val_from_usermem(uint32_t position, uint32_t size)
{
    void *value = NULL;
    value = malloc(size);
    memcpy(value, user_mem + position, size);

    return value;
}

void set_val_to_usermem(void *value, uint32_t position, uint32_t size)
{
    memcpy(user_mem + position, value, size);
}
