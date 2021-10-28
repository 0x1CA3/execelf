#define _GNU_SOURCE
#include "execelf.h"



/*
execelf
Date: 10/27/21
Author: 0x1CA3
*/


int file_check(char *filename) {
	FILE * executable = fopen(filename, "r");
	if (executable == NULL) {
		fprintf(stderr, "Error: File '%s' was not found!\n", filename);
		return 1;
	}
	fclose(executable);
}

static void file_execution(size_t size, char *elf, char **f_file, char **envp) {
	int des;	
	des = memfd_create("", FD_CLOEXEC);	
	write(des, elf, size);

	sprintf(e_elf, "/proc/self/fd/%u", des);
	execve(e_elf, f_file, envp);
}

int main(int argc, char **argv, char **envp) {
	int des;
	char *elf;
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <elf_file>\n", argv[0]);
		exit(EXIT_FAILURE);
	} else {
		if (file_check(argv[1]) == 1) {
			exit(EXIT_FAILURE);
		} else {
			des = open(argv[1], O_RDONLY);
			fstat(des, &l_stat);
			elf = malloc(l_stat.st_size);
			read(des, elf, l_stat.st_size);
			file_execution(l_stat.st_size, elf, &argv[1], envp);	
		}
	}
	EXIT_SUCCESS;
}
