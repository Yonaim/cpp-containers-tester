#!/usr/bin/env bash
set -euo pipefail

# Small UI helpers (colors, error printing). Kept generic (not "diff"-specific).

ui_print_die() { echo "[ERROR] $*" >&2; exit 1; }

# ANSI colors (global)
# C0 = reset
# C1 = primary highlight (information / header)
# CG = success
# CR = error
# CY = warning
# Cx = dim / secondary
UI_C0="\033[0m"; UI_C1="\033[96m"; UI_CG="\033[92m"
UI_CR="\033[91m"; UI_CY="\033[93m"; UI_Cx="\033[90m"

ui_print_start_header() {
    local type="$1" module="$2" target="$3" seed="$4" makefile="$5" log_dir="$6" ts="$7"
    echo -e "${UI_C1}==========================================${UI_C0}"
    echo -e "${UI_C1} Running TESTS for: ${type} ${module}${UI_C0}"
    echo -e "${UI_C1}------------------------------------------${UI_C0}"
    echo -e "${UI_Cx}Target  : ${target}${UI_C0}"
    echo -e "${UI_Cx}Seed    : ${seed}${UI_C0}"
    echo -e "${UI_Cx}Makefile: ${makefile}${UI_C0}"
    echo -e "${UI_Cx}Logs dir: ${log_dir}/${UI_C0}"
    echo -e "${UI_Cx}Time    : ${ts}${UI_C0}"
    echo -e "${UI_C1}==========================================${UI_C0}"
}

ui_print_result_header() {
    echo -e "${UI_C1}==========================================${UI_C0}"
    echo -e "${UI_C1} Test Results${UI_C0}"
    echo -e "${UI_C1}==========================================${UI_C0}"
}

ui_print_run_info() {
    local ft_bin="$1" std_bin="$2"
    echo -e "${UI_CY}→ Running tests...${UI_C0}"
    echo -e "${UI_Cx}FT bin: $(basename "${ft_bin}")${UI_C0}"
    echo -e "${UI_Cx}STD bin: $(basename "${std_bin}")${UI_C0}"
}

ui_print_diff_result() {
    local test_name="$1"
    local ft_log="$2"
    local std_log="$3"
    local diff_log="$4"
    echo -e "${UI_C0}------------------------------------------${UI_C0}"
    if [[ -s "${diff_log}" ]]; then
        echo -e "${UI_CR}[DIFF FAIL]${UI_C0} Differences found for ${test_name}"
        echo -e "${UI_Cx}FT log : ${ft_log}${UI_C0}"
        echo -e "${UI_Cx}STD log: ${std_log}${UI_C0}"
        echo -e "${UI_Cx}DIFF   : ${diff_log}${UI_C0}"
        # echo -e "${UI_Cx}----- DIFF START -----${UI_C0}"
        # head -n 10 "${diff_log}"
        # echo -e "${UI_Cx}----- (truncated) -----${UI_C0}"
    else
        echo -e "${UI_CG}[DIFF PASS]${UI_C0} Outputs identical for ${test_name}"
    fi
    echo -e "${UI_C0}------------------------------------------${UI_C0}"
}

ui_print_footer() {
    local ft_log="$1" std_log="$2" diff_log="$3"
    echo -e "${UI_C1}==========================================${UI_C0}"
    echo -e "${UI_Cx}FT log : ${ft_log}${UI_C0}"
    echo -e "${UI_Cx}STD log: ${std_log}${UI_C0}"
    echo -e "${UI_Cx}DIFF   : ${diff_log}${UI_C0}"
    echo -e "${UI_C1}==========================================${UI_C0}"
}

ui_print_exit_code_result() {
  local rc_ft="$1" rc_std="$2"

  local ft_tag std_tag

  if [[ "$rc_ft" == "0" ]]; then
    ft_tag="OK"
  else
    ft_tag="FAIL"
  fi

  if [[ "$rc_std" == "0" ]]; then
    std_tag="OK"
  else
    std_tag="FAIL"
  fi

  if [[ "$rc_ft" != "0" || "$rc_std" != "0" ]]; then
    echo -e "${UI_CR}[EXIT CODE FAIL]${UI_C0}"
  else
    echo -e "${UI_CG}[EXIT CODE PASS]${UI_C0}"
  fi

  echo "  ft  : ${rc_ft} (${ft_tag})"
  echo "  std : ${rc_std} (${std_tag})"
}
