//
// Created by merhab on 2023/3/20.
//
#include <stdio.h>
#include "mnvariantList.h"
#include "mntest.h"



int main(int argc, char const *argv[]){
mnvariantList * list = mnvariantList_init(0);
mnvariant* var1 = VAR_S("nour");
mnvariantList_add(list,var1);
    test(list->array[0]== var1,"eqauls");
}


