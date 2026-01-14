#ifndef SCREEN_H
#define SCREEN_H

#include <cstdint>

// Константы VGA
#define VIDEO_MEMORY 0xB8000U
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

// Прототипы функций
void vga_putchar(char c, int x, int y, uint8_t color);
void vga_print(const char* str, int x, int y);
void clear_screen();

#endif // SCREEN_H
