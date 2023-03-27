#pragma once
typedef void QDir;

char *QDir_separator();//tested
char *QDir_cleanPath(char *path);
char QDir_mkdir(char* path);
char QDir_exists(char *path);
