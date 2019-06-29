#include <tty.h>
#include <multiboot.h>

extern "C" void kmain(multiboot_info_t * multiboot_structure, unsigned int multiboot_magic) {
    TTY::initialize();

    printf("Kernel loaded successfully\n");

    while(1);
}

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;

extern "C" void constructors() {
    for(constructor * i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}
