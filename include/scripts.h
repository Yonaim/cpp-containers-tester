#ifndef SCRIPTS_H
#define SCRIPTS_H

#include <string>
#include <vector>

struct ScriptInfo
{
    std::string name;    // file name only
    std::string path;    // ./script/xxx.sh
    std::string preview; // first line or short description
};

struct ScriptNameLess
{
    bool operator()(const ScriptInfo &a, const ScriptInfo &b) const { return a.name < b.name; }
};

namespace scripts
{
    std::string             read_first_line(const std::string &path);
    std::vector<ScriptInfo> scan_scripts(const std::string &script_dir);

    int find_script_by_name(const std::vector<ScriptInfo> &list, const std::string &name);

    void print_scripts_grouped(const std::vector<ScriptInfo> &list);

    void show_script_head(const ScriptInfo &si, int lines);
} // namespace scripts

#endif
