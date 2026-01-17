#!/usr/bin/env bash
set -euo pipefail

# Structured metrics comparison for stress/perf runs.
# Extracts deterministic fields (e.g., ops/seed/size/checksum) and ignores timing.

LIB_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# shellcheck source=/dev/null
source "${LIB_DIR}/ui.sh"

_metrics_normalize_log() {
  local log="$1" out="$2"

  awk '
  {
    name=$1;
    if (name == "") next;
    ops=seed=size=checksum="";
    for (i=2; i<=NF; i++) {
      split($i, kv, "=");
      if (kv[1] == "ops") ops=kv[2];
      else if (kv[1] == "seed") seed=kv[2];
      else if (kv[1] == "size") size=kv[2];
      else if (kv[1] == "checksum") checksum=kv[2];
    }
    if (ops != "" || seed != "" || size != "" || checksum != "") {
      printf "%s", name;
      if (ops != "") printf " ops=%s", ops;
      if (seed != "") printf " seed=%s", seed;
      if (size != "") printf " size=%s", size;
      if (checksum != "") printf " checksum=%s", checksum;
      printf "\n";
    }
  }' "${log}" >"${out}"
}

# Usage: compare_structured_metrics <std_log> <ft_log> <metrics_log>
compare_structured_metrics() {
  local std_log="$1" ft_log="$2" metrics_log="$3"

  : >"${metrics_log}"

  local tmp_dir tmp_std tmp_ft
  tmp_dir="$(mktemp -d)"
  tmp_std="${tmp_dir}/std.metrics"
  tmp_ft="${tmp_dir}/ft.metrics"

  _metrics_normalize_log "${std_log}" "${tmp_std}"
  _metrics_normalize_log "${ft_log}" "${tmp_ft}"

  if [[ ! -s "${tmp_std}" && ! -s "${tmp_ft}" ]]; then
    echo "No structured metrics found; skipping metrics comparison." >>"${metrics_log}"
    rm -rf "${tmp_dir}"
    return 0
  fi

  if [[ ! -s "${tmp_std}" || ! -s "${tmp_ft}" ]]; then
    echo "Structured metrics missing in one log." >>"${metrics_log}"
    rm -rf "${tmp_dir}"
    return 1
  fi

  diff -u "${tmp_std}" "${tmp_ft}" >"${metrics_log}" || {
    rm -rf "${tmp_dir}"
    return 1
  }

  rm -rf "${tmp_dir}"
  return 0
}
