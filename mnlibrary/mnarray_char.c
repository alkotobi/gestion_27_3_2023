//
// Created by merhab on 2023/3/20.
//
#include "mnarray_char.h"

mnarray_char *mnarray_char_new() {
    return mnarray_new();
}

mnarray_char *mnarray_char_init(mnarray_char *chars, char *str) {
    size_t i=0;
    while (str[i]!=0){
        mnarray_add(chars, (void *) str[i]);
    }
}
