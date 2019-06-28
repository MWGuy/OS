#include <tty.h>

extern "C" void kmain(const void* multiboot_structure, unsigned int multiboot_magic)
{
	TTY::initialize();
    TTY::write_string("Hello, new user!\nI`m new OS!\n");
    TTY::set_color(VGA_COLOR_LIGHT_BLUE);
    TTY::write_string("Hello, kernel World!\n");
    while(1);
}

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;

extern "C" void constructors()
{
    for(constructor * i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}
