#include "screen.h"

void vga_putchar(char c, int x, int y, uint8_t color) {
    volatile uint16_t* video = (volatile uint16_t*)VIDEO_MEMORY;
    video[y * VGA_WIDTH + x] = (uint16_t)((color << 8) | (uint8_t)c);
}

void vga_print(const char* str, int x, int y) {
    for (int i = 0; str[i] != '\0'; i++) {
        vga_putchar(str[i], x + i, y, 0x07U);
    }
}

void clear_screen() {
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            vga_putchar(' ', x, y, 0x00U);
        }
    }
}
