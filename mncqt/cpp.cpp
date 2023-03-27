
#include "cpp.h"

extern "C"
void cpp_free(void* var) {
    delete (var);
}
