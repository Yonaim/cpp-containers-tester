#ifndef FS_H
#define FS_H

#include <string>

namespace fs
{
    bool        is_directory(const std::string &path);
    bool        is_file(const std::string &path);
    std::string join_path(const std::string &a, const std::string &b);
} // namespace fs

#endif
