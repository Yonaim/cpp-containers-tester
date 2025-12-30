#include <csignal>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include "ansi_ui.h"
#include "app.h"
#include "exec.h"
#include "fs.h"
#include "settings.h"
#include "util.h"

static bool g_running = true;
static void on_sigint(int) { g_running = false; }

static int run_diff_entry(const std::string &group, const std::string &module)
{
    std::vector<std::string> args;
    args.push_back(group);
    args.push_back(module);
    return exec::run_bash_argv(DIFF_ENTRY_PATH, args);
}

static void expand_selection(const std::string &sel, const std::vector<std::string> &all,
                             std::vector<std::string> &out)
{
    out.clear();
    if (sel == "all")
        out = all;
    else
        out.push_back(sel);
}

static int prompt_choice(const char *title, const std::vector<std::string> &items)
{
    std::cout << ui::C_BOLD << title << ui::C_RESET << "\n";
    for (size_t i = 0; i < items.size(); ++i)
        std::cout << "  " << ui::C_BOLD << (i + 1) << ui::C_RESET << ") " << items[i] << "\n";
    std::cout << ui::C_DIM << "Select number (or 'q' to cancel): " << ui::C_RESET;

    std::string line;
    if (!std::getline(std::cin, line))
        return -1;
    line = util::trim(line);
    if (line == "q" || line == "quit" || line == "exit")
        return -1; // exit

    int idx = util::parse_index(line);
    if (idx <= 0 || (size_t)idx > items.size())
        return -2; // invalid
    return idx - 1;
}

static bool ensure_repo_layout()
{
    if (!fs::is_directory(SCRIPT_DIR_PATH))
    {
        std::cerr << ui::C_RED << "Error: " << SCRIPT_DIR_PATH << " directory not found."
                  << ui::C_RESET << "\n";
        std::cerr << "Run this program from the repository root.\n";
        return false;
    }
    if (!fs::is_file(DIFF_ENTRY_PATH))
    {
        std::cerr << ui::C_RED << "Error: " << DIFF_ENTRY_PATH << " not found." << ui::C_RESET
                  << "\n";
        std::cerr << "Place diff_entry.sh under ./script and try again.\n";
        return false;
    }
    return true;
}

// legacy
static void print_help()
{
    ui::title_bar();
    std::cout << ui::C_BOLD << "Usage:" << ui::C_RESET << "\n";

    std::cout << "  " << ui::C_BOLD << "menu" << ui::C_RESET
              << "                     : interactive test menu (module -> group)\n";
    std::cout << "  " << ui::C_BOLD << "run" << ui::C_RESET
              << "                      : alias for 'menu'\n";

    std::cout << "  " << ui::C_BOLD << "clear" << ui::C_RESET
              << "                    : clear screen\n";
    std::cout << "  " << ui::C_BOLD << "help | ?" << ui::C_RESET
              << "                  : show this help\n";
    std::cout << "  " << ui::C_BOLD << "exit | quit | q" << ui::C_RESET
              << "         : exit program\n";

    ui::hr('-');
    std::cout << ui::C_DIM << "Notes:\n"
              << " - Run this program from the repository root.\n"
              << " - The menu executes ./script/diff_entry.sh <group> <module> via /bin/bash.\n"
              << " - 'all' selections run multiple combinations in sequence.\n"
              << ui::C_RESET;
}

static bool run_menu()
{
    std::vector<std::string> modules;
    modules.push_back("vector");
    modules.push_back("map");
    modules.push_back("utils");
    modules.push_back("stack");
    modules.push_back("all");

    std::vector<std::string> groups;
    groups.push_back("basic");
    groups.push_back("perf");
    groups.push_back("stress");
    groups.push_back("all");

    int m = -2;
    while (m == -2)
    {
        m = prompt_choice("Select module:", modules);
        if (m == -1)
            return false;
        else if (m == -2)
            std::cout << ui::C_YELLOW << "Invalid selection.\n" << ui::C_RESET << "\n";
    }
    std::string module_sel = modules[(size_t)m];

    std::cout << '\n';
    int g = -2;
    while (g == -2)
    {
        g = prompt_choice("Select group:", groups);
        if (g == -1)
            return false;
        else if (g == -2)
            std::cout << ui::C_YELLOW << "Invalid selection.\n" << ui::C_RESET << "\n";
    }
    std::string group_sel = groups[(size_t)g];

    std::vector<std::string> module_list, group_list;
    std::vector<std::string> module_all;
    module_all.push_back("vector");
    module_all.push_back("map");
    module_all.push_back("utils");
    module_all.push_back("stack");

    std::vector<std::string> group_all;
    group_all.push_back("basic");
    group_all.push_back("stress");
    group_all.push_back("perf");

    expand_selection(module_sel, module_all, module_list);
    expand_selection(group_sel, group_all, group_list);

    for (size_t gi = 0; gi < group_list.size(); ++gi)
    {
        for (size_t mi = 0; mi < module_list.size(); ++mi)
        {
            ui::hr('=');
            std::cout << ui::C_BOLD << "Running: " << ui::C_RESET << ui::C_MAG << group_list[gi]
                      << " " << module_list[mi] << ui::C_RESET << "\n";
            ui::hr('-');

            const double t0 = (double)clock() / (double)CLOCKS_PER_SEC;
            int          code = run_diff_entry(group_list[gi], module_list[mi]);
            const double t1 = (double)clock() / (double)CLOCKS_PER_SEC;

            ui::hr('-');
            std::cout << ui::C_DIM << "Elapsed (cpu clock): " << ui::C_RESET << ui::C_BOLD
                      << ((t1 - t0) * 1000.0) << " ms" << ui::C_RESET << "\n";

            if (code == 0)
                std::cout << ui::C_GREEN << "Result: OK (exit code 0)" << ui::C_RESET << "\n";
            else
                std::cout << ui::C_RED << "Result: FAIL (exit code " << code << ")" << ui::C_RESET
                          << "\n";

            ui::hr('=');
        }
    }
    return true;
}

namespace app
{
    int run()
    {
        std::signal(SIGINT, on_sigint);
        std::cout.setf(std::ios::unitbuf);

        if (!ensure_repo_layout())
            return 1;

        ui::clear_screen();
        ui::title_bar();
        std::cout << "\n";

        while (g_running)
        {
            if (run_menu() == false)
                break;
        }
        return 0;
    }
} // namespace app
