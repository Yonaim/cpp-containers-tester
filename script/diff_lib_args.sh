#!/usr/bin/env bash
set -euo pipefail

diff_usage_and_exit() {
    cat <<EOF
Usage: $0 <basic|perf|stress> <utils|vector|map|stack> [--makefile PATH]
EOF
    exit 0
}

diff_validate_group_module() {
    local group="$1" module="$2"
    case "${group}" in basic|perf|stress) ;; *) diff_die "Invalid group: ${group} (use basic|perf|stress)" ;; esac
    case "${module}" in utils|vector|map|stack) ;; *) diff_die "Invalid module: ${module} (use vector|map|stack|utils)" ;; esac
}

# Prints: "GROUP|MODULE|MAKEFILE_PATH"
diff_parse_args() {
    local group="${1:-}" module="${2:-}"
    shift 2 || true

    [[ -n "${group}" && -n "${module}" ]] || diff_die "Need <group> and <module> (e.g. basic vector)"
    diff_validate_group_module "${group}" "${module}"

    local makefile_path=""

    while [[ $# -gt 0 ]]; do
        case "$1" in
            --makefile)
                [[ $# -ge 2 ]] || diff_die "Missing value for --makefile"
                makefile_path="$2"
                shift 2
                ;;
            -h|--help)
                diff_usage_and_exit
                ;;
            *)
                diff_die "Unknown option: $1"
                ;;
        esac
    done

    echo "${group}|${module}|${makefile_path}"
}
