#include "include/types.h"
#include "include/screen.h"

void kernel_main() {
    screen_clear();
    screen_write("Floppa OS v0.1\n", 0x0F);
    screen_write("> ", 0x07);
}
