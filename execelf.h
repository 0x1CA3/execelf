#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>


/*
execelf.h
Date: 10/27/21
Author: 0x1CA3
*/


char e_elf[256];
struct stat l_stat;
int file_check(char *filename);
static void file_execution(size_t size, char *elf, char **f_file, char **envp);
