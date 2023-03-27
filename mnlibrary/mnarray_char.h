//
// Created by merhab on 2023/3/20.
//

#pragma once
#include "mnarray.h"
#include "mncstring.h"

typedef mnarray mnarray_char;

mnarray_char* mnarray_char_new();
mnarray_char* mnarray_char_init(mnarray_char* chars,char* str);