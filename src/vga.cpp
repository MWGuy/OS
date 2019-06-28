#include <vga.h>

uint8_t VGA::entry_color(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}
 
uint16_t VGA::entry(unsigned char uc, uint8_t color) {
	return (uint16_t) uc | (uint16_t) color << 8;
}
