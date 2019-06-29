#ifndef LIBC_H
#define LIBC_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#define isdigit(c) ((c)>='0' && (c)<='9') ? 1 : 0

size_t strlen(const char * str);
void itoa(char *buf, int base, int d);
int atoi(const char * string);
char * strrev(char * s);
char * strcpy(char * s, const char * t);
char * strncpy(char * s, const char * t, size_t n);
char * strcat(char * s, const char * t);
char * strncat(char *s, const char *t, size_t n);
const char * strchr(const char * s, char t);
int strcmp(const char * s1, const char * s2);
long strtol(char * str, char** endp, int base __attribute__((unused)));
char * strpbrk(const char * s, const char * accept);
size_t strspn(const char * s, const char * accept);
char * strtok(char * s, const char * delim);

void printf(const char * __format, ...);

#endif // LIBC_H
