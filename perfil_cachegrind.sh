#!/usr/bin/env bash
set -euo pipefail

mkdir -p perfiles
CLASICA="${1:-./perfiles/clasica}"
BLOQUES="${2:-./perfiles/bloques}"

valgrind --tool=cachegrind --cache-sim=yes --branch-sim=yes \
  --cachegrind-out-file=perfiles/cachegrind_clasica.out \
  "$CLASICA" 512 >/dev/null 2>&1

valgrind --tool=cachegrind --cache-sim=yes --branch-sim=yes \
  --cachegrind-out-file=perfiles/cachegrind_bloques.out \
  "$BLOQUES" 512 64 >/dev/null 2>&1

cg_annotate perfiles/cachegrind_clasica.out > perfiles/clasica.txt
cg_annotate perfiles/cachegrind_bloques.out > perfiles/bloques.txt
