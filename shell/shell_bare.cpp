#include "../drivers/screen.h"  // Теперь vga_* функции доступны
#include <cstring>
#include <cstdint>  // Для uint8_t

// Глобальный буфер для ввода команды
static char input_buffer[256] = {0};
static int input_pos = 0;

void show_comparatives_info_bare() {
    // Очищаем область вывода (строки 3–26)
    for (int y = 3; y <= 26 && y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            vga_putchar(' ', x, y, 0x00U);
        }
    }

    vga_print("=== DEGREES OF COMPARISON OF ADJECTIVES ===", 0, 3);
    vga_print("", 0, 4);
    vga_print("In English, there are 3 degrees of comparison:", 0, 5);
    vga_print("- Positive (basic form): big, beautiful, good", 0, 6);
    vga_print("- Comparative: bigger, more beautiful, better", 0, 7);
    vga_print("- Superlative: the biggest, the most beautiful, the best", 0, 8);
    vga_print("", 0, 9);

    vga_print("RULES FOR FORMATION:", 0, 10);
    vga_print("1. Short adjectives (1–2 syllables):", 0, 11);
    vga_print("   - add -er for comparative: cold → colder", 0, 12);
    vga_print("   - add the + -est for superlative: cold → the coldest", 0, 13);
    vga_print("2. Long adjectives (3+ syllables):", 0, 14);
    vga_print("   - use 'more' for comparative: interesting → more interesting", 0, 15);
    vga_print("   - use 'the most' for superlative: interesting → the most interesting", 0, 16);
    vga_print("3. Irregular forms:", 0, 17);
    vga_print("   - good → better → the best", 0, 18);
    vga_print("   - bad → worse → the worst", 0, 19);
    vga_print("   - far → farther/further → the farthest/furthest", 0, 20);
    vga_print("", 0, 21);

    vga_print("EXAMPLES:", 0, 22);
    vga_print("• small → smaller → the smallest", 0, 23);
    vga_print("• happy → happier → the happiest", 0, 24);
    vga_print("• modern → more modern → the most modern", 0, 25);
    vga_print("• expensive → more expensive → the most expensive", 0, 26);
}

void execute_command_bare(const char* command) {
    if (strncmp(command, "help", 4) == 0 && (command[4] == ' ' || command[4] == '\0')) {
        vga_print("Available commands:", 0, VGA_HEIGHT - 6);
        vga_print("  help - show this help", 0, VGA_HEIGHT - 5);
        vga_print("  clear - clear screen", 0, VGA_HEIGHT - 4);
        vga_print("  echo [text] - print text", 0, VGA_HEIGHT - 3);
        vga_print("  comparatives - show info about adjective comparison degrees", 0, VGA_HEIGHT - 2);
        vga_print("  exit - exit shell", 0, VGA_HEIGHT - 1);
    } else if (strncmp(command, "clear", 5) == 0 && (command[5] == ' ' || command[5] == '\0')) {
        clear_screen();
        vga_print("FloppaOS> ", 0, VGA_HEIGHT - 1);
    } else if (strncmp(command, "echo", 4) == 0) {
        const char* space_pos = strchr(command, ' ');
        if (space_pos && space_pos[1] != '\0') {
            vga_print(space_pos + 1, 0, VGA_HEIGHT - 3);
        } else {
            vga_print("(no text provided)", 0, VGA_HEIGHT - 3);
        }
    } else if (strncmp(command, "comparatives", 10) == 0 && (command[10] == ' ' || command[10] == '\0')) {
        show_comparatives_info_bare();
    } else if (strncmp(command, "exit", 4) == 0 && (command[4] == ' ' || command[4] == '\0')) {
        vga_print("Exiting shell...", 0, VGA_HEIGHT - 1);
        asm volatile("cli");
        while (true) {
            asm volatile("hlt");
        }
    } else {
        vga_print("Unknown command. Type 'help' for available commands.", 0, VGA_HEIGHT - 1);
    }
}

// Заглушка драйвера клавиатуры
char read_keyboard_input() {
    // В реальном коде: чтение из порта 0x60
    return 0;
}
