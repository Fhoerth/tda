#!/bin/sh
DIR=$(dirname "$0")
sh "$DIR/../../../compile_template.sh" example_1
sh "$DIR/../../../compile_template.sh" example_2
sh "$DIR/../../../compile_template.sh" example_3
sh "$DIR/../../../compile_template.sh" example_4
