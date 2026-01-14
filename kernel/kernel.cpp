#include "kernel.h"
#include "../drivers/screen.h"

void print_welcome_message() {
    print_string("Добро пожаловать в MyOS v0.1!\n");
    print_string("Введите 'help' для списка команд.\n");
}

void kernel_main() {
    clear_screen();
    print_welcome_message();
}
