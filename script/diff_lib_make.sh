#!/usr/bin/env bash
set -euo pipefail

diff_get_root_dir() {
    local script_dir="$1"
    (cd "${script_dir}/.." && pwd)
}

diff_resolve_makefile() {
    local root="$1" makefile_path="$2"
    if [[ -z "${makefile_path}" ]]; then
        # Default to test/Makefile for your current repo layout
        makefile_path="${root}/test/Makefile"
    fi
    [[ -f "${makefile_path}" ]] || diff_die "Makefile not found: ${makefile_path}"
    echo "${makefile_path}"
}

# Usage: diff_split_makefile_path "/path/to/Makefile" out_dir_var out_file_var
diff_split_makefile_path() {
    local makefile_path="$1"
    local __out_dir="$2"
    local __out_file="$3"

    local d f
    d="$(dirname "${makefile_path}")"
    f="$(basename "${makefile_path}")"

    printf -v "${__out_dir}" '%s' "${d}"
    printf -v "${__out_file}" '%s' "${f}"
}

diff_make_seed() { echo $(( $(date +%s) % 100000 )); }
diff_make_timestamp() { date +'%y%m%d_%H%M%S'; }

diff_require_executable() {
    local path="$1"
    [[ -x "${path}" ]] || diff_die "Missing executable: ${path}"
}

diff_make_clean() {
    local make_dir="$1" make_file="$2"
    echo -e "${DIFF_CY}→ Cleaning old builds...${DIFF_C0}"
    make -C "${make_dir}" -f "${make_file}" fclean >/dev/null
}

diff_make_build_one() {
    local make_dir="$1" make_file="$2" make_target="$3" module="$4" ns="$5"
    local -a extra=()

    # built with C++11 for std
    if [[ "${ns}" == "std" ]]; then
        echo -e "${DIFF_CY}→ Using CXXSTD=c++11 for std build${DIFF_C0}"
    fi
    # no deprecated declarations error for utils build
    if [[ "${module}" == "utils" ]]; then
        extra+=( "CXXFLAGS_COMMON+=-Wno-deprecated-declarations" )
    fi

    echo -e "${DIFF_CY}→ Building ${ns}: make ${make_target}${DIFF_C0}"
    if ! make -j -C "${make_dir}" -f "${make_file}" "${make_target}" "NAMESPACE=${ns}" "${extra[@]}" >/dev/null; then
        echo -e "${DIFF_CR}[ERROR] build failed (${ns}, ${make_target})${DIFF_C0}"
        exit 1
    fi
}

diff_run_bins_and_log() {
    local group="$1" seed="$2"
    local ft_bin="$3" std_bin="$4"
    local ft_log="$5" std_log="$6"

    if [[ "${group}" == "stress" ]]; then
        "${ft_bin}"  "${seed}" > "${ft_log}" 2>&1
        "${std_bin}" "${seed}" > "${std_log}" 2>&1
    else
        "${ft_bin}"  > "${ft_log}" 2>&1
        "${std_bin}" > "${std_log}" 2>&1
    fi
}

diff_make_diff_logs() {
    local std_log="$1" ft_log="$2" diff_log="$3"
    echo -e "${DIFF_CY}→ Comparing outputs...${DIFF_C0}"
    diff -u "${std_log}" "${ft_log}" > "${diff_log}" || true
}
