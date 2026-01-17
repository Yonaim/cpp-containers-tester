#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# shellcheck source=/dev/null
source "${SCRIPT_DIR}/utils/execute.sh"
# shellcheck source=/dev/null
source "${SCRIPT_DIR}/utils/exit_code.sh"
# shellcheck source=/dev/null
source "${SCRIPT_DIR}/utils/metrics.sh"

main() {
  execute_run_case "stress" "$@"

  local metrics_log exit_log
  metrics_log="${EXEC_LOG_DIR}/${EXEC_TS}_${EXEC_TEST_NAME}_metrics.log"
  exit_log="${EXEC_LOG_DIR}/${EXEC_TS}_${EXEC_TEST_NAME}_exit.log"

  local metrics_fail=0
  if ! compare_structured_metrics "${EXEC_STD_LOG}" "${EXEC_FT_LOG}" "${metrics_log}"; then
    metrics_fail=1
  fi

  local exit_fail=0
  if ! check_exit_code "${EXEC_RC_FT}" "${EXEC_RC_STD}" "${exit_log}"; then
    exit_fail=1
  fi

  ui_print_result_header
  ui_print_exit_code_result "${EXEC_RC_FT}" "${EXEC_RC_STD}"
  ui_print_metrics_result "${EXEC_TEST_NAME}" "${EXEC_FT_LOG}" "${EXEC_STD_LOG}" "${metrics_log}" "${metrics_fail}"

  if [[ ${metrics_fail} -ne 0 || ${exit_fail} -ne 0 ]]; then
    return 1
  fi
  return 0
}

main "$@"
