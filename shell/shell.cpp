#include <iostream>
#include <cstring>
#include "shell.h"
#include "../lib/string_utils.h"

void execute_command_os(const char* command) {
    if (strcmp(command, "help") == 0) {
        std::cout << "Доступные команды:\n";
        std::cout << "  help - показать эту справку\n";
        std::cout << "  clear - очистить экран\n";
        std::cout << "  echo [текст] - вывести текст\n";
        std::cout << "  comparatives - показать информацию о степенях сравнения прилагательных\n";
        std::cout << "  exit - выйти из оболочки\n";
    } else if (strcmp(command, "clear") == 0) {
        std::system("clear"); // или "cls" для Windows
    } else if (strncmp(command, "echo", 4) == 0) {
        const char* space_pos = strchr(command, ' ');
        if (space_pos) {
            std::cout << (space_pos + 1) << "\n";
        } else {
            std::cout << "\n";
        }
    } else if (strcmp(command, "comparatives") == 0) {
        std::cout << "=== СТЕПЕНИ СРАВНЕНИЯ ПРИЛАГАТЕЛЬНЫХ ===\n\n";
        std::cout << "В английском языке есть 3 степени сравнения:\n";
        std::cout << "- Положительная (исходная форма): big, beautiful, good\n";
        std::cout << "- Сравнительная: bigger, more beautiful, better\n";
        std::cout << "- Превосходная: the biggest, the most beautiful, the best\n\n";

        std::cout << "ПРАВИЛА ОБРАЗОВАНИЯ:\n";
        std::cout << "1. Короткие прилагательные (1–2 слога):\n";
        std::cout << "   - добавляем -er для сравнительной: cold → colder\n";
        std::cout << "   - the + -est для превосходной: cold → the coldest\n";
        std::cout << "2. Длинные прилагательные (3+ слога):\n";
        std::cout << "   - используем 'more' для сравнительной: interesting → more interesting\n";
        std::cout << "   - 'the most' для превосходной: interesting → the most interesting\n";
        std::cout << "3. Неправильные формы:\n";
        std::cout << "   - good → better → the best\n";
        std::cout << "   - bad → worse → the worst\n";
        std::cout << "   - far → farther/further → the farthest/furthest\n\n";

        std::cout << "ПРИМЕРЫ:\n";
        std::cout << "• small → smaller → the smallest\n";
        std::cout << "• happy → happier → the happiest\n";
        std::cout << "• modern → more modern → the most modern\n";
        std::cout << "• expensive → more expensive → the most expensive\n";
    } else if (strcmp(command, "exit") == 0) {
        std::cout << "Завершение работы оболочки...\n";
    } else {
        std::cout << "Неизвестная команда: " << command << "\n";
        std::cout << "Введите 'help' для справки.\n";
    }
}

void start_shell_os() {
    char input[256];

    while (true) {
        std::cout << "MyOS> ";
        std::cin.getline(input, sizeof(input));

        if (strlen(input) > 0) {
            execute_command_os(input);
            if (strcmp(input, "exit") == 0) {
                break;
            }
        }
    }
}
