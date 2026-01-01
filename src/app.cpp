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

// ====================== Signal handling ====================== //

static bool g_running = true;
static void on_sigint(int) { g_running = false; }

// ====================== Menu data (created once) ====================== //

static const std::vector<std::string> kModules = {"utils", "vector", "map", "stack", "all"};

static const std::vector<std::string> kTypes = {"basic", "stress", "perf", "all"};

static const std::vector<std::string> kAllModules = {"utils", "vector", "map", "stack"};

static const std::vector<std::string> kAllTypes = {"basic", "stress", "perf"};

// ====================== Helpers ====================== //

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
        return -1;

    int idx = util::parse_index(line);
    if (idx <= 0 || static_cast<size_t>(idx) > items.size())
        return -2;

    return idx - 1;
}

// ====================== Execution ====================== //

static std::string entry_script_for_type(const std::string &type)
{
    if (type == "basic")
        return "script/basic_entry.sh";
    if (type == "stress")
        return "script/stress_entry.sh";
    if (type == "perf")
        return "script/perf_entry.sh";
    return "";
}

static int run_entry(const std::string &type, const std::string &module)
{
    const std::string script = entry_script_for_type(type);
    if (script.empty())
        return 1;

    std::vector<std::string> args;
    args.push_back(module); // entry.sh <module>

    return exec::run_bash_argv(script, args);
}

// ====================== Repo check ====================== //

static bool ensure_repo_layout()
{
    if (!fs::is_directory(SCRIPT_DIR_PATH))
    {
        std::cerr << ui::C_RED << "Error: " << SCRIPT_DIR_PATH << " directory not found."
                  << ui::C_RESET << "\n";
        std::cerr << "Run this program from the repository root.\n";
        return false;
    }
    return true;
}

// ====================== Menu ====================== //

static bool run_menu()
{
    int m = -2;
    while (m == -2)
    {
        m = prompt_choice("Select module:", kModules);
        if (m == -1)
            return false;
        if (m == -2)
            std::cout << ui::C_YELLOW << "Invalid selection.\n\n" << ui::C_RESET;
    }
    std::string module_sel = kModules[static_cast<size_t>(m)];

    std::cout << "\n";

    int t = -2;
    while (t == -2)
    {
        t = prompt_choice("Select test type:", kTypes);
        if (t == -1)
            return false;
        if (t == -2)
            std::cout << ui::C_YELLOW << "Invalid selection.\n\n" << ui::C_RESET;
    }
    std::string type_sel = kTypes[static_cast<size_t>(t)];

    std::vector<std::string> module_list;
    std::vector<std::string> type_list;

    expand_selection(module_sel, kAllModules, module_list);
    expand_selection(type_sel, kAllTypes, type_list);

    for (size_t ti = 0; ti < type_list.size(); ++ti)
    {
        for (size_t mi = 0; mi < module_list.size(); ++mi)
        {
            ui::hr('=');
            std::cout << ui::C_BOLD << "Running: " << ui::C_RESET << ui::C_MAG << type_list[ti]
                      << " " << module_list[mi] << ui::C_RESET << "\n";
            ui::hr('-');

            // const double t0 = static_cast<double>(clock()) / CLOCKS_PER_SEC;

            int code = run_entry(type_list[ti], module_list[mi]);
            (void)code;

            // const double t1 = static_cast<double>(clock()) / CLOCKS_PER_SEC;

            // ui::hr('-');
            // std::cout << ui::C_DIM << "Elapsed (cpu clock): " << ui::C_RESET << ui::C_BOLD
            //           << ((t1 - t0) * 1000.0) << " ms" << ui::C_RESET << "\n";
            // ui::hr('=');
        }
    }
    return true;
}

// ====================== App entry ====================== //

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
            if (!run_menu())
                break;
        }
        return 0;
    }
} // namespace app
