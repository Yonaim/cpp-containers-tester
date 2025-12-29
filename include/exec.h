#ifndef EXEC_H
#define EXEC_H

#include "scripts.h"

namespace exec
{
    int run_bash_argv(const std::string &script_path, const std::vector<std::string> &args);
} // namespace exec

#endif
