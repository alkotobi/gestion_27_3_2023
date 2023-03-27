#include <stdio.h>
#include "mnarray_t.h"
#include "cstring_test.h"
#include "mnvariant_t.h"
#include "mncstringList_t.h"
#include "mnstring_t.h"
#include "mndictionary_t.h"

int main(int argc, char const *argv[])
{
 assert(mndictionary_test());
 assert(mnarray_test());
 assert(cstring_test());
 assert(mnvariant_test());
 assert(mncstingList_test());
 assert(mnstring_test());
 print_blue("\n");print_blue("\n");print_blue("\n");
 print_green("ALL WORKING ALHAMDO LILAH\n");
   // printf("hello world\n\n %d",*(arr->array[0]));
  //char r = do_test();
    /* code */
  return 0;
}