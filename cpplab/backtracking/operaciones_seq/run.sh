#!/bin/sh

pushd out > /dev/null

echo "== Running Tests =="
echo "== BACKTRACKING =="
# gtime -f "\nTiempo total: %E (%es)\nMemoria máxima: %M KB" ./operaciones_seq_bt
echo ""

echo "== Running Tests =="
echo "== DYNAMIC PROGRAMMING =="
gtime -f "\nTiempo total: %E (%es)\nMemoria máxima: %M KB" ./operaciones_seq_dp
echo ""

popd > /dev/null
