#!/usr/bin/env bash
set -euo pipefail

# Output comparison (diff) only.
# This file must NOT care about exit codes or runtime failures.

LIB_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# shellcheck source=/dev/null
source "${LIB_DIR}/ui.sh"

# Usage: diff_run <std_log> <ft_log> <diff_log>
diff_run() {
  local std_log="$1" ft_log="$2" diff_log="$3"
  echo -e "${UI_CY}→ Comparing outputs (diff)...${UI_C0}"
  diff -u "${std_log}" "${ft_log}" >"${diff_log}" || true
}
