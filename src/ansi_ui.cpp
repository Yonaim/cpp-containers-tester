#include <iostream>
#include "ansi_ui.h"
#include "settings.h"

namespace ui
{
    const char *C_RESET = "\033[0m";
    const char *C_DIM = "\033[2m";
    const char *C_BOLD = "\033[1m";
    const char *C_RED = "\033[31m";
    const char *C_GREEN = "\033[32m";
    const char *C_YELLOW = "\033[33m";
    const char *C_BLUE = "\033[34m";
    const char *C_MAG = "\033[35m";
    const char *C_CYAN = "\033[36m";
    const char *C_GRAY = "\033[90m";

    // horizontal rule
    void hr(char ch)
    {
        std::cout << C_GRAY;
        for (int i = 0; i < 72; ++i)
            std::cout << ch;
        std::cout << C_RESET << "\n";
    }

    void title_bar()
    {
        hr('=');
        std::cout << C_BOLD << C_CYAN << "CPP-CONTAINERS TEST RUNNER" << C_RESET << "\n";
        hr('=');
    }

    void hint_bar()
    {
        std::cout << C_DIM << "Commands: " << C_RESET << C_BOLD << "list" << C_RESET << ", "
                  << C_BOLD << "run <index|name>" << C_RESET << ", " << C_BOLD << "r <...>"
                  << C_RESET << ", " << C_BOLD << "show <index|name>" << C_RESET << ", " << C_BOLD
                  << "help" << C_RESET << ", " << C_BOLD << "clear" << C_RESET << ", " << C_BOLD
                  << "exit" << C_RESET << "\n";
    }

    void clear_screen() { std::cout << "\033[2J\033[H"; }
} // namespace ui
