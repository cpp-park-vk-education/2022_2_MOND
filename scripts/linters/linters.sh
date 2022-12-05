#!/usr/bin/env bash

set -o pipefail

function print_header() {
  echo -e "\n***** ${1} *****"
}

function check_log() {
  LOG=$({ ${1}; } 2>&1)
  STATUS=$?
  echo "$LOG"
  if echo "$LOG" | grep -q -E "${2}"; then
    exit 1
  fi

  if [ $STATUS -ne 0 ]; then
    exit $STATUS
  fi
}

if [ $# -lt 2 ]; then
  echo "Invalid number of parameters: $#"
  exit 0
fi

if [ "$1" = "--cpplint" ] || [ "$1" = "--all" ]; then
  print_header "RUN cpplint"
  check_log "cpplint.py $2" "Can't open for reading"
fi

if [ "$1" = "--cppcheck" ] || [ "$1" = "--all" ]; then
  print_header "RUN cppcheck"
  check_log "cppcheck $2 --std=c++17 --language=c++ --enable=all --inconclusive --error-exitcode=1 --suppress=missingIncludeSystem" "cppcheck failed"
fi
print_header "SUCCESS"
