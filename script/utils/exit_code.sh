#!/usr/bin/env bash
set -euo pipefail

# Exit-code evaluation only.
# This file must NOT perform diffing.

LIB_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# shellcheck source=/dev/null
source "${LIB_DIR}/ui.sh"

# Writes a short report to exit_log and returns 0/1.
# Usage: check_exit_code <rc_ft> <rc_std> <exit_log>
check_exit_code() {
  local rc_ft="$1" rc_std="$2" exit_log="$3"

  : >"${exit_log}"
  {
    echo "ft_exit_code=${rc_ft}"
    echo "std_exit_code=${rc_std}"
  } >>"${exit_log}"

  [[ "$rc_ft" == "0" && "$rc_std" == "0" ]]
}
