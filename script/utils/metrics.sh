#!/usr/bin/env bash
set -euo pipefail

# Structured metrics comparison for stress/perf runs.
# Extracts deterministic fields (ops/seed/size/checksum) and ignores timing for
# pass/fail. Timing metrics are reported separately for visibility.

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

_metrics_extract_timings() {
  local log="$1" out="$2"

  awk '
  {
    name=$1;
    if (name == "") next;
    wall=""; cpu="";
    for (i=2; i<=NF; i++) {
      split($i, kv, "=");
      if (kv[1] == "wall_ms") wall=kv[2];
      else if (kv[1] == "cpu_ms") cpu=kv[2];
    }
    if (wall != "" || cpu != "") {
      printf "%s %s %s\n", name, wall, cpu;
    }
  }' "${log}" | sort >"${out}"
}

append_timing_summary() {
  local std_log="$1" ft_log="$2" metrics_log="$3"

  local tmp_dir tmp_std tmp_ft
  tmp_dir="$(mktemp -d)"
  tmp_std="${tmp_dir}/std.timings"
  tmp_ft="${tmp_dir}/ft.timings"

  _metrics_extract_timings "${std_log}" "${tmp_std}"
  _metrics_extract_timings "${ft_log}" "${tmp_ft}"

  if [[ ! -s "${tmp_std}" && ! -s "${tmp_ft}" ]]; then
    echo "TIMING: No timing metrics found; skipping timing summary." >>"${metrics_log}"
    rm -rf "${tmp_dir}"
    return 0
  fi

  if [[ ! -s "${tmp_std}" || ! -s "${tmp_ft}" ]]; then
    echo "TIMING: Timing metrics missing in one log; skipping timing summary." >>"${metrics_log}"
    rm -rf "${tmp_dir}"
    return 0
  fi

  echo "TIMING: Summary (ft vs std) for wall_ms/cpu_ms (ratio = ft/std)." >>"${metrics_log}"

  awk '
    FNR==NR { ft_wall[$1]=$2; ft_cpu[$1]=$3; next }
    {
      name=$1;
      std_wall=$2;
      std_cpu=$3;
      ftw=ft_wall[name];
      ftc=ft_cpu[name];
      if (ftw == "" && ftc == "") {
        printf "TIMING: %s missing ft timings\n", name;
        next;
      }
      ratio_wall = (std_wall != "" && std_wall > 0) ? ftw / std_wall : 0;
      ratio_cpu = (std_cpu != "" && std_cpu > 0) ? ftc / std_cpu : 0;
      printf "TIMING: %s wall_ms ft=%s std=%s ratio=%.2fx | cpu_ms ft=%s std=%s ratio=%.2fx\n",
        name, ftw, std_wall, ratio_wall, ftc, std_cpu, ratio_cpu;
      if (std_wall != "" && std_wall > 0) {
        total_std_wall += std_wall;
        total_ft_wall += ftw;
      }
      if (std_cpu != "" && std_cpu > 0) {
        total_std_cpu += std_cpu;
        total_ft_cpu += ftc;
      }
    }
    END {
      if (total_std_wall > 0) {
        printf "TIMING: TOTAL wall_ms ft=%s std=%s ratio=%.2fx\n",
          total_ft_wall, total_std_wall, total_ft_wall / total_std_wall;
      }
      if (total_std_cpu > 0) {
        printf "TIMING: TOTAL cpu_ms ft=%s std=%s ratio=%.2fx\n",
          total_ft_cpu, total_std_cpu, total_ft_cpu / total_std_cpu;
      }
    }' "${tmp_ft}" "${tmp_std}" >>"${metrics_log}"

  rm -rf "${tmp_dir}"
  return 0
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
    echo "Structured metrics missing in one log (expected ops/seed/size/checksum per test)." >>"${metrics_log}"
    rm -rf "${tmp_dir}"
    return 1
  fi

  diff -u "${tmp_std}" "${tmp_ft}" >"${metrics_log}" || {
    rm -rf "${tmp_dir}"
    return 1
  }

  echo "Structured metrics match (ops/seed/size/checksum per test)." >>"${metrics_log}"
  rm -rf "${tmp_dir}"
  return 0
}
