#include "cqdir_t.h"

char cqdir_test()
{
   print_green(QDir_separator());
   printf("\n");
   char *str=QStandardPaths_writableLocation(QStandardPaths_DesktopLocation);
   mnstring path;
   mnstring_init_cstring_ref(&path,str);
   mnstring_concat_msstr_cstr(&path,QDir_separator());
   mnstring_concat_msstr_cstr(&path,"TESTING");
   char res=QDir_mkdir(path.string); 
   res=res*QDir_exists(path.string);
   mnstring_clean(&path);
   return res;
}