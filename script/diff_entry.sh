#!/usr/bin/env bash
set -euo pipefail

# Entry point for diff build+run+compare.
# Usage:
#   ./script/diff_entry.sh <basic|perf|stress> <vector|map|stack|utils> [--makefile PATH]
#
# Examples:
#   ./script/diff_entry.sh basic vector
#   ./script/diff_entry.sh perf map
#   ./script/diff_entry.sh stress utils
#   ./script/diff_entry.sh basic vector --makefile ./test/Makefile

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# shellcheck source=/dev/null
source "${SCRIPT_DIR}/diff_lib_ui.sh"
# shellcheck source=/dev/null
source "${SCRIPT_DIR}/diff_lib_args.sh"
# shellcheck source=/dev/null
source "${SCRIPT_DIR}/diff_lib_make.sh"

main() {
    local parsed type module makefile_opt
    parsed="$(diff_parse_args "$@")"
    type="${parsed%%|*}"; parsed="${parsed#*|}"
    module="${parsed%%|*}"; makefile_opt="${parsed#*|}"

    local root makefile_path make_dir make_file
    root="$(diff_get_root_dir "${SCRIPT_DIR}")"
    makefile_path="$(diff_resolve_makefile "${root}" "${makefile_opt}")"
    diff_split_makefile_path "${makefile_path}" make_dir make_file

    local make_target="${type}_${module}"
    local name="containers"
    local bin_dir="${root}/bin"
    local log_dir="${root}/logs"
    local seed ts
    seed="$(diff_make_seed)"
    ts="$(diff_make_timestamp)"

    mkdir -p "${log_dir}"

    diff_ui_header "${type}" "${module}" "${make_target}" "${seed}" "${makefile_path}" "${log_dir}" "${ts}"

    diff_make_clean "${make_dir}" "${make_file}"

    diff_make_build_one "${make_dir}" "${make_file}" "${make_target}" "${module}" "ft"
    diff_make_build_one "${make_dir}" "${make_file}" "${make_target}" "${module}" "std"

    local test_name="${make_target}"
    local ft_bin="${bin_dir}/ft_${test_name}"
    local std_bin="${bin_dir}/std_${test_name}"
    diff_require_executable "${ft_bin}"
    diff_require_executable "${std_bin}"

    local ft_log="${log_dir}/${ts}_${test_name}_ft.log"
    local std_log="${log_dir}/${ts}_${test_name}_std.log"
    local diff_log="${log_dir}/${ts}_${test_name}_diff.log"

    diff_ui_run_info "${ft_bin}" "${std_bin}"

    diff_run_bins_and_log "${type}" "${seed}" "${ft_bin}" "${std_bin}" "${ft_log}" "${std_log}"

    diff_make_diff_logs "${std_log}" "${ft_log}" "${diff_log}"
    diff_ui_diff_result "${test_name}" "${diff_log}"
    diff_ui_footer "${ft_log}" "${std_log}" "${diff_log}"
}

main "$@"
