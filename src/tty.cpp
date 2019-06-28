#include <tty.h>

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t * terminal_buffer;

void TTY::initialize() {
	terminal_row = 0;
    terminal_column = 0;
    terminal_color = VGA::entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = VGA::entry(' ', terminal_color);
		}
	}
}
 
void TTY::set_color(uint8_t color) {
    terminal_color = color;
}
 
void TTY::put_entry_at(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = VGA::entry(c, color);
}
 
void TTY::put_char(char c) {
    TTY::put_entry_at(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
        terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
            terminal_row = 0;
	}
}
 
void TTY::write(const char* data, size_t size) {
	size_t g = 0;
	
	for (size_t i = 0; i < size; i++) {
		if (data[i] == '\n') {
			for (int j = 0; j < VGA_WIDTH - g; ++j)
                TTY::put_char(' ');
			g = 0;
		} else {
			g++;
            TTY::put_char(data[i]);
		}
	}
}
 
void TTY::write_string(const char * data) {
    TTY::write(data, strlen(data));
}
