#include "user_mem/user_mem.h"
#include <cspecs/cspec.h>

context(User_memory) {

    initialize_cfg("memoria.config"); // podemos tener configs diferentes para los tests
    instanciate_user_mem();

    describe("User memory"){
        
        it("should set and get values from memory"){

            uint32_t val = 3;
            uint32_t position = 0;
            uint32_t size = sizeof(val);

            set_val_to_usermem((void *)&val, position, size);

            uint32_t mem_val = *(uint32_t *)get_val_from_usermem(position, size);

            // ↑ no me gusta el casteo, pero lo hago solo en test
            // memoria no le importa el tipo, mete y saca lo que sea. No pregutna

            should_int(mem_val) be equal to(val);
        }end

    }end

    destroy_user_mem();
}