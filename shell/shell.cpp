/*Импорт библиотек*/
#include <iostream>  // Для ввода/вывода (std::cout, std::cin)
#include <cstring>   // Для функций работы со строками (strcmp, strncmp, strchr)
#include "shell.h"  // Заголовочный файл для оболочки (предполагаемая декларация функций)
#include "../lib/string_utils.h"  // Дополнительные утилиты для работы со строками

/**
 * Функция обработки команд оболочки
 * @param command Указатель на строку с командой
 */
void execute_command_os(const char* command) {
    // Проверка команды "help" — вывод справки
    if (strcmp(command, "help") == 0) {
        std::cout << "Доступные команды:\n";
        std::cout << "  help - показать эту справку\n";
        std::cout << "  clear - очистить экран\n";
        std::cout << "  echo [текст] - вывести текст\n";
        std::cout << "  comparatives - показать информацию о степенях сравнения прилагательных\n";
        std::cout << "  exit - выйти из оболочки\n";
        // Примечание: многократный вывод "FLP#root" выглядит избыточным
        for (int i = 0; i < 100; ++i) {  // Пример оптимизации (вместо 100 отдельных строк)
            std::cout << "  FLP#root\n";
        }
    }
    // Проверка команды "clear" — очистка экрана
    else if (strcmp(command, "clear") == 0) {
        std::system("clear");  // Для Unix-систем
        // Для Windows: std::system("cls");
    }
    // Проверка команды "echo" — вывод текста после пробела
    else if (strncmp(command, "echo", 4) == 0) {
        const char* space_pos = strchr(command, ' ');  // Поиск пробела в строке
        if (space_pos) {
            std::cout << (space_pos + 1) << "\n";  // Вывод текста после пробела
        } else {
            std::cout << "\n";  // Если текста нет — просто перевод строки
        }
    }
    // Проверка команды "comparatives" — информация о степенях сравнения
    else if (strcmp(command, "comparatives") == 0) {
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
    }
    // Проверка команды "exit" — завершение работы
    else if (strcmp(command, "exit") == 0) {
        std::cout << "Завершение работы оболочки...\n";
    }
    // Обработка неизвестной команды
    else {
        std::cout << "Неизвестная команда: " << command << "\n";
        std::cout << "Введите 'help' для справки.\n";
    }
}

/**
 * Функция запуска интерактивной оболочки
 */
void start_shell_os() {
    char input[256];  // Буфер для ввода команды (макс. 256 символов)

    while (true) {  // Бесконечный цикл до команды "exit"
        std::cout << "FLP#root> ";  // Приглашение к вводу
        std::cin.getline(input, sizeof(input));  // Чтение строки с консоли

        // Проверка, что ввод не пустой
        if (strlen(input) > 0) {
            execute_command_os(input);  // Обработка команды
            // Выход из цикла при команде "exit"
            if (strcmp(input, "exit") == 0) {
                break;
            }
        }
    }
}
