// runner/main.cpp
// cpp-containers test runner
// Interactive diff test runner for Ecole42-style containers project.
// Place the ./runner directory at repo root and compile/run from repo root.
//
// Notes:
// - Executes only shell scripts under ./script
// - Uses /bin/bash to run scripts even if they are not executable.
// - Type: show, list, run <name|index>, r <...>, help, clear, exit

#include "app.h"

int main() { return app::run(); }
