#include <cstdlib>
#include <iostream>
#include <sys/wait.h>
#include "ansi_ui.h"
#include "exec.h"

namespace exec
{
    int run_script_bash(const ScriptInfo &si)
    {
        const std::string cmd = "bash -lc \"bash '" + si.path + "'\"";

        std::cout << ui::C_DIM << "Command: " << ui::C_RESET << ui::C_GRAY << cmd << ui::C_RESET
                  << "\n";

        int rc = std::system(cmd.c_str());
        if (rc == -1)
            return 127;

        if (WIFEXITED(rc))
            return WEXITSTATUS(rc);
        if (WIFSIGNALED(rc))
            return 128 + WTERMSIG(rc);
        return rc;
    }

#include <unistd.h>
#include <sys/wait.h>

    int run_bash_argv(const std::string &script_path, const std::vector<std::string> &args)
    {
        std::vector<std::string> argv_s;
        argv_s.push_back("/bin/bash");
        argv_s.push_back(script_path);
        argv_s.insert(argv_s.end(), args.begin(), args.end());

        std::vector<char *> argv;
        argv.reserve(argv_s.size() + 1);
        for (size_t i = 0; i < argv_s.size(); ++i)
            argv.push_back(const_cast<char *>(argv_s[i].c_str()));
        argv.push_back(NULL);

        pid_t pid = fork();
        if (pid < 0)
            return 127;

        if (pid == 0)
        {
            execv("/bin/bash", &argv[0]);
            _exit(127);
        }

        int status = 0;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            return WEXITSTATUS(status);
        return 128;
    }

} // namespace exec
