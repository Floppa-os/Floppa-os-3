.global start
.code32

start:
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss
    mov $0x9000, %esp

    call kernel_main

hang:
    jmp hang
