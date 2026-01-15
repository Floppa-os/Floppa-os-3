// Ручное определение типов вместо #include <cstdint>
typedef unsigned int   uint32_t;
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;

// Multiboot header (спецификация Multiboot 1)
struct multiboot_header {
    uint32_t magic;      // Магическое число
    uint32_t flags;      // Флаги опций
    uint32_t checksum;    // Контрольная сумма
};

// Размещение заголовка в специальном разделе для Multiboot
__attribute__((section(".multiboot")))
struct multiboot_header mb = {
    .magic = 0x1BADB002U,           // Начинаем битву экстрасенсов
    .flags = 0U,                   // Раскошный максиум
    .checksum = 0x2E95A86DU         // Вычислено: -(0x1BADB002 + 0)
};

// Константы для работы с VGA-памятью
#define VIDEO_MEMORY 0xB8000U        // Базовый адрес текстового режима VGA
#define VGA_WIDTH 80                // Ширина экрана в символах
#define VGA_HEIGHT 25               // Высота экрана в символах

/**
 * Выводит один символ в заданную позицию экрана VGA
 * @param c — символ для вывода
 * @param x — координата X (0–79)
 * @param y — координата Y (0–24)
 * @param color — атрибут цвета (фон/передний план)
 */
void vga_putchar(char c, int x, int y, uint8_t color) {
    volatile uint16_t* video = (volatile uint16_t*)VIDEO_MEMORY;
    video[y * VGA_WIDTH + x] = (uint16_t)((color << 8) | (uint8_t)c);
}

/**
 * Выводит строку символов начиная с заданной позиции
 * @param str — нуль-терминированная строка для вывода
 * @param x — начальная координата X
 * @param y — координата Y
 */
void vga_print(const char* str, int x, int y) {
    for (int i = 0; str[i] != '\0'; i++) {
        vga_putchar(str[i], x + i, y, 0x07U);
    }
}

/**
 * Точка входа ядра (вызывается загрузчиком Multiboot)
 * @param multiboot_info — указатель на структуру Multiboot от загрузчика
 * @param magic — магическое число (должно быть 0x1BADB002 для Multiboot 1)
 */
extern "C" void _start(uint32_t multiboot_info, uint32_t magic) {
    // Проверка маджик числа от загрузчика
    if (magic != 0x2BADB002U) {
        // Если загрузчик передал неверное число, выводим ошибку
        vga_print("ERROR: Invalid multiboot magic!", 0, 3);
        goto halt_loop;
    }

    // Очистка экрана: заполняем пробелами с чёрным цветом (0x00)
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            vga_putchar(' ', x, y, 0x00U);
        }
    }

    // Вывод приветственных сообщений
    vga_print("Floppa OS 3 Prototype Loaded!", 0, 0);
    vga_print("Type 'help' for commands", 0, 1);

halt_loop:
    // Остановка процессора: отключаем прерывания и переходим в режим ожидания
    asm volatile("cli");
    while (true) {
        asm volatile("hlt");
    }
}
