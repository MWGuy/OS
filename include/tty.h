#ifndef TERMINAL_H
#define TERMINAL_H

#include <vga.h>

class TTY {
public:
	static void initialize();
	static void set_color(uint8_t color);
	static void put_entry_at(char c, uint8_t color, size_t x, size_t y);
	static void put_char(char c);
	static void write(const char * data, size_t size);
	static void write_string(const char* data);
};

#endif // TERMINAL_H
