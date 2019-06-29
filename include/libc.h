#ifndef LIBC_H
#define LIBC_H

#include <stdbool.h>
#include <stdarg.h>

typedef char                     int8_t;
typedef unsigned char           uint8_t;
typedef short                   int16_t;
typedef unsigned short         uint16_t;
typedef int                     int32_t;
typedef unsigned int           uint32_t;
typedef long long int           int64_t;
typedef unsigned long long int uint64_t;
typedef uint32_t                 size_t;

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
void * malloc(size_t size);
void free(void * ptr);

#endif // LIBC_H
