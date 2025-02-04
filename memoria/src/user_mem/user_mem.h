#ifndef INICIAR_MEMORIA_USUARIO_H_
#define INICIAR_MEMORIA_USUARIO_H_

#include "t_config/t_config.h"
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void instanciate_user_mem();

void destroy_user_mem();

/// @brief Get a value from the user memory
/// @param position the initial position (phisical address) of the value to get
/// @param size the size of the value to get
void *get_val_from_usermem(uint32_t position, uint32_t size);

/// @brief Sets a value in the user memory, in a specific position
/// @param value the value to save in memory position (phisical address) of the value to get
/// @param position the initial position (phisical address) of the value to get
/// @param size the size of the value to set
void set_val_to_usermem(void *value, uint32_t position, uint32_t size);

#endif