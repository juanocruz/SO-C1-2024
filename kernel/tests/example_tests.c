#include <stdio.h>
#include <stdbool.h>
#include <cspecs/cspec.h>
#include <utils/hello.h>

context (example) {
    bool la_verdad = true;

    describe("Hello world") {
        it("la_verdad should be true") {
            decir_hola("Kernel");
            should_bool(la_verdad) be equal to(true);
        } end
    } end

}