#!/bin/sh
DIR=$(dirname "$0")
sh "$DIR/../../compile_template.sh" dobra
sh "$DIR/../../compile_template.sh" dobra_with_pruning
sh "$DIR/../../compile_template.sh" cd
