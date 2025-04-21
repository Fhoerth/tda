#!/bin/sh

pushd out > /dev/null

echo "== Running Tests =="
echo "== Example 1 =="
gtime -f "\nTiempo total: %E (%es)\nMemoria máxima: %M KB" ./example_1
echo ""

echo "== Running Tests =="
echo "== Example 2 =="
gtime -f "\nTiempo total: %E (%es)\nMemoria máxima: %M KB" ./example_2
echo ""

echo "== Running Tests =="
echo "== Example 3 =="
gtime -f "\nTiempo total: %E (%es)\nMemoria máxima: %M KB" ./example_3
echo ""

echo "== Running Tests =="
echo "== Example 3 =="
gtime -f "\nTiempo total: %E (%es)\nMemoria máxima: %M KB" ./example_4
echo ""

popd > /dev/null
