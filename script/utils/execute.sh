#!/usr/bin/env bash
set -euo pipefail

# Common execute/build/run plumbing shared by basic_entry.sh / stress_entry.sh / perf_entry.sh.
#
# Responsibilities:
#   - parse shared args
#   - resolve Makefile path
#   - build ft + std targets
#   - run both binaries, capture stdout/stderr into logs and capture exit codes
#
# Non-responsibilities (kept separate on purpose):
#   - diffing logs
#   - evaluating exit codes

LIB_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
# Root directory that contains the entry scripts and the Makefile(s).
SCRIPT_DIR="$(cd "${LIB_DIR}/.." && pwd)"

# shellcheck source=/dev/null
source "${LIB_DIR}/ui.sh"
# shellcheck source=/dev/null
source "${LIB_DIR}/makefile_helpers.sh"

_execute_validate_type() {
  case "${1}" in basic|stress|perf) : ;; *) ui_print_die "Invalid type: ${1} (use basic|stress|perf)" ;; esac
}

_execute_validate_module() {
  case "${1}" in utils|vector|map|stack) : ;; *) ui_print_die "Invalid module: ${1} (use utils|vector|map|stack)" ;; esac
}

_execute_usage() {
  local type="$1"
  cat <<EOF2
Usage:
  $(basename "$0") <utils|vector|map|stack> [--makefile PATH] ${type:+}

Options:
  --makefile PATH   Override Makefile path (default: <root>/test/Makefile)
  --seed N          (stress only) Seed value passed to the binary
  -h, --help        Show this help
EOF2
}

# Globals exported by execute_run_case (consumed by entry scripts)
EXEC_GROUP=""
EXEC_MODULE=""
EXEC_SEED=""
EXEC_ROOT=""
EXEC_MAKEFILE=""
EXEC_MAKE_DIR=""
EXEC_MAKE_FILE=""
EXEC_TARGET=""
EXEC_TEST_NAME=""
EXEC_FT_BIN=""
EXEC_STD_BIN=""
EXEC_LOG_DIR=""
EXEC_TS=""
EXEC_FT_LOG=""
EXEC_STD_LOG=""
EXEC_RC_FT=""
EXEC_RC_STD=""

_execute_parse_args() {
  local type="$1"; shift

  local module="${1:-}"; shift || true
  [[ -n "${module}" ]] || { _execute_usage "${type}"; ui_print_die "Missing <module>"; }
  _execute_validate_module "${module}"

  local makefile_opt=""
  local seed_opt=""

  while [[ $# -gt 0 ]]; do
    case "$1" in
      --makefile)
        [[ $# -ge 2 ]] || ui_print_die "Missing value for --makefile"
        makefile_opt="$2"; shift 2
        ;;
      --seed)
        [[ $# -ge 2 ]] || ui_print_die "Missing value for --seed"
        seed_opt="$2"; shift 2
        ;;
      -h|--help)
        _execute_usage "${type}"
        exit 0
        ;;
      *)
        ui_print_die "Unknown option: $1"
        ;;
    esac
  done

  # Default seed only matters for stress.
  if [[ "${type}" == "stress" ]]; then
    if [[ -z "${seed_opt}" ]]; then
      seed_opt="$(execute_make_seed)"
    fi
  else
    seed_opt=""
  fi

  EXEC_MODULE="${module}"
  EXEC_SEED="${seed_opt}"
  EXEC_MAKEFILE="$(execute_resolve_makefile "${EXEC_ROOT}" "${makefile_opt}")"
  execute_split_makefile_path "${EXEC_MAKEFILE}" EXEC_MAKE_DIR EXEC_MAKE_FILE
}

_execute_run_one() {
  local type="$1" seed="$2" bin="$3" log="$4" out_var="$5"

  # Avoid aborting the whole script if the child exits non-zero.
  set +e
  if [[ "${type}" == "stress" ]]; then
    "${bin}" "${seed}" >"${log}" 2>&1
  else
    "${bin}" >"${log}" 2>&1
  fi
  local rc=$?
  set -e

  printf -v "${out_var}" '%s' "${rc}"
}

# Public API
# Usage:
#   execute_run_case <basic|stress|perf> <module> [--makefile PATH] [--seed N]
#
# Side effects:
#   - sets EXEC_* globals
#   - builds binaries
#   - writes logs
#   - captures EXEC_RC_FT / EXEC_RC_STD
execute_run_case() {
  local type="$1"; shift
  _execute_validate_type "${type}"

  EXEC_GROUP="${type}"
  EXEC_ROOT="$(execute_get_root_dir "${SCRIPT_DIR}")"

  _execute_parse_args "${type}" "$@"

  EXEC_TARGET="${type}_${EXEC_MODULE}"
  EXEC_TEST_NAME="${EXEC_TARGET}"

  local bin_dir="${EXEC_ROOT}/bin"
  EXEC_LOG_DIR="${EXEC_ROOT}/logs"
  EXEC_TS="$(execute_make_timestamp)"

  mkdir -p "${EXEC_LOG_DIR}"

  # UI header: show '-' seed for non-stress.
  local seed_disp="${EXEC_SEED:-'-'}"
  ui_print_start_header "${EXEC_GROUP}" "${EXEC_MODULE}" "${EXEC_TARGET}" "${seed_disp}" "${EXEC_MAKEFILE}" "${EXEC_LOG_DIR}" "${EXEC_TS}"

  execute_make_clean "${EXEC_MAKE_DIR}" "${EXEC_MAKE_FILE}"

  execute_make_build_one "${EXEC_MAKE_DIR}" "${EXEC_MAKE_FILE}" "${EXEC_TARGET}" "${EXEC_MODULE}" "ft"
  execute_make_build_one "${EXEC_MAKE_DIR}" "${EXEC_MAKE_FILE}" "${EXEC_TARGET}" "${EXEC_MODULE}" "std"

  EXEC_FT_BIN="${bin_dir}/ft_${EXEC_TEST_NAME}"
  EXEC_STD_BIN="${bin_dir}/std_${EXEC_TEST_NAME}"
  execute_require_executable "${EXEC_FT_BIN}"
  execute_require_executable "${EXEC_STD_BIN}"

  EXEC_FT_LOG="${EXEC_LOG_DIR}/${EXEC_TS}_${EXEC_TEST_NAME}_ft.log"
  EXEC_STD_LOG="${EXEC_LOG_DIR}/${EXEC_TS}_${EXEC_TEST_NAME}_std.log"

  ui_print_run_info "${EXEC_FT_BIN}" "${EXEC_STD_BIN}"

  _execute_run_one "${EXEC_GROUP}" "${EXEC_SEED}" "${EXEC_FT_BIN}"  "${EXEC_FT_LOG}"  EXEC_RC_FT
  _execute_run_one "${EXEC_GROUP}" "${EXEC_SEED}" "${EXEC_STD_BIN}" "${EXEC_STD_LOG}" EXEC_RC_STD
}
