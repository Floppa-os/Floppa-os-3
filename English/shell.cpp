#include <iostream>  // Для ввода/вывода (std::cout, std::cin)
#include <cstring>   // Для функций работы со строками (strcmp, strncmp, strchr)
#include "shell.h"  // Заголовочный файл для оболочки (предполагаемая декларация функций)
#include "../lib/string_utils.h"

/**
 * Processes shell commands
 * @param command Pointer to the command string
 */
void execute_command_os(const char* command) {
    // Handle "help" command — display help menu
    if (strcmp(command, "help") == 0) {
        std::cout << "Available commands:\n";
        std::cout << "  help - display this help menu\n";
        std::cout << "  clear - clear the screen\n";
        std::cout << "  echo [text] - print the specified text\n";
        std::cout << "  comparatives - show information about adjective comparison degrees\n";
        std::cout << "  exit - exit the shell\n";
        
        // Note: Repeated "FLP#root" output seems redundant
        for (int i = 0; i < 100; ++i) {  // Optimized loop instead of 100 separate lines
            std::cout << "  FLP#root\n";
        }
    }
    // Handle "clear" command — clear screen
    else if (strcmp(command, "clear") == 0) {
        std::system("clear");  // Unix/Linux systems
        // For Windows: std::system("cls");
    }
    // Handle "echo" command — print text after the space
    else if (strncmp(command, "echo", 4) == 0) {
        const char* space_pos = strchr(command, ' ');  // Find space in the command
        if (space_pos) {
            std::cout << (space_pos + 1) << "\n";  // Print text after the space
        } else {
            std::cout << "\n";  // If no text — just print newline
        }
    }
    // Handle "comparatives" command — show adjective comparison rules
    else if (strcmp(command, "comparatives") == 0) {
        std::cout << "=== ADJECTIVE COMPARISON DEGREES ===\n\n";
        std::cout << "English has 3 comparison degrees:\n";
        std::cout << "- Positive (base form): big, beautiful, good\n";
        std::cout << "- Comparative: bigger, more beautiful, better\n";
        std::cout << "- Superlative: the biggest, the most beautiful, the best\n\n";

        std::cout << "FORMATION RULES:\n";
        std::cout << "1. Short adjectives (1–2 syllables):\n";
        std::cout << "   - Add -er for comparative: cold → colder\n";
        std::cout << "   - Use 'the + -est' for superlative: cold → the coldest\n";
        std::cout << "2. Long adjectives (3+ syllables):\n";
        std::cout << "   - Use 'more' for comparative: interesting → more interesting\n";
        std::cout << "   - Use 'the most' for superlative: interesting → the most interesting\n";
        std::cout << "3. Irregular forms:\n";
        std::cout << "   - good → better → the best\n";
        std::cout << "   - bad → worse → the worst\n";
        std::cout << "   - far → farther/further → the farthest/furthest\n\n";

        std::cout << "EXAMPLES:\n";
        std::cout << "• small → smaller → the smallest\n";
        std::cout << "• happy → happier → the happiest\n";
        std::cout << "• modern → more modern → the most modern\n";
        std::cout << "• expensive → more expensive → the most expensive\n";
    }
    // Handle "exit" command — terminate shell
    else if (strcmp(command, "exit") == 0) {
        std::cout << "Terminating shell...\n";
    }
    // Handle unknown commands
    else {
        std::cout << "Unknown command: " << command << "\n";
        std::cout << "Type 'help' for assistance.\n";
    }
}

/**
 * Starts the interactive shell
 */
void start_shell_os() {
    char input[256];  // Input buffer (max 256 characters)

    while (true) {  // Infinite loop until "exit" command
        std::cout << "FLP#root> ";  // Command prompt
        std::cin.getline(input, sizeof(input));  // Read input from console

        // Check if input is not empty
        if (strlen(input) > 0) {
            execute_command_os(input);  // Process the command
            // Exit loop if "exit" command is entered
            if (strcmp(input, "exit") == 0) {
                break;
            }
        }
    }
}
