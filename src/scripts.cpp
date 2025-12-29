#include <algorithm>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include "ansi_ui.h"
#include "fs.h"
#include "scripts.h"
#include "util.h"

namespace scripts
{
    std::string read_first_line(const std::string &path)
    {
        std::ifstream ifs(path.c_str());
        if (!ifs)
            return "";
        std::string line;
        std::getline(ifs, line);
        return line;
    }

    static void print_one_script_line(size_t i, const ScriptInfo &si)
    {
        std::ostringstream idx;
        idx << (i + 1);

        std::cout << ui::C_CYAN << "[" << idx.str() << "]" << ui::C_RESET << " " << ui::C_BOLD
                  << si.name << ui::C_RESET;

        if (!si.preview.empty())
            std::cout << "  " << ui::C_DIM << si.preview << ui::C_RESET;

        std::cout << "\n";
    }

    std::vector<ScriptInfo> scan_scripts(const std::string &script_dir)
    {
        std::vector<ScriptInfo> out;

        DIR *dp = ::opendir(script_dir.c_str());
        if (!dp)
            return out;

        struct dirent *ent = 0;
        while ((ent = ::readdir(dp)) != 0)
        {
            std::string name = ent->d_name;
            if (name == "." || name == "..")
                continue;
            if (!util::ends_with(name, ".sh"))
                continue;

            ScriptInfo si;
            si.name = name;
            si.path = fs::join_path(script_dir, name);

            std::string first = util::trim(read_first_line(si.path));
            si.preview = first;

            out.push_back(si);
        }
        ::closedir(dp);

        std::sort(out.begin(), out.end(), ScriptNameLess());
        return out;
    }

    void print_scripts_grouped(const std::vector<ScriptInfo> &list)
    {
        if (list.empty())
        {
            std::cout << ui::C_RED << "No scripts found under ./script" << ui::C_RESET << "\n";
            return;
        }

        std::cout << ui::C_BOLD << "Available scripts (grouped):" << ui::C_RESET << "\n";
        ui::hr('-');

        bool any_basic = false;
        bool any_stress = false;
        bool any_perf = false;
        bool any_other = false;

        for (size_t i = 0; i < list.size(); ++i)
            if (util::starts_with(list[i].name, "diff_basic_"))
            {
                any_basic = true;
                break;
            }

        for (size_t i = 0; i < list.size(); ++i)
            if (util::starts_with(list[i].name, "diff_stress_"))
            {
                any_stress = true;
                break;
            }

        for (size_t i = 0; i < list.size(); ++i)
            if (util::starts_with(list[i].name, "diff_perf_"))
            {
                any_perf = true;
                break;
            }

        for (size_t i = 0; i < list.size(); ++i)
        {
            if (!util::starts_with(list[i].name, "diff_basic_") &&
                !util::starts_with(list[i].name, "diff_stress_") &&
                !util::starts_with(list[i].name, "diff_perf_"))
            {
                any_other = true;
                break;
            }
        }

        if (any_basic)
        {
            std::cout << ui::C_BOLD << ui::C_GREEN << "[BASIC]" << ui::C_RESET << "\n";
            for (size_t i = 0; i < list.size(); ++i)
                if (util::starts_with(list[i].name, "diff_basic_"))
                    print_one_script_line(i, list[i]);
            ui::hr('-');
        }

        if (any_stress)
        {
            std::cout << ui::C_BOLD << ui::C_YELLOW << "[STRESS]" << ui::C_RESET << "\n";
            for (size_t i = 0; i < list.size(); ++i)
                if (util::starts_with(list[i].name, "diff_stress_"))
                    print_one_script_line(i, list[i]);
            ui::hr('-');
        }

        if (any_perf)
        {
            std::cout << ui::C_BOLD << ui::C_MAG << "[PERF]" << ui::C_RESET << "\n";
            for (size_t i = 0; i < list.size(); ++i)
                if (util::starts_with(list[i].name, "diff_perf_"))
                    print_one_script_line(i, list[i]);
            ui::hr('-');
        }

        if (any_other)
        {
            std::cout << ui::C_BOLD << ui::C_BLUE << "[OTHER]" << ui::C_RESET << "\n";
            for (size_t i = 0; i < list.size(); ++i)
                if (!util::starts_with(list[i].name, "diff_basic_") &&
                    !util::starts_with(list[i].name, "diff_stress_") &&
                    !util::starts_with(list[i].name, "diff_perf_"))
                    print_one_script_line(i, list[i]);
            ui::hr('-');
        }

        std::cout << ui::C_DIM << "Tip: run 1   |   run diff_basic_map.sh" << ui::C_RESET << "\n";
    }

    int find_script_by_name(const std::vector<ScriptInfo> &list, const std::string &name)
    {
        std::string n = util::trim(name);
        if (n.empty())
            return -1;

        for (size_t i = 0; i < list.size(); ++i)
            if (list[i].name == n)
                return (int)i;

        if (!util::ends_with(n, ".sh"))
        {
            std::string with = n + ".sh";
            for (size_t i = 0; i < list.size(); ++i)
                if (list[i].name == with)
                    return (int)i;
        }
        return -1;
    }

    void show_script_head(const ScriptInfo &si, int lines)
    {
        std::ifstream ifs(si.path.c_str());
        if (!ifs)
        {
            std::cout << ui::C_RED << "Failed to open: " << si.path << ui::C_RESET << "\n";
            return;
        }

        std::cout << ui::C_BOLD << "File: " << ui::C_RESET << si.path << "\n";
        ui::hr('-');

        std::string line;
        int         n = 0;
        while (n < lines && std::getline(ifs, line))
        {
            std::ostringstream ln;
            ln << (n + 1);
            std::cout << ui::C_DIM << ln.str() << " | " << ui::C_RESET << line << "\n";
            ++n;
        }
        ui::hr('-');
    }
} // namespace scripts
