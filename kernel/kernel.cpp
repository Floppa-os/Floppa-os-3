#include "kernel.h"
#include "../drivers/screen.h"

void kernel_main() {
    clear_screen();
    print_welcome_message();
}
