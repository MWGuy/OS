#include <libc.h>
#include <tty.h>
#include <memory.h>

size_t strlen(const char* str) {
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

void itoa(char *buf, int base, int d) {
    char *p = buf;
    char *p1, *p2;
    unsigned long ud = d;
    int divisor = 10;

    if (base == 'd' && d < 0) {
        *p++ = '-';
        buf++;
        ud = -d;
    }
    else if (base == 'x')
        divisor = 16;

    do {
        int remainder = ud % divisor;
        *p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
    } while (ud /= divisor);

    *p = 0;

    p1 = buf;
    p2 = p - 1;
    while (p1 < p2) {
        char tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
        p1++;
        p2--;
    }
}

int atoi(const char * string) {
    int ret=0;
    while (isdigit(* string)) {
        ret *= 10;
        ret += (int) (* string - '0');
        string++;
    }

    return ret;
}

char * strrev(char* s) {
    unsigned int i, j;
    char c;
    for(i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
    return s;
}

char * strcpy(char * s, const char * t) {
    while((*s++ = *t++));
    return s;
}

char * strncpy(char * s, const char * t, size_t n) {
    size_t i = 0;
    while((i++ < n) && (*s++ = *t++));
    return s;
}

char * strcat(char * s, const char * t) {
    strcpy(s+strlen(s),t);
    return s;
}

char * strncat(char *s, const char *t, size_t n) {
    strncpy(s+strlen(s),t,n);
    return s;
}

const char * strchr(const char *s, char t) {
    while(*s) {
        if(*s == t) return s;
        ++s;
    }

    return nullptr;
}

int strcmp(const char * s1, const char * s2) {
    for (; *s1 == *s2; s1++, s2++)
        if (*s1 == '\0')
            return 0;

    return ((*(unsigned char *)s1 < *(unsigned char *)s2) ? -1 : +1);
}

int strncmp(const char * s1, const char * s2, size_t num) {
    for(size_t i=0; i<num; i++) {
        if(s1[i] != s2[i])
            return 1;
    }

    return 0;
}

long strtol(char * str, char ** endp, int base __attribute__((unused))) {
    long ret = 0; int i=0;

    while(isdigit(str[i])) {
        ret *= 10;
        ret += str[i] - '0';
    }

    *endp = &str[i];
    if(str[0] == '-')
        ret = -ret;

    if(str[0] == '+')
        ret = +ret;

    return ret;
}
char * strpbrk(const char * s, const char * accept) {
    while (*s != '\0') {
        const char *a = accept;
        while (*a != '\0')
            if (*a++ == *s)
                return (char *) s;
        ++s;
    }
    return nullptr;
}

size_t strspn(const char * s, const char * accept) {
    const char *p, *a;
    size_t count = 0;

    for (p = s; *p != '\0'; ++p) {
        for (a = accept; *a != '\0'; ++a)
            if (*p == *a)
                break;

        if (*a == '\0')
            return count;
        else
            ++count;
    }
    return count;
}

char * strtok(char * s, const char * delim)
{
    static char * olds = nullptr;
    char * token;

    if (s == nullptr)
        s = olds;

    /* Scan leading delimiters.  */
    s += strspn (s, delim);
    if (*s == '\0') {
        olds = s;
        return nullptr;
    }

    /* Find the end of the token.  */
    token = s;
    s = strpbrk (token, delim);
    if (s == nullptr) {
        /* This token finishes the string.  */
        olds = token;
    } else {
        /* Terminate the token and make OLDS point past it.  */
        *s = '\0';
        olds = s + 1;
    }

    return token;
}

void printf(const char *format, ...) {
    char ** arg = (char **) &format;
    int c;
    char buf[20];

    arg++;

    while ((c = *format++) != 0) {
        if (c != '%')
            TTY::put_char(c);
        else {
            char *p, *p2;
            int pad0 = 0, pad = 0;

            c = *format++;
            if (c == '0') {
                pad0 = 1;
                c = *format++;
            }

            if (c >= '0' && c <= '9') {
                pad = c - '0';
                c = *format++;
            }

            switch (c) {
                case 'd':
                case 'u':
                case 'x':
                case 'i':
                    itoa (buf, c, *((int *) arg++));
                    p = buf;
                    goto string;
                case 's':
                    p = *arg++;
                    if (! p)
                        p = "(null)";
                string:
                    for (p2 = p; *p2; p2++);
                    for (; p2 < p + pad; p2++)
                        TTY::put_char(pad0 ? '0' : ' ');
                    while (*p)
                        TTY::put_char(*p++);
                    break;

                default:
                    TTY::put_char(*((int *) arg++));
                    break;
            }
        }
    }
}

void * malloc(size_t size) {
    if(MemoryManager::activeMemoryManager == nullptr)
        return nullptr;
    return MemoryManager::activeMemoryManager->malloc(size);
}

void free(void * ptr) {
    if(MemoryManager::activeMemoryManager != nullptr)
        MemoryManager::activeMemoryManager->free(ptr);
}