/**
 * Floppa OS 3
 * Минимальное ядро для архитектуры x86
 * Автор: Mickredset
 * Некомерческая компания: Floppa os
 */
#include <iostream>
#include <string>
// библиотеки <stdint.h> использовать не получится
// с помощью C вручную выставляем конфигурацию
typedef unsigned int   uint32_t; // 32 бита (4 байта)
typedef unsigned char  uint8_t;  // 8 бит (1 байт)
typedef unsigned short uint16_t; // 16 бит (2 байта)

// Блок памяти
// 8 килобайтах файла, чтобы понять, что это вообще операционная система.
struct multiboot_header {
    uint32_t magic;    // Метка: 0x1BADB002 говорит загрузчику, что мы Multiboot-совместимы.
    uint32_t flags;    // Настройки: запрашиваем ли мы видеорежим, карту памяти и т.д.
    uint32_t checksum; // Проверка: magic + flags + checksum должны давать 0.
};

// Размещаем паспорт в специальной секции ".multiboot"
__attribute__((section(".multiboot")))
struct multiboot_header mb = {
    .magic = 0x1BADB002U,           // Битва мэджиков
    .flags = 0U,                    // Флаги не ставим, нам пока ничего не нужно от загрузчика.
    .checksum = 0x2E95A86DU         // (-(0x1BADB002 + 0))
};

// --- КОНСТАНТЫ  VGA ---
// Текстовый режим VGA начинается по адресу 0xB8000. 
#define VIDEO_MEMORY 0xB8000U
#define VGA_WIDTH 80                // Стандартная ширина консоли
#define VGA_HEIGHT 25               // Стандартная высота консоли

/**
 * Управление памятью VGA (простыми словами)
 */
void vga_putchar(char c, int x, int y, uint8_t color) {
    // функция vga_putchar
    // Каждая ячейка экрана — это 2 байта: [БАЙТ ЦВЕТА][БАЙТ СИМВОЛА ASCII]
    volatile uint16_t* video = (volatile uint16_t*)VIDEO_MEMORY;
    
    // Вычисляем индекс в одномерном массиве памяти на основе координат (x, y)
    video[y * VGA_WIDTH + x] = (uint16_t)((color << 8) | (uint8_t)c);
}

/**
 * Печать строки
 */
void vga_print(const char* str, int x, int y) {
    for (int i = 0; str[i] != '\0'; i++) {
        // 0x07U — это серый текст на черном фоне (стандарт)
        vga_putchar(str[i], x + i, y, 0x07U);
    }
}

/**
 * ГЛАВНАЯ ФУНКЦИЯ ЯДРА (_start)
 * Начало терминала для пользователя через VGA
 */
extern "C" void _start(uint32_t multiboot_info, uint32_t magic) {
    
    // 1. Проверяем, что нас загрузил правильный загрузчик
    // По спецификации Multiboot, в регистре EAX должно быть число 0x2BADB002.
    if (magic != 0x2BADB002U) {
        vga_print("FATAL ERROR: Unknown Bootloader!", 0, 0);
        goto halt_loop;
    }

    // 2. Очищаем экран
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            vga_putchar(' ', x, y, 0x00U); // 0x00 — черный на черном
        }
    }

    // При успешной загрузке
    vga_print("Floppa OS 3 kernel mode active", 0, 0);
    vga_print("FLP OS", 0, 1);
    vga_print("-----------------------------", 0, 2);
    vga_print("Status: Kernel mode active", 0, 3);
    vga_print("Wait for commands...", 0, 4);
    vga_print("Wait for commands...", 0, 5);
    vga_print("Wait for commands...", 0, 6);
    vga_print("Wait for commands...", 0, 7);
    vga_print("Wait for commands...", 0, 8);
    vga_print("C++ main.cpp", 0, 9);
    vga_print("Wait for commands...", 0, 10);
    vga_print("Wait for commands...", 0, 11);
    vga_print("Wait for commands...", 0, 12);
    vga_print("Wait for commands...", 0, 13);
    vga_print("Wait for commands...", 0, 14);
    vga_print("Wait for commands...", 0, 15);
    vga_print("Wait for commands...", 0, 16);
    vga_print("Wait for commands...", 0, 17);
    vga_print("Wait for commands...", 0, 18);
    vga_print("Wait for commands...", 0, 19);
    vga_print("Wait for commands...", 0, 20);
    

halt_loop:
    // Оптимизация
    // Цикл
    asm volatile("cli");      // Отключаем аппаратные прерывания
    while (true) {
        asm volatile("hlt");  // Переводим процессор в режим низкого энергопотребления
    }
}
