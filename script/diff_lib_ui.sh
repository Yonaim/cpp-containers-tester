#!/usr/bin/env bash
set -euo pipefail

diff_die() { echo "[ERROR] $*" >&2; exit 1; }

# ANSI colors (global)
DIFF_C0="\033[0m"; DIFF_C1="\033[96m"; DIFF_CG="\033[92m"
DIFF_CR="\033[91m"; DIFF_CY="\033[93m"; DIFF_Cx="\033[90m"

diff_ui_header() {
    local group="$1" module="$2" target="$3" seed="$4" makefile="$5" log_dir="$6" ts="$7"
    echo -e "${DIFF_C1}==========================================${DIFF_C0}"
    echo -e "${DIFF_C1} Running DIFF for: ${group} ${module}${DIFF_C0}"
    echo -e "${DIFF_C1}------------------------------------------${DIFF_C0}"
    echo -e "${DIFF_Cx}Target  : ${target}${DIFF_C0}"
    echo -e "${DIFF_Cx}Seed    : ${seed}${DIFF_C0}"
    echo -e "${DIFF_Cx}Makefile: ${makefile}${DIFF_C0}"
    echo -e "${DIFF_Cx}Logs dir: ${log_dir}/${DIFF_C0}"
    echo -e "${DIFF_Cx}Time    : ${ts}${DIFF_C0}"
    echo -e "${DIFF_C1}==========================================${DIFF_C0}"
}

diff_ui_run_info() {
    local ft_bin="$1" std_bin="$2"
    echo -e "${DIFF_CY}→ Running tests...${DIFF_C0}"
    echo -e "${DIFF_Cx}FT : ${ft_bin}${DIFF_C0}"
    echo -e "${DIFF_Cx}STD: ${std_bin}${DIFF_C0}"
}

diff_ui_diff_result() {
    local test_name="$1" diff_log="$2"
    if [[ -s "${diff_log}" ]]; then
        echo -e "${DIFF_CR}[FAIL]${DIFF_C0} Differences found for ${test_name}"
        echo -e "${DIFF_Cx}----- DIFF START -----${DIFF_C0}"
        head -n 30 "${diff_log}"
        echo -e "${DIFF_Cx}----- (truncated) -----${DIFF_C0}"
    else
        echo -e "${DIFF_CG}[PASS]${DIFF_C0} Outputs identical for ${test_name}"
    fi
}

diff_ui_footer() {
    local ft_log="$1" std_log="$2" diff_log="$3"
    echo -e "${DIFF_C1}------------------------------------------${DIFF_C0}"
    echo -e "${DIFF_Cx}FT log : ${ft_log}${DIFF_C0}"
    echo -e "${DIFF_Cx}STD log: ${std_log}${DIFF_C0}"
    echo -e "${DIFF_Cx}DIFF   : ${diff_log}${DIFF_C0}"
    echo -e "${DIFF_C1}==========================================${DIFF_C0}"
}
