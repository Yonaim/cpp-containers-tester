#include <sys/stat.h>
#include "fs.h"

namespace fs
{
    bool is_directory(const std::string &path)
    {
        struct stat st;
        if (::stat(path.c_str(), &st) != 0)
            return false;
        return S_ISDIR(st.st_mode);
    }

    bool is_file(const std::string &path)
    {
        struct stat st;
        if (::stat(path.c_str(), &st) != 0)
            return false;
        return S_ISREG(st.st_mode);
    }

    std::string join_path(const std::string &a, const std::string &b)
    {
        if (a.empty())
            return b;
        if (a[a.size() - 1] == '/')
            return a + b;
        return a + "/" + b;
    }
} // namespace fs
