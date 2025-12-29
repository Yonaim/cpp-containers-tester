#include <cstdlib>
#include <sstream>
#include "util.h"

namespace util
{
    std::string trim(const std::string &s)
    {
        size_t b = 0;
        while (b < s.size() && (s[b] == ' ' || s[b] == '\t' || s[b] == '\n' || s[b] == '\r'))
            ++b;
        size_t e = s.size();
        while (e > b &&
               (s[e - 1] == ' ' || s[e - 1] == '\t' || s[e - 1] == '\n' || s[e - 1] == '\r'))
            --e;
        return s.substr(b, e - b);
    }

    std::string to_lower(std::string s)
    {
        for (size_t i = 0; i < s.size(); ++i)
        {
            if (s[i] >= 'A' && s[i] <= 'Z')
                s[i] = char(s[i] - 'A' + 'a');
        }
        return s;
    }

    bool ends_with(const std::string &s, const std::string &suffix)
    {
        if (s.size() < suffix.size())
            return false;
        return s.compare(s.size() - suffix.size(), suffix.size(), suffix) == 0;
    }

    bool starts_with(const std::string &s, const std::string &prefix)
    {
        if (s.size() < prefix.size())
            return false;
        return s.compare(0, prefix.size(), prefix) == 0;
    }

    int parse_index(const std::string &token)
    {
        if (token.empty())
            return -1;
        for (size_t i = 0; i < token.size(); ++i)
        {
            if (token[i] < '0' || token[i] > '9')
                return -1;
        }
        long v = std::strtol(token.c_str(), 0, 10);
        if (v <= 0 || v > 1000000)
            return -1;
        return (int)v;
    }

    std::vector<std::string> split_ws(const std::string &line)
    {
        std::istringstream       iss(line);
        std::vector<std::string> out;
        std::string              tok;
        while (iss >> tok)
            out.push_back(tok);
        return out;
    }
} // namespace util
