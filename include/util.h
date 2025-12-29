#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>

namespace util
{
    std::string trim(const std::string &s);
    std::string to_lower(std::string s);

    bool ends_with(const std::string &s, const std::string &suffix);
    bool starts_with(const std::string &s, const std::string &prefix);

    int parse_index(const std::string &token);

    std::vector<std::string> split_ws(const std::string &line);
} // namespace util

#endif
