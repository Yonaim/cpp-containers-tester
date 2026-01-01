#!/usr/bin/env bash
set -euo pipefail

# Makefile/path helpers used by the execute layer.

execute_get_root_dir() {
    local script_dir="$1"
    (cd "${script_dir}/.." && pwd)
}

execute_resolve_makefile() {
    local root="$1" makefile_path="$2"
    if [[ -z "${makefile_path}" ]]; then
        # Default to test/Makefile for your current repo layout
        makefile_path="${root}/test/Makefile"
    fi
    [[ -f "${makefile_path}" ]] || ui_print_die "Makefile not found: ${makefile_path}"
    echo "${makefile_path}"
}

# Usage: execute_split_makefile_path "/path/to/Makefile" out_dir_var out_file_var
execute_split_makefile_path() {
    local makefile_path="$1"
    local __out_dir="$2"
    local __out_file="$3"

    local d f
    d="$(dirname "${makefile_path}")"
    f="$(basename "${makefile_path}")"

    printf -v "${__out_dir}" '%s' "${d}"
    printf -v "${__out_file}" '%s' "${f}"
}

execute_make_seed() { echo $(( $(date +%s) % 100000 )); }
execute_make_timestamp() { date +'%y%m%d_%H%M%S'; }

execute_require_executable() {
    local path="$1"
    [[ -x "${path}" ]] || ui_print_die "Missing executable: ${path}"
}

execute_make_clean() {
    local make_dir="$1" make_file="$2"
    echo -e "${UI_CY}→ Cleaning old builds...${UI_C0}"
    make -C "${make_dir}" -f "${make_file}" fclean >/dev/null
}

execute_make_build_one() {
    local make_dir="$1" make_file="$2" make_target="$3" module="$4" ns="$5"
    local -a extra=()

    # built with C++11 for std
    if [[ "${ns}" == "std" ]]; then
        echo -e "${UI_CY}→ Using CXXSTD=c++11 for std build${UI_C0}"
    fi
    # no deprecated declarations error for utils build
    if [[ "${module}" == "utils" ]]; then
        extra+=( "CXXFLAGS_COMMON+=-Wno-deprecated-declarations" )
    fi

    echo -e "${UI_CY}→ Building ${ns}: make ${make_target}${UI_C0}"
    if ! make -j -C "${make_dir}" -f "${make_file}" "${make_target}" "NAMESPACE=${ns}" "${extra[@]}" >/dev/null; then
        echo -e "${UI_CR}[ERROR] build failed (${ns}, ${make_target})${UI_C0}"
        exit 1
    fi
}
