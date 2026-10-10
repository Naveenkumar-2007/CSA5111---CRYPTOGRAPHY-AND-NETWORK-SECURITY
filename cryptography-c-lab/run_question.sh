#!/usr/bin/env bash
set -euo pipefail

if [[ $# -ne 1 || ! "$1" =~ ^[0-9]{1,2}$ ]]; then
  echo "Usage: ./run_question.sh QUESTION_NUMBER"
  echo "Example: ./run_question.sh 1"
  exit 2
fi

number=$(printf '%02d' "$1")
source_file=$(find . -maxdepth 1 -type f -name "q${number}_*.c" -print -quit)
if [[ -z "$source_file" ]]; then
  echo "No source file found for question $1. Available questions: 1-40."
  exit 1
fi

mkdir -p build
executable="build/q${number}"
echo "Compiling $source_file ..."
gcc -std=c11 -Wall -Wextra -Wpedantic "$source_file" -o "$executable" -lm -lcrypto
echo "Running question $1 ..."
exec "$executable"
