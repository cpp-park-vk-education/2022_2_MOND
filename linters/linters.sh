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

if ${1} -eq "--clang" || ${1} -eq "--all"; then
  print_header "RUN clang-tidy"
  check_log "clang-tidy ./Tests/*.cpp -warnings-as-errors=* -extra-arg=-std=c++17 -- -Iproject/include" "Error (?:reading|while processing)"
fi

if ${1} -eq "--cpplint" || ${1} -eq "--all"; then
  print_header "RUN cpplint"
  check_log "cpplint ./Tests/*.cpp" "Can't open for reading"
fi

if ${1} -eq "--cppcheck" || ${1} -eq "--all"; then
  print_header "RUN cppcheck"
  check_log "cppcheck ./Tests/*.cpp --enable=all --inconclusive --error-exitcode=1 --suppress=missingIncludeSystem" "\(information\)"
fi
print_header "SUCCESS"
